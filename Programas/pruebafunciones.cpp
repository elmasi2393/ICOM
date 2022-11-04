#include <iostream>
using namespace std;
void incrementar_valor(int x) { // por valor
    x++;
}
void incrementar_puntero(int *x) { // por puntero 
    (*x)++;
}
void incrementar_referencia(int &x) { // por referencia 
    x++;
}
int main() {
int x = 1; incrementar_valor(x);
    cout << "x = " << x << endl;
    incrementar_puntero(&x);
    cout << "x = " << x << endl;
    incrementar_referencia(x);
    cout << "x = " << x << endl;
}