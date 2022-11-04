#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct P2D_t {
    double X;
    double Y; 
void print(){ cout << "X: " << X << " -  Y: " << Y << endl; }
};

/**
 * @brief contruct_vector
 * @p contruye un vector a partir de dos puntos
 * @param startSeg 
 * @param endSeg 
 * @return P2D_t 
 * @retval vector contruido a partir de dos puntos
 */
P2D_t constructVector(P2D_t startSeg, P2D_t endSeg) {return {endSeg.X - startSeg.X, endSeg.Y - startSeg.Y};}

/**
 * @brief product_X
 * @p realiza el producto cruz entre dos vectores.
 * @param p_Start inicio del primer vector
 * @param p_End fin del primer vector
 * @param q_Start inicio del segundo vector
 * @param q_End fin del segundo vector
 * @return double 
 */
double product_X(P2D_t p_Start, P2D_t p_End, P2D_t q_Start, P2D_t q_End){ 
    P2D_t p = constructVector(p_Start, p_End);
    P2D_t q = constructVector(q_Start, q_End);

    return (q.X * p.Y) - (q.Y * p.X); 
    }

double modulo(P2D_t startSeg, P2D_t endSeg) { return sqrt((endSeg.X-startSeg.X)*(endSeg.X-startSeg.X) + (endSeg.Y-startSeg.Y)*(endSeg.Y-startSeg.Y)); }


/**
 * @brief isOnTheRight
 * @p Indica si un punto esta a la derecha, izquierda o es coincidente a un segmento
 * @param point 
 * @param startSeg 
 * @param endSeg 
 * @return int 
 * @retval 1 Si esta a la derecha
 * @retval -1 Si esta a la izqueirda
 * @retval 0 Si son coincidentes
 */
int isOnTheRight(P2D_t point, P2D_t startSeg, P2D_t endSeg){
    if(product_X(startSeg, endSeg, startSeg, point) > 0) {return 1;}
    else if(product_X(startSeg, endSeg, startSeg, point) < 0) {return -1;}
    else {return 0;}
}

/**
 * @brief areOnTheSame
 * 
 * @param startSeg 
 * @param endSeg 
 * @param points 
 * @return int
 * @retval 1 si estan todos a la derecha
 * @retval -1 si estan todos a la izquierda
 * @retval 0 si hay algunos a la izquierda y algunos a la derecha
 */
int areOnTheSame(P2D_t startSeg, P2D_t endSeg, vector<P2D_t> points){
    int flag = 0;   //Inicializo una flag como 0
    for(int i = 0; i < points.size(); i++){
        int direccion = isOnTheRight(points.at(i), startSeg, endSeg);

        if(direccion > 0) { flag = 1; }
        else if(direccion < 0 && flag == 1) { return 0; }    //Devuelvo 0 si detecto que son diferentes
        else if(direccion == 0) {continue;}
        else{ flag = -1;}
    }
    return flag; //Devuelvo 1 si estan a la derecha y -1 si estan a la izquierda
}
// Retorna 1 si el polígono recibido es convexo, 0 en caso contrario
// Recibe un polígono como un vector de vértices
int isConvexPolygon( vector<P2D_t> polygon ){
    int flag = 0;
    for(int i=0; i<polygon.size(); i++) {
        int direccion = areOnTheSame(polygon.at(i), polygon.at((i+1) % polygon.size()), polygon);

        if(direccion == 0) { return 0;}  //Si los puntos no estan en el mismo lado no es convexo
        if(direccion == 1 && flag == -1) { return 0; } //Si detectamos uno a la derecha y antes estaban todos a la izquierda, devuelvo 0
        else if(direccion == 1) { flag = 1; }   //Si los puntos estan a la derecha, levanto el flag
        else if(direccion == -1 && flag ==1) {return 0;}    //Si estaban a la derecha y ahora estan a la izquierda, no es convexo
        else if(direccion == -1) {flag = -1;} //Si estan a la izquierda sin antes haber uno a la derecha, establezco en -1
    }

    return 1;
}
double angleToPoint(P2D_t point, P2D_t pStart, P2D_t pEnd){ return asin((product_X(point, pStart, point, pEnd))/(modulo(point, pStart)*modulo(point, pEnd))); }

// Retorna 1 si el punto es interior, 0 en caso contrario
// Recibe un punto y el polígono como vector de vértices
int isInside( P2D_t point, vector<P2D_t> polygon ){
    double angle = 0;
    for (int i = 0; i < polygon.size(); i++){
        double angle_med= angleToPoint(point, polygon.at(i), polygon.at((i+1) % polygon.size()));
        angle += angle_med;
        // cout << "angle: " << angle_med << endl;
    }
    if(angle < 0.00001) {return 0;}
    else {return 1;}
}

int main(int argc, char **argv){
    // P2D_t p1 = {0, 0}, p2 = {1, 1}, p3 = {-2, 1}, p4 = {3, 1};
    vector<P2D_t> polygon ({{0,0}, {0,1}, {1,1}, {1,0}});

    // cout << isOnTheRight(p3, p1, p2) << endl;
    // cout << isOnTheRight(p4, p1, p2) << endl;
    cout << isConvexPolygon(polygon) << endl;
    cout << isInside({2, 2}, polygon) << endl;

    // a.print();
    // for (int i = 0; i < polygon.size(); i++) { polygon.at((i+1) % polygon.size()).print(); }

    return 0;  
}
