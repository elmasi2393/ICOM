#include <iostream>

#include <cmath>
#include <vector>
#include <list>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;
// define una coordenada bidimensional
struct P2D {
    double x, y;

    // M�todo que debe rotar el punto un dado 'angulo' en sentido anti-horario
    // alrededor del punto 'center'
    void rotate(const P2D &center, double angulo){
        double x_ = x - center.x;
        double y_ = y - center.y;
        double coseno = cos(angulo);
        double seno = sin(angulo);
        x = x_ * coseno - y_ * seno + center.x;
        y = x_ * seno + y_ * coseno + center.y;
    }
    // M�todo que debe desplazar el punto en el corrimiento dado
    void move(double deltaX, double deltaY){
        x += deltaX;
        y += deltaY;
    }

};

// clase abstracta que define una interface para la graficaci�n de
// primitivas gr�ficas elementales (l�neas, c�rculos, puntos)
class Renderer {
    public:
        // limpia el renderer
        virtual void clear() = 0;

        // Dibuja una l�nea
        virtual void line(P2D from, P2D to) = 0;

        // Dibuja un c�rculo
        virtual void circle(P2D center, double r) = 0;

        // Dibuja un punto
        virtual void point(P2D p) = 0;
};

// clase que deriva de Renderer y su �nica funci�n debe ser anunciar (imprimir) las
// operaciones que le son solicitadas (con sus argumentos).
class FakeRenderer : public Renderer{
    public:
        void clear(){
            cout << "clear" << endl;
        }
        void line(P2D from, P2D to){
            cout << "line from (" << from.x << ", " << from.y << ") to (" << to.x << ", " << to.y << ")" << endl;
        }
        void circle(P2D center, double r){
            cout << "circle at (" << center.x << ", " << center.y << ") with radius " << r << endl;
        }
        void point(P2D p){
            cout << "point at (" << p.x << ", " << p.y << ")" << endl;
        }
};

// predeclaraci�n
class Shape;

// define un contenedor de formas,
class ShapeContainer
{
    public:
        // Destructor, tiene que hacerse cargo de los objetos contenidos
        ~ShapeContainer(){

        }

        // agrega una nueva forma, es colocada al tope del z-order, retorna el mismo objeto agregado
        Shape* addShape(Shape *f){
            shapes.push_back(f);
            return f;
        }

        // remueve la forma y retorna el mismo objeto (si no exist�a, retorna nullptr)
        Shape* removeShape(Shape *f){
            for(auto it=shapes.begin(); it!=shapes.end(); it++){
                if((*it) == f){
                    shapes.erase(it);
                    return *it;
                }
            }
            return nullptr;
        }

        // lleva la forma 'f' al tope del z-order
        void bringToFront(Shape *f){
            for(auto it=shapes.begin(); it!=shapes.end(); it++){
                if((*it) == f){
                    shapes.push_back(*it);
                    shapes.erase(it);
                    break;
                }
            }
        }

        // lleva la forma 'f' al fondo del z-order
        void sendToBack(Shape *f){
            cout << shapes.size() << endl;
            for(auto it=shapes.begin(); it!=shapes.end(); it++){
                if((*it) == f){
                    shapes.push_front(*it);
                    shapes.erase(it);
                    break;
                }
            }
        }

    protected:
        // contenedor de hijos polim�rficos
        // ToDo: elija el tipo de contenedor adecuado
        list<Shape*> shapes;
};
// Define la clase abstracta Shape y su interfase
class Shape
{
    public:
        // construye un Shape.
        Shape(ShapeContainer *parent_): parent(parent_) {}

        virtual ~Shape() {
            delete parent;
        }

        // se dibuja utilizando un dado renderer
        virtual void draw(Renderer &renderer) const = 0;  // ToDo

        // se desplaza un dado corrimiento
        virtual void move(double deltaX, double deltaY) = 0; // ToDo

        // rota la forma un dado 'angulo' en sentido anti-horario sobre un dado 'centro'
        virtual void rotate(P2D centro, double angulo) = 0; // ToDo

        // rota la forma un dado 'angulo' sobre su propio centro
        virtual void rotate(double angulo) = 0; // ToDo

        // lleva al objeto al tope del z-order entre su hermanos
        void bringToFront(){
            if(parent != nullptr)
                parent->bringToFront(this);
        }

        // lleva al objeto al fondo del z-order entre su hermanos
        void sendToBack(){
            if(parent != nullptr)
            	parent->sendToBack(this);
        }

