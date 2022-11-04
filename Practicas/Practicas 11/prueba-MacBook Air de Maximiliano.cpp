#include <iostream>

using namespace std;

class A{
    void f(){ A = 2;}
    virtual void g(){ A = 2;}
    int A;
};

int main(){
    cout << sizeof(A) << endl;

    return 0;
}
