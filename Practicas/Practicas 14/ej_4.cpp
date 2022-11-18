#include <iostream>
#include <set>
#include <unordered_set>
#include <chrono>

using namespace std;

int main(){
    set<int> s;
    

    for(int i=0; i<100; i++){
        s.insert(i);
    }
    unordered_set<int> u(s.begin(), s.end());

    s.insert(45);
    s.insert(12);
    s.insert(2);

    auto start = chrono::steady_clock::now();
    auto pos = s.find(88);
    auto end = chrono::steady_clock::now();

    cout << "Tiempo de busqueda set: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;

    start = chrono::steady_clock::now();
    auto pos_u = u.find(88);
    end = chrono::steady_clock::now();
    cout << "Tiempo de busqueda unordered_set: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns" << endl;

    for(auto i = u.begin(); i != u.end(); ++i){
        cout << *i << " ";
    }
    cout << endl;
    // for(; it != s.end(); it++){
    //     cout << *it << " ";
    // }
    // cout << endl;

    return 0;
}