#include <iostream>

using namespace std;

int main(int argc, char **argv){

    double x = 1.9;
    int y;

    y = x;
    x = y;

    cout << x << " " << y << endl;
    

    return 0;
}