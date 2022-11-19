#include <cassert>
#include <cctype>
#include <string.h>
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

#define ALPHABET_SIZE 26
// funci�n auxiliar: retorna el indice que le corresponde a un caracter dado
static int getIndexForChar(int c)
{
	int ret = toupper(c) - 'A';     //  calcula el indice pasando la letra a may�scula
	assert(ret >= 0 && ret < ALPHABET_SIZE);
	return ret;
}

// funci�n auxiliar: retorna el caracter que le corresponde a un indice dado
static char getCharForIndex(int i)
{
	assert(i >= 0 && i < ALPHABET_SIZE);
	return i + 'A';
}

// Nodo de un Trie
struct TrieNode {
	TrieNode() {
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			children[i] = nullptr;
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			delete children[i];
	}

	int numKeys() {
		if (this == nullptr)
			return 0;
		int ret = 0;
		if (defineKey)
			ret = 1;
		for (int i = 0; i < ALPHABET_SIZE; i++)
			ret += children[i]->numKeys();
		return ret;
	}

	bool defineKey = false;    		                 // true/false si define o no una clave
	TrieNode *children[ALPHABET_SIZE];       // puntero a los hijos de este prefix, 
											 // nullptr si no hay hijo que expanda en esa letra
};

// estructura de un Trie
struct Trie {
	Trie() {
		root = new TrieNode;
	}
	~Trie() {
		delete root;
	}

	// agrega una clave al Trie
	void insertKey(const char key[]) {
		TrieNode* pCursor = root;
		// va recorriendo el prefix, creando nodos si es necesario
		for (size_t level = 0; level < strlen(key); level++) {
			int index = getIndexForChar(key[level]);
			if( pCursor->children[index] == nullptr )
				pCursor->children[index] = new TrieNode;
			pCursor = pCursor->children[index];		//Quedo apuntando al ultimo nodo
		}
		//Cuando se llega al final, marca el nodo como que define una clave
		// marca defineKey en el �ltimo valor de pCursor si es que no estaba ya definido como clave
		if (pCursor->defineKey == false) {	
			pCursor->defineKey = true;
			numKeys++;   // aumento la cantidad de claves del trie
		}
	}
	
	// busca el nodo donde termina un prefix
	TrieNode* searchPrefix(const char key[]) const {
		int length = strlen(key);
		TrieNode* pCursor = root;

		// va recorriendo el prefix
		for (int level = 0; level < length; level++) {
			int index = getIndexForChar(key[level]);
			if (!pCursor->children[index])  // si no se extiende, la clave no existe
				return nullptr;
			pCursor = pCursor->children[index];
		}
		return pCursor;
	}

	bool existKey(const char key[]) {
		int length = strlen(key);
		int index;
		TrieNode* pCursor = searchPrefix(key);
		return pCursor != nullptr && pCursor->defineKey == true;
	}
	int trieNumWordsWithPrefix(const char* prefix) {
		TrieNode* keyNode = searchPrefix(prefix);
		return keyNode->numKeys();
	}

	bool check() {
		int nk = root->numKeys();
		return nk == numKeys;
	}

	TrieNode *root;		    // contenedor real de datos
	unsigned int numKeys = 0;	// n�mero de claves en el trie
};

// TODO
void trieGetEnabledKeys(const Trie* trie, const char* prefix, bool enabledKeys[ALPHABET_SIZE]){
	TrieNode* keyNode = trie->searchPrefix(prefix);	//Indica el TrieNode donde termina

	for(size_t i = 0; i < ALPHABET_SIZE;  i++){		//Activo los caracteres que estan habilitados para ese TrieNode
		if(keyNode->children[i] != nullptr)			//Si el nodo se expande, significa que esa letra esta habilitada
			enabledKeys[i] = true;	//Establesco en true si existe el nodo
		else						
			enabledKeys[i] = false;	//Establesco en false si no existe el nodo
	}
	return;
}

// TODO
using ListWord = list<string>;
ListWord trieGetKeys(const Trie* trie, const char* prefix){
	ListWord list;

	TrieNode* keyNode = trie->searchPrefix(prefix);	//Indica el TrieNode donde termina

	for(size_t i = 0; i < ALPHABET_SIZE; i++){	//Recorro todos los nodos
		if(keyNode->children[i] != nullptr)	{	//Si el puntero es no nulo, significa que existe el nodo y agrego la palabra
			string word = prefix;			//Agrego el prefijo
			cout << "Agrego: " << word << endl;
			word += getCharForIndex(i);	//Agrego la letra
			if(keyNode->children[i]->defineKey){	//Si la letra que expando define una palabra
				list.push_back(word);	//Agrego la palabra a la lista
				cout << "Word pushed: " << word << endl;
			}
			ListWord listAux = trieGetKeys(trie, word.c_str());	//Busco las palabras que se expanden de esa letra
			list.splice(list.end(), listAux);	//Agrego las palabras a la lista
		}
	}
	return list;
}

int main()
{
	Trie* pTrie = new Trie;

	ifstream ifile("calles.txt");
	assert(ifile.is_open());
	string s;

	while (ifile >> s) {
		pTrie->insertKey(s.c_str());
	}

	cout << "Chequeo: " << pTrie->check() << endl;

	bool enabledKeys[ALPHABET_SIZE];
	trieGetEnabledKeys(pTrie, "A", enabledKeys);
	for (auto b : enabledKeys)
		cout << b << " ";
	cout << endl;

	ListWord list = trieGetKeys(pTrie, "M");
	cout << "claves con M =====>\n";
	for (auto& l : list)
		cout << l << endl;

	list = trieGetKeys(pTrie, "MO");
	cout << "claves con MO =====>\n";
	for (auto& l : list)
		cout << l << endl;

	list = trieGetKeys(pTrie, "MOR");
	cout << "claves con MOR =====>\n";
	for (auto& l : list)
		cout << l << endl;


	delete pTrie;

	return 0;
}

