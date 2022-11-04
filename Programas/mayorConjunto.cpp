#include <iostream>
#include <vector>

using namespace std;

int main(){

    vector<int> arr;
    arr = {0, 67, -90, 56, -12, 4, 78, -43};
    
    int mayor = arr[0];

    for(const auto &value : arr) {
        // cout<< value <<endl;
        if(value >= mayor){
            mayor = value;
        }
    }

    cout << "mayor: " << mayor << endl; //
    return 0; 
}

// int main(){

//     int arr[] = {1,2,3,4,5,6,7};
//     cout << "arr size: " << sizeof(arr) << endl;

//     for(int i = 0; i < sizeof(arr); i++) {
//         cout<< arr[i] << endl;
//     }

//     return 0; 
// }