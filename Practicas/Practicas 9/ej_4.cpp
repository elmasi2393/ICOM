#include <iostream>

using namespace std;

/**
 * @brief CompareStrings
 * @p compara dos strings
 * @param str1 
 * @param str2 
 * @return int 
 * @retval -1 si str1 es menor que str2
 * @retval 1 si str1 es amyor que str2
 * @retval 0 si str1 es igual a str2
 */
int CompareStrings(const char *str1, const char *str2){
    int i = 0;
    while( str1[i] && str1[i] == str2[i]) 
        i++;

    if(str1[i] > str2[i]){ return 1;}           //stri1 es mayor devuelvo 1
    else if (str1[i] < str2[i]) {return -1;}    //str1 es menor devuelvo -1  
    
    return 0; //Devuelvo 0 si no entra a los if
    }



int main(int argc, char **argv){

    cout << CompareStrings("ja", "hola") << endl;
    cout << CompareStrings("hola", "hola") << endl;
    cout << CompareStrings("hola", "ja") << endl;
    return 0;
}