    private:
        ShapeContainer *parent;
};

// define un gr�fico, compuestos de 0 o mas formas con un dado z-order
class Canvas : public ShapeContainer
{
    public:
        // solicita dibujar todas las formas del gr�fico
        void draw(Renderer &renderer){
            for(auto it=shapes.begin(); it!=shapes.end(); it++){
                (*it)->draw(renderer);
            }
        }

        // solicita mover todas las formas del gr�fico
        void move(double deltaX, double deltaY){
            for(auto it=shapes.begin(); it!=shapes.end(); it++){
                (*it)->move(deltaX, deltaY);
            }
        }

        // solicita rotar todas las formas del gr�fico
        void rotate(P2D centro, double angulo){
            for(auto it=shapes.begin(); it!=shapes.end(); it++){
                (*it)->rotate(centro, angulo);
            }
        }
};

// Define una l�nea como forma, debe implementar su interface
class Line : public Shape{
    public:
        Line(ShapeContainer *parent_, P2D from_, P2D to_): Shape(parent_), from(from_), to(to_) {}

        void draw(Renderer &renderer) const{
            renderer.line(from, to);
        }

        void move(double deltaX, double deltaY){
            from.move(deltaX, deltaY);
            to.move(deltaX, deltaY);
        }

        void rotate(P2D centro, double angulo){
            from.rotate(centro, angulo);
            to.rotate(centro, angulo);
        }

        void rotate(double angulo){
            P2D centro = {(from.x + to.x)/2, (from.y + to.y)/2};
            from.rotate(centro, angulo);
            to.rotate(centro, angulo);
        }

    private:
        P2D from;
        P2D to;
};

// Define un pol�gono como forma, debe implementar su interface
class Polygon : public Shape{
    public:
        Polygon(ShapeContainer *parent_, vector<P2D> points_): Shape(parent_), points(points_) {}

        void draw(Renderer &renderer) const{
            for(int i = 0; i < points.size(); i++){
                renderer.line(points[i], points[(i+1)%points.size()]);
            }
        }

        void move(double deltaX, double deltaY){
            for(auto it=points.begin(); it!=points.end(); it++){
                (*it).move(deltaX, deltaY);
            }
        }

        void rotate(P2D centro, double angulo){
            for(auto it=points.begin(); it!=points.end(); it++){
                (*it).rotate(centro, angulo);
            }
        }

        void rotate(double angulo){
            P2D centro = {0, 0};
            for(auto it=points.begin(); it!=points.end(); it++){
                centro.x += (*it).x;
                centro.y += (*it).y;
            }
            centro.x /= points.size();
            centro.y /= points.size();
            for(auto it=points.begin(); it!=points.end(); it++){
                (*it).rotate(centro, angulo);
            }
        }

    private:
        vector<P2D> points;
};

// Define un c�rculo como forma, debe implementar su interface
class Circle : public Shape{
    public:
        Circle(ShapeContainer *parent_, P2D center_, double radius_): Shape(parent_), center(center_), radius(radius_) {}

        void draw(Renderer &renderer) const{
            renderer.circle(center, radius);
        }

        void move(double deltaX, double deltaY){
            center.move(deltaX, deltaY);
            }

        void rotate(P2D centro, double angulo){
            center.rotate(centro, angulo);
        }

        void rotate(double angulo){
            center.rotate(center, angulo);
        }

    private:
        P2D center;
        double radius;
};


// Main para probar el ejercicio
int main()
{
    // genero un Canvas
    Canvas c;
    
    // le agrego Shapes quedandome con los punteros como para manipularlos
    Shape *shapes[] =
    {
        c.addShape(new Line(&c, P2D{0,1}, P2D{1, 0})),
        c.addShape(new Polygon(&c, {{0,0}, { 1, 0}, { 1, 1}, {0, 1}, { 0, 0 }})),
        c.addShape(new Circle(&c, P2D{0.5, 0.5}, 0.5))
    };
    
    // Creo un Remderer
    FakeRenderer r;
    cout << "Line" << endl;
    r.clear();
    c.draw(r);

    // manipulo formas/canvas
    cout << "Polygon" << endl;
    shapes[2]->sendToBack();
    r.clear();
    c.draw(r);

    c.move(1, 1);
    c.rotate({0,0}, M_PI/2);
    r.clear();
    c.draw(r);
    cout << "Circle" << endl;
    shapes[2]->bringToFront();
    r.clear();
    c.draw(r);

    cout << "Termina" << endl;

    return 0;
}
