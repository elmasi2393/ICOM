#include <iostream>
#include "arrayNativos.h"
#include <chrono>

using namespace std;

int main(int argc, char** argv){

    int v[10];
    int u[100];
    int w[500];
    int h[1000];
    int x[5000];
    int y[10000];


    for(int i = 0; i < sizeof(v)/sizeof(int); i++){  v[i] = rand(); }  //Inicializado de vector de manera aleatoria
    for(int i = 0; i < sizeof(u)/sizeof(int); i++){  u[i] = rand(); }
    for(int i = 0; i < sizeof(w)/sizeof(int); i++){  w[i] = rand(); }
    for(int i = 0; i < sizeof(h)/sizeof(int); i++){  h[i] = rand(); }
    for(int i = 0; i < sizeof(x)/sizeof(int); i++){  x[i] = rand(); }
    for(int i = 0; i < sizeof(y)/sizeof(int); i++){  y[i] = rand(); }

    //VECTOR v
    auto begin = chrono::high_resolution_clock::now();      //Ponemos a medir el tiempo
    OrdenaArrayNativo(v, sizeof(v)/sizeof(int));            //Acomodamos el vector
    auto end = chrono::high_resolution_clock::now();        //Tomamos el tiempo de salida

    auto elapsed_v = chrono::duration_cast<chrono::nanoseconds>(end - begin);   //Registramos cuanto demora

    //VECTOR u
    begin = chrono::high_resolution_clock::now();      //Ponemos a medir el tiempo
    OrdenaArrayNativo(u, sizeof(u)/sizeof(int));            //Acomodamos el vector
    end = chrono::high_resolution_clock::now();        //Tomamos el tiempo de salida

    auto elapsed_u = chrono::duration_cast<chrono::nanoseconds>(end - begin);   //Registramos cuanto demora

    //VECTOR w
    begin = chrono::high_resolution_clock::now();      //Ponemos a medir el tiempo
    OrdenaArrayNativo(w, sizeof(w)/sizeof(int));            //Acomodamos el vector
    end = chrono::high_resolution_clock::now();        //Tomamos el tiempo de salida

    auto elapsed_w = chrono::duration_cast<chrono::nanoseconds>(end - begin);   //Registramos cuanto demora

    //VECTOR h
    begin = chrono::high_resolution_clock::now();      //Ponemos a medir el tiempo
    OrdenaArrayNativo(h, sizeof(h)/sizeof(int));            //Acomodamos el vector
    end = chrono::high_resolution_clock::now();        //Tomamos el tiempo de salida

    auto elapsed_h = chrono::duration_cast<chrono::nanoseconds>(end - begin);   //Registramos cuanto demora

    //VECTOR x
    begin = chrono::high_resolution_clock::now();      //Ponemos a medir el tiempo
    OrdenaArrayNativo(x, sizeof(x)/sizeof(int));            //Acomodamos el vector
    end = chrono::high_resolution_clock::now();        //Tomamos el tiempo de salida

    auto elapsed_x = chrono::duration_cast<chrono::nanoseconds>(end - begin);   //Registramos cuanto demora

    //VECTOR y
    begin = chrono::high_resolution_clock::now();      //Ponemos a medir el tiempo
    OrdenaArrayNativo(y, sizeof(y)/sizeof(int));            //Acomodamos el vector
    end = chrono::high_resolution_clock::now();        //Tomamos el tiempo de salida

    auto elapsed_y = chrono::duration_cast<chrono::nanoseconds>(end - begin);   //Registramos cuanto demora

    // cout << "| VECTOR |   TIEMPO   |" << endl;
    // cout << "|    v   |    " << elapsed_v.count() << "  |" << endl;
    // cout << "|    u   |    " << elapsed_u.count() << "  |" << endl;
    // cout << "|    w   |    " << elapsed_w.count() << "  |" << endl;
    // cout << "|    h   |    " << elapsed_h.count() << "  |" << endl;
    // cout << "|    x   |    " << elapsed_x.count() << "  |" << endl;
    // cout << "|    y   |    " << elapsed_y.count() << "  |" << endl;

        cout <<"VECTOR, TIEMPO" << endl;
    cout << "v , " << elapsed_v.count() << endl;
    cout << "u , " << elapsed_u.count() << endl;
    cout << "w , " << elapsed_w.count() << endl;
    cout << "h , " << elapsed_h.count() << endl;
    cout << "x , " << elapsed_x.count() << endl;
    cout << "y , " << elapsed_y.count()  << endl;



    return 0;
}