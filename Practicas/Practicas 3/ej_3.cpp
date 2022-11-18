#include <iostream>
#include <cmath>

#define cota_error 0.01

using namespace std;

int main(){
    const int limit= 100000;
    double pi = 1;
    int a = -1;
    int i = 3;

    while(abs(M_PI/4 - pi) > cota_error){
        pi = pi + (double(a)/i);
        // cout << pi << " " << i << " " << a << endl;
        a *= (-1);
        i += 2;
    }
    pi *= 4;

    // for (int i = 3; i < limit; i=i+2){
    //     pi = pi + (float(a)/i);
    //     // cout << pi << " " << i << " " << a << endl;
    //     a *= (-1);
    // }
    // pi *= 4;

    cout << "pi: " << pi << endl;

    return 0;
}