#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

class NNode {
    public:
        // inicializa un nuevo nodo con 'v' como valor del nodo
        NNode(int v){
            value = v;
            for(int i = 0; i<MAX_CHILD; i++)
                children[i] = nullptr; 
        };    // ToDo

        // destruye el nodo
        ~NNode(){
            for(int i = 0; i<MAX_CHILD; i++)
                delete children[i]; 
        };        // ToDo

        // agrega un nuevo nodo con valor 'v' cumpliendo los requerimientos dados
        void addNode(int v){
            for(int i = 0; i<MAX_CHILD; i++){
                if(children[i] == nullptr){
                    children[i] = new NNode(v);
                    return;
                }
            }
            int peso = children[0]->peso(); int aux = 0;
            for(int i = 1; i<MAX_CHILD; i++){
                if(peso > children[i]->peso()){
                    peso = children[i]->peso();
                    aux = i;
                }
            }
            children[aux]->addNode(v);
        };  // ToDo

        // cuenta y retorna la cantidad de nodos, incluyendose a si mismo
        int peso(){
            int peso = 1;
            for(int i = 0; i<MAX_CHILD; i++){
                if(children[i] == nullptr)
                    continue;
                peso += children[i]->peso();
            }
            return peso;
        };       // ToDo
    
        // retorna true/false indicando si 'v' esta contenido como 'value' en algun nodo
        
        bool esMiembro(int v){
            if(v == value)
                return 1;
            for(int i = 0; i<MAX_CHILD; i++){
                if(children[i] == nullptr)
                    continue;
                if(children[i]->esMiembro(v))
                    return 1;
            }
            return 0;
        };       // ToDo

        // retorna true si es un nodo terminal (sin hijos), falso en caso contrario
        bool esHoja(){
            for(int i = 0; i<MAX_CHILD; i++){
                if(children[i] == nullptr)
                    continue;
                return 0;
            }
            return 1;
        };   // ToDo

        // retorna la altura (cantidad de niveles) que tiene el arbol.
        int altura(){
            if(esHoja())
                return 1;
            int max = 0; int aux = 0;
            for(int i = 0; i<MAX_CHILD; i++){
                if(children[i] == nullptr)
                    continue;
                aux = children[i]->altura();
                if(aux > max)
                    max = aux;
            }
            return max+1 ;
        };     // ToDo
    
    private:
        int value;
        static const int MAX_CHILD = 4;
        NNode *children[MAX_CHILD];
};


int main()
{
    srand((unsigned int) time(NULL));
    NNode* arbol = new NNode(rand() % 1000);
    int hprev = 1;
    int pprev = 1;

    for (int i = 2; i <= 2500; i++) {
        arbol->addNode(rand() % 1000);
        int h = arbol->altura();
        if (h != hprev) {
            assert(i == arbol->peso());
            cout << "n: " << i - 1 << ", w: " << i - 1 << ", h: " << hprev << endl;
            cout << "n: " << i << ", w: " << arbol->peso() << ", h: " << h << ", n_lev: " << i - pprev << "\n...\n";
            hprev = h;
            pprev = i;
        }
    }

    cout << "Peso:        " << arbol->peso() << endl;
    cout << "Altura:      " << arbol->altura() << endl;
    cout << "esta el 10?: " << arbol->esMiembro(10) << endl;
    cout << "esta el 20?: " << arbol->esMiembro(20) << endl;
    cout << "esta el 30?: " << arbol->esMiembro(30) << endl;
    cout << "esta el 40?: " << arbol->esMiembro(40) << endl;
    cout << "esta el 50?: " << arbol->esMiembro(50) << endl;

    delete arbol;
    cin.get();
    return 0;
}