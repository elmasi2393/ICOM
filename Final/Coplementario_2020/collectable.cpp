#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct StatWord {
    string   word;
    unsigned repeatCnt;
    bool operator<(const StatWord& e) {
        return repeatCnt < e.repeatCnt;
    }
};

class Collectable {
public:
    virtual vector<StatWord> collect() const = 0;
};

// TODO  TrieCollectable
class TrieCollectable : public Collectable {
    public:
        TrieCollectable(): numKeys(0) { root = new TrieNode(); }
        ~TrieCollectable(){ delete root; }

        // inserta una nueva clave si no est� presente
        // o incrementa el repeatCnt si la clave exist�a previamente. 
        void insertKey(const char* key){
            TrieNode* reference = root; //Establesco la primera referencia en el root
            cout << string(key) << endl;
            for(int i=0; i < strlen(key); i++){
                int index = getIndexForChar(key[i]); //Busco el indice para el character
                if(reference->children[index] == nullptr){
                    reference->children[index] = new TrieNode();
                }
                reference = reference->children[index]; //Apunto al ultimo nodo donde asigne
            }
            if(!reference->repeatCnt)   //Si la palabra no estaba, incremento las palabras en el arbol
                numKeys++;
            reference->repeatCnt++; //Incremento el contador de palabras
        }
        
        // retorna la cantidad de veces que una clave se repite. 
        unsigned numReps(const char* key){
            if(!getNumKeys()) return 0; //Si no hay palabras en el Trie no se repiten
            
            int len = strlen(key);  //Establesco el tamanio de mi palabra
            TrieNode *reference = root;
            for(int i=0; i<len; i++){   //Me meto en el arbol para buscarla
            	int index = getIndexForChar(key[i]);
                if(reference->children[index] == nullptr)
                	return 0;   //Si la clave no existe, devuelvo 0
                reference = reference->children[index];
            }
            return reference->repeatCnt;    //Devuelvo la cantidad de palabras
        } 

        unsigned getNumKeys() {
            return numKeys;
        }
        vector<StatWord> collect() const{   //Tengo que ir metiendome en el arbol y sacar las palabras
            vector<StatWord> result;
            TrieNode * reference = root;



        }

    private:
        static const unsigned ALPHABET_SIZE = 26;

        struct TrieNode {
            TrieNode(): repeatCnt(0) {
                for(int i=0; i<ALPHABET_SIZE; i++)  //Pongo a todos los hijos como nulos
                	children[i] = nullptr;
            }
            ~TrieNode(){
                for(int i=0; i<ALPHABET_SIZE; i++)  //Deleteo todos los children
                    delete children[i];
            }

            unsigned repeatCnt;       //  0: es solo prefix
                                      // >0: cantidad de veces que la clave se repitio
            
            struct TrieNode* children[ALPHABET_SIZE];
        };

        TrieNode* root; // contenedor real de datos 
        unsigned numKeys; // n�mero de claves en el trie
        vector<StatWord> stat; 

        static int getIndexForChar(int c){
	        int ret = toupper(c) - 'A';     //  calcula el indice pasando la letra a may�scula
	        assert(ret >= 0 && ret < ALPHABET_SIZE);
	        return ret;
        }

        // funci�n auxiliar: retorna el caracter que le corresponde a un indice dado
        static char getCharForIndex(int i){
	        assert(i >= 0 && i < ALPHABET_SIZE);
	        return i + 'A';
        }
};


// TODO  TreeCollectable

// prueba del collectable para analizar la ley de Zipf
void Zipf(const Collectable& c) {
    vector<StatWord> words = c.collect();
    sort(words.rbegin(), words.rend());

    cout << "Stats for words: " << endl;
    for (const auto& x : words)
        cout << x.word << " : " << x.repeatCnt << endl;
}

int main()
{
    ifstream in("palabras");

    TrieCollectable trieColl;
    TreeCollectable treeColl;

    string s;
    while (in >> s) {
        trieColl.insertKey(s.c_str());
        treeColl.addWord(s);
    }

    cout << "con TrieCollectable: " << endl;
    Zipf(trieColl);

    cout << "con TreeCollectable: " << endl;
    Zipf(treeColl);

    return 0;

}


