#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Noiserer {
    public:
        Noiserer (double minV_, double maxV_) : minV(minV_), maxV(maxV_) {};
        double operator()(double v);
    private:
        double minV, maxV;
};

double Noiserer::operator() (double v){
    return v + ((rand()/double(RAND_MAX)) * (maxV - minV/2.0)) + minV/2.0;
}

int main(int argc, char **argv){
    vector<double> in  {1.28, 6.54, 7.90, 2.345, 5.89};
    vector<double> out (in.size());

    //Imprimo el vector in
    for (const auto& v : in){
        cout << v << "\t";
    }
    cout << endl;

    transform(in.begin(), in.end(), out.begin(), Noiserer(2, 8));

    cout << "--------------------------------" << endl;

    //Imprimo el vector in
    for (const auto& v : out){
        cout << v << "\t";
    }
    cout << endl;
    
    return 0;
}