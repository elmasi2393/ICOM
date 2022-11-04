#include <iostream>

using namespace std;

void probarReferencia (int &a);
void probarPuntero(int *b);

int main(){
    int x = 20;

    cout << "Valor de la variable x inicial: " << x << endl;
    cout << "Direccion de memoria de la variable x inicial: " << &x << endl;

    // probarReferencia(x);
    probarPuntero(&x);

    cout << "Valor de la variable x final: " << x << endl;
    cout << "Direccion de memoria de la variable x final: " << &x << endl;

    return 0;
}

void probarReferencia (int &a){
    cout << "Valor de la variable a inicial: " << a << endl;
    cout << "Direccion de memoria de la variable a inicial: " << &a << endl;

    a = 8;
    
    cout << "Valor de la variable a final: " << a << endl;
    cout << "Direccion de memoria de la variable a final: " << &a << endl;

    return;
}

void probarPuntero(int *b){
    cout << "Valor de la variable a inicial: " << *b << endl;
    cout << "Direccion de memoria de la variable a inicial: " << b << endl;

    *b = 14;
    
    cout << "Valor de la variable a final: " << *b << endl;
    cout << "Direccion de memoria de la variable a final: " << b << endl;

    return;
}