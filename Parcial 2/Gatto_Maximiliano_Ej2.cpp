#include <unordered_map>
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

#define N_COLS 20
#define N_FILS 20

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2> &pair) const
	{
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

class SparseMatrix
{
public:
	SparseMatrix(size_t nf, size_t nc): nfils(nf), ncols(nc) {
		elts.reserve(nfils*ncols);	//Reservo el espacio para alocar los elementos
	}

	// impone el valor del elemento (i,j)
	void setElement(size_t i, size_t j, double val){
		// cout << "setElement: " << i << " , " << j << endl;
		elts[pair(i, j)]= val;	//Guardo el valor en el par i, j
	}

	// recupera el valor correspondiente al elemento (i,j)
	// Hint: no utilizar [] sobre el mapa para evitar la creación automágica
	// de elementos no existentes.
	double getElement(size_t i, size_t j) const{
		auto val = elts.find(pair(i,j));
		if(val != elts.end())
			return elts.at(pair(i, j));	//Devuelvo el elemento de la posicion i, j
		return 0;
	}

	void print() const{
		//printer
		for(int i = 0; i < ncols; i++){			//Recorro todas las columnas
			for(int j = 0; j < nfils; j++){		//Recorro todas las filas
				cout << getElement(i, j) << " ";
			}
			cout << endl;
		}
	}
	
	SparseMatrix operator*(const SparseMatrix &m){
		if(ncols == m.nfils){
			SparseMatrix result(nfils, ncols);
			for(int i = 0; i < nfils; i++){
				for(int j = 0; j < m.ncols; j++){
					double r = 0;
					for(int k = 0; k < nfils; k++){
						r += getElement(k, j) * m.getElement(j, k);
					}
					result.setElement(j, i, r);
				}
			}
			return result;
		}
		return SparseMatrix(0, 0);	//Sino retorna una matriz nula


	}


private:
	size_t nfils, ncols;

	unordered_map<pair<size_t, size_t>, double, pair_hash> elts;
};

int main()
{
	srand(time(NULL));
	SparseMatrix mat(N_FILS, N_COLS);

	// fill with some values
	for (size_t i = 0; i < size_t(N_FILS * N_COLS * 0.2); i++)
	{
		mat.setElement(rand() % N_FILS, rand() % N_COLS, i);
	}

	mat.print();
	SparseMatrix mat1(mat*mat);
	mat1.print();
	
	return 0;
}