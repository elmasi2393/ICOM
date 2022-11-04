#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// UDT para representar las coordenadas de una celda del laberinto
struct Celda
{
    int i; // fila
	int j; // columna
};

// UDT para representar el laberinto
struct Laberinto
{
	// la representación como vector de strings, permite usarla como matriz rep[i][j]
    vector<string> rep;

	// todos los caracteres que puede haber en el laberinto
    const char pared = '#';
    const char entrada = 'E';
    const char salida = 'S';
    const char espacio = ' ';
    const char entrada_visitada='e';
    const char salida_visitada='s';
    const char espacio_visitado='o';

	// construey el laberinto leyendo desde el archivo cuyo nombre es el argumento
    Laberinto(const string &filename)
    {
		// TODO
    }

	// busca la celda que contiene el caracter c y la retorna
	// se usa para localizar la entrada del laberinto
    Celda buscar(char c)
    {
		//TODO
	}
	
	// imprime el laberinto
	void print()
	{
		// TODO
    }

    void resolver()
    {
        Celda ent = buscar(entrada);
        if ( backtrack(ent) )
        {
           print();
           cout << "Encontré la solucion" << endl;
        }
        else
        {
            cout << "No hay solucion" << endl;
        }
    }

	// funcion recursiva que intenta encontrar la salida desde la celda cel
	// que se le pasa como argumento. A medida que avanza, va marcando los
	// celdas como visitadas. si por un camino no se llega a la salida, vuelve
	// a marcar la celda como no visitada y retorna falso.
	// si encuentra la salida retorna verdadero.
    bool backtrack(Celda cel)
    {
		// TODO
    }
};

int main()
{
    Laberinto lab("laberinto.txt");
    lab.print();
    lab.resolver();
    return 0;
}
