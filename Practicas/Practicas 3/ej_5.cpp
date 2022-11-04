#include <iostream>

using namespace std;

double miSqrt(double a);

int main(){
    int n;
    cout << "Ingrese un numero al cual calcularle la raiz cuadrada por aproximacion: ";
    cin >> n; 
    cout << miSqrt(n) << endl;
    return 0;
}

double miSqrt(double a){
    int n_it = 30;
    double sqrt = 1;
    for(int i=0; i<n_it; i++){
        sqrt = (sqrt + a/sqrt)/2;
        cout << "sqrt = " << sqrt << endl;
    }
    return sqrt;
}