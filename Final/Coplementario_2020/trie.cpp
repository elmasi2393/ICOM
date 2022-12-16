
class Trie {
    public:
        Trie();    // TODO 
        ~Trie();   // TODO 

        // inserta una nueva clave si no está presente
        // o incrementa el repeatCnt si la clave existía previamente. 
        void insertKey(const char* key); // TODO 
        
        // retorna la cantidad de veces que una clave se repite. 
        unsigned numReps(const char* key); // TODO 

        unsigned getNumKeys() {
            return numKeys;
        }

    private:
        static const unsigned ALPHABET_SIZE = 26;

        struct TrieNode {
            TrieNode();     // TODO
            ~TrieNode();    // TODO

            unsigned repeatCnt;       //  0: es solo prefix
                                      // >0: cantidad de veces que la clave se repitio
            
            struct TrieNode* children[ALPHABET_SIZE];
        };

        TrieNode* root; // contenedor real de datos 
        unsigned numKeys; // número de claves en el trie 
};

