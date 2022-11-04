#include <iostream>

using namespace std;

struct A{
    int a;
    A (int a){
        this->a = a;
    }
    void print(){ cout << a << endl;}
};

int main(int argc, char **argv){

A a = {4};  //Constructor por defecto
A b(67);    //Constructor definido
A c = b;    //Constructor copia

a.print();
b.print();
c.print();

}