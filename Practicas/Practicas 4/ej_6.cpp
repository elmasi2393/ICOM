#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    int flag = 0, c;

    while ( (c = cin.get()) != EOF){
        if (c =='('){ flag = 1; }
        else if (c == ')'){ flag = 0; }
        else if (flag == 0){ cout.put(c); }
    }

    return 0; 
}
