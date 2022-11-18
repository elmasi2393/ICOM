#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <chrono>


using namespace std;

//Functor para duplicar
struct Duplicate{
    void operator()(int &x){ 
        x *= 2; 
        }
};

void duplicate(int &x){ 
    x *=2;

    return;
}

template<class T> void print(T &x){
    for(auto a: x){
        cout << a << " ";
    }
    cout << endl;
}

int main(){

    vector<int> v (5);

    cout << "Inicializacion de vector" << endl;
    // for(auto &i: v){
    //     i = rand();
    // }
    for(int i = 0; i < v.size(); i++){
        v[i] = i;
    }

    list<int> l (v.begin(), v.end());
    deque<int> d (v.begin(), v.end());

    sort(v.begin(), v.end());
    l.sort();
    sort(d.begin(), d.end());

    //Duplico vector
    cout << "--- Vector ---" << endl;
    print<vector<int>>(v);
    for_each(v.begin(), v.end(), Duplicate{});
    print<vector<int>>(v);

    //Duplico Lista
    cout << "--- Lista ---" << endl;
    print<list<int>>(l);
    for_each(l.begin(), l.end(), Duplicate{});
    print<list<int>>(l);

    //Duplico deque
    cout << "--- Deque ---" << endl;
    print<deque<int>>(d);
    for_each(d.begin(), d.end(), Duplicate{});
    print<deque<int>>(d);

    return  0;

}