#include <iostream>

using namespace std;

int main(){
    int a = 4;
    int *p = &a;
    int **q = &p;

    cout << "a = " << a << endl;
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "&p = " << &p << endl;

    cout << "*p :" << *p << endl;
    cout << "*q :" << *q << endl;

    cout << "*(*q): " << *(*q) << endl;

    return 0;
}