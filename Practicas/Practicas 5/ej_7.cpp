#include <iostream>
#include "arrayNativos.h"

using namespace std;

int main(int argc, char **argv){

    int v[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    ImprimeVector(v, sizeof(v)/sizeof(int));
    InvierteArrayNativo(v, sizeof(v)/sizeof(int));
    cout << "---------------" << endl;
    ImprimeVector(v, sizeof(v)/sizeof(int));
    return 0; 
}