#include <iostream>

using namespace std;

int n_forms (int n){
    if (n == 1) {return 1;}
    else if (n == 2) {return 2;}

    return n_forms(n-1) + n_forms(n-2);
}

int main(int argc, char* argv[]) {
    cout << n_forms(4) << endl;
    return 0;
}