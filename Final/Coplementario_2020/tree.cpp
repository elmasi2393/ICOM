#include <string>

using namespace std;

class Tree {
public:
    Tree();     // TODO
    ~Tree();    // TODO

    // agrega un nuevo nodo (o aumenta el repeatCnt de un nodo existente)
    void addWord(const string& w);  // TODO

    // retorna la cantidad de repeticiones de la palabra dado en el arbol
    unsigned numReps(const string &w); // TODO 
 

private:
    struct TreeNode {
        TreeNode(const string& s);   // TODO

        string word;
        unsigned repeatCnt;
        TreeNode* left;
        TreeNode* right;
    };

    TreeNode* root;
};

