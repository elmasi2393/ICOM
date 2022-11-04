#include <iostream>

using namespace std;

void desplazar(int V[], int N, int idx) {
    int i = N;
    while(i > idx){ 
        V[i] = V[i - 1];
        i--;
    }
}
int puntoInsercion(int v, int V[], int n){
    int idx = 0;
    while(idx < n && V[idx] < v){ idx ++;}

    return idx;
}
void insertarOrdenado(int v, int V[], int n){
    int idx = puntoInsercion(v, V, n);
    desplazar(V, n, idx);
    V[idx] = v;

}
void OrdenaArrayNativo(int V[], int n){
    for(int i = 0; i < n; i++){ insertarOrdenado(V[i], V, i); }
    
}

int main(int argc, char **argv){

    int v[10] = {3, 2, 5, 1, 9 ,0, 8, 4, 7, 6};
    // cout << "n: " << sizeof(v) << endl;
    OrdenaArrayNativo(v, 10);

    for(int i = 0; i<10; i++){ cout << v[i] << endl;}

    return 0;
}

// void OrdenaArrayNativo(int V[], int n){
//     int vect_ord[n];
//     vect_ord[0] = V[0];
//     cout << "vect_ord[0]: " << vect_ord[0]<< endl;


//     for (int i = 1; i < n; i++){
//         int p = V[i];   //Buscamos la siguiente componente del vector desordeneado
//         cout << "p: " << p << endl;
//         int pos = i;    //Por defecto, asignamos que la posicion en la cual insertarlo es la ultima

//         for(int j = 0; j < i; j++){ //Preguntamos la posicion del vector ordenado en la que va
//             if(p < vect_ord[j]){ 
//                 pos = j;
//                 cout << p << " < " << vect_ord[j] << " pos: " << pos << endl;
//                 break;
//                 } // Si encontramos uno mas chico, almacenamos la posicion en la que va
//         }

//         for(int k = pos; k <= i; k++){
//             int t = vect_ord[k];
//             vect_ord[k] = p;
//             cout << "t: " << t << "| vect_ord[" << k <<"] = " << vect_ord[k] << endl;
//             p = t;
//         }
//     }

//     for (int i = 0; i < n; i++){ cout << vect_ord[i] << endl;}

// }
