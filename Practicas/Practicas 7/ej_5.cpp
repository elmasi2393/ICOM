#include <iostream>

#define MX 10
#define MY 10

using namespace std;


void FloodFill(int M[MX][MY], int X, int Y, int C1){
    if(M[X][Y] == C1) { return;}
    else{M[X][Y] = C1; }

    FloodFill(M, X+1, Y, C1);
    FloodFill(M, X-1, Y, C1);
    FloodFill(M, X, Y+1, C1);
    FloodFill(M, X, Y-1, C1);
}

void print_matrix(int M[MX][MY]){
        for (int i = 0; i < MY; i++){
        for(int j = 0; j < MX; j++){
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]){
    int C1 = 8;
    int M[MX][MY] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, C1, C1, C1, C1, C1, C1, 0, 0},
                    {0, 0, C1, 0, 0, 0, 0, C1, 0, 0},
                    {0, 0, C1, 0, 0, 0, 0, C1, 0, 0},
                    {0, 0, C1, 0, 0, 0, 0, C1, 0, 0},
                    {0, 0, C1, 0, 0, 0, 0, C1, 0, 0},
                    {0, 0, C1, 0, 0, 0, 0, C1, 0, 0},
                    {0, 0, C1, 0, 0, 0, 0, C1, 0, 0},
                    {0, 0, C1, C1, C1, C1, C1, C1, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}
                    };
    int A[MX][MY] = {{0, 0, 0, 0, 0, C1, C1, 0, 0, 0},
                    {0, 0, C1, C1, C1, 0, C1, 0, 0, 0},
                    {0, 0, C1, 0, 0, 0, 0, C1, 0, 0},
                    {0, 0, 0, C1, 0, 0, 0, C1, 0, 0},
                    {0, 0, 0, 0, C1, 0, 0, 0, C1, 0},
                    {0, 0, 0, 0, C1, 0, 0, C1, 0, 0},
                    {0, 0, C1, C1, 0, 0, C1, 0, 0, 0},
                    {0, C1, 0, 0, 0, C1, C1, 0, 0, 0},
                    {0, 0, C1, C1, C1, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}
                    };
    print_matrix(M);
    FloodFill(M, 5, 5, C1);
    cout << "================================" << endl;
    print_matrix(M);

    cout << "*********************************" << endl;
    cout << "*********************************"<< endl;
    print_matrix(A);
    FloodFill(A, 5, 5, C1);
    cout << "================================" << endl;
    print_matrix(A);


    return 0;
}