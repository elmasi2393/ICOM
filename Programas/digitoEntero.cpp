#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    vector<int> arr;
    arr = {23, 678, -23, -90, 7654, 3, 12, -1, 8, 82310213, 23135, 31245, 32};

    for(const auto& i : arr){
        cout << "number: " << i << " last digit: " << abs(i%10) << endl;
    }    

    return 0;
}