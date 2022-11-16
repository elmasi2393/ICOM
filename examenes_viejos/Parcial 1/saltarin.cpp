#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

// UDT para representar una casilla del tablero
struct Casilla {
    int salto; // longitud del salto desde esta casilla
    int nummov = -1; // si la casilla forma parte de la solucion, el numero de movida
    bool visitada = false; // si la casilla ya fue visitada o no
};

// UDT que representa el juego
struct Saltarin {
    static const int N = 10; // tamaño del tablero N x N
    Casilla tablero[N][N]; // representacion del tablero como matriz de casillas
    int nummov; // para llevar la cuenta de en que movida voy

	// Constructor que lee los saltos del archivo que recibe como argumento
    Saltarin(string file) {
		fstream iFile(file);
        if (iFile){
            for (int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    int d;
                    iFile >> d;
                    this->tablero[i][j].salto = d;
                }
            }
            iFile.close();
        }
        nummov = 0;
	};

	// metodo recursivo que resuelve el juego a partir de la casilla {i,j}
    bool resolver(int i, int j) {

        if (i < 0 ||  j < 0 || i > 9 || j > 9){ return false; }    //Si caigo afuera, devuelvo falso
        else if (tablero[i][j].visitada == 1) { return false; }     //Si ya visite la casilla, no es por aca

        tablero[i][j].visitada = true; //Marco la casilla visitada

        tablero[i][j].nummov = nummov;
        nummov++;

        if(i == 9 && j == 9){ return 1; } //Si ya estoy en el ultimo el juego esta resuelto

        if (resolver(i +  tablero[i][j].salto, j)) { return true; }
        else if (resolver(i -  tablero[i][j].salto, j)) { return true; }
        else if (resolver(i , j + tablero[i][j].salto)) { return true; }
        else if (resolver(i, j - tablero[i][j].salto))  { return true; }

    };

	// imprime el tablero, con la info del salto y nummov de cada casilla
    void print()
    {
		for(int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                if(tablero[i][j].nummov != -1){
                    cout << tablero[i][j].salto << " (" << tablero[i][j].nummov << ") \t";
                }else{
                    cout << tablero[i][j].salto << "\t";
                }
            }
            cout << endl;
    }
    return;
    };
};
int main() {   
    cout << "Uno con salida " << endl;
    string file = "consalida.txt";
    Saltarin salta(file);
    salta.print();

    if (!salta.resolver(0,0)){ cout << "No hay salida " << endl;}
    else {
        cout << "Encontre la salida " << endl;
        salta.print();
    }
        cout << endl<<"Uno sin salida " << endl;

    file = "sinsalida.txt";
    Saltarin salta2(file);
    salta2.print();
    if (!salta2.resolver(0,0))
    {
        cout << "No hay salida " << endl;
    }
    else
    {
        cout << "Encontre la salida " << endl;
        salta2.print();
    }

    return 0;
}

