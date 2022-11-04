#include <iostream>
#include <cmath>

using namespace std; 

double promedio(double datos[], int n);
double dstandard(double datos[], int n);

int main(int argc, char** argv){

    double v[5] = {1, 2, 3, 4, 5};

    // for(int i=0; i<10; i++){ v[i] = (sizeof(v)/sizeof(int))*(rand()/RAND_MAX); }

    cout << promedio(v, sizeof(v)/sizeof(double)) << endl;
    cout << dstandard(v, sizeof(v)/sizeof(double)) << endl;

    return 0;
}

double promedio(double datos[], int n){
    double p = 0;
    for (int i = 0; i<n; i++){ p += datos[i]; }
    cout << p << endl;
    return p/n;

}
double dstandard(double datos[], int n){
    double p = promedio(datos, n);
    double std = 0;
    for (int i = 0; i < n; i++){ std += (datos[i] - p)*(datos[i] - p); }

    return sqrt(std/(n-1));

}