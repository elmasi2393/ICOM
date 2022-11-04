#include <iostream>
#include <cmath>

using namespace std;

struct Punto2D {
    double x; /** Posicion x del punto en cartesiana */
    double y; /** Posicion y del punto en cartesiana */
    //Defino este operador para cambiar facilmente el vector entre dos puntos (ej: V_0_1 + -V_1_0)
    Punto2D operator*(int c) {return {c*x, c*y}; }
};

/**
 * @brief Triangulo
 * @p Estructura que permite determianr un angulo por medio de sus puntos
 * 
 * @param Punto2D[3]
 * 
 */
struct Triangulo {
    Punto2D vertices[3]; /** vertices array */

    enum ClaseLado   { EQUILATERO, ISOCELES, ESCALENO }; /** enumeracion con clases de lados*/
    enum ClaseAngulo { ACUTANGULO, RECTANGULO, OBTUSANGULO }; /**enumeracion con clases de angulos*/
    
    /**
     * @brief constructVector
     * @p Contruye un vector a traves de dos puntos
     * @param startSeg 
     * @param endSeg 
     * @return Punto2D 
     */
    Punto2D constructVector(Punto2D startSeg, Punto2D endSeg) {return {endSeg.x - startSeg.x, endSeg.y - startSeg.y};}

    /**
     * @brief modulo
     * @p obtiene el modulo de un VECTOR
     * @param startSeg 
     * @param endSeg 
     * @return double 
     */
    double modulo(Punto2D startSeg, Punto2D endSeg){ return sqrt((endSeg.x - startSeg.x)*(endSeg.x - startSeg.x) + (endSeg.y - startSeg.y)*(endSeg.y - startSeg.y)); }

    /**
     * @brief prod_escalar
     * @p Realiza el producto escalar ENTRE VECTORES
     * @p Posible mejora: pasarle los puntos y que construya el vector
     * @param startSeg 
     * @param endSeg 
     * @return double 
     */
    double prod_escalar (Punto2D startSeg, Punto2D  endSeg) {return (startSeg.x * endSeg.x + startSeg.y * endSeg.y);}

    /**
     * @brief clasificaPorLado
     * @p Clasifica al triangulo por sus Lados (EQUILATERO, ISOCELES y ESCALENO)
     * @return ClaseLado 
     */
    ClaseLado clasificaPorLado() {
        //Primero se obtiene el modulo de cada lado
        double mod_v1 = modulo(vertices[0], vertices[1]);
        double mod_v2 = modulo(vertices[0], vertices[2]);
        double mod_v3 = modulo(vertices[1], vertices[2]);

    
        if(mod_v1 == mod_v2 && mod_v2 == mod_v3) {return EQUILATERO;}                   //Si todos son iguales es EQUILATERO
        if(mod_v1 == mod_v2 || mod_v1 == mod_v3 || mod_v2 == mod_v3) {return ISOCELES;} //Si al menos dos son iguales es ISOCELES
        else {return ESCALENO;}                                                         //Sino es ESCALENO
    }

    /**
     * @brief clasificaPorAngulo
     * @p clasifica al triangulo por sus angulos
     * @return ClaseAngulo 
     */
    ClaseAngulo clasificaPorAngulo(){
        //Construyo los lados necesarios
        Punto2D v_0_1 = constructVector(vertices[0], vertices[1]);
        Punto2D v_0_2 = constructVector(vertices[0], vertices[2]);
        Punto2D v_1_2 = constructVector(vertices[1], vertices[2]);

        //Calculo los cosenos de los angulos
        double cos_1 = prod_escalar(v_0_1, v_0_2);
        double cos_2 = prod_escalar(v_0_1*(-1), v_1_2);
        double cos_3 = prod_escalar(v_0_2*(-1), v_1_2*(-1));


        if(cos_1 == 0 || cos_2 == 0 || cos_3 == 0) { return RECTANGULO; }   //Si un coseno es 0, significa que es RECTANGULO
        if(cos_1 > 0 && cos_2 > 0 && cos_3 > 0) { return ACUTANGULO; }      //Si todos los cosenos son mayores a 0, es ACUTANGULO
        else{ return OBTUSANGULO; }     //Sino es OBTUSANGULO
    }


};

int main(){
    Triangulo t1 = {{{0, 0}, {1, 2}, {-1, 0.78}}};

    switch(t1.clasificaPorLado()){
        case t1.EQUILATERO: cout << "EQUILATERO" << endl; break;
        case t1.ISOCELES: cout << "ISOCELES" << endl; break;
        case t1.ESCALENO: cout << "ESCALENO" << endl; break;
        default: cout << "ERROR" << endl; break;
    }

    switch(t1.clasificaPorAngulo()){
        case t1.ACUTANGULO: cout << "ACUTANGULO" << endl; break;
        case t1.RECTANGULO: cout << "RECTANGULO" << endl; break;
        case t1.OBTUSANGULO: cout << "OBTUSANGULO" << endl; break;
        default: cout << "ERROR" << endl; break;
    }
    return 0;
}