#include <iostream>
#include <vector>

using namespace std;

struct T{
    int a;
    T(const T &x) {     //Construccion copia
        this->a = x.a;
        cout << "Se consruyó por copia ;)" << endl;
        }
    explicit T (int a){          //Constructor definido // Al poner explicito, queda explicito que se requiere llamarlo
        this->a = a;
        cout << "Se construyo :) " << a << endl;
    }
    ~T(){ cout << "Se destruyo :(" << a << endl; }
    void print(){ cout << a << endl;}
};

int main(int argc, char **argv) {
    vector<T> v (10, T(7)); //Ava queda el explicit
    cout << v.size()<< endl;
    v.resize(13,T(0));

    return 0;

}