#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Punto2D {
    double X;
    double Y; 
};

struct Poligono {
    public:
        // construye un poligono cerrado con los vertices dados
        Poligono(const vector<Punto2D> &vertices);
        // retorna el perimetro del poligono
        double perimetro();
        // retorna el area del poligono
        double area();
    private:
        vector<Punto2D> vertices;
        double distancia(const Punto2D & begin, const Punto2D & end);
};

Poligono::Poligono(const vector<Punto2D> &vertices): vertices{vertices} {};

double Poligono::distancia(const Punto2D & begin, const Punto2D & end){
    return sqrt((end.X - begin.X)*(end.X - begin.X) + (end.Y - begin.Y)*(end.Y - begin.Y));
}

double Poligono::perimetro(){
    double perimetro = 0;

    for(int i = 0; i < this->vertices.size(); i++){
        perimetro += this->distancia(this->vertices.at(i), this->vertices.at((i+1) % this->vertices.size()));
    }

    return perimetro;
}

double Poligono::area(){
    double area = 0;

    for(int i=0; i<this->vertices.size()-1; i++){
        area += this->vertices.at(i).X * this->vertices.at(i+1).Y - this->vertices.at(i+1).X * this->vertices.at(i).Y;
    }
    //return 1/2 * (area + this->vertices.at(vertices.size()-1).X * this->vertices.at(0).Y - this->vertices.at(0).X * this->vertices.at(vertices.size()-1).Y);
    return 0.5 * abs((area + this->vertices.at(vertices.size()-1).X * this->vertices.at(0).Y - this->vertices.at(0).X * this->vertices.at(vertices.size()-1).Y));
}

int main(){

    vector<Punto2D> vertices {{0, 0}, {0, 1}, {1, 1}, {1, 0}};

    Poligono pol(vertices);

    cout << pol.perimetro() << endl;
    cout << pol.area() <<  endl;

    return 0;
}