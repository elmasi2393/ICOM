#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

enum Direction {  LEFT, RIGHT, UP, DOWN, NUM_DIRS }; // enumeración de las posibles direcciones (la última es auxiliar)

struct Punto2D{
    int x, y;
    bool operator==(const Punto2D &p) const { return (x == p.x) && (y == p.y); }
    Punto2D &operator=(const Punto2D &p) { x = p.x; y = p.y; return *this; }
};

struct Entity { //Tipo definido por el usuario para representar a la entidad representación: 2 enteros para representar la posición
    Punto2D pos {0, 0};
    vector<Punto2D> path;


    /**
     * @brief move
     * @p: Permite desplazarte en una posicion
     * @param d: Direccion donde moverse
     */
    bool move(Direction d) {// método para mover la entidad en una dirección determinada
        switch(d) {
                case LEFT: 
                    if(!chequeaPaso(Punto2D{pos.x-1, pos.y}))   //Si no puedo dar el paso
                        return false;
                    pos.x -= 1; //Sino voy a la izquierda
                    path.push_back(pos); //Agrego al path
                    return true;
                case RIGHT:
                    if(!chequeaPaso(Punto2D{pos.x+1, pos.y}))   //Si no puedo dar el paso
                        return false;
                    pos.x += 1; //Sino voy a la derecha
                    path.push_back(pos); //Agrego al path
                    return true;
                case UP:
                    if(!chequeaPaso(Punto2D{pos.x, pos.y+1}))   //Si no puedo dar el paso
                        return false;
                    pos.y += 1; //Sino voy a arriba
                    path.push_back(pos); //Agrego al path
                    return true;
                case DOWN:
                    if(!chequeaPaso(Punto2D{pos.x, pos.y-1}))   //Si no puedo dar el paso
                        return false;
                    pos.y -= 1; //Sino voy a abajo
                    path.push_back(pos); //Agrego al path
                    return true;
                default: return false; // si llega hasta acá debería disparar una excepcion }
        }
        
    }
    int pathLen(){ return path.size(); }
    void reset(){ path.clear(); pos = {0, 0};}
    
    bool chequeaPaso(Punto2D pos){
        for(Punto2D &a: path)
            if(a == pos) return false;
        return true;
    }


};


int main(){
    srand(time(0)); // Inicializa generador pseudo-aleatorio

    const int NUM_CASOS = 1000;
    const int MAX_PASOS = 10000;
    Entity e;
    for (int caso = 0; caso < NUM_CASOS; caso++) { 
        e.reset();  // resetea el camino de la entidad, como si empezara nuevamente
    for (int paso = 0; paso < MAX_PASOS; paso++) {
        // el método move debe retornar true si se pudo realizar el paso, o false
        // si el movimiento pasa por una posición ya visitada
        if(!e.move(Direction(rand() % NUM_DIRS)) )
            break;
        }
        cout << e.pathLen() << endl;
    }

    return 0;
}