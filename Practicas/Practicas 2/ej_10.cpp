#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int r, g, b, color;

    cout << "Ingrese color rojo, verde y azul separado por espacios: ";
    cin >> hex >> r >> hex >> g >> hex >> b;

    color = r << 16 | g << 8 | b;

    cout << "r: " << hex << r << "g: " << hex << g << "b: " << hex << b << endl;
    cout << "color: " << hex << color << endl;


    return 0;
}