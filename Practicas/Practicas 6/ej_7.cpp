#include <iostream>

using namespace std;

struct A{
    int a;
    A(const A &x) {     //Construccion copia
        this->a = x.a;
        cout << "Se consruyó por copia ;)" << endl;
        }
    A (int a){          //Constructor definido
        this->a = a;
        cout << "Se construyo :)" << endl;
    }
    void print(){ cout << a << endl;}
};

void mostrar(A a){
    cout << "El valor de a por funcion es: " << a.a << endl;
    cout << "direccion a: " << &a << endl;
}

A copiar (A a) { return a;}

int main(int argc, char **argv){

A b(67);    //Constructor definido
A c = b;    //Constructor copia

b.print();
cout << "direccion b: " << &b << endl;
c.print();
cout << "direccion c: " << &c << endl;


mostrar(b); //Funcion que pasa copia de b

A d = copiar(b);    //Construye una copia para pasar y para devolver
d.print();
cout << "direccion d: " << &d << endl;

return 0;
}