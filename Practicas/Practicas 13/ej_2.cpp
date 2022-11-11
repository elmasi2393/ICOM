#include <iostream>

using namespace std;

template<class T> struct CoordenadaCartesiana3D{
    T x;
    T y;
    T z;

    void print(){
        cout << "x: " << x << ", y: " << y << ", z: " << z << endl;
    }
}; 

int main(){
    CoordenadaCartesiana3D<double> c1 {2.5, 6.7, 8.9};
    CoordenadaCartesiana3D<int> c2 {3, 8, 12};

    c1.print();
    c2.print();

    return 0;

}