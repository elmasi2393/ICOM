#include <iostream>
#include <vector>

using namespace std;

class Contenedor {
	public:
		Contenedor(vector<char> v) {
			if (v.size() < 3){ this->caracteres = v; }
			else{ cout << "No se pudo inicializar" << endl; }
		}

		bool esIgual()
		{
			return (caracteres.at(0)==caracteres.at(1));
		} 

		void fijarse()
		{
			cout << "Los caracteres son: " << (esIgual() ? "IGUALES" : "DISTINTOS") << endl;
		}	

	private:
		vector<char> caracteres; 

};

int main(){

	Contenedor c(vector<char> {'a','b'});

	c.fijarse();

	return 0;

}
