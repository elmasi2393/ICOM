#include <iostream>
#include <chrono>

#define N 10

using namespace std;

int main(int argc, char **argv){

    auto begin = chrono::high_resolution_clock::now();
    int rep[N], limits[N+1];
    limits[0] = 0;

    //Inicializo los limites de manera generica
    for (int i = 0; i<N; i++){
        limits[i+1] = (i+1) * (RAND_MAX/N);
        rep[i] = 0; //Inicializadmos en 0 para evitar valores basura
    }

    char n = 0xFF;
    while(n){   //Nos da la cantidad de numeros
        n--;
        int x = rand(); //Elegimos un numero de manera aleatoria

        for(int i = 0; i < N; i++){ //Decidimos en que intervalo esta
            if(x >= limits[i] && x < (limits[i+1]-1))   {rep[i]++; break;}  //Si esta dentro del intervalo, no seguimos comparando
        }
    }
    for (int i = 0; i < N; i++) {
        cout << "rep[" << i << "]: " << rep[i] << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

    cout << "Time Elapsed: " << elapsed.count() << " ns" << endl;

    return 0;
}