#include <iostream>
#include <vector>
#include <array>

#define N 10

using namespace std;


void ImprimeVector(double Vector[], int NumElementos);
void ImprimeVector(vector<double> Vector, int NumElementos);
void ImprimeVector(array<double, N> Vector, int NumElementos);


int main(int argc, char **argv) {
    double v[N];
    array<double, N> arr;
    vector<double> vct(N);

    //Asignacion de valores
    for (int i = 0; i < N; i++){
        v[i] = rand();
        arr.at(i) = rand();
        vct[i] = rand();
    }

    cout << "v[0]: " << v[0] << " &v[0]: " << &v[0] << endl;
    cout << " &v: " << &v << endl;

    cout << "arr.at(0): " << arr.at(0) << " &arr.at(0): " << &arr.at(0) << endl;
    cout << "&arr: " << &arr << endl;

    cout << "vct[0]: " << vct[0] << " &vct[0]: " << &vct[0] << endl;
    cout << "&vct: " << &vct[0] << endl;
    
    ImprimeVector(v, N);
    ImprimeVector(arr, N);
    ImprimeVector(vct, N);

    cout << "v[0]: " << v[0] << " &v[0]: " << &v[0] << endl;
    cout << " &v: " << &v << endl;

    cout << "arr.at(0): " << arr.at(0) << " &arr.at(0): " << &arr.at(0) << endl;
    cout << "&arr: " << &arr << endl;

    cout << "vct[0]: " << vct[0] << " &vct[0]: " << &vct[0] << endl;
    cout << "&vct: " << &vct[0] << endl;

    return 0; 
}

void ImprimeVector(double Vector[], int NumElementos){
    for(int i = 0; i < NumElementos; i++)
        cout << Vector[i] << endl;
    cout << "Vector[0]: " << Vector[0] << " &Vector[0]: " << &Vector[0] << endl;
    cout << " &Vector: " << &Vector << endl;
}
void ImprimeVector(vector<double> Vector, int NumElementos){
    for(const auto &value : Vector){ cout << value << endl; }
    cout << "Vector.at(0): " << Vector[0] << " &Vector.at(0): " << &Vector[0] << endl;
    cout << " &Vector: " << &Vector << endl;

    
}
void ImprimeVector(array<double, N> Vector, int NumElementos){
    for(const auto &value : Vector){ cout << value << endl; }
    cout << "Vector[0]: " << Vector.at(0) << " &Vector[0]: " << &Vector.at(0) << endl;
    cout << " &Vector: " << &Vector << endl;
}