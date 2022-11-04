#include <iostream>

using namespace std;

struct A{
    A() { cout << "se construyo A" << endl; }
    ~A() { cout << "se destruyo A" << endl; }
};

struct B{
    A b;
    B() { cout << "se construyo B" << endl; }
    ~B() { cout << "se destruyo B" << endl; }

};

int main(int argc, char **argv){
    B a[2];

    return 0;
}