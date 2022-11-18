#include <iostream>
#include <cstdlib>
#include <cmath>

/* --------- AGUJA DE BUFFON -----------

Se tiene un plano infinito con lineas horizontales igualmente espaciadas y una aguja de longitud igual a la separacion entre lineas. Se tira de manera aleatoria la aguja y se pregunta si la aguja toca alguna linea. El valor de pi se calcula como 2*n/NUM_CICLOS, donde N es la cantidad de veces que la aguja toco una linea.

Para ello, se obtienen aleatoriamente un numero, que defina la posicion inicial del extremo inferior de la aguja, y el angulo entre la aguja y una linea horizontal. Se limita aposiciones entre 0 y 1 ya que se obtiene el mismo resultado. Sea y el extremo inicial de la aguja y (y + sin(phi)) el otro extremo. Si 0<y + sin(phi) < 1, significa que la aguja esta entre las lineas, sino la aguja toca una linea horizontal
*/
const int NUM_CICLOS = 100000;

using namespace std; 


// int main(int argc, char **argv){

//     double y = 0, phi = 0;
//     int N = 0;
//     srand(time(0));

//     for(int i = 0; i < NUM_CICLOS; i++){
//         y = 1.0 * rand()/RAND_MAX; //Defino posicion
//         phi = rand(); //Defino el seno del angulo

//         cout << "y: " << y << " sin_phi: " << sin(phi) << endl;

//         if((y + sin(phi)) >= 1 || (y + sin(phi) <= 0)) { N++;}    //Verifico si esta entre lineas
//     }
//     cout << "N = " << N << endl;
//     cout << "pi: " << 2*NUM_CICLOS/double(N) << endl;
// }

int main(int argc, char **argv){

    
    double y = 0, phi = 0;
    int N = 0;
    srand(time(0));

    for(int i = 0; i < NUM_CICLOS; i++){
        y = 1.0 * rand()/RAND_MAX; //Defino posicion
        phi = rand(); //Defino el seno del angulo

        cout << "y: " << y << " sin_phi: " << sin(phi) << endl;

        if((y + sin(phi)) >= 1 || (y + sin(phi) <= 0)) { N++;}    //Verifico si esta entre lineas
    }
    cout << "N = " << N << endl;
    cout << "pi: " << 2*NUM_CICLOS/double(N) << endl;
}
