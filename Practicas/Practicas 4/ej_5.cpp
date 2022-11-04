#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int c;
    while((c = cin.get()) != EOF){
        if(c > 96 && c < 123){ c -= 32; }

        cout.put(c);
    }
    return 0; 
}