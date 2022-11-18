#include <iostream>
#include <deque>
#include <cassert>

using namespace std;

template <class T> class Queue{
public:
    void put(T e){// coloca un nuevo elemento en la cola
        elts.push_back(e);
    }
    T get(){      // retira el elemento más antiguo de la cola unsigned int size(); // retorna la cantida de elementos contenidos
        assert(elts.size() != 0);

        T out = elts.front();
        elts.pop_front();
        return out;
    }
private:
    deque<T> elts; // a definir
};

int main(){
    Queue<int> pila;

    for(int i=0; i<10; i++){
        pila.put(i);
    }

    for(int i=0; i<10; i++){
        cout << pila.get();
    }
    cout << endl;


    return 0;
}
