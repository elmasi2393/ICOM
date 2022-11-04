#include <iostream>

using namespace std;

int main(int argc, char **argv){
    int c, characters = 0, words = 0, lines = 0;


    while ((c = cin.get()) != EOF){ 
        characters++;
        if(c == '\n'){
            lines++;
        }
        if(c == '\n' || c == '\t' || c == ' '){
            words++;
            }
    }
    cout << "characters: " << characters << " words: " << words << " lines: " << lines <<endl;

    return 0; 
}