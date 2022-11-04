#include <iostream>
#include <vector>

using namespace std;

class Figura {
    public:
    Figura(){
        cout << "Construyendo figura" << endl;
    }
        virtual void dibujar () const = 0;
        // virtual ~Figura();
    virtual ~Figura(){
        cout << "descontuyendo figuras.." << endl;
    }
};

class Cuadrado : public Figura {
    public:
        Cuadrado(){
            cout << "construyendo cuadrado" << endl;
        }
        void dibujar () const{
            cout << "cuadrado" << endl;
        }
        ~Cuadrado(){
            cout << "descontruyendo cuadrado" << endl;
        }
};

class Circulo : public Figura {
    public:
        Circulo (){
            cout << "construyendo circulo" << endl;

        }
        void dibujar () const{
            cout << "circulo" << endl;
        }
        ~Circulo (){
            cout << "Descontuyendo circulo" << endl;
            }
};

class Triangulo : public Figura {
    public:
        Triangulo() {
            cout << "construyendo triangulo" << endl;
        }
        void dibujar () const{
            cout << "triangulo " << endl;
            }
        ~Triangulo(){
            cout << "descontuyendo triangulo " << endl;
        }
};



int main(){

    vector<Figura *> figuras {new Cuadrado, new Circulo, new Triangulo};
    
    for (int i = 0; i <3 ; i++) {
        figuras[i]->dibujar();
    }

    for (auto &fig : figuras){
        delete fig;
    }

    return 0;
}