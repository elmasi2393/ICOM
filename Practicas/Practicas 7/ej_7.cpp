#include <iostream>

using namespace std;

int StrStr(char s1[], char s2[]){
    int i = 0;
    int index = -1; //Inicio el indice con -1 como si no hubiera encontrado


    while (s1[i] != '\0'){
        if(s1[i] == s2[0]){ //Detecto ocurrencia
            index = i;
            int j = 0;
            while(s2[j] != '\0'){   //A partir de la ocurrencia comparo
                if(s1[j+i] == '\0'){  //Si no entra s2 en s1 a partir de la ocurrencia, rompo porque no entra
                    index -1;
                    break;
                }
                if(s2[j] != s1[j+i]){ //Si detecto que son desiguales, rompo el while y reseteo el index.
                    index = -1;
                    break;
                }
                j++;
            }
        }
        if (index != -1){ break; }
        i++;    //Si rompi antes o no detecto ocurrencia, incremento hasta la siguiente ocurrencia
    }
    return index;
}

int main(int argc, char **argv){

    cout << StrStr("JUAN ESTA CASADO CON MARIA", "ASADO") << endl;

    return 0;
}