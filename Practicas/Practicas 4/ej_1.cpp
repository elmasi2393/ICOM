#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std; 

int main(int argc, char **argv) {
    double x = 0, y = 0;
    int num_pasos, n1 = 0;
    srand(time(0));

    cout << "Defina el numero de interaciones para calcular pi: ";
    cin >> num_pasos;

    for (int i = 0; i < num_pasos; i++) {
        x = (-1 + rand() % num_pasos)/ double(num_pasos);
        y = (-1 + rand() % num_pasos)/ double(num_pasos);

        if(sqrt(x*x + y*y) <= 1){ n1++; }
    }

    cout << "pi = " << 4*(n1/double(num_pasos)) << endl;
    return 0;  
}