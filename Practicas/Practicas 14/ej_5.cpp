#include <iostream>
#include <list>

using namespace std;

int main(){
    list<int> lista {1, 2, 3, 4, 5, 6};

    // auto pos = lista.begin();
    auto pos = find(lista.begin(), lista.end(), 4);

    lista.insert(pos, 4, 17);
    // cout << *pos << endl;

    
    for(auto i = lista.begin(); i != lista.end(); i++){
        cout << *i << " ";
    }
    cout << endl;

    return 0;
}