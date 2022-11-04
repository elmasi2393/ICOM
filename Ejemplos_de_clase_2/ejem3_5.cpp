/* aritmética simple*/
#include "icom_helpers.h"

int main()   	
{
    cout << "Ingrese un numero en punto flotante:\n";
    double n;
    cin >> n;
    cout << "n == " << n 
         << "\nn+1 == " << n + 1			// '\n' significa newline 
         << "\ntres veces n == " << 3 * n
         << "\nel doble de n == " << n + n
         << "\nla mitad de n == " << n / 2
         << "\nla raiz cuadrada de n == " << sqrt(n) // función de lib.
         << '\n'; 

    return 0;
}
