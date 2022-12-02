#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode;

using Tree = TreeNode *;

const Tree EmptyTree = nullptr;

struct TreeNode {
	int valor;
	Tree left;
	Tree right;
	TreeNode(int v): valor(v) {}
	~TreeNode(){
		delete left;
		delete right;
	}
};

Tree TreeInsert(Tree t, int v)
{
	if (t == EmptyTree)
		return new TreeNode(v);
	if (v < t->valor)
		t->left = TreeInsert(t->left, v);
	else
		t->right = TreeInsert(t->right, v);
	return t;
}

std::vector<int> serializar(Tree t1){
	// static vector<int> result;

	if(t1 != EmptyTree){
		vector<int> result1 = serializar(t1->right);	//Busco para las dos ramas del arbol
		vector<int> result2 = serializar(t1->left);
		vector<int> res(result1.size() + result2.size());	//Creo un nuevo contenedor del resultado
		merge(result1.begin(), result1.end(), result2.begin(), result2.end(), res.begin());	//Junto los dos vectores
		res.push_back(t1->valor);	//Meto el elemnto que falta
		return res;	//devuelvo el resultado
	}else{
		return vector<int>();	//Si es nulo devuelvo un vector vacio
	}
}
bool arboles_semejantes(Tree t1, Tree t2){
	vector<int> T1 = serializar(t1);
	vector<int> T2 = serializar(t2);
	if(T1.size() != T2.size()){	//Si no son del mismo tamanio, ya se que no son semejantes
		return false;
	}
	//ordeno los vectores
	sort(T1.begin(), T1.end());
	sort(T2.begin(), T2.end());

	return T1 == T2;	//Devuelvo si son iguales
}
int numNodos(Tree t)
{
	if (t == EmptyTree)
		return 0;
	return 1 + numNodos(t->left) + numNodos(t->right);
}
bool esta_balanceado(Tree t)
{
	if (t == EmptyTree)
		return true;

	int numNodos_left = numNodos(t->left);
	int numNodos_right = numNodos(t->right);
	if (abs(numNodos_left - numNodos_right) > 1)
		return false;

	return esta_balanceado(t->left) && esta_balanceado(t->right);
}

Tree balancear(Tree t){
	if(esta_balanceado(t))	//Si ya esta balanceado, delvolvemos el mismo arbol
		return t;
	if(t == EmptyTree)
		return t;

	//Sino se comienza el proceso para balancear
	vector<int> res = serializar(t);	//Primero serializo el arbol
	sort(res.begin(), res.end());		//Despues lo ordeno
	

	vector<int> first, second; 	//Creo los vectores para contener las dos mitades
	size_t n = res.size();
	//Posible mejora con funcion de algortim
	for(int i=0; i<n/2; i++){	//Dividimos en la mitad
		first.push_back(res[i]);
		if(i == (n/2-1))	//Para evitar poner la mitad
			continue;
		second.push_back(res[n - i -1 ]);
	}

	cout << endl;
	Tree t_res = EmptyTree;
	t_res = TreeInsert(t_res, res.at(n/2)); //Inserto el elemento del medio en el arbol

	for(auto a: first)
		t_res = TreeInsert(t_res, a);		//Inserto a la izqueirda los primeros elementos
	for(auto b: second)
		t_res = TreeInsert(t_res, b);	//Inserto los demas a la derecha

	t_res = balancear(t->right);	//balanceo el arbol de la derecha
	t_res = balancear(t->left);		//balanceo el arbol de la izquierda

	return t_res;
};



int main() {

	Tree t1 = EmptyTree;
	Tree t2 = EmptyTree;
	for (int i = 0; i < 100; i++) {
		t1 = TreeInsert(t1, i);
		t2 = TreeInsert(t2, 99-i);
	}
	// for (int i = 0; i < 100; i++) {	//Descomentar para verificar la funcionalidad de semejanets
	// 	t1 = TreeInsert(t1, i);
	// }
	// for (int i = 0; i < 50; i++) {
	// 	t2 = TreeInsert(t2, i);
	// }
	

	cout << " semejantes: " << arboles_semejantes(t1, t2) << endl;

	Tree t = balancear(t1);


	cout << "numNodos t : " << numNodos(t) << endl;
	cout << "numNodos t1: " << numNodos(t1) << endl;
	cout << "Balance  t:  " << esta_balanceado(t) << endl;  
	cout << "Balance t1:  " << esta_balanceado(t1) << endl; 
	cout << "Balance t2:  " << esta_balanceado(t2) << endl; 

	delete t;
	delete t1;
	delete t2;

	return 0;
}
