#include <iostream>

using namespace std;

void print(int *matriz, int n){
    for (int i = 0; i < n*n; i++){
        if(!(i%n)){ cout << endl; }
        cout << *(matriz+i) << "\t";
    }
    cout << endl;
    return;
}

void fun() {
    int a[3][3] = { 0 };    //Relleno una matriz de enteros con todos 0
    print(&a[0][0], 3);
    int *pFilas[3] = { &a[0][0], &a[1][0], &a[2][0] };  //Creo un vector de punteros, con la referencia a cada fila de la matriz
    print(pFilas[0], 3);
    pFilas[0][0] = pFilas[1][0] = pFilas[2][0] = 1; //A cada fila en la posicion 0, le asignas un 1
    print(pFilas[0], 3);
}

int main(int argc, char **argv){
    fun();
    return 0;
}