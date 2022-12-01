#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

class NNode {
    public:
        // inicializa un nuevo nodo con 'v' como valor del nodo
        NNode(int v);    // ToDo

        // destruye el nodo
        ~NNode();        // ToDo

        // agrega un nuevo nodo con valor 'v' cumpliendo los requerimientos dados
        void addNode(int v);  // ToDo

        // cuenta y retorna la cantidad de nodos, incluyendose a si mismo
        int peso();       // ToDo
    
        // retorna true/false indicando si 'v' esta contenido como 'value' en algun nodo
        bool esMiembro(int v);       // ToDo

        // retorna true si es un nodo terminal (sin hijos), falso en caso contrario
        bool esHoja();   // ToDo

        // retorna la altura (cantidad de niveles) que tiene el arbol.
        int altura();     // ToDo
    
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

    return 0;
}