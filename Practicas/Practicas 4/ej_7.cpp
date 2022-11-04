#include <iostream>

using namespace std;

//funcion que recibe 2 char por copia y devuelve un bool indicando si los char recibidos son iguales (true) o no (false)
bool esIgual(char c1, char c2); //TODO : Resolver esta funcion de 3 formas distintas


//funcion que recibe 2 char por copia, y, usando la funcion esIgual(char, char), imprime en pantalla si los caracteres son iguales o distintos. La funcion no devuelve nada (void)
void fijarse(char c1, char c2)
{
	cout << "Los caracteres son: " << (esIgual(c1,c2) ? "IGUALES" : "DISTINTOS") << endl;
}

int main(){
	
	char caracter_1,caracter_2;
	
	cout << "Ingrese un caracter: ";
	cin >> caracter_1;
	
	cout << endl << "Ingrese otro caracter: ";
	cin >> caracter_2;
	
	fijarse(caracter_1,caracter_2);	

	return 0;

}
/**
 * @brief esIgual - Metodo 1
 * @p compara si son igualees. Si se cumple devuelve 1 y sino un 0
 * @param c1 
 * @param c2 
 * @return true son iguales 
 * @return false son desiguales
 */
bool esIgual(char c1, char c2) {
    if (c1 == c2){ return true; }
    return false;
}

/**
 * @brief esIgual - Metodo 2
 * @p compara si son desiguales. Si se cumple devuelve 0, y sino un 1
 * @param c1 
 * @param c2 
 * @return true No son desiguales
 * @return false Son desiguales
 */
bool esIgual(char c1, char c2) {
    if (c1 != c2){ return false; }
    return true;
}

/**
 * @brief esIgual - Metodo 3
 * @p Compara si a > b o si b > a. Se se cumple significa que no son iguales y devuelve 0, sino devuelve 1
 * @param c1 
 * @param c2 
 * @return true Si son iguales
 * @return false Si son diferenes
 */
bool esIgual(char c1, char c2) {
    if (c1 >c2 || c1 < c2){ return false; }
    return true;
}



