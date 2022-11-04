/* lectura de strings */

#include "icom_helpers.h"

int main()   	
{
    cout << "Ingrese su nombre (termine con Enter):\n";

    string nombre;	// declaracion de la variable 'nombre'
			// todas las variables tienen tipo, en este caso
                    // string: cadena de caracteres alfanumericos
    cin >> nombre;	// lee caracteres hasta un 'whitespace'
                    // 'whitespace': espacio/tab/return/…

    cout << "Hola " << nombre << "!\n";
    return 0;
}
