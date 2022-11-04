#include "icom_helpers.h"
struct Complejo {
    double re, im;
    
    void print() {
        cout << "(" <<re << " + i " << im << ")\n";
    }
    Complejo operator+(Complejo a) {
        Complejo result = { re + a.re, im + a.im};
        return result;
    }
};

int main() {
    Complejo c1 = {1.2, 3.4}, c2 = {5.6, 7.8},
             c3 = c1 + c2;
    c3.print();
    return 0;
}
