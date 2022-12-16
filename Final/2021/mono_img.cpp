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
		MonoImg(size_t ancho, size_t alto, Color c = BLANCO);	// TODO
		// destruye la im�gen (libera todos sus recursos)
		~MonoImg();												// TODO

		// retorna el ancho de la imagen
		size_t getWidth() const;								// TODO

		// retorna el alto de la imagen
		size_t getHeight() const;								// TODO

		// impone el pixel (X,Y) con color c
		void setPixel(size_t x, size_t y, Color c);				// TODO

		// retorna el color del pixel en (x,y)
		Color getPixel(size_t x, size_t y) const;				// TODO

	
	private:
		// TODO
		// ...
	    
};


MonoImg* decompress(const string &filename);					// TODO

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

	return 0;
}


