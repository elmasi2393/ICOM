#include "icom_helpers.h"

struct A 
{
    A()            { cout << "Construyendo " << this << endl; }
    A(const A &b)  { cout << "Haciendo una copia de " << &b << " en " << this << endl; }
    ~A() { cout << "Destruyendo " << this << endl; } 
};

int main()
{
    A a;
    cout << "a esta en " << &a << endl;
    A b(a);
    cout << "b esta en " << &b << endl;
    return 0;
}