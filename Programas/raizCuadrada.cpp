#include <iostream>
#include <cmath>

using namespace std;

int main(){

    cout << "Inserte un numero" << endl;
    double a;
    cin >> a;

    double x0 = 0;
    double x1 = 1;
    
    while((abs(x1 - x0) > 0.1)){
        x0 = x1;
        x1 = (x0 + a/x0)/2.0;
    }
    
    cout << x1 << endl;

    return 0;
}