#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

using Tick = unsigned int;
using WorkUnitId = unsigned int;

// describe una accion: 
struct ActionDescriptor {
    string accion;          // descripci�n de la accion
    Tick   neededTime;      // tiempo necesario para llevarla a cabo (en Ticks)
};

// describe una unidad de trabajo
class WorkUnit {
    public:
        WorkUnit(WorkUnitId id_, Tick creationTime) : id(id_) {
            addAction("Creacion", creationTime);
        }
        
        // agrega una nueva accion al workunit
        void addAction(const string& action_, Tick t){
            actionHistory.push_back({action_,t});
        }; // TODO ok

        // imprime el id del workunit y todas las acciones aplicadas
        // para cada accion debe imprimir el tiempo de aplicacion y la descripcion de la accion
        void listActions(){
            int n = actionHistory.size();
            cout<< "Id: "<< id<<endl;
            for(int i = 0; i<n; i++)
                cout<<"Tiempo: "<<actionHistory[i].time <<"\tAccion: " <<actionHistory[i].action<<endl;  
        };   // TODO ok

    private:
        WorkUnitId id;              // identificacion de la accion
        // describe una accion aplicada al WorkUnit
        struct AppliedAction {      
            string action;          // descripci�n de la accion realizada
            Tick time;              // tiempo en que se le aplico la accion
        };
        // conjunto de acciones que se le aplicaron al WorkUnit
        vector<AppliedAction> actionHistory;    
};

// Describe una cola de punteros a WorkUnit
class XferQueue {
    public:
        // coloca un nuevo elemento en la cola
        void put(WorkUnit* pwu) {
            queue.push_back(pwu);
        }

        // retorna el elemento m�s viejo en la cola (la cola NO debe estar vac�a)
        WorkUnit *get() {
            assert(!isEmpty());
            WorkUnit* ret = queue.front();
            queue.pop_front();
            return ret;
        }

        // chequea si la cola esta o no vacia
        bool isEmpty() {
            return queue.size() == 0;
        }                

    private:
        deque<WorkUnit*> queue;
};

// describe un stage
class Stage {
    public:
        Stage() : state(IDLE) {}
        virtual void doTick(Tick t) = 0;    // todo Stage instanciable tiene que implementar este servicio

    protected:
        enum State { IDLE, WORKING};
        State state;
};

// Describe un stage de produccion de WorkUnits
// Tienen la responsabilidad de que a cada tbwu (time-between-workunit)
// generar un nuevo workunit y colocarlo en su cola de salida (qout)
// los identificadores de los Workunit creados tienen que ser
// 0, 1, 2, 3, ...
class Producer: public Stage {
    public:
        Producer(XferQueue* qout_, Tick tbwu_): qout(qout_), tbwu(tbwu_), num_work_unit(0),last_produced(0) {};   
        // TODO ok

        // a cada tbwu ticks debe generar un nuevo WorkUnit y ponerlo en la cola de salida
        void doTick(Tick t){
            if((t - last_produced) > tbwu){
                state = WORKING;
                qout->put(new WorkUnit(num_work_unit, t));
                num_work_unit++;
                last_produced = t;
            }   
            else{
                state = IDLE;
            }
        };   // TODO ok

    private:
        XferQueue* qout;
        const Tick tbwu;
        int num_work_unit;          // id del siguiente work unit a generar
        Tick last_produced;         // tiempo al que se produjo el anterior work unit. Tengo que esperar tbwu para poder producir otro 
        // TODO ok
};

// describe un stage consumidor de workunits
// lo unico que debe hacer con los Workunits que saca de qin es listarle las acciones de transformaci�n
// que recibio y destruir la accion
class Consumer : public Stage {
    public:
        Consumer(XferQueue* qin_): qin(qin_){};   // TODO ok


        // si hay algo en la cola de entreda debe consumirlo, listar las acciones de transformacion
        // que le fueron aplicadas y destruir la WorkUnit
        void doTick(Tick t){
            if(qin->isEmpty()){
                state = IDLE;
                return;   
            }
            state = WORKING;
            WorkUnit* ptr = qin->get();
            ptr->listActions();
            delete ptr;
        };   // TODO ok
 
    private:
        XferQueue* qin;
};

