#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

enum Color {
	NEGRO,
	BLANCO,
};

class MonoImg {
	public:
		// crea una imagen de un dado color (BLANCO por defecto)
		MonoImg(size_t ancho_, size_t alto_, Color c = BLANCO){
			assert(ancho_ > 0 && alto_ > 0);	//Vemos si el tamanio es valido

			ancho = ancho_;
			alto = alto_;
			image = new unsigned int [alto*((ancho+31)/32)];	//Creo el arreglo valido para la imagen
			// cout << "Image: " << alto*((ancho+31)/32) << endl;
			unsigned int value;
			if(c)	//Si la establesco en blanco, asigno todos en uno
				value = 0xFFFFFFFF;
			else 	//Sino todos en nego
				value = 0x00000000;
			for(int i = 0; i < alto*((ancho+31)/32); i++){
				image[i] = value;
				// cout << image[i] << endl;
			}
		}
		// destruye la im�gen (libera todos sus recursos)
		~MonoImg(){
			delete [] image;
		}

		// retorna el ancho de la imagen
		size_t getWidth() const { return ancho;}

		// retorna el alto de la imagen
		size_t getHeight() const{ return alto;}

		// impone el pixel (X,Y) con color c
		void setPixel(size_t x, size_t y, Color c){
			int index = (x / 32);	//Vector de la fila y-esima
			unsigned int pixels = image[index + y*((ancho+31)/32)];	//Obtengo entero donde esta el pixel
			int bit = (x % 32);	//Obtengo el pixel a modificar
			// cout << c << endl;
			if(c)
				image[index + y*((ancho+31)/32)] |= (1 << bit);
			else
				image[index + y*((ancho+31)/32)] &= ~(1 << bit);
			
		}

		// retorna el color del pixel en (x,y)
		Color getPixel(size_t x, size_t y) const{
			int index = (x / 32);	//Vector de la fila y-esima
			// cout << "index: " << index << endl;
			// cout << "pos: " << y*((ancho+31)/32) << endl;
			unsigned int pixels = image[index + y*((ancho+31)/32)];	//Obtengo entero donde esta el pixel
			// cout << "pixels: " << hex << pixels << endl;
			int d = (x % 32);	//Obtengo el pixel a modificar

			if(pixels &= (1 << d))
				return BLANCO;
			else
				return NEGRO;
		}
	
	private:
		unsigned int * image;
		size_t ancho;
		size_t alto;
};


MonoImg* decompress(const string &filename){
	ifstream file(filename);
	try{
		if(!file.is_open())
			throw runtime_error("No se pudo abrir el archivo");

		int ancho, alto, nruns;
		file >> ancho >> alto >> nruns;	//Saco las caracteristicas

		MonoImg * img = new MonoImg(ancho, alto);
		// cout << "Se creo" << endl;
		int x = 0, y = 0, n = 0;
		for(int i = 0; i < nruns; i++){			//Recorro todos los runs
			unsigned int runs;
			file >> runs;		//Saco un run
			unsigned int nrep = (runs & 0x7F);	//Obtengo la cantidad de repeticiones
			Color color = Color((runs >> 7));	//Obtengo el color

			for(int j = 0; j < nrep; j++){
				img->setPixel(x, y, (color? BLANCO : NEGRO));	//Establesco cada color
				x += 1;	//Incremento a la siguiente posicion
				// cout << "x: " << x << " y: " << y << endl;
			}
			if(x >= img->getWidth()){
				x = 0;
				y++;
			}
		}
		return img;

	}catch(const runtime_error &e){
		cout << e.what() << endl;
	}
	return nullptr;
}

void printImg(const MonoImg* img)
{
	for (uint32_t y = 0; y < img->getHeight(); y++) {
		for (uint32_t x = 0; x < img->getWidth(); x++) {
			Color c = img->getPixel(x, y);
			cout << ((c == BLANCO) ? 'x' : ' ');
		}
		cout << endl;
	}
}

int main()
{
	MonoImg* img = decompress("img.compressed");
	
	printImg(img);

	delete img;
	// cout << 0xFFFFFFFF << endl;

	return 0;
}


