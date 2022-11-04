#include <iostream>
/*
La clase base tiene un elemento de tipo entero, por ende tiene como tamanio r bytes
En cambio, la clase Deriv, al agregar otro atributo de tipo int agrega 4 bytes, por ende
el temenio de esta es mayor

*/

using namespace std;

/**
 * @brief Base class
 * @p La clase Base tiene solo un atributo de tipo int
 */
class Base{
    private:
        int miembro_b;
};

/**
 * @brief Deriv class
 * @p la clase Deriv hereda de la clase base y agrega un atributo propio de tipo entero
 */
class Deriv : public Base{
    public:
        int get() const { return miembro_d; }
    private:
        int miembro_d = 0;
};

/**
 * @brief f
 * @p toma un valor de tipo Base e imprime su tamanio
 * 
 * @param b type Base
 * 
 */
void f(Base b){
    cout << sizeof(b) << endl;
    // cout << b.get() << endl;    //No puedo ya que la clase get no tiene el metodo

}

int main(){
    //Creo objeto de tipo base
    Deriv b;

    // Imprimo el tamanio del objeto
    cout << sizeof(b) << endl;
    cout << b.get() << endl;

    //La funcion f permite recibir valores de un objeto de clase heredada, pero solamente usa los atributos presentes en la clase base
    f(b);

    return 0;
}