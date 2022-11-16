#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Mazo {
	public:
		// Construye una instancia de Mazo leyendo las 'cartas' a partir la 
	    // informaci�n le�da en el 'iFile'.
		// El archivo cuenta con un string por rengl�n, con los s�mbolos de la
		// carta
		Mazo(const string &fname);                    // TODO

		// M�todo que verifica que todo par de cartas del mazo tenga un solo 
		// elemento en com�n.
		bool esValido();                              // TODO

		//Funci�n que imprime el mazo
		void print();						          // TODO

	private:
		// representacion de todas las cartas
		vector<string> cartas;

		// M�todo que retorna la cantidad de s�mbolos comunes entre las cartas
		// en las posici�n i y j
		unsigned int coincidencias(int i, int j);     // TODO
};

int main(){
	Mazo m("mazo.txt");

	m.print();

	cout << "el mazo es " << (m.esValido() ? "VALIDO" : "INVALIDO") << endl;

	return 0;

}
