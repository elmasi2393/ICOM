#include <iostream>
#include <cmath>

using namespace std;

struct Punto3D_t {
    double x, y, z;
    
    void print() {
        cout << "(" << x << " , " << y << " , " << z << ")" << endl;
    }
    /**
     * @brief modulo
     * @p :Devuelve el modulo entre dos vectores
     * @param Punto3D_t b
     * @return double 
     */
    double modulo(Punto3D_t b){ return sqrt(pow(x - b.x, 2) + pow(y - b.y,2) + pow(z - b.z,2)); }
};

int main() {
    Punto3D_t x = {2, 4, 8}, y = {4, 7, 1};

    x.print();
    cout << "modulo: "<< x.modulo(y) << endl;

    return 0;
}
