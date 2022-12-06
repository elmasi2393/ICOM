#include "icom_helpers.h"

// estos son los caracteres que se pueden encontrar en el laberinto
const char pared = '#';
const char espacio = ' ';
const char espacio_visitado = 'o';
const char entrada = 'E';
const char entrada_visitada = 'e';
const char salida = 'S';
const char salida_visitada='s';

struct Celda
{
    int f, c;
};

class Laberinto
{
public:
	// constructor del laberinto que implementa el algoritmo descripto en el enunciado
    Laberinto(size_t nf_, size_t nc_);//TODO
	// imprime el laberinto (es idéntica a la del parcial)
    void print()
    {
        for(size_t i=0; i<nf; ++i )
            cout << txtrep[i] << endl;
    }
private:
    // numero de filas y columnas, deben ser impar y nf * nc >=15
    size_t nf, nc;
	// representacion textual del laberinto como matriz de caracteres.
    vector<string> txtrep;
};

int main() // TODO

