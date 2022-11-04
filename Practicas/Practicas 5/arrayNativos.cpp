#include <iostream>

using namespace std;
/**
 * @brief ImprimeVector
 * 
 * @param Vector 
 * @param NumElementos 
 */
void ImprimeVector(int Vector[], int NumElementos){
    for(int i = 0; i < NumElementos; i++)
        cout << Vector[i] << endl;
}

/**
 * @brief IngresarVector
 * @p permite al usuario ingresar los elementos de un vector 
 * @param Vector 
 * @param NumElementos 
 */
void IngresarVector(int Vector[], int NumElementos){
    for(int i = 0; i < NumElementos; i++){
        cout << "Ingrese el " << i+1 << " del vector: ";
        cin >> Vector[i];
    }
    return;
}

/**
 * @brief desplazar
 * @p utilizada para desplazar las componentes de un vector desde un subindice hasta el final
 * @p utilizada en el ordenamiento
 * @param V 
 * @param N 
 * @param idx 
 */
void desplazar(int V[], int N, int idx) {
    int i = N;
    while(i > idx){ 
        V[i] = V[i - 1];
        i--;
    }
}

/**
 * @brief puntoInsercion
 * @p determina el punto de insercion en el ordanemiento
 * @param v 
 * @param V 
 * @param n 
 * @return int 
 */
int puntoInsercion(int v, int V[], int n){
    int idx = 0;
    while(idx < n && V[idx] < v){ idx ++;}

    return idx;
}
/**
 * @brief insertarOrdenado
 * @p: inserta un numero en la posicion correcta dentro de un vector
 * @param v 
 * @param V 
 * @param n 
 */
void insertarOrdenado(int v, int V[], int n){
    int idx = puntoInsercion(v, V, n);
    desplazar(V, n, idx);
    V[idx] = v;

}

/**
 * @brief OrdenaArrayNativo
 * @p Ordena los elementos de un array por el metodo de insercion
 * @param V 
 * @param n 
 */
void OrdenaArrayNativo(int V[], int n){
    for(int i = 0; i < n; i++){ insertarOrdenado(V[i], V, i); }
    
}
void invertir(int v, int i, int V[], int n){
    V[i] = V[n-i-1];
    V[n-1-i] = v;
    
    return;
    }
void InvierteArrayNativo(int V[], int n){
    for(int i = 0; i <= n/2; i++){  invertir(V[i], i, V, n); }
}
