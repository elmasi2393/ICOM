#include <iostream>

using namespace std;


void Replace(char s[], char nuevo, char viejo){
    int i = 0;
    while(s[i] != '\0'){
        if (s[i] == viejo) { s[i] = nuevo;}
        i++;
    }
    return;
}

int main(){

    char s[] = "Hola mundo";

    Replace(s, 'u', 'o');

    int i = 0;
    while(s[i] != '\0'){
        cout.put(s[i]);
        i++;
    }
    cout << endl;
    

    return 0;
}