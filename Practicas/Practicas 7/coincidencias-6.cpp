#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

class Mazo {
  public:
  // Construye una instancia de Mazo leyendo las 'cartas' a partir la
  // informacion leida en el archivo 'mazo.txt'.
  // El archivo cuenta con un string por renglon, con los simbolos de la
  // carta
    Mazo(const string &fname){ // TODO
      string carta;
      fstream iFile(fname);

      if(iFile){
        while(iFile >> carta){  cartas.push_back(carta);  }
      }
    }
    // Metodo que verifica que todo par de cartas del mazo tenga un solo
    // elemento en comun.
    bool isEqual(const string & carta, vector<string>::iterator it_begin, vector<string>::iterator it_end){ //Comparo una carta con las posiciones del maso indicadas
      for(;it_begin != it_end; ++it_begin){
        if(carta == *it_begin){ return true; }
      }
      return false;
    }

    bool esValido(){
      for(int i=0; i< cartas.size(); ++i){
        if(isEqual(cartas.at(i), cartas.begin()+i+1, cartas.end())){ return false; }  //Pregunto por cada carta con el resto de las demas pasandole el iterador desde la siguiente hasta la ultima
      }
      //Si pasa la prueba de que no sean iguales, se verifica la coincidencia
      for(int i=0; i<cartas.size(); i++){   //Pregunto cada carta por todas las demas del maso
        for(int j=i; j<cartas.size(); j++) {
          if(this->coincidencias(i, j) > 1 ){ return false;}
        }
      }

      return true;
    }
    //Funcion que imprime el mazo
    void print(){
      for(const auto & carta : cartas){ cout << carta << endl; }
    }

  private:
    // representacion de todas las cartas
    vector<string> cartas;

    // Metodo que retorna la cantidad de simbolos comunes entre las cartas
    // en las posiciones i y j
    unsigned int coincidencias(int i, int j); 

    //Funcion auxiliar que calcula el numero de ocurrencias del
    //caracter c en el string s1
    int encontrar_car(const string &s1, char c) {
      int ocurrencias = 0;
      for (int i = 0; i < s1.size(); i++)
      {
        if (c == s1[i])
        ocurrencias++;
      }
    return ocurrencias;
    }
};

unsigned int Mazo::coincidencias(int i, int j){ 
  //Chequeo que los  indices
  //estén dentro del tamaño del arreglo:
  assert(i < cartas.size() || j < cartas.size());
  string si = cartas[i], sj = cartas[j];
  // Chequeo que las cartas tengan mismo
  //numero de figuras:
  assert(si.size() == sj.size());
  int num_fig = si.size(), ocur = 0;
  for (int k = 0; k < num_fig; k++)
    ocur += encontrar_car(sj, si[k]);

  return ocur;
};

int main() {
  Mazo m("mazo.txt");
  m.print();
  cout << "el mazo es " << (m.esValido() ? "VALIDO" : "INVALIDO") << endl;

  return 0;
}