#include <iostream>

using namespace std;

bool esDivisiblePor7(int nro){
    if(nro < 10 && nro > -10){
        if (nro == 7 || nro == -7 || nro == 0){ return 1; }
        return 0;
    }
    else{ esDivisiblePor7( (nro/10) - 2* (nro%10) ); }
}

int main(int argc, char **argv){
    if(esDivisiblePor7(63)){ cout << "es divisible por 7 :)" << endl;}
    else{ cout << "No es divisible por 7 :(" << endl; }

    return 0;
}