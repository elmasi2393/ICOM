#include <iostream>

using namespace std;

//version recursiva
void print_binary_rec( unsigned int n);

//version no recursiva
/**
 * @brief print_binary
 * @p al desplazar pierdo los digitos, por lo que se podria usar un enmascaramiento para ir detectando de a un solo bit, pero no se testeo
 * @param n 
 */
void print_binary( unsigned int n){
    for(int i = 0; i < sizeof(n)*8 ; i++){
        cout << (n << i);
    }
    cout << endl;

}


int main(int argc, char **argv) {
    unsigned int n = 0x00000002;
    //0000 0000 0000 0000 0000 0000 0000 0010
    // cout << (n << 1) << endl;

    print_binary(n);

    return 0;
}