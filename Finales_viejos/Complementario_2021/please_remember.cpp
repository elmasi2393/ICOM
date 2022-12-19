#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace std;

class Image
{
    public:
        virtual ~Image() { }

        virtual size_t getXSize() const = 0;
        virtual size_t getYSize() const = 0;

        virtual int getPixel(size_t x, size_t y) const = 0;
        virtual void setPixel(size_t x, size_t y, int v) = 0;

        virtual void print() const = 0;
        virtual Image *clone() const = 0;

        size_t getNumPixels() const {
            return getXSize() * getYSize();
        }
        int getPixel(size_t k) const {
            return getPixel(k % getXSize(), k / getXSize());
        }
        void setPixel(size_t k, int v) {
            setPixel(k % getXSize(), k / getXSize(), v);
        }
};


class AssoMem
{
    public:
        static const size_t MAX_ITER = 10;
        static const size_t DIFF_THRESHOLD = 2;

        // TODO
        AssoMem(size_t num_neuronas);

        // TODO
        // Libera todos los patterns que fueron cargados
        ~AssoMem();

        // TODO
        size_t getNumNeuronas() const;

        // TODO
        // Agrega el pattern a sus patterns
        void addPattern(const Image *pattern);

        // TODO
        size_t getNumPatterns() const;

        // TODO
        // Calcula los pesos con los patterns cargados
        void learn();

        // TODO: Funcion que intenta recordar la imagen que se pasa como argumento
        // Retorna nullptr si no lo recuerda o el puntero al pattern recordado
        const Image *remember(const Image *img);

        // TODO
        void print_patterns() const;

    private:

        //  TODO: Devuelve el numero de diferencias entre dos imagenes
        static size_t pattern_diff(const Image *img1, const Image *img2);

        const size_t NUM_NEURONAS;

        vector<const Image *> patterns;

        // TODO
        // Definir miembro para representar los pesos w_i,j
};


template <size_t X_SIZE, size_t Y_SIZE>
class FixedImage : public Image
{
    public:
        // TODO
        size_t getXSize() const override;

        // TODO
        size_t getYSize() const override;

        // TODO
        int getPixel(size_t x, size_t y) const override;

        // TODO
        void setPixel(size_t x, size_t y, int v) override;

        // TODO
        void print() const override;

        // TODO
        // Aloca dinámicamente una nueva imagen copia de la actual y retorna su dirección de memoria
        FixedImage *clone() const override;

        static FixedImage *load(istream &is) {
            return new FixedImage(is);
        }

        static FixedImage *load(const string &filename)  {
            ifstream ifs(filename);
            return load(ifs);
        }

    private:
        // Constructor que lee la imágen desde un input stream
        FixedImage(istream &is) {
            string line;
            for( size_t y = 0; y < Y_SIZE; ++y ) {
                getline(is, line);
                if( ! is )
                    throw runtime_error("Invalid Pattern");
                if( line.size() != X_SIZE )
                    throw runtime_error("Invalid Pattern");
                for( size_t x = 0; x < X_SIZE; ++x )
                    pixels[y][x] = line[x] == '1' ? 1 : -1;
            }
            getline(is, line);
        }

        // Constructor copia por default
        FixedImage(const FixedImage &) = default;

        // Alamacenamiento de los pixels de la imagen
        int pixels[Y_SIZE][X_SIZE];
};


int main()
{
    const size_t X_SIZE = 25;
    const size_t Y_SIZE = 25;

    const size_t NUM_PIXELES = X_SIZE * Y_SIZE;
    const size_t NUM_NEURONAS = NUM_PIXELES;

    // Alias al tipo de imagen a utilizar
    using TestPattern = FixedImage<X_SIZE, Y_SIZE>;

    AssoMem assomem(NUM_NEURONAS);

    // Carga los patrones desde formas.dat
    ifstream ifs("formas.dat");
    try {
        while( true )
            assomem.addPattern(TestPattern::load(ifs));
    } catch( exception &e ) {
        if( assomem.getNumPatterns() == 0 ) {
            cout << "Error loading patterns from formas.dat!\n";
            return 1;
        }
    }
    cout << "Patrones de entrenamiento: " << endl;
    assomem.print_patterns();

    // Entrena la red de Hopfield
    assomem.learn();

    // Pruebas de la red
    
    cout << "TEST recordada: " << endl;
    Image *recuerda = TestPattern::load("recuerda.dat");
    auto res = assomem.remember(recuerda);
    if( res ) {
        cout << "\nOK: Lo recuerda y lo tenia que recordar\n\n";
        res->print();
    } else
        cout << "\nKO: No lo recuerda y lo tendria que recordar\n\n";

    cout << "TEST NO recordada: " << endl;
    Image *olvida = TestPattern::load("olvida.dat");
    res = assomem.remember(olvida);
    if( res ) {
        cout << "\nKO: Lo recuerda y no lo tendria que recordar\n\n";
        res->print();
    } else
        cout << "\nOK: No lo recuerda y no lo tendria que recordar\n\n";

    delete recuerda;
    delete olvida;

    return 0;
}
