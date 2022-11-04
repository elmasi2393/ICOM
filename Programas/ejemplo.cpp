#include <iostream>

namespace otro{
    int x;
}

int x;

int main(){

    ::x = 3;
    x  = 4;
    otro::x = 8;


    std::cout << ::x<< ' ' << x << ' ' << otro::x << std::endl;

    return 0;
}