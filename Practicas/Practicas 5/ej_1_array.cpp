#include <iostream>
#include <chrono>
#include <array>

#define N 10

using namespace std;

int main(int argc, char **argv){

    auto begin = chrono::high_resolution_clock::now();
    array<int, N> rep = {0};
    array<int, N+1> limits = {0};

    //Inicializo los limites de manera generica
    int cont = 0;
    for (auto &c: limits) { c = cont * (RAND_MAX/N); cont++;} 

    char n = 0xFF;
    while(n){   //Nos da la cantidad de numeros
        n--;
        int x = rand(); //Elegimos un numero de manera aleatoria

        for(int i = 0; i < N; i++){ //Decidimos en que intervalo esta
            if(x >= limits.at(i) && x < (limits.at(i+1)-1))   {rep.at(i)++; break;}  //Si esta dentro del intervalo, no seguimos comparando
        }
    }
    //Imrpimimos los valores
    for (const auto &c: rep) { cout << "rep: " << c << endl; }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

    cout << "Time Elapsed: " << elapsed.count() << " ns" << endl;

    return 0;
}