#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char **argv){

    double x;
    cout << "Inserte x para evaluar polinomio 3x^3 - 5x^2 + 6" << endl;
    cin >> x;

    cout << "Result: " << 3*pow(x, 3) - 5*pow(x, 2) + 6 << endl;

    return 0;
}
