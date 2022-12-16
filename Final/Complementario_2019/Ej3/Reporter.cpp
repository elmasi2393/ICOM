#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct P2D {
    double x;
    double y;
};

// define la abstracción de un ReportRender, una entidad que es capaz de "dibujar" elementos sencillos de un documento
class ReportRender {
    public:
        virtual void drawText(const string text, const P2D &p) = 0;
        virtual void setFont(const string &fontName, int fontSz) = 0;
        virtual void setPenColor(unsigned int rgbColor) = 0;
        virtual void drawLine(const P2D &p1, const P2D &p2) = 0;
};

// implementacion de un ReportRender trucho, solo anuncia las acciones que le piden realizar junto a sus argumentos.
class FakeReporterRender : public ReportRender {
    // TODO
};


// Los reportes incluyen elementos fijos: textos, lineas, cajas, de diferentes colores o fonts
// y elementos variables que estan identificados por una clave, pero cuyos valores cambian de reporte en reporte.
// imaginar una factura de servicios, en donde hay una mayoria de elementos identicos en todas las facturas 
// (marcos, encabezados, logos, etc.) y hay elementos propios de cada factura (nombrte, domicilio, consumo, montos, etc.)
// La parte fija esta definida en un archivo template de reporte, los valores de los elementos variables 
// en un archivo de VariableData, con eso un reporte puede "renderizarse" varias veces con diferente VariableData.

// define el conjunto de valores de datos variable para un dato variable.
class ReportVariableData {
    public:
        // constructor que se inicializa tomando los pares <key, value> desde un archivo
        ReportVariableData(const string &fname)  {   // se los daria hecho
            ifstream in(fname);
            assert(in);
            string line;
            while (getline(in, line)) {
                std::istringstream is_line(line);
                std::string key;
                if (getline(is_line, key, '=')) {
                    std::string value;
                    if (getline(is_line, value)) {
                        vData[key] = value;
                    }
                }
            }
        }
        // retorna el valor del campo dado, o "" si no está presente
        string getFieldValue(const string &fieldName) const
        {
            // TODO
        }

    private:
        // los pares son almacenados en un mapa.
        map<string, string> vData;
};

// define la abstracción que representa un elemento de un reporte
// se le pide que sepa "renderizarse" sobre un ReportRender, utilizando los
// datos variables en caso que sea necesario.
class ReportAction
{
    public:
        virtual void operator()(ReportRender *, const ReportVariableData *) const = 0;
};

// identifica un texto fijo dentro del reporte.
// lo define un texto y su posicion
class TextReportAction: public ReportAction
{
    public:
        TextReportAction(const string &t, const P2D &p_)
            : text(t), p(p_) {}
        void operator()(ReportRender *rr, const ReportVariableData *rvd) const 
        {
            // TODO
        }
        static ReportAction *buildFromFile(ifstream &in) { 
            string text;
            P2D p;
            in >> text >> p.x >> p.y;
            return new TextReportAction(text, p);
        }
    private:
        string text;
        P2D p;
};

// representa un cambio de font en el reporte
// lo define el nombre y tamaño del font
class FontReportAction : public ReportAction
{
    public:
        FontReportAction(const string &fn, int sz_)
            : fontName(fn), sz(sz_) {}
        void operator()(ReportRender *rr, const ReportVariableData *rvd) const 
        {
            // TODO
        }
        static ReportAction *buildFromFile(ifstream &in) {  
            // TODO
        }
    private:
        string fontName;
        int sz;
};

// representa un cambio de lapiz para el dibujado de lineas/cajas
// lo define el ancho del lapiz
class PenReportAction : public ReportAction
{
    public:
        PenReportAction(unsigned int rgbColor_)
            : rgbColor(rgbColor_){}
        void operator()(ReportRender *rr, const ReportVariableData *rvd) const 
        {
            // TODO
        }
        static ReportAction *buildFromFile(ifstream &in) {
            // TODO
        }
private:
        unsigned int rgbColor;
};

