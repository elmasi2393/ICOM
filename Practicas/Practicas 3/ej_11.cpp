#include <iostream>

using namespace std;

struct P2D_t {
    double X;
    double Y; 
void print(){
    cout << "X: " << X << " -  Y: " << Y << endl; 
}

double product_X(P2D_t p){ return (p.X * Y) - (p.Y * X); }

P2D_t contruct_vector(P2D_t endSeg){ return {endSeg.X - X, endSeg.Y - Y};}    
};

int isOnTheRight(P2D_t point, P2D_t startSeg, P2D_t endSeg);

int main(int argc, char **argv){
    P2D_t p1 = {0, 0}, p2 = {1, 1}, p3 = {-2, 1}, p4 = {3, 1};
    cout << isOnTheRight(p3, p1, p2) << endl;
    cout << isOnTheRight(p4, p1, p2) << endl;

    return 0;  
}

int isOnTheRight(P2D_t point, P2D_t startSeg, P2D_t endSeg){
    if( startSeg.contruct_vector(endSeg).product_X(startSeg.contruct_vector(point)) > 0) { return 1; }
    else if( startSeg.contruct_vector(endSeg).product_X(startSeg.contruct_vector(point)) < 0) { return -1; }
    else{ return 0;}
}