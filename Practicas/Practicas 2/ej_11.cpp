#include <iostream>
#include <cmath>

using namespace std;

struct Complejo {
    double re, im;
    
    void print() {
        cout << "(" <<re << " + i " << im << ")\n";
    }
    Complejo operator+(Complejo a) {
        Complejo result = { re + a.re, im + a.im};
        return result;
    }
    Complejo operator-(Complejo a) { return { re - a.re, im - a.im }; }
    Complejo operator*(Complejo a) { return { re * a.re - im * a.im, re * a.im + im * a.re } ;}
    Complejo operator/(Complejo a) { return {(re * a.re + im * a.im)/(pow(a.re, 2) + pow(a.im, 2)), (-re * a.im + im * a.re)/(pow(a.re, 2) + pow(a.im, 2))} ; }
};

int main() {
    Complejo c1 = {1.2, 3.4}, c2 = {5.6, 7.8},
             c3 = c1 + c2;
    c3.print();
    (c1 - c2).print();
    (c1 * c2).print();
    (c1 / c2).print();
    return 0;
}
