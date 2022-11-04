#include <iostream>

using namespace std;

class A{
    public:
        A(){ cout << "Se construto A" << endl;};
        ~A(){ cout << "Se descontruyo A" << endl;}; //
};

class B{
    public:
        B(){ cout << "Se construto B" << endl;};
        B(const B &ba) { cout << "Se construyo por copia" << endl;};
        ~B(){ cout << "Se descontruyo B" << endl;}; //
};
void funB(){
    B b;
    string a = "Hola";
    throw a;
};

void funA(){
    A a;
    funB();
};

int main(int argc, char* argv[]){
    try{
        funA();

    }
    catch(B exc){
        cout << "Agarro exc" << endl;
    }
    catch(string exc){
        cout << "Agarro exc:" << exc << endl;
    }

    return 0;
}