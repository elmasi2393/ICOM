#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Mazo
{
public:
  // Construye una instancia de Mazo leyendo las 'cartas' a partir la
  // informacion leida en el archivo 'mazo.txt'.
  // El archivo cuenta con un string por renglon, con los simbolos de la
  // carta
  Mazo(const string &fname); // TODO
	
  //Funcion que imprime el mazo
  void print(); //TODO

private:
  // representacion de todas las cartas
  vector<string> cartas;

};

int main()
{
  Mazo m("mazo.txt");
  
  m.print();

  return 0;
}
