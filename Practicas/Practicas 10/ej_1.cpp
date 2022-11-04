#include <iostream>
#include <cstdlib>
#include <string>
#include <array>

using namespace std;

struct Terna {
        int i;
        int j;
        int value; 
        Terna(int i, int j, int value) : i(i), j(j), value(value) {};
        //Operador
        bool operator<(const Terna &t2) const { return value < t2.value; }

        void print(){
            cout << "i: " << i << ", j: " << j << ", value: " << value << endl;
        }
};
//Defino criterio de comparacion
bool comparar_distancia (const Terna &a, const Terna &b){
    //Compara con la distancia de i, j al origen
    return ( (a.i *a.i + a.j * a.j) < (b.i * b.i + b.j * b.j));
        
    }

int main(){
    //Defino un vector de ternas
    array <Terna, 3>  v{Terna(7,8,3), Terna(1,4,1), Terna(2,5,-1)};

    //COMPARO POR MAYOR
    cout << "--------- COMPARA MAYOR ---------" << endl;
    //Imprimo todas las ternas de un vector antes de ordenar
    for(int i = 0; i < sizeof(v)/sizeof(Terna); i++){
        v[i].print();
    }
    cout << "------------------------------------------------------------ " << endl;
    sort(v.begin(), v.end());
        for(int i = 0; i < sizeof(v)/sizeof(Terna); i++){
        v[i].print();
    }
    //COMPARO POR MODULO
    cout << "--------- COMPARA MODULO ---------" << endl;
    //Imprimo todas las ternas de un vector antes de ordenar
    for(int i = 0; i < sizeof(v)/sizeof(Terna); i++){
        v[i].print();
    }
    cout << "------------------------------------------------------------ " << endl;
    sort(v.begin(), v.end(), comparar_distancia);
        for(int i = 0; i < sizeof(v)/sizeof(Terna); i++){
        v[i].print();
    }

    return 0;
}