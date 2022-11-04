/* conversor de pulgadas a milímetro */
#include "icom_helpers.h"

int main()   	
{
    const double mm_per_inch = 25.4;
    
    int length = 1;        // longitud en pulgadas
    
    while( length != 0 )   // length == 0 se usa para terminar el programa
    {				// sentencia compuesta
        cout << "Ingrese una longitud en pulgadas: ";
        cin >> length;
        cout << length << " pulgadas, son " << mm_per_inch * length
             << " milímetros\n";
    }
    return 0;
}
