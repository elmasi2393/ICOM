#include <iostream>
#include <vector>
#include <array>

using namespace std;

class Figura {
    public:
        virtual void dibujar () const = 0;
};

class Cuadrado : public Figura {
    public:
        void dibujar () const{
            cout << "cuadrado" << endl;
        }
};

class Circulo : public Figura {
    public:
        void dibujar () const{
            cout << "circulo" << endl;
        }
};

class Triangulo : public Figura {
    public:
        void dibujar () const{
            cout << "triangulo " << endl;
            }
};


int main(){

    Figura * figuras [] = {new Cuadrado, new Circulo, new Triangulo};
    
    for (int i = 0; i <3 ; i++) {
        figuras[i]->dibujar();
    }

    return 0;
}