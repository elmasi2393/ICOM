#include <string>
#include <iostream>
#include <fstream>
#include <cassert>


using namespace std;

class Tree {
public:
    Tree(): root(nullptr) {};
    ~Tree(){ delete root; };    //PREGUNTAR

    // agrega un nuevo nodo (o aumenta el repeatCnt de un nodo existente)
    void addWord(const string& w){
        if(root == nullptr){
            root = new TreeNode(w);
            return;
        }

        TreeNode * reference = root;    //Comienzo en la raiz

        while(reference != nullptr){
            if(w < reference->word){         //Si es menor voy a la izqueirda
                if(reference->left == nullptr){
                	reference->left = new TreeNode(w);
                    break;
                }
                reference = reference->left;

            }
            else if(w > reference->word){    //Si es mayor voy a la derecha
                if(reference->right == nullptr){
                	reference->right = new TreeNode(w);
                    break;
                }
                reference = reference->right;
            }
            else{   //Si es igual, rompo e incremento
                reference->repeatCnt++;
                break;
            }
        }
    }


    // retorna la cantidad de repeticiones de la palabra dado en el arbol
    unsigned numReps(const string &w){
        TreeNode * reference = root;
        while(reference != nullptr){
            if(w < reference->word)             //Si es menor, busco a la izqueirda
                reference = reference->left;
            else if(w > reference->word)    //Si es mayor, busco a la derecha
                reference = reference->right;
            else
                return reference->repeatCnt;    //Si es igual, retorno las repeticiones
        }
        return 0; //
    }
 

private:
    struct TreeNode {
        TreeNode(const string& s): word(s), left(nullptr), right(nullptr), repeatCnt(1) {}

        string word;
        unsigned repeatCnt;
        TreeNode* left;
        TreeNode* right;
    };

    TreeNode* root;
};

int main(){
    ifstream file("palabras");
    Tree t;
    try{
        if(!file.is_open())
        	throw runtime_error("No pude abrir el archivo");
        string str;
        while(file >> str){
            // cout << str << endl;
            t.addWord(str);   //Inserto todas las palabras en el arbol
        }
        cout << t.numReps("parque") << endl;
        // string key = "me";
        // cout << t.numReps(key.c_str()) << endl;
        
    }catch(runtime_error& e){
        cout << e.what() << endl;
    }
    return 0;
}
