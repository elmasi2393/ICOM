#include <iostream>

#include <cmath>
#include <vector>
#include <list>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// define una coordenada bidimensional
struct P2D {
    double x, y;

    // Método que debe rotar el punto un dado 'angulo' en sentido anti-horario
    // alrededor del punto 'center'
    void rotate(const P2D &center, double angulo);  // ToDo

    // Método que debe desplazar el punto en el corrimiento dado
    void move(double deltaX, double deltaY);        // ToDo

};

// clase abstracta que define una interface para la graficación de
// primitivas gráficas elementales (líneas, círculos, puntos)
class Renderer {
    public:
        // limpia el renderer
        virtual void clear() = 0;

        // Dibuja una línea
        virtual void line(P2D from, P2D to) = 0;

        // Dibuja un círculo
        virtual void circle(P2D center, double r) = 0;

        // Dibuja un punto
        virtual void point(P2D p) = 0;
};

// clase que deriva de Renderer y su única función debe ser anunciar (imprimir) las
// operaciones que le son solicitadas (con sus argumentos).
class FakeRenderer : public Renderer{
    // ToDo
};

// predeclaración
class ShapeContainer;

// Define la clase abstracta Shape y su interfase
class Shape
{
    public:
        // construye un Shape.
        Shape(ShapeContainer *parent_); // ToDo

        virtual ~Shape() { }

        // se dibuja utilizando un dado renderer
        virtual void draw(Renderer &renderer) const = 0;  // ToDo

        // se desplaza un dado corrimiento
        virtual void move(double deltaX, double deltaY) = 0; // ToDo

        // rota la forma un dado 'angulo' en sentido anti-horario sobre un dado 'centro'
        virtual void rotate(P2D centro, double angulo) = 0; // ToDo

        // rota la forma un dado 'angulo' sobre su propio centro
        virtual void rotate(double angulo) = 0; // ToDo

        // lleva al objeto al tope del z-order entre su hermanos
        void bringToFront(); // ToDo

        // lleva al objeto al fondo del z-order entre su hermanos
        void sendToBack(); // ToDo

    private:
        ShapeContainer *parent;
};


// define un contenedor de formas,
class ShapeContainer
{
    public:
        // Destructor, tiene que hacerse cargo de los objetos contenidos
        ~ShapeContainer(); // ToDo

        // agrega una nueva forma, es colocada al tope del z-order, retorna el mismo objeto agregado
        Shape* addShape(Shape *f); // ToDo

        // remueve la forma y retorna el mismo objeto (si no existía, retorna nullptr)
        Shape* removeShape(Shape *f); // ToDo

        // lleva la forma 'f' al tope del z-order
        void bringToFront(Shape *f); // ToDo

        // lleva la forma 'f' al fondo del z-order
        void sendToBack(Shape *f); // ToDo

    protected:
        // contenedor de hijos polimórficos
        // ToDo: elija el tipo de contenedor adecuado
};

// define un gráfico, compuestos de 0 o mas formas con un dado z-order
class Canvas : public ShapeContainer
{
    public:
        // solicita dibujar todas las formas del gráfico
        void draw(Renderer &renderer); // ToDo

        // solicita mover todas las formas del gráfico
        void move(double deltaX, double deltaY);  // ToDo

        // solicita rotar todas las formas del gráfico
        void rotate(P2D centro, double angulo);   // ToDo
};

// Define una línea como forma, debe implementar su interface
class Line : public Shape
{
    // ToDo
};

// Define un polígono como forma, debe implementar su interface
class Polygon : public Shape
{
    // ToDo
};

// Define un círculo como forma, debe implementar su interface
class Circle : public Shape
{
    // ToDo
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
    r.clear();
    c.draw(r);

    // manipulo formas/canvas
    
    shapes[2]->sendToBack();
    r.clear();
    c.draw(r);

    c.move(1, 1);
    c.rotate({0,0}, M_PI/2);
    r.clear();
    c.draw(r);

    shapes[2]->bringToFront();
    r.clear();
    c.draw(r);

    return 0;
}
