#include <iostream>

using namespace std;



int hanoi (int n, int from, int to, int aux){
    static int i = 0;
    if (n == 1) { cout << "mover de " << from << " a " << to << endl; 
    i++;
    return i;
    }

    hanoi(n-1, from, aux, to);
    hanoi(1, from, to, aux);
    hanoi(n-1, aux, to, from);

    return i;
}

int main(int argc, char* argv[]){

    
    cout << hanoi(3, 1, 3, 2) << endl;

    return 0;
}