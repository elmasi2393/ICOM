// #include "icom_helpers.h"
#include <cassert>
#include <cctype>
#include <string.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;   


// caracteres en el mapa (el nombre de la variable indica su significado)
const char bunker = 'B';
const char bunkerVisitado='b';
const char salida='S';
const char pared='#';
const char espacio=' ';
const char espacioVisitado='o';
const char espacioResaltado='*';

// estructura para representar una celda del mapa {fila, columna}
struct Celda
{
    // fila f y columna c de la celda
    Celda(size_t fila, size_t col): f(fila), c(col) {}
    size_t f,c;
    void print() const{
        cout << "f: " << f << " c: " << c << endl;
    }
};

// UDT para representar la instalacion (su mapa y sus niveles de radiacion)
class LaberintoRadiactivo
{
public:
    // UDT que representa un camino de salida:
    struct Camino
    {
        // constructor default
        Camino():radTotal(0.0){}
        //destructor
        ~Camino() {}
        // agrega la celda cel al camino y suma la radiacion rad al total acumulado
        void agregarCelda(Celda cel, float rad){
            // cout << "agrego" << endl;
            path.push_back(cel);
            radTotal += rad;
        }
        void print() const{
            cout << "radTotal: " << radTotal << endl;
            for(auto a: path){
                a.print();
            }
        }
        // vector de celdas que componen el camino
        vector<Celda> path;
        // radiacion total acumulada a lo largo del camino
        float radTotal;
    };
    // construye el LaberintoRadiactivo usando el archivo mapa_file que contiene el mapa en representacion ASCII
    // y radlevel_file que contiene 3 valores por cada linea: fila, columna y radiacion
    LaberintoRadiactivo(string mapa_file,string radlevel_file){
        //Leo ambos archivos
        ifstream map_file(mapa_file);
        ifstream rad_file(radlevel_file);

        //Guardado de mapa
        string value;
        while(getline(map_file, value)){
            mapa.push_back(value);
            value.clear();
        }
        nf = mapa.size();
        nc = mapa.at(0).size();
        rad.resize(mapa[0].size()); //Guardo lugar para las columnas
        for(auto &c : rad){
            c.resize(mapa.size()); //Guardo lugar para las filas
        }
        // //Guardo los niveles de radiacion
        int f, c;
        float n;
        // cout << "Niveles de radiacion" << endl;
        // cout << rad.size() << endl;
        // cout << rad[0].size() << endl;
        while(rad_file >> f >> c >> n){
            // cout << " " << f << " " << c << " " << n << endl;
            rad[f][c] = n;
        }

    }
    // imprime el mapa en su estado actual
    void print(){
        for(auto c : mapa){
            cout << c << endl;
        }
    }
    // encuentra el mejor camino y lo resalta en el mapa
    // imprime el mapa y la radiacionTotal
    void resolver(){
        // localiza(bunker);
        Celda inicio = localiza(bunker);
        Camino * cam = buscarMejorCamino(inicio); //Empiezo desde el bunker

        for(auto c : cam->path){
            mapa[c.f][c.c] = espacioResaltado;
        }
        cout << "Radiacion recibida: " << cam->radTotal << endl; 
        
        
    }
private:
    // localiza la celda donde se encuentra el caracter c y la retorna
    Celda localiza(char c){
        for(int i = 0; i < nf; i++){
            for(int j = 0; j < nc; j++){
                if(mapa.at(i).at(j) == c){
                    cout << "i: " << i << "j: " << j << endl;
                    return Celda(i, j);
                }
            }
            }
    }
    
    // recorre el laberinto recursivamente desde la Celda cel buscando la salida.
    // no se permite moverse en diagonal.
    // Si no encuentra la salida retorna nullptr.
    // Si la encuentra retorna un puntero al camino que conduce a la salida
    // minimizando la radiacion total. El camino se va armando en el mismo proceso recursivo.
    // Ayuda1: hay que buscar a partir de cada vecino, porque hay mas de un camino posible y nada garantiza que el primero que se encuentre sea el mejor
    // Ayuda2: hay que seleccionar y retornar el camino que tenga la minima radiacion total (y que va a hacer con los otros?)
    // Ayuda3: hay que desmarcar la casilla (ponerla como no visitada), antes de retornar, porque puede ser visitada nuevamente por otro camino.
    Camino * buscarMejorCamino(Celda cel){
        char c = mapa[cel.f][cel.c];
        
        if( (c == pared)||(c == espacioVisitado)||(c == espacioResaltado))      
            return nullptr;
        //Las paredes del laberinto tienen #, asi que no hay que chequear los bordes

        if (c == salida){
            Camino* ptr = new Camino; 
            ptr->agregarCelda(cel,rad[cel.f][cel.c]);
            return ptr;
        }

        if ((c == espacio)||(c == bunker)){
            mapa[cel.f][cel.c] = espacioVisitado;

            Camino * ptr1 = buscarMejorCamino({cel.f+1,cel.c});
            Camino * ptr2 = buscarMejorCamino({cel.f-1,cel.c});
            Camino * ptr3 = buscarMejorCamino({cel.f,cel.c+1});
            Camino * ptr4 = buscarMejorCamino({cel.f,cel.c-1});
            Camino * ptr[] = {ptr1,ptr2,ptr3,ptr4};

            float radiacion_aux= -1;
            int aux_index;

            for(int i = 0; i<4; i++){
                if(ptr[i] == nullptr){
                    continue;
                }
                if(radiacion_aux < 0){                        //Este if nos seria necesario si hubiera un dato de radiacion maxima que poseea el camino          
                    radiacion_aux= ptr[i]->radTotal;
                    aux_index = i;
                }
                else{
                    if(radiacion_aux > ptr[i]->radTotal){
                        radiacion_aux= ptr[i]->radTotal;
                        aux_index = i;
                    } 
                    else{
                        delete ptr[i];                              //El otro camino es mejor, tengo que eliminar este
                    }
                }
            }

            mapa[cel.f][cel.c] = espacio;                       // Antes de volver, despinto
            if(radiacion_aux == -1){                            // Es decir, si no encontre ningun camino
                return nullptr;
            }

            ptr[aux_index]->agregarCelda(cel,rad[cel.f][cel.c]);
            return ptr[aux_index];
        }
        
        throw("No se determino la salida");
        return nullptr;
    }

    // dimensiones del mapa nf=numero de filas, nc=numero de columnas
    size_t nf,nc;
    // mapa de la instalacion en representacion de caracteres, cada fila es un string y cada caracter dentro de ese string es una celda
    // se puede ver como una matriz
    vector<string>mapa;
    // valores de radiacion residual rad[i][j] para cada celda {i,j}
    vector<vector<float>> rad;
};

int main()
{
    LaberintoRadiactivo labrad("mapa.txt","niveles_radiacion.txt");
    labrad.print();
    labrad.resolver();
    labrad.print();
    // try
    // {
    //     LaberintoRadiactivo labrad("mapa.txt","niveles_radiacion.txt");
    //     labrad.print();
    //     labrad.resolver();
    //     return 0;
    // }
    // catch (string &s)
    // {
    //     cerr<< "Error: " << s << endl;
    //     return -1;
    // }
    // catch(...)
    // {
    //     cerr << "Error inesperado"<< endl;
    //     return -1;
    // }
}
