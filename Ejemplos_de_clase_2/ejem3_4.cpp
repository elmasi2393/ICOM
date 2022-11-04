/* lectura de nombre y edad */
#include "icom_helpers.h"

int main()   	
{
    cout << "Ingrese su nombre y edad:\n";

    string nombre;	
    int edad;	
    cin >> nombre >> edad;


    cout << "Hola " << nombre << " edad " << edad << '\n';
    return 0;
}
