#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    //DEFINICION DE VARIABLES
    int N;      //Numero a convertir
    int base;   //Base a convertir
    const vector<char> caracteres = {'A', 'B', 'C', 'D', 'E', 'F'}; //Defino caracteres
    vector<int> v; //Defino vector donde poner los restos y el ultimo cociente

    cout << "Ingrese un numero en decimal y la base a la que la lo quiere convectir (entre 2 y 16), separados por estacios: ";
    cin >> N >> base;
    
    //Metodo divisiones sucesivas
    while(1){
        int cociente = N/base;
        int restos = N%base;
        // cout << "cociente: " << cociente << endl;

        v.push_back(restos);    //Agregamos los restos
        if(cociente <= base){   //Si el cociente es igual o mas chico que la base, el algoritmo termina
            v.push_back(cociente);
            break;
        }
        N = cociente;   //Asignamos nuestro nuevo divisor para la siguiente iteracion
    }   
    reverse(v.begin(), v.end());    //Damos vuelta el vector para recorrerlo como range
    
    for(const auto& value : v){     //Recorremos el vector e imprimimos los caracteres correspondientes
        if (value >10){ cout << caracteres[value - 10];}
        else{ cout << value;}
    }
    cout << endl;

    return 0;
}