// describe los stages de transformacion
// se construye con un puntero a la cola de entrada, uno a la cola de salida y un
// conjunto de acciones que describen las transformaciones que realiza el stage.
// El estado de creaci�n del stage es IDLE (no se esta procesando ninguna WorUnit)
// cuando se consigue un WorkUnit para a estado WORKING y cuando termina de aplicarle
// todas las acciones pasa nuevamente a estado IDLE.
class WorkingStage : public Stage {
    public:
        WorkingStage(XferQueue* qin_, XferQueue* qout_, const vector<ActionDescriptor>& actions_): qin(qin_), qout(qout_), actions(actions_), current(nullptr), index(0), last_time(0)
        {
            state = IDLE;
        };   // TODO ok

        // en estado IDLE chequea si hay algo en qin, si lo hay lo saca y cambia a WORKING y inicializa lo que necesite
        // para tener informacion de las acciones que se van a ir aplicando.
        //  en estado WORKING va aplicando las acciones de acuerdo a los tiempos necesarios 
        // para cada accion, las acciones que va aplicando deben ser agregadas a la WorkUnit WorkUnit::addAction
        void doTick(Tick t){
            if(state == IDLE){
                if(qin->isEmpty())
                    return;
                state = WORKING;
                current = qin->get();
                last_time = t;
                return;
            }

            if( index == actions.size()){
                qout -> put(current);
                index = 0;
                current = nullptr;
                state = IDLE;
                return;
                last_time = t;
            }

            if(t > last_time + (actions[index]).neededTime ){
                current ->addAction(actions[index].accion, t);
                index++;
                last_time = t;
            }
        };  // TODO

    private:
        XferQueue *qin;
        XferQueue *qout;
        const vector<ActionDescriptor> actions;
        WorkUnit* current;              // Work Unit sobre la cual laburamos
        int index;             // Indice de la accion a ejecutar
        Tick last_time;                 // Tiempo al cual se ejecuto la ultima accion
        // TODO ok
};

// planificador de ejecuci�n
class Scheduler {
    public:
        void registerStage(Stage* stg) {
            stages.push_back(stg);
        }

        void simulate(Tick ticks) {
            for (Tick t = 0; t < ticks; t++) {
                for (auto s : stages)
                    s->doTick(t);
            }
        }

    private:
        vector<Stage*> stages;
};

// test del sistema
int main() {
    // colas
    XferQueue q0, q1, q2, q3, q4, q5;
    
    // producer
    const Tick timeBetweenWU = 300;
    Producer producer(&q0, timeBetweenWU);
    
    // consumer
    Consumer consumer(&q5);

    // acciones de transformaci�n de los distintos WorkinStages
    vector<ActionDescriptor> s1Actions = {
        {"Presentacion de chasis en marco", 80},
        {"Fijacion soporte motor", 40},
        {"Colocacion Capot", 100},
        {"Colocacion Tapa de caja", 100},
    };

    vector<ActionDescriptor> s2Actions = {
        {"Colocacion puerta izquierda", 50},
        {"Colocacion puerta derecha", 50},
        {"Calibraci�n de componentes moviles", 140},
    };
    vector<ActionDescriptor> s3Actions = {
        {"Aplicacion de pintura base", 50},
        {"Aplicacion de pintura bicapa", 50},
        {"Aplicacion de barniz", 50},
        {"Pulido", 40},
    };
    vector<ActionDescriptor> s4Actions = {
        {"Colocacion de tren de transmision", 60},
        {"Colocacion de Motor", 200},
        {"Colocacion Rueda 1", 20},
        {"Colocacion Rueda 2", 20},
        {"Colocacion Rueda 3", 20},
        {"Colocacion Rueda 4", 20},
    };

    vector<ActionDescriptor> s5Actions = {
        {"Colocacion torpedo de instrumentos", 200},
        {"Colocacion volante", 40},
        {"Colocaci�n butacas delanteras", 50},
        {"Colocaci�n butacas traseras", 50},
    };

    // working stages
    WorkingStage ws[5] = {
        WorkingStage(&q0, &q1, s1Actions),
        WorkingStage(&q1, &q2, s2Actions),
        WorkingStage(&q2, &q3, s3Actions),
        WorkingStage(&q3, &q4, s4Actions),
        WorkingStage(&q4, &q5, s5Actions)
    };
    
    Scheduler sched;
    
    // registracion de stages en el planificador
    sched.registerStage(&producer);
    
    for (auto& s : ws)
        sched.registerStage(&s);
    
    sched.registerStage(&consumer);

    // simulacion
    sched.simulate(10000);
    system("pause");
    return 0;
}
