#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define num_elements 500

using namespace std; 

struct P2D_t {
    double X;
    double Y;
    P2D_t() : X(0.0), Y(0.0) {};
    P2D_t (double x, double y) : X(x), Y(y) {};

    void print(){ cout << "X: " << X << " -  Y: " << Y << endl; }
};

int index_max (const vector<P2D_t> &points){
    int i = 0;
    int index = 0;
    double max = points.at(0).Y;
    for(const auto & point : points){
        if (point.Y > max) { index = i; }\
        i++;   
    }
    return index;
}

int main(){
    ifstream iFile("peaks.dat") ;

    vector<P2D_t> points;

    if(iFile.is_open()){
        vector <double> datos;
        double d;

        while(iFile >> d){
            datos.push_back(d);
        }
        iFile.close();
        for(int i = 0; i < datos.size(); i+=2){
            points.push_back(P2D_t(datos[i], datos[i+1]));
        }
    }

    for (const auto & point : points){ cout << point.X << " " << point.Y << endl ;}

    int index = index_max(points);

    cout << "Y max: " << points.at(index).Y << " X correspondiente: " << points.at(index).X << endl;

    return 0;
}


