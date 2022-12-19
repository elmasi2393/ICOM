#include <iostream>
#include <string>

using namespace std;

bool esNumeroClaro(const string &numero){
    for(int i=0; i<numero.size();i++){
        int n = numero.at(i) - '0';   //Busco la cantidad de i que tendria que tener
        int cont = 0;   //Inicializo un contador en 0
        auto pos = numero.find(i + '0');    //Busco la primera ocurrencia del i
        while(pos != string::npos){
            cont++; //Si esta dentro del string, incremento el contador
            pos = numero.find(i + '0', pos+1);    //Chequeo si hay otra ocurrencia
        }
        // cout << "cont: " << cont << endl;
        if(cont != n) return false; //Si no son iguales, no es claro
    }
    return true;
}
bool esNumeroClaro(int rango){
    return esNumeroClaro(to_string(rango));
}
int main(){
    string n = "6210001000";
    cout <<(esNumeroClaro(n)? "Es numero claro": "No es numero claro")<< endl;
    cout <<(esNumeroClaro(1210)? "Es numero claro": "No es numero claro")<< endl;
    return 0;
}