#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>

using namespace std;

// Define una variable de un modelo, por simplicidad se soporta un solo tipo de variable.
class Variable {
	public:
		Variable(const string& vname, double initValue = 0);

		double getValue() const;		// TODO

		void setValue(double v);		// TODO

	private:
		string varName;	
		double varValue;
};

// Define un administrador de variables. Todas las variables on pontencial intercambio 
// entre modelos debe ser registrada en este Manager
class VarManager {
	public:
		void      registerVar(Variable* v);					// TODO
		Variable* getVariable(const string& varName);		// TODO

		const list<const Variable*> getAllVariables();		// TODO

	private:
		map<string, Variable *> vars;
};

// Define la interface que debe satisfacer todo modelo en la simulación
class Model {
	public:
		Model(const string& modelName);
		virtual ~Model();
		
		// método que dá oprtunidad al modelo a que registre todas las variables propiad
		virtual void create(VarManager&) = 0;

		// método que dá la oportunidad de "attacharse" a variables de otros modelos, a través del nombre
		virtual void connect(const VarManager&) = 0;

		// método que dá la oportunidad de destruir/liberar todos los recursos con que cuenta el modelo
		virtual void destroy() = 0;

		// método que solicita al modelo que avance un paso en la simulación, actualizando sus variables propias
		virtual void doStep(uint64_t currT) = 0;

	protected:
		string name;		// nombtre del modelo
};

// modelo ejemplo que debería modelar un grifo    // TODO
class Grifo : public Model
{
	public:
		Grifo(const string& name);
};

// modelo ejemplo que debería modelar un tanque    // TODO
class Tanque : public Model
{
	public:
		Tanque(const string& name);

};

// modelo ejemplo que debería modelar una bomba de riego   // TODO
class BombaRiego : public Model                     
{
	public:
		BombaRiego(const string& name);

};

// modelo ejemplo que debería modelar un aspersor  // TODO
class AspersorRiego : public Model
{
	public:
		AspersorRiego(const string& name);

};

// modelo ejemplo que satisface la interface Model, perop que solo monitorea el estado de todas las variables.
// // TODO
class FakeModelMonitor : public Model
{
	public:
		FakeModelMonitor(const string& name);

};

// Modela un contexto de simulación, donde los modelos se registran y hay un scheduler que
// controla la evolución sincrónica de mos modelos.
class Simulator
{
	public:
		Simulator();						// TODO
		void registerModel(Model* m);		// TODO
		void prepare();						// TODO

		void simulate(uint64_t duration);	// TODO

	private:

		// controla la evolución de todos los modelos en forma sincrónica
		class Scheduler {
			public:
				Scheduler(const vector<Model*>& models_);   // TODO

				void doStep(uint64_t t);					// TODO

			private:
				const vector<Model*>& models;

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

