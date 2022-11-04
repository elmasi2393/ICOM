/* ejemplo de assert */
#include <assert.h>
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Ingrese un número positivo "; double v;
    cin >> v;
    assert(v >= 0);
    cout << "la raiz cuadrada es: " << sqrt(v) << '\n';
return 0; }