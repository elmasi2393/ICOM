#include <iostream>
#define N 10

using namespace std;

void ImprimeVector(double Vector[], int NumElementos);

int main(int argc, char **argv) {
    double v[N];
    for (int i = 0; i < N; i++) { v[i] = N * (rand() / double(RAND_MAX)); }

    ImprimeVector(v, N);
    return 0; 
}

void ImprimeVector(double Vector[], int NumElementos){
    for(int i = 0; i < NumElementos; i++)
        cout << Vector[i] << endl;
}