#include <iostream>
#include <cmath>

using namespace std;

//Functor abstracto de tipo serie
class Serie{
    public:
        virtual double operator()(int i) = 0;
};
//Functor heredado 1
class S1: public Serie{
    public:
    	S1(double a, double b) : a(a), b(b) {}
        double operator()(int i){ return a*pow(b, i); }
    private:
    	double a, b;
};
//Functor heredado 2
class S2: public Serie{
    public:
        double operator()(int i){ return 1/(pow(M_PI, i)); }
};
//Functor heredado 3
class S3: public Serie{
    public:
    	double operator()(int i){ return pow(-3, i)/(2*i+1); }
};


//Estructura de no excepcion
struct NotConvergeException : public runtime_error{
    NotConvergeException(const char * w): runtime_error(w) {}
};

//Funcion para calcular series
double limiteSerie(int M, Serie &serie, double cota_error){
    double result = 0;

    //Calculo el resultado de la serie
    for (int i = 0; i < M; i++){
        double t = serie(i);
        result += t;
        if(abs(t) < cota_error){ return result; }
    }

    throw NotConvergeException("No convergio");

}


int main(){
    double result;
    double cota_error = 0.01;
    S1 s1(1, 0.5);
    S2 s2;
    S3 s3;

    try{
        result = limiteSerie(10, s3, cota_error);
        cout << result << endl;
    }catch(NotConvergeException &e){
        cout << e.what() << endl;
    }

    return 0;
}