#include <vector>
#include <array>
#include <iostream>
#include <fstream>

using namespace std;

// cada celda de un cuerpo escaneado esta represendado por un valor "resonante" representado por una
// intensidad: un valor entero, sin signo en el intervalo [0,255]
using Celda = unsigned char;


const unsigned int SCAN_LINE_SZ    = 128;
const unsigned int LINES_PER_PLANE = 128;


// define una l�nea de scan (direcci�n X)
using ScanLine  = array<Celda,    SCAN_LINE_SZ>;

// define un plano de scan (direcci�n X,Y)
using ScanPlane = array<ScanLine, LINES_PER_PLANE>;

// define un vol�men de scan (direcci�n X,Y,Z)
using ScanBody  = vector<ScanPlane>;

class ScanAnalyzer {
    public:
        // La estructura Sensitivity define la sensibilidad a ser aplicada en el analisis de una
        // imagen escaneada. La sensibilidad esta caracterizada por 2 par�metros
        struct Sensitivity {
            // definen el rango de detecci�n de los puntos (ver enunciado)
            Celda  minValue;
            Celda  maxValue;

            // define la minima proporcion [0, 1.0] de puntos de un plano (en Z) que deben ser sospechosos para que
            // el plano sea sospechoso (0: 0%, 1.0: 100%) (ver enunciado)
            double umbral; 
        };

        // analiza la imagen 'image' y retorna un vector de todos los planos (identificado por �ndice de plano)
        // que son sospechosos dado la sensibilidad dada por 'params'
		vector<unsigned int> doWork(const ScanBody& image, const Sensitivity& params);          // TODO

    private:
		bool puntoSospechoso(const ScanBody& image, const Sensitivity& params, int x, int y, int z);  // TODO
		bool planoSospechoso(const ScanBody& image, const Sensitivity& params, int z);               // TODO
};

bool ScanAnalyzer::puntoSospechoso(const ScanBody& image, const Sensitivity& params, int x, int y, int z){


	return true;
};



// fake scan image generation
#define _USE_MATH_DEFINES
#include <math.h>

ScanBody genImage()
{
	const unsigned int BODY_LEN = 256;
	ScanBody img;
	for (unsigned int z = 0; z < BODY_LEN; z++) {
		ScanPlane sp;
		double modulador = sin(z * M_PI / BODY_LEN);
		modulador *= modulador;
		modulador *= modulador;
		for (unsigned int y = 0; y < LINES_PER_PLANE; y++) {
			for (unsigned int x = 0; x < SCAN_LINE_SZ; x++) {
				double xf = (x * M_PI / SCAN_LINE_SZ) - M_PI / 2;
				double yf = (y * M_PI / LINES_PER_PLANE) - M_PI / 2;
				double val = cos(xf) * cos(yf);
				val *= modulador;
				sp[y][x] = (unsigned char) (val*255);
			}
		}
		img.push_back(sp);
	}
	return img;
}

int main()
{
	cout << "Generando imagen trucha...\n";
	ScanBody image = genImage();
	cout << "imagen generada...\n";

	ScanAnalyzer analyzer;
	ScanAnalyzer::Sensitivity  s = { 150, 200, 0.10 };

	cout << "Procesando...\n";
	vector<unsigned int> planos = analyzer.doWork(image, s);
	cout << "Completed...\n";
	for (auto x : planos)
		cout << "El plano " << x << " es sospechoso\n";


	return 0;
}