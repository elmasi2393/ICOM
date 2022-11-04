#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Contenedor {
	public:
		Contenedor() 
		
		{
			string c_aux;
			
			while (true)
			{
				cout << "Ingrese un string de 8 caracteres: ";
				cin >> c_aux;
				if (c_aux.length()==8)
				{
					cartas.push_back(c_aux);
					break;
				}
				else
					cout << "Dije 8 caracteres!" << endl;
			}		
	
			while (true)
			{
				cout << "Ingrese otro string de 8 caracteres: ";
				cin >> c_aux;
				if (c_aux.length()==8)
				{
					cartas.push_back(c_aux);
					break;
				}
				else
					cout << "Dije 8 caracteres!" << endl;
			}
		}
		
		//funcion que se fija si al menos un caracter de cada una de las 2 cartas coincide con al menos un caracter de la otra. Si existe una coincidencia, evuelve true, sino false.
		bool coincidencia(); //TODO

		void fijarse()
		{
			cout << "Las cartas coinciden en algun caracter? " << (coincidencia() ? "SI" : "NO") << endl;
		}	

	private:
		vector<string> cartas; 

};

int main(){

	Contenedor c;

	c.fijarse();

	return 0;

}
