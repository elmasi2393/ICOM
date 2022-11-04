#include <iostream>

using namespace std;

int MCD (int a, int b){
    if(b == 0) {return a;}

    return MCD(b, a%b);
}

int MCM(int a, int b){
    return (a*b) / (MCD(a, b));
}

int main(int argc, char **argv){
    cout << MCD(21, 15) << endl;
    cout << MCM(21, 15) << endl;

    return 0;  
}