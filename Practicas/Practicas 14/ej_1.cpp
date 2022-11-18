#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <chrono>


using namespace std;

int main(){

    vector<int> v (500);

    cout << "Inicializacion de vector" << endl;
    for(auto &i: v){
        i = rand();
    }
    list<int> l (v.begin(), v.end());
    deque<int> d (v.begin(), v.end());
    cout << "Ordenando..." << endl;
    auto start = chrono::steady_clock::now();
    sort(v.begin(), v.end());
    auto end = chrono::steady_clock::now();
    cout << "Tiempo: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;

    cout << "Inicializacion de lista" << endl;
    
    auto it = l.begin();
    for(; it != l.end(); it++){
        *it = rand();
    }
    cout << "Ordenando..." << endl;
    start = chrono::steady_clock::now();
    l.sort();
    end = chrono::steady_clock::now();
    cout << "Tiempo: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;

    cout << "Inicializacion de deque" << endl;
    
    for(auto &i: d){
        i = rand();
    }
    cout << "Ordenando..." << endl;
    start = chrono::steady_clock::now();
    sort(d.begin(), d.end());
    end = chrono::steady_clock::now();
    cout << "Tiempo: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;


    // auto it2 = l.begin();

    // for(int i = 0; i < l.size() ; i++){
    //     cout << "vector: " << v[i] << endl;
    //     cout << "list: " << *it2++ << endl;
    //     cout << "d: " << d[i] << endl;
    // }

    return  0;

}