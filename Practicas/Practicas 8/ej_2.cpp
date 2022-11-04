#include <iostream>
#include <vector>

using namespace std;

int cbu_check(const char cbu[]){
    //Defino los pesos de la comprobacion
    int first_weight[] = {7, 1, 3, 9, 7, 1, 3};
    int second_weight[] = {3, 9, 7, 1, 3, 9, 7, 1, 3, 9, 7, 1, 3};

    //defino las variabless donde guardo la sumatoria
    int sum = 0;
    
    //Verifico los primeros 8 digitos
    for(int i = 0; i < 7; i++){ sum += (cbu[i] - '0') * first_weight[i]; }

    // cout << sum << endl;
    // cout << 10 - (sum%10) << "  " << (cbu[7]-'0') << endl;
    if(10 - (sum%10) != (cbu[7]-'0')){ return 0; }  //Si no son iguales ya no es valido y devuelvo 0
    
    //Verifico los segundos 14 digitos
    sum = 0;
    for(int i = 8; i < 21; i++){ sum += (cbu[i] - '0') * second_weight[i-8]; }
    // cout << sum << endl;
    // cout << 10 - (sum%10) << "  " << (cbu[21]-'0') << endl;
    if(10 - (sum%10) != (cbu[21]-'0')){ return 0; }  //Si no son iguales ya no es valido y devuelvo 0

    return 1;   //Se paso las dos verificaciones, es correcto
}


int main(int argc, char** argv){
    char cbu[] = "2850590940090418135201";

    if(cbu_check(cbu)){ cout << "El CBU es correcto" << endl; }
    else{ cout << "El CBU es incorrecto" << endl; }

    for(int i = 0; i<sizeof(cbu); i++){ cout << cbu[i]; }

    cout << endl;

    return 0;
}