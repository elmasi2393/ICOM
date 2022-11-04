#include "icom_helpers.h"

int main()
{
    char   c = 'a';
    int    a = 7;
    double x = 1.2;
    int   *pa = &a;
 
    // se va a imprimir el valor, el tamaño y donde esta la memoria asociada de cada variable
    // el operador & aplicado a una variable da acceso a su dirección en memoria

    cout << "a: " << a << " #" << sizeof(a) << " bytes @" << &a << '\n';
    cout << "pa: " << pa << " #" << sizeof(pa) << " bytes *pa contiene " << *pa << '\n';
    
    cout << "x: " << x << " #" << sizeof(x) << " bytes @" << &x << '\n';

    cout << "c: " << c << " #" << sizeof(c) << " bytes @" << hex << (intptr_t) &c << '\n';

    return 0;
}
