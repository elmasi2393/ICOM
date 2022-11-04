#include <iostream>
#include <cmath>

#define _USE_MATH_DEFINES

// #define N 1000
#define epsilon 0.0001

using namespace std;

using fun_ptr_t = double (*)(double);

/**
 * @brief integra
 * @p integra una funcion por metodo de los poligonos
 * @p INTENTAR HACERLA RECURSIVA
 * 
 * @param a limite inferior
 * @param b limite superior
 * @param fun funcion
 * @return double 
 */
// double integra(double a, double b, fun_ptr_t fun){
//     double result = 0.0, fa = fun(a), fb = fun(b);

//     for(int i = 0; i < N; i++){
//         result += fun(a + i*((b-a)/double(N)));        
//     }

//     return ((b-a)/double(N)) * (((fa+fb)/2.0) + result);
// }

double integra(double a, double b, fun_ptr_t fun){
    //Funcion
    // int(fx) = h/2(f(a) + 2*sum(f(a+i*h)) +fb)

    //Define initial numbers of iterations
    int N = 10;

    //Define initial values of results
    double result_prev = 0.0, result_post = 0.0;
    double fa = fun(a), fb = fun(b), h = (b-a)/double(N);

    //Calculo la integral

    do{  //Verifico si la diferencia entre integrales es menor a un epsilon
        result_prev = result_post;
        result_post = 0;

        for(int i = 0; i < N; i++){
            result_post += fun(a + i*h);        
        }
        //Obtengo el resultado previo
        result_post = (h/2)*(fa + 2*result_post + fb);

        N *= 2;                 //Incrementamos el doble la cantidad de intervaloes
        h = (b-a)/double(N);    //Cambiamos el ancho del intervalo

    }while(abs(result_post - result_prev) > epsilon);

    return result_post;
}

int main(int argc, char **argv){
    double a = 0, b = M_PI/2;

    cout << "Integration: " << integra(a, b, sin) << endl;

    return 0;
}