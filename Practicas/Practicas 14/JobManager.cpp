#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <deque>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

// define la abstracci�n de un Job. 
// Cada Job tendr� un nombre y un m�todo "run" que realiza el trabajo espec�fico.
class Job {
    public:
        Job(const string &tname) : name(tname) {}
        virtual ~Job() {}

        virtual void run() = 0;

        string getName() { return name; }

    protected:
        string name;
};

// implementa un administrador de Jobs. 
// internamente mantiene los jobs registrados en una cola de punteros a Jobs.
class JobManager{
    public:
        // agrega un job a la cola de jobs pendientes
        void addJob(Job *job) {
            jobs.push_back(job);
        }
        // remueve y retorna el job mas antiguo. Retorna nullptr si no hay mas jobs pendientes. 
        Job *getJob() {
            if(jobs.size() != 0){
                Job * out = jobs.front();
                jobs.pop_front();
                // cout << "Job asigned: ";
                // cout << out->getName() << endl;
                return out;
            }
            return nullptr;
        }
    private:
        deque<Job *> jobs;
};

// entidad que ejecuta jobs tomados desde un JobManager pasado en la construcci�n del objeto
class Worker {
    public:
        Worker(JobManager *jmp): jm(jmp) {};

        // esta funci�n deber� tomar Jobs desde el JobManager e ir ejecutandolos
        // hasta que no existan mas Jobs que procesar.
        void start() {

            while(true){
                Job *ptr = jm->getJob();
                if(ptr == nullptr)
                    break;
                ptr->run();
            }
        }

    private:
        JobManager * jm;
};

///////////////////////////////////


// Job que aproxima e imprime el valor de Pi siguiendo la serie num�rica propuesta por Leibniz (ejercicio 3, pr�ctica 4)
// la cota de error deseado se pasa como argumento al constructor de la clase.
class PiJob : public Job {
    public:
        PiJob(double error) : Job("Calcula Pi por Leibniz"), cotaError(error) {}

        void run() {
            //Calcular pi por serie aproximada de Leibniz
            cout << this->getName() << endl;
            double pi = 1;
            int a = -1;
            int i = 3;

            while(abs(M_PI/4 - pi) > cotaError){
                pi = pi + (double(a)/i);
                a *= (-1);
                i += 2;
            }
            cout << "Pi: " << 4*pi << endl; 

        }
    private:
        double cotaError;
};


// Job que aproxima e imprime el valor de la raiz cuadrada de un n�mero siguiendo el algoritmo del ejercicio 4 de la pr�ctica 4
// El valor y la cota de error deseado se pasa como argumento al constructor de la clase.
class SqrtJob : public Job {
    public:
        SqrtJob(double valor_, double error) : Job("Calculo aproximado de sqrt"), valor(valor_), cotaError(error) {}

        void run() {
                int n_it = 30;
                double sqrt_p = 1;
                double real_value = sqrt(valor);

                while(abs(real_value-sqrt_p) > cotaError){
                    sqrt_p = (sqrt_p + valor/sqrt_p)/2;
                }
                cout << "Raiz de "<< valor << " : " << sqrt_p << endl;
                // for(int i=0; i<n_it; i++){
                //     sqrt = (sqrt + valor/sqrt)/2;
                //     cout << "sqrt = " << sqrt << endl;
                // }
        }
    private:
        double valor;
        double cotaError;

};

// Job que se ejecuta durante una cantidad dada de tiempo (segundos) e imprime el valor del tiempo cada segundo
// La cantidad de segundos que durar� la ejecuci�n se pasa como argumento al constructor de la clase.
// ver aclaraci�n (2) en el pr�ctico.
class TimerJob : public Job {
    public:
        TimerJob(unsigned int t) : Job("Timer"), timeToRun(t) {}

        void run() {
            cout << this->getName() << endl;
            this_thread::sleep_for(chrono::milliseconds{timeToRun});
            cout << "Se esperaron: " << timeToRun << "ms" << endl;
        }
    private:
        unsigned int timeToRun;
};


int main()
{
    JobManager jm;
    Worker w(&jm);

    PiJob pi1(0.1), pi2(0.00001);
    SqrtJob sq1(100, 0.0001), sq2(1524, 0.000001), sq3(49, 0.00001);
    TimerJob t1(5), t2(7);

    jm.addJob(&pi1);
    jm.addJob(&t1);
    jm.addJob(&pi2);
    jm.addJob(&sq1);
    jm.addJob(&sq2);
    jm.addJob(&sq3);
    jm.addJob(&t2);

    w.start();


}
