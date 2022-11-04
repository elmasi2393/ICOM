#include <iostream>

using namespace std;

typedef void (*FunPtr_t)(void);

void funA(){ cout << "funA" << endl;}
void funB(){ cout << "funB" << endl;}
void funC(){ cout << "funC" << endl;}
void funD(){ cout << "funD" << endl;}
void funE(){ cout << "funE" << endl;}

int main(){
    FunPtr_t fun[] = {funA, funB, funC, funD, funE};

    for(int i=0; i < 5; i++){
        int x = rand() % 5;
        fun[x]();
    }

    return 0;
}