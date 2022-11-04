#include <iostream>

using namespace std;

int main(int argc, char **argv) {  
    int t;
    cin >> t; // Ingreso de horas
    int segundos = t%60;
    int minutos = (t/60)%60; //
    int horas = t/3600;

    cout << "horas: "   << horas << " minutos: " << minutos << " segundos: " << segundos << endl;

    return 0; //
}