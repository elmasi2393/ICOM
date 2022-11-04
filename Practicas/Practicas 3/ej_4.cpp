#include <iostream>
#include <cmath>
#include <assert.h>

using namespace std;

int suma(int N);

int main(){
    int N;
    cout << "Ingrese un numero hasta cual sumar: ";
    cin >> N;
    cout << "\nEl resultado de sumar los N primeros numeros es: " << suma(N) << endl;
    // cout << pow(2, 8*sizeof(unsigned int)) << endl;
    return 0;
}

int suma(int N){
    unsigned int sum = 0;
    for(int i = 1; i <= N; i++){
        sum += i;
        assert(sum <= pow(2, 8*sizeof(unsigned int)));
    }
    return sum;
}