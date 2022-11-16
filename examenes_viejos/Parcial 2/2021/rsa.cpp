#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

using MensajeCifrado = vector<long>;

ostream &operator<<(ostream &os, const MensajeCifrado &msg) {
    os << '{';
    for( auto m : msg )
        os << m << ',';
    os << '}';
    return os;
}


long exponente_modular(long x, long n1, long n2)
{
    if (n1 == 0)
        return 1;
    else
        return (x * exponente_modular(x, n1 - 1, n2)) % n2;
}


void prueba_exponente_modular()
{
    long primos[] = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};

    for(auto & val: primos){
        cout << "Prueba con " << val << endl;
        cout << "  2^" << val -1 << " mod " << val << " = " << exponente_modular(2, val-1, val) << endl;
    }
    return;
    // Opcional: prueba de función exponente_modular
    //           (1 << (p-1)) % p == 1 
}

MensajeCifrado cifra(const string &s, long e, long n)
{
    MensajeCifrado res;
    for( auto &c : s )
        res.push_back( exponente_modular(c, e, n) );

    return res;
}

string descifra(const MensajeCifrado &msg, long d, long n)
{
    string res;

    for(auto &c: msg)
        res.push_back(exponente_modular(c, d, n));

    return res;
}

void prueba_descifra()
{
    MensajeCifrado msg{4162,5524,789,1445,4537,3698,964,1273,4252,
                       1412,3698,6600,5526,5526,2759,2757,2333};
    long d = 1553;
    long n = 6767;

    cout << descifra(msg, d, n) << endl;
}

long rand_primo()
{
    long result;
    do{
        result = 30 + rand() % 170;

    }while(exponente_modular(2, result-1, result) != 1);

    return result;
}


long MCD (long a, long b){
    if(b == 0) {return a;}

    return MCD(b, a%b);
}

long coprimo(long r)
{
    long result = 17;
    
    while(result <r){
        if(MCD(result, r) == 1)     //Si lo encontramos rompemos
            break;
        result += 2;
    }
    return result;
}

struct Terna {
    long x;
    long y;
    long mcd;
};

ostream &operator<<(ostream &os, const Terna &t) {
    return cout << "x: " << t.x << ", y: " << t.y << ", mcd: " << t.mcd; 
}

Terna eulerext(long a, long b)
{
    if(b == 0)
        return Terna {1, 0, a};

    Terna result = eulerext(b, a%b);

    return Terna {result.y, result.x - (a/b)*result.y, result.mcd};
}

struct Claves {
    long e;
    long d;
    long n;
};

ostream &operator<<(ostream &os, const Claves &c) {
    return cout << "{ e: " << c.e
                << ", d: " << c.d
                << ", n: " << c.n
                << " }";
}

Claves genera_claves()
{
    long p = rand_primo();
    long q;
    do{                 //Obtengo un numero primo distinto de p
        q = rand_primo();
    } while(q == p);

    long n = p*q;
    long r = (p-1)*(q-1);
    long e = coprimo(r);
    long d = eulerext(e, r).x;
    
    cout << eulerext(e, r) << endl;

    if(d < 0)
        d = (d+r)%r;

    return Claves {e, d, n};
}

void prueba()
{
    string s = "Ejercicio 3 - Parcial 3 ICOM 2021";

    auto claves = genera_claves();
    cout << "Claves: " << claves << endl;

    auto msg = cifra(s, claves.e, claves.n);

    for (auto &c: msg)
        cout << c;
    cout << endl;

    string line = descifra(msg, claves.d, claves.n);
    cout << line << endl;


}

int main()
{
    srand(time(nullptr));

    prueba_exponente_modular();

    prueba_descifra();

    long primo = rand_primo();
    cout << "Prueba primo: " << primo << endl;
    cout << "Coprimo: " << coprimo(primo) << endl;

    prueba();

    return 0;
}
