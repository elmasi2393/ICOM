#include <iostream>
#include <string>

using namespace std;

template <class T> class Vector  {
    public:
        Vector(int s);
        ~Vector();
        Vector(const Vector &v);
        Vector& operator=(const Vector& v);
        T& operator[](int idx);
        T  operator[](int idx) const; 
        int size() const;
    private:
        int sz;
        T *elem;
};

template <class T> Vector<T>::Vector(int s){
    this->sz = s;
    this->elem = new T[this->sz];
}

template <class T> Vector<T>::~Vector(){
    delete[] elem;
}

template <class T> Vector<T>::Vector(const Vector &v){
    this->sz = v.size();
    this->elem = new T[this->sz];

    for(int i = 0; i < this->sz; i++){
        this->elem[i] = v[i];
    }
}

template <class T> Vector<T>& Vector<T>::operator=(const Vector& v){
    if(this == &v) {return *this; }

    delete[] this->elem;

    this->sz = v.size();
    this->elem = new T[this->sz];

    for(int i = 0; i < this->sz; i++){
        this->elem[i] = v[i];
    }

    return *this;
};

template <class T> T& Vector<T>::operator[](int idx){
    return this->elem[idx];
}

template <class T> T Vector<T>::operator[](int idx) const{
    return this->elem[idx];
}

template <class T> int Vector<T>::size() const { return this->sz; }

//-------------------------------------------------------------------------

template <class J> struct Punto2D{
    J x;
    J y;
};

//----------------- CLASE PARA BOOL --------------------------

template <> class Vector<bool>  {
    public:
        Vector(int s){
            this->sz = s;
            this->elem = new char[this->nBytes(this->sz)];
        }
        ~Vector(){
            delete[] elem;
        }
        Vector(const Vector<bool> &v){
            this->sz = v.size();
            this->elem = new char[this->nBytes(this->sz)];

            for(int i = 0; i < this->nBytes(this->sz); i++){
                this->elem[i] = v[i];
            }
        }
        Vector& operator=(const Vector<bool>& v){
            if(this == &v) {return *this; }

            delete[] this->elem;

            this->sz = v.size();
            this->elem = new char[this->nBytes(this->sz)];

            for(int i = 0; i < this->nBytes(this->sz); i++){
                this->elem[i] = v[i];
            }

            return *this;
        }
        bool set(int idx, bool value){  //Setea un valor booleano en un byte
            if(idx < 0 || idx >= this->sz) { return false; }    //Me fijo si el indice esta dentro del rango

            int byte = this->nBytes(idx);   //Obtengo el byte en el que se encuentra
            int bit = idx % 8;              //Obtengo el indice dentro de ese byte

            if(value){  //Pregunto si se quiere asignar un true o false
                this->elem[byte] |= (1 << bit);     //En caso de true, hago un OR con un 1 en el bit correspondiente
            } else {
                this->elem[byte] &= ~(1 << bit);    //En caso de false, hago un AND con un 0 en el bit correspondiente
            }

            return true;    //Devuelvo true si se pudo asigna
        }
        bool  operator[](int idx) const{
            if(idx < 0 || idx >= this->sz) { return false; }    //Me fijo si el indice esta dentro del rango

            int byte = this->nBytes(idx);   //Obtengo el byte en el que se encuentra
            int bit = idx % 8;              //Obtengo el indice dentro de ese byte

            return this->elem[byte] & (1 << bit);   //Devuelvo el valor del bit correspondiente
        } 
        int size() const{ return this->sz; }
        void print() const{
            for(int i=0; i< this->sz; i++){
                cout << this->operator[](i) << " ";
            }
            cout << endl;
        }
    private:
        int sz;
        char *elem;

        int nBytes(int n) const{
            if(n % 8 == 0){
                return n / 8;
            } else {
                return (n / 8) + 1;
            }
        }
};

//---------------------------------------------------------------------------

template <class T> void printVector(vector<T> &v){
    for(int i = 0; i < v.size();  i++){
        cout << v[i] << " ";
    }
    cout << endl;
};

void f() {
    Vector<double> dvec(5);
    dvec[0] = 3.14;
    double d = dvec[0];

    Vector<string> strvec(10); 
    strvec[0] = "hola";
    cout << strvec[0] << endl;

    Vector<Punto2D<double>> p2dvec(3); 
    p2dvec[0] = Punto2D<double>{ 1.1, 0.2 }; 
    Punto2D p2d = p2dvec[0];

    cout << p2d.x << endl;

    Vector<bool> bvec(11);
    bvec.set(0, true);
    bvec.set(1, false);
    bvec.print();

    Vector<bool> bvec2 = bvec;
    bvec2.set(9, true);
    bvec2.print();


    return;
}

int main(){
    f();

    return 0;
}