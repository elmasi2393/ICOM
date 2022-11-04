#include <iostream>
#include <vector>

using namespace std;

//funcion que recibe 1 vector<char> por referencia y devuelve un bool indicando si los char recibidos son iguales (true) o no (false)
bool esIgual(vector<char> &c); //TODO : Resolver esta funcion de 3 formas distintas

//funcion que recibe 1 vector<char> por copia, y, usando la funcion esIgual(vector<char> &), imprime en pantalla si los caracteres son iguales o distintos. La funcion no devuelve nada (void)
void fijarse(vector<char> c); //TODO : Resolver esta funcion de 2 formas distintas

int main(){
	
	char c_aux;
	vector<char> caracteres;
	
	cout << "Ingrese un caracter: ";
	cin >> c_aux;
	caracteres.push_back(c_aux);	
	
	cout << endl << "Ingrese otro caracter: ";
	cin >> c_aux;
	caracteres.push_back(c_aux);

	fijarse(caracteres);
	

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
bool esIgual(vector<char> &c) {
    if (c[0] == c[1]){ return true; }
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
// bool esIgualesIgual(vector<char> &c) {
//     if (c[0] != c[1]){ return false; }
//     return true;
// }

// /**
//  * @brief esIgual - Metodo 3
//  * @p Compara si a > b o si b > a. Se se cumple significa que no son iguales y devuelve 0, sino devuelve 1
//  * @param c1 
//  * @param c2 
//  * @return true Si son iguales
//  * @return false Si son diferenes
//  */
// bool esIgual(vector<char> &c) {
//     if (c[0] > c[1] || c[0] < c[1]){ return false; }
//     return true;
// }

void fijarse(vector<char> c)
{
	cout << "Los caracteres son: " << (esIgual(c) ? "IGUALES" : "DISTINTOS") << endl;
}

