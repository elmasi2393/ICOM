#include <iostream>
#include <cstdlib>

using namespace std;

struct Terna {
        int i;
        int j;
        int value; 

        void print(){
            cout << "i: " << i << ", j: " << j << ", value: " << value << endl;
        }
};
//Defino criterio de comparacion
int comparar (const void * a, const void * b){
    return ( ((Terna*)a)->value - ((Terna*)b)->value);
}

int comparar_distancia (const void * a, const void * b){
    //Compara con la distancia de i, j al origen

    return ( (((Terna *)a)->i * ((Terna *)a)->i + ((Terna *)a)->j * ((Terna *)a)->j) - (((Terna *)b)->i * ((Terna *)b)->i + ((Terna *)b)->j * ((Terna *)b)->j));
        
    }

int main(){
    //Defino un vector de ternas
    Terna v [3] = {{7,8,3}, {1,4,1}, {2,5,-1}};

    //COMPARO POR MAYOR

    cout << "--------- COMPARA MAYOR ---------" << endl;
    //Imprimo todas las ternas de un vector antes de ordenar
    for(int i = 0; i < sizeof(v)/sizeof(Terna); i++){
        v[i].print();
    }

    //Ordeno el vector
    qsort(v, sizeof(v)/sizeof(Terna) ,sizeof(Terna), comparar);
    cout << endl;
    //Imprimo todas las ternas de un vector despues de ordenar
    for(int i = 0; i < sizeof(v)/sizeof(Terna); i++){
        v[i].print();
    }

    cout << "--------- COMPARA DISTANCIA ---------" << endl;
    //COMPARA POR DISTANCIA
        //Imprimo todas las ternas de un vector antes de ordenar
    for(int i = 0; i < sizeof(v)/sizeof(Terna); i++){
        v[i].print();
    }

    //Ordeno el vector
    qsort(v, sizeof(v)/sizeof(Terna) ,sizeof(Terna), comparar_distancia);
    cout << endl;
    //Imprimo todas las ternas de un vector despues de ordenar
    for(int i = 0; i < sizeof(v)/sizeof(Terna); i++){
        v[i].print();
    }
    return 0;
}