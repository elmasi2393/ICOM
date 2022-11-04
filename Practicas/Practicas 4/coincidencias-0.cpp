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
