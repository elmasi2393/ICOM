#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Punto2D {
    int x, y;
    void print() const{
        cout << "( " << x +1 << ", " << y +1 << ") ";
    }
};
struct IslaGrafeno {
    vector<Punto2D> puntos;

    void print() const{
        for(auto &value: puntos){
            value.print();
            cout << '\t';
        }
        cout << endl;
        cout << "-------------------------------------" << endl;
    }
};

struct STM_image {
    unsigned int width;
    unsigned int height;
    vector<unsigned short> pixels;

    unsigned int ij2index(int i, int j) const{
        assert(i >= 0 && i < (int) width && j >= 0 && j < (int) height);
        unsigned int pixelIndex = i * width + j;
        assert(pixelIndex < pixels.size());
        return pixelIndex;
    }
    unsigned short getPixel(int i, int j) const{
        unsigned int pixelIndex = ij2index(i, j);
        return pixels[pixelIndex];
    }
    void setPixel(int i, int j, unsigned short value) {
        unsigned int pixelIndex = ij2index(i, j);
        pixels[pixelIndex] = value;
    } 
    void print() const{
    for(int i = 0; i<this->width; i++){
        for(int j=0; j<this->height; j++){
            cout << this->getPixel(i, j) << '\t';
        }
        cout << endl;
    }
    };
};

struct GrafenoAnalizer {
    GrafenoAnalizer(unsigned short threshold_) {
        threshold = threshold_;
    }
    vector<IslaGrafeno> analize(STM_image img);
    void detect_island(STM_image &img, int i, int j, IslaGrafeno & islas);

    unsigned short threshold;
};
void GrafenoAnalizer::detect_island(STM_image &img, int i, int j, IslaGrafeno &islas){
    if(i < 0 || i > img.width-1 || j < 0 || j > img.height-1){ return;} //Si me voy de la matriz retorno
    if(img.getPixel(i, j) < this->threshold){ return;}  //Si es menor que el umbral, retorno
    else{   //Si es mayor que el umbral, guardo el punto y piso la posicion
            islas.puntos.push_back({i, j});
            img.setPixel(i, j, 0);
        }
    detect_island(img, i+1, j, islas);
    detect_island(img, i-1, j, islas);
    detect_island(img, i, j+1, islas);
    detect_island(img, i, j-1, islas);
};

vector<IslaGrafeno> GrafenoAnalizer::analize(STM_image img){
    vector<IslaGrafeno> result;

    for(int i = 0; i < img.width; i++){
        for(int j = 0; j < img.height; j++){
            IslaGrafeno isla;
            detect_island(img, i, j, isla);
            if(isla.puntos.size() > 0){ result.push_back(isla); }
        }
    }
    return result;

};

int main(){

    STM_image img;
    img.height = 5;
    img.width = 5;
    
    vector<unsigned short> pixels {5, 5, 2, 2, 2,2, 2, 2, 2, 2, 2, 5, 5, 2, 2, 2, 5, 5, 2, 2, 2, 5, 5, 2, 2 };
    // cout << pixels.size() << endl;
    img.pixels = pixels;
    img.print();

    GrafenoAnalizer analisis(3);

    vector<IslaGrafeno> result = analisis.analize(img);
    cout << result.size() << endl;
    for(int i = 0; i < result.size(); i++){
        result.at(i).print();
    }

    return 0;
}
