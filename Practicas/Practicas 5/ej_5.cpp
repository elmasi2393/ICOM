#include <iostream>
#include "arrayNativos.h"

using namespace std;

int main(int argc, char **argv) {

    
    int v[10] = {3, 2, 5, 1, 9 ,0, 8, 4, 7, 6};

    ImprimeVector(v, 10);
    OrdenaArrayNativo(v, 10);
    ImprimeVector(v, 10);

    return 0; 
}