#ifndef ARRAYNATIVOS
#define ARRAYNATIVOS

#include <iostream>

using namespace std;
//funciones de interfaz
void ImprimeVector(int Vector[], int NumElementos);
void IngresarVector(int Vector[], int NumElementos);

//Ordenamiento
void desplazar(int V[], int N, int idx) ;
int puntoInsercion(int v, int V[], int n);
void insertarOrdenado(int v, int V[], int n);
void OrdenaArrayNativo(int V[], int n);

//Inversion
void invertir(int v, int i, int V[], int n);
void InvierteArrayNativo(int V[], int n);

#endif