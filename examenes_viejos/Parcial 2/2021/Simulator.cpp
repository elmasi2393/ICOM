#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>

using namespace std;

// Define una variable de un modelo, por simplicidad se soporta un solo tipo de variable.
class Variable {
	public:
		Variable(const string& vname, double initValue = 0): varName(vname), varValue(initValue) {};

		double getValue() const{ return varValue; }

		void setValue(double v){
			varValue = v;
		}
		string getName() const{ return varName;}

	private:
		string varName;	
		double varValue;
};

// Define un administrador de variables. Todas las variables on pontencial intercambio 
// entre modelos debe ser registrada en este Manager
class VarManager {
	public:
		void registerVar(Variable* v){
			vars[v->getName()] = v;
		}
		Variable* getVariable(const string& varName) const{
			return vars.at(varName);
		}

		const list<const Variable*> getAllVariables(){
			list<const Variable*> variables;
			
			for(auto it = vars.begin(); it != vars.end(); it++){
				variables.push_back(it->second);
			}

			return variables;
		}

	private:
		map<string, Variable *> vars;
};

// Define la interface que debe satisfacer todo modelo en la simulaci�n
class Model {
	public:
		Model(const string& modelName): name(modelName) {}
		virtual ~Model() {};
		
		// m�todo que d� oprtunidad al modelo a que registre todas las variables propiad
		virtual void create(VarManager&) = 0;

		// m�todo que d� la oportunidad de "attacharse" a variables de otros modelos, a trav�s del nombre
		virtual void connect(const VarManager&) = 0;

		// m�todo que d� la oportunidad de destruir/liberar todos los recursos con que cuenta el modelo
		virtual void destroy() = 0;

		// m�todo que solicita al modelo que avance un paso en la simulaci�n, actualizando sus variables propias
		virtual void doStep(uint64_t currT) = 0;

	protected:
		string name;		// nombtre del modelo
};

// modelo ejemplo que deber�a modelar un grifo    // TODO
class Grifo : public Model
{
	public:
		Grifo(const string& modelName):  Model(modelName), apertura("apertura") {}
		~Grifo() {};

		void create(VarManager& vm){
			vm.registerVar(&apertura);
		}
		void destroy() {};

		void connect(const VarManager& vm){
			nivel = vm.getVariable("nivel"); //Conecto con la altura del tanque para saber el caudal de salida
		}
		void doStep(uint64_t currT){
			if(nivel->getValue() < 50){
				apertura.setValue(10);
			}else{
				apertura.setValue(0);
			}
		}

	private:
		Variable apertura;	//El grifo tiene una apertura y un caudal de salida
		Variable * nivel;
};
// modelo ejemplo que deber�a modelar un tanque    // TODO
class Tanque : public Model
{
	public:
		Tanque(const string& name): Model(name), nivel("nivel") {}
		~Tanque() {};
	
		void create(VarManager& vm){
			vm.registerVar(&nivel);
		}
	
		void destroy() {};

		void connect(const VarManager& vm){
			apertura = vm.getVariable("apertura");	//Depende de la apertura de la canilla
		}
		void doStep(uint64_t currT){
			if(apertura->getValue() > 5){
				nivel.setValue((currT%5) * (apertura->getValue()) );	//Proporcional al tiempo y la apertura
			}
			else{
				nivel.setValue(nivel.getValue() -1 );	//Decrebe con el tiempo
			}
		}

	private:
		Variable nivel;
		Variable * apertura;
};

// modelo ejemplo que deber�a modelar una bomba de riego   // TODO
class BombaRiego : public Model                     
{
	public:
		BombaRiego(const string& name): Model(name), presion("presion") {}
		~BombaRiego() {};

		void create(VarManager& vm){
			vm.registerVar(&presion);
		}
		void destroy() {};

		void connect(const VarManager& vm){
			nivel = vm.getVariable("nivel");	//Depende de la apertura de la canilla
		}
		void doStep(uint64_t currT){
			if(nivel->getValue() < 5){
				presion.setValue(presion.getValue() - 1); //Si el nivel decrece de un limite, la presion decae
			}
			else{
				presion.setValue(10);	//Sino, lo pongo en la maxima
			}
		}

	private:
		Variable presion;
		Variable * nivel;
};

// modelo ejemplo que deber�a modelar un aspersor  // TODO
class AspersorRiego : public Model
{
	public:
		AspersorRiego(const string& name): Model(name), alcance("alcance") {}
		~AspersorRiego() {};
	
		void create(VarManager& vm){
			vm.registerVar(&alcance);
		}
		void destroy() {};

		void connect(const VarManager& vm){
			presion = vm.getVariable("presion");	//Depende de la apertura de la canilla
		}
		void doStep(uint64_t currT){
			if(presion->getValue() > 9.9){
				alcance.setValue(5);	//Si el valor de presion es el adecuando, el alcance el fijo
			}
			else{
				alcance.setValue(alcance.getValue() -1 );	//Decrebe con el tiempo
			}
		}
	
	private:
		Variable alcance;
		Variable * presion;

};

// modelo ejemplo que satisface la interface Model, perop que solo monitorea el estado de todas las variables.
// // TODO
class FakeModelMonitor : public Model
{
	public:
		FakeModelMonitor(const string& name): Model(name) {};
		~FakeModelMonitor() {};

		void create(VarManager& vm){ 
			this->vm = &vm;
		}
		void connect(const VarManager& vm){};
		void destroy() {};
		void doStep(uint64_t currT){
			list<const Variable*> variables = vm->getAllVariables();

			for(auto it = variables.begin(); it != variables.end(); it++){
				cout << (*it)->getName() << " : " << (*it)->getValue() << endl;
			}
		}
	private:
		VarManager * vm;

};

// Modela un contexto de simulaci�n, donde los modelos se registran y hay un scheduler que
// controla la evoluci�n sincr�nica de mos modelos.
class Simulator
{
	public:
		Simulator(): sched(models) {} //Cargo el schedule

		void registerModel(Model* m){
			models.push_back(m);

		}
		void prepare(){
			currTime = 0;

			for(auto& it : models){		//Primero pongo todas en el varMgr
				it->create(varMgr);
			}
			for (auto& it : models){	//Luego vinculamos las variables
				it->connect(varMgr);
			}
		}

		void simulate(uint64_t duration){
			for(uint64_t i = 0; i < duration; i++){
				sched.doStep(i); 	//Agu paso a paso de la simulacion
			}
		}

	private:

		// controla la evoluci�n de todos los modelos en forma sincr�nica
		class Scheduler {
			public:
				Scheduler(const vector<Model*>& models_): models(models_) {}

				void doStep(uint64_t t){
					for(auto & it : models){	//Ejecuto un paso en cada modelo
						it->doStep(t);
					}
				}
			private:
				const vector<Model*> & models;

		};
		vector<Model*> models;
		uint64_t       currTime = 0;

		VarManager     varMgr;
		Scheduler      sched;

};


int main()
{
	Simulator simulator;
	simulator.registerModel(new Grifo("grifo"));
	simulator.registerModel(new Tanque("Tanque"));
	simulator.registerModel(new BombaRiego("Bomba"));
	simulator.registerModel(new AspersorRiego("Aspersor1"));
	simulator.registerModel(new AspersorRiego("Aspersor2"));
	simulator.registerModel(new AspersorRiego("Aspersor3"));
	simulator.registerModel(new AspersorRiego("Aspersor4"));
	simulator.registerModel(new FakeModelMonitor("Monitor"));

	simulator.prepare();

	simulator.simulate(10000);

	return 0;

}

