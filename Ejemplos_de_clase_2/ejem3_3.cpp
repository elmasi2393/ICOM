#include "icom_helpers.h"

int main()   	
{
    cout << "Ingrese su nombre y apellido:\n";

    string nombre;	
    string apellido;	
    cin >> nombre >> apellido;

    string nombre_completo = nombre + ' ' + apellido;

    cout << "Hola " << nombre_completo << '\n';
    return 0;
}
