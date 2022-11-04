#include <iostream>
#include <string>
// #include <vector> 

using namespace std;

int main(int argc, char **argv) {
    //Definicion de variables
    string word = "balseiro";
    int letterVowel = 0, letterConsonant = 0, w = 1, code = 0;

    for(const auto&  letter: word) { 
        if(letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u'){
            letterVowel += letter*w;
            // cout << "vowel: " << int(letter) << " w: " << w << " Letter vowel: " << letterVowel << endl;
        }else{
            letterConsonant += letter*w;
            // cout << "consonant: " << int(letter) << " w: " << w << " Letter consonant: " << letterConsonant << endl;
        }
        w+=1;
    }
    cout << "Out: " << letterVowel*4 + letterConsonant*2 << endl;
    // cout << "Vowel: " << letterVowel << endl;
    // cout << "Consonants: " << letterConsonant << endl;

    return 0; 
}
