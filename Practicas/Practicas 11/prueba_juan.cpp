#include <iostream>

using namespace std;

class Figura{
    public:
        virtual void dibujar(){
            cout << "Dibujando figura" << endl;
        }

};

class Triangulo : public Figura{
};

int main(){
    Triangulo a;

    a.dibujar();

    return 0;
}