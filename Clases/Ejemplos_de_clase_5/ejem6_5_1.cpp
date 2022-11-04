#include "icom_helpers.h"

void func(vector<int> &a) {
    cout << "En func &a[0] = " << &a[0] << '\n';
    cout << "En func &a    = " << &a << '\n';
    a[1] = 32;
}

int main(void)
{
    vector<int> v {0, 1, 2, 3, 4, 5, 6};   
    cout << "En main &v[0] = " << &v[0] << '\n';
    cout << "En main &v    = " << &v << '\n';

    func(v);
    cout << "En main v[1] = " << v[1] << '\n';

    return 0;
}