// representa una linea dentro del reporte
// la define sus puntos extremos
class LineReportAction : public ReportAction
{
    public:
        LineReportAction(const P2D &p1_, const P2D & p2_)
            : p1(p1_), p2(p2_) {}
        void operator()(ReportRender *rr, const ReportVariableData *rvd) const 
        {
            // TODO
        }
        static ReportAction *buildFromFile(ifstream &in) { 
            // TODO
        }
    private:
        P2D p1;
        P2D p2;
};

// representa una caja dentro del reporte
// la define su vértice superior izquierdo, el ancho y el alto de la caja
class BoxReportAction : public ReportAction
{
    public:
        BoxReportAction(const P2D &p1_, int ancho_, int alto_)
            : p1(p1_), ancho(ancho_), alto(alto_) {}
        void operator()(ReportRender *rr, const ReportVariableData *rvd) const
        {
            // TODO
        }
        static ReportAction *buildFromFile(ifstream &in) {
            // TODO
        }

    private:
        P2D p1;
        int ancho, alto;
};

// representa un campo variable dentro del reporte
// lo define su key dentro de vdata y la posición donde se pondría
class VDataReportAction : public ReportAction
{
    public:
        VDataReportAction(const string &k, const P2D &p_)
            : key(k), p(p_) {}
        void operator()(ReportRender *rr, const ReportVariableData *rvd) const
        {
            // TODO
        }

        static ReportAction *buildFromFile(ifstream &in) { 
            // TODO
        }
    private:
        string key;
        P2D p;
};

// Representa una elemento que permite construir elementos de reporte a partir de un file
class Factory {
    public:
        Factory() {
            creators["TEXT"]  = TextReportAction::buildFromFile;
            creators["FONT"]  = FontReportAction::buildFromFile;
            creators["PEN"]   = PenReportAction::buildFromFile;
            creators["LINE"]  = LineReportAction::buildFromFile;
            creators["BOX"]   = BoxReportAction::buildFromFile;
            creators["FIELD"] = VDataReportAction::buildFromFile;
        }
        ReportAction *build(const string &objType, ifstream &in) const {
            auto f = creators.find(objType);
            if (f != creators.end())
                return f->second(in);
            assert(0);
            return nullptr;
        }

    private:
        using  CreatorFun = ReportAction* (*)(ifstream &in);
        map<string, CreatorFun> creators;

};

// representa todos los elementos de un reporte, esos elementos de alguna forma y ayudados por un
// Factory son leidos desde un archivo y colocados en un contenedor de elementos.
class ReportTemplate {
    public:
        ReportTemplate(const Factory &tf, const string &fname) {
            ifstream in(fname);
            assert(in);
            string name;
            while (in >> name) 
                actions.push_back(tf.build(name, in));
            
        }
        ~ReportTemplate() {
            // TODO
        }
        // le indica que se va a empezar a recorrer el reporte, debería colocar un iterador o un indice al comienzo 
        // del contenedor
        void start() { 
            // TODO
        }  

        // retorna la proxima accion o nullptr si ya no hay mas acciones
        const ReportAction *nextAction() 
        {
            // TODO
        }

        // finaliza el recorrido del reporte
        void end() {
            // TODO
        }


    private:
        vector<ReportAction *> actions;
        // TODO
        // ...
};


class Reporter {
    public:
        Reporter(const Factory &tf, const string &templateName, ReportRender *r)
            : repTemplate(tf, templateName), render(r) {}

        void doReport(string vDataFile) {      
            ReportVariableData vdata(vDataFile);

            repTemplate.start();
            const ReportAction *pAction;

            while ((pAction = repTemplate.nextAction()) != nullptr) {
                (*pAction)(render, &vdata);
            }
            repTemplate.end();
        }


    private:
        ReportTemplate repTemplate;
        ReportRender *render;

};

int main()
{
    FakeReporterRender frr;
    Factory tf;

    Reporter r(tf, "listado.template", &frr);

    r.doReport("vdp1.dat");
    r.doReport("vdp2.dat");
    return 0;
}

