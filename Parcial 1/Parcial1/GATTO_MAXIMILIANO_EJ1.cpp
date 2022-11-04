#include <iostream>
#include <string>
#include <vector>


using namespace std;

struct StatWords {
    struct StatRecord{
        char character;
        unsigned int repCnt;
    };
    vector<StatRecord> records;
    /**
     * @brief addCharacter
     * @p agrega un caracter a las estadisticas
     * 
     * @param character 
     */
    void addCharacter(const char &character){   //Añadir un caracter al registro
        bool flag = false;

        for(auto &record : records){
            if(character == ' ') { continue; }      //No anado los espacios en blanco
            if(record.character == character){    //Si encuentro incremento y rompo
                record.repCnt++;
                flag = true;
                break;
            }
        }
        if(!flag){ records.push_back({character, 1});}   //Si no encuentro lo agrego con rep = 1
        return;
    }
    /**
     * @brief addWord
     * @p agrega los caracteres de un string a StatWords
     * 
     * @param word 
     */
    void addWord(const string &word){       //Añado los caracteres de una palabra tipo string al registro
        for(int i = 0; i < word.size(); i++){
            this->addCharacter(word.at(i));
        }
        return;
    }
        /**
         * @brief print()
         * @p Funcion usada para visualizar las estadisticas de un StatWords
         * 
         */
        void print(){   //Funcion para imprimir
        for(auto &record : records){ cout << "word: " << record.character << " rep: " << record.repCnt << endl; }

        return;
    }
};
/**
 * @brief to_minus()
 * @p DEVELOPING: convierte todas las letras de un string a minusculas
 * @param str 
 * @return string 
 */
string to_minus(const string & str){
    char prov [str.size()];

    for(int i = 0; i < str.length(); i++){
        if(str.at(i) > 90 || str.at(i) < 65){
                
            prov[i] = char(str.at(i) + 32);
        }else{

            prov[i] += char(str.at(i));
        }
    }

    string result = prov;
    return result;
};

/**
 * @brief isAnagram
 * @p indica si una palabra es anagrama o no
 * 
 * @p BUG: distingue mayusculas y minusculas
 * @param s1 
 * @param s2 
 * @return true 
 * @return false 
 */
bool isAnagram(const std::string &s1, const std::string &s2){
    int flag = 0;

    StatWords stats_1;
    StatWords stats_2;

    stats_1.addWord(s1);    //Agrego los datos de ambos string
    stats_2.addWord(s2);

    // stats_1.print();
    // stats_2.print();

    for(const auto &S1 : stats_1.records){  //tomo cada elemento del primer stats_1
        flag = 0;

        for(const auto &S2 : stats_2.records){
            if(S1.character == S2.character && S1.repCnt == S2.repCnt){ //Pregunto si alguno es igual al anterior
                flag = 1;
            }
        }
        if(!flag){ return false; }  //Si al salir del for el flag sigue en 0, significa que no ecnontro coincidencia entonces rompo
    }

    return true; //Si no rompi en algun ciclo, es porque todos coinciden

}
//Falta distincion mayusculas y minusculas

int main(int argc, char **argv){
    StatWords stats;

    string s1 = "iam lordvold emort";
    string s2 = "to mmarv oloriddle";
    

    // cout << to_minus(s1) << endl;
    char prov [s1.size()];

    string v = prov;
    cout << v << endl;

    cout << ((isAnagram(s1, s2) == true)? "Es anagrama" : "No es anagrama") << endl;

    return 0;

}

