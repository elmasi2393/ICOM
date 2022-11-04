#include <iostream>

using namespace std;

/**
 * @brief intercambiar
 * @p intercambiar elementos
 * @param a 
 * @param b 
 */
void intercambiar(double *a, double *b){    //Generamos funcion para intercambiar elementos
    double prov = *a;
    *a = *b;
    *b = prov;

    return;
}

/**
 * @brief TransponeNN
 *  @p transpone elementos de una matriz de 10X10
 * @param matriz 
 * @param n 
 */
void TransponeNN(double *matriz, int n){
    for (int i = 0; i < n; i++){        //Recorro cada fila
        for (int j = i; j < n; j++){    //Recorro las columnas a partir de la fila q me encuente
            intercambiar(matriz+(n*i + j), matriz+(n*j + i)); //Intercambio componentes
        } 
    }
}

/**
 * @brief print
 * @p imprime una matriz de 10X10
 * @param matriz 
 * @param n 
 */
void print(double *matriz, int n){
    for (int i = 0; i < n*n; i++){
        if(!(i%n)){ cout << endl; }
        cout << *(matriz+i) << "\t";
    }
    cout << endl;
    return;
}

int main(int argc, char **argv) {

    double m[10][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                        {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
                        {31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
                        {41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
                        {51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
                        {61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
                        {71, 72, 73, 74, 75, 76, 77, 78, 79, 80},
                        {81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
                        {91, 92, 93, 94, 95, 96, 97, 98, 99, 100}};
    print(&m[0][0], 10);

    TransponeNN(&m[0][0], 10);
    cout << "--------------------------------------------------------" << endl;
    print(&m[0][0], 10);

    

    // cout << *(d+90) << endl;
    // TransponeNN(&m[0][0], 10);

    return 0;

}