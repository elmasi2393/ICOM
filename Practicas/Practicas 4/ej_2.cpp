#include <iostream>
#include <cmath>

using namespace std;

enum Direction {  LEFT, RIGHT, UP, DOWN, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT, NONE, NUM_DIRS }; // enumeración de las posibles direcciones (la última es auxiliar)

struct Entity { //Tipo definido por el usuario para representar a la entidad representación: 2 enteros para representar la posición
    int x, y;

/**
 * @brief move
 * @p: Permite desplazarte en una posicion
 * @param d: Direccion donde moverse
 */
void move(Direction d) {// método para mover la entidad en una dirección determinada

    switch(d) {
            case LEFT:  x--; break;
            case RIGHT: x++; break;
            case UP:    y++; break;
            case DOWN:  y--; break;
            case UP_RIGHT: x++; y++; break;
            case UP_LEFT: x--; y++; break;
            case DOWN_RIGHT: x++; y--; break;
            case DOWN_LEFT: x--; y--; break;
            case NONE:  break;
            default: break; // si llega hasta acá debería disparar una excepcion }
    }
}
/**
 * @brief experimento
 * @p: realiza N movimientos al azar partiendo del origen
 * @param N: numeros de movimientos
 * @return double: Distancia al origen
 */
double experimento(int N){
    Entity e = { 0, 0 };
    for(int contador = 0; contador < N; contador++){ e.move(Direction(rand() % NUM_DIRS)); }
    
    return sqrt(e.x*e.x + e.y*e.y);
    }
/**
 * @brief experimentos
 * @p: realiza M veces experimento(N)
 * @param M  Numero de veces a realizar experimento
 * @param N  Numero de movimientos realizado en experimento
 * @return double: Distancia promedio de los M experimento
 */
double experimentos(int M, int N){
    double dist_prom = 0, a = 0;
    for (int i = 0; i < M; i++) { dist_prom += experimento(N); }

    return dist_prom/M;
}
void print() { // método para imprimir la posición y distancia al origen
cout << "X: " << x << " Y: " << y << " Dist.: " << sqrt(x*x+y*y) << '\n'; }

};

const int NUM_PASOS = 500;

int main(int argc, char **argv){
    Entity e = { 0, 0 };

    srand(time(0)); // Inicializa generador pseudo-aleatorio

    // for(int contador = 0; contador < NUM_PASOS; contador++){
    //     e.move(Direction(rand() % NUM_DIRS));
    //     e.print();
    // }
    // cout << "\n \n";
    // e.print();

    // cout << "experimento = " << e.experimento(23)<< endl;
    // cout << "experimentos = " << e.experimentos(10, 23) << endl;

    // e.print();
cout << "| N | " << "| Distancia promedio |" << endl;
    for (int i = 0; i <NUM_PASOS; i++){
        cout << "| " << i << " |     " << e.experimentos(10000, i) << " |" << endl;
    }

    return 0; 
}