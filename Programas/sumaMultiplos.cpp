#include <iostream>

using namespace std; 

int main(int argc, char **argv) {
    int suma = 0;
    int x = 0;

    cin >> x; 
    for(int i = 1; i < 100; i++) { 
        if(i%x != 0)
            continue;
        else
            suma += i;
    }
    cout << suma << endl;

    return 0;
}
