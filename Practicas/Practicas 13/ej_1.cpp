#include <iostream>

using namespace std;

template<class T>
T Fibonacci(T n) {
    if( n == 0 || n == 1) return n;
    
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}
template<class T>
T factorial(T n){
    if(n == 0){ return 1;}
    return n * factorial(n - 1);
}

int main(){
    cout << factorial(20) << endl;
    cout << factorial(20L) << endl;
    cout << factorial(40.0) << endl;
    cout << factorial(40.0f) << endl;
    return 0;
}