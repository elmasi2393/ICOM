#include <iostream>
#include <string>

using namespace std;

void CapitalizeFirst(std::string &phrase){
    int pos = 0;
    
    while(pos != string::npos){
        pos = phrase.find(' ', pos+1);
        if(phrase.at(pos+1) > 96 && phrase.at(pos+1) < 123){
            phrase.at(pos+1) -= 32;
        }
    }
    return;
}

int main(){
    string s1 = "este es El primer parcial de introduccion al computo";

    cout << s1 << endl;
    CapitalizeFirst(s1);
    cout << s1 << endl;

    return 0;
}