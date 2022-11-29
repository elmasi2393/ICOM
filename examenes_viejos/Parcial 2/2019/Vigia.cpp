#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <vector>
#include <fstream>

#include <iostream>

using namespace std;

using Gris = unsigned char;

struct Punto2D {
    unsigned int x;
    unsigned int y;
};

class ImagenGris {
public:
    ImagenGris(const string &fname) {
        loadFrom(fname);
    }
    ImagenGris(size_t ancho_, size_t alto_): ancho(ancho_), alto(alto_){
        cout << "Construct" << endl;
        pixels.reserve(ancho * alto);
    }
    Gris getPixel(int i, int j) const{
        unsigned int index = ij2index(i, j);
        return pixels.at(index);
    }
    void setPixel(int i, int j, Gris color){
        // cout << "setPixel" << endl;
        unsigned int index = ij2index(i, j);
        pixels[index] = color;
    }
    size_t getAncho() const{ return ancho; }
    size_t getAlto() const{ return alto; }
    size_t getTamImage() const{ return pixels.size(); }
    Punto2D centroide() const{
        unsigned int X = 0;
        unsigned int Y = 0;
        unsigned int M = 0;
        cout << "Centroide" << endl;
        for(int i = 0; i < ancho; i++){ //Recorro a lo ancho
            unsigned int peso = 0;
            for(int j = 0; j < alto; j++){  //Busco el peso del pixel
                unsigned int index = ij2index(i, j);
                peso += pixels[index];
            }
            X += peso*i;    //Pondero la posicion por el peso
            M += peso;      //Sumo al peso total
        }
        X = X/M;    //Defino coordenada X del centro de masa

        M = 0;  //Redefino la masa en 0

        for(int i = 0; i < alto; i++){ //Recorro a lo alto
            unsigned int peso = 0;
            for(int j = 0; j < ancho; j++){  //Busco el peso del pixel
                unsigned int index = ij2index(j, i);
                peso += pixels[index];
            }
            Y += peso*i;    //Pondero la posicion por el peso
            M += peso;      //Sumo al peso total
        }
        Y = Y/M; //Defino coordenada Y del centro de masa

        return Punto2D{X, Y};

    }

    unsigned int ij2index(int i, int j) const{
        assert(i >= 0 && i < (int) ancho && j >= 0 && j < (int) alto);
        unsigned int pixelIndex = j * alto + i;
        // cout << "pixelIndex: " << pixelIndex << endl;
        // cout << "pixel size: " << pixels.size() << endl;
        // assert(pixelIndex < pixels.size());
        return pixelIndex;
    }

    void loadFrom(const string &fname) {
        ifstream f(fname);
        assert(f);
        f >> ancho >> alto;
        pixels.clear();
        pixels.reserve(ancho * alto);
        int c;
        while (f >> c)
            pixels.push_back(Gris(c));
        assert(ancho * alto == pixels.size());
    }

private:
    size_t ancho, alto;
    vector<Gris> pixels;
};

class CamProcessor {
public:
    CamProcessor(const ImagenGris &back, Gris th) : background(back), threshold(th) {}

    // Solicita el procesamiento de una nueva imagen proveniente
    // de la c�mara, el centroide de la imagen resta entre este nuevo frame
    // y el background ser� retornada como resultado del procesamiento
    Punto2D procFrame(const ImagenGris &frame) {
        cout << "Procesamiento imagen" << endl;

        ImagenGris result(frame.getAncho(), frame.getAlto());   //Construyo mi imagen de resultado
        // cout << result

        //Resta de imagenes
        for(int i = 0; i < frame.getAncho(); i++) {         //Recorro a lo ancho
            for(int j = 0; j < frame.getAlto(); j++) {      //Recorro a lo alto

                Gris level = frame.getPixel(i, j) - background.getPixel(i, j);  //Guardo la resta de los pixeles
                if(level < threshold){  //Si es menor a threshold pongo 0
                    result.setPixel(i, j, 0);
                }else{                  //Sino guardo el valor
                    result.setPixel(i, j, level);
                }
            }
        }

        return result.centroide();
    }
private:
    const ImagenGris background;   // imagen gris de fondo
    Gris threshold;                 // umbral de detecci�n
};


class FakeCam {
    public:
        FakeCam() : fnames({ "image1.img", "image2.img", "image3.img", "image4.img" }) {}

        void nextFrame(ImagenGris &img) {
            img.loadFrom(fnames[frame % fnames.size()]);
            frame++;
        }

    private:
        vector<string> fnames;
        int frame = 0;
};

int main()
{
    ImagenGris img("bg.img");
    CamProcessor vigia(img, 10);

    FakeCam cam;

    while (true) {
        cam.nextFrame(img);
        Punto2D c = vigia.procFrame(img);
        cout << "x: " << c.x << "  y: " << c.y << endl;
    }
}

