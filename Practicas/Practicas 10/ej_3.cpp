#include <iostream>

using namespace std;

struct A {
    int val;
    A() { 
        val=0;
        cout << "A default: "<<this << '\t' << val << endl;
        }
    A(int v) {
        val=v;
        cout<< " A con argumento: "<< this << '\t' << val << endl; 
    }
    ~A() {
        cout << "~A: "<< this << '\t' << val<<endl;
} 
};

int main(int argc, char **argv){
    A *pa = new A(10);
    A *pb = new A[10];

    // destruccion de pa y pb
    delete pa;
    delete [] pb;

    return 0;
}