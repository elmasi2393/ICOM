#include <iostream>

using namespace std;

int main(){
    //Definicion de variables como float
    float x1 = 1.126, x2 = -1.125, x3 = -0.001;
    float Sf = 0;

    //Realizacion de la sumatoria como float
    for (int i = 0; i<0xFFFFFF; i++){
        Sf += (x1 + x2 + x3);
    }

    //Definicion de variables como double
    double x1b = 1.126, x2b = -1.125, x3b = -0.001;
    double Sd = 0;
    for (int i = 0; i<0xFFFFFF; i++){
        Sd += (x1b + x2b + x3b);
    }
    
    //Las variables como double tienen mayor precision que las float
    cout << "Sf (float) = " << Sf << endl;
    cout << "Sf (double) = " << Sd << endl;

    return 0;
}