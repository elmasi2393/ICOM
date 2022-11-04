#include "icom_helpers.h"

struct T {
    int x, y;
    T() {
        x = y = 0;
        cout << "Construccion con T()\n";
    }
    T(int x_, int y_) {
        x = x_;
        y = y_;
        cout << "Construccion con T(int, int)\n";
    }
    ~T() {
        cout << "Destruccion (" << x << ", " << y << ")\n";
    }
    void print() {
        cout << "(" << x << ", " << y << ")\n";
    }
};

int main() {
    T t1;
    t1.print();
    cin.get();
    {
        T t3(3,4);
        t3.print();
        cin.get();
    }            // sale de scope t3
    T t2(1,2);
    t2.print();
    cin.get();
    return 0;
}                // salen de ambito t2 y t1
