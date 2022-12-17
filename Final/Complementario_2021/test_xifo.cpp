#include <iostream>
#include <vector>
#include <list>

using namespace std;


class FIFO_IF {
public:
	// agrega un nuevo elemento, excepcion cuando el contenedor esta lleno
	virtual void put(int e) = 0;

	// recupera el elemento m�s viejo, excepcion cuando el contenedor esta vac�o
	virtual int  get() = 0;

	// chequea si el contenedor est� vac�o
	virtual bool isEmpty() = 0;

	// vac�a el contenedor
	virtual void clear() = 0;


	struct ERROR_FIFO_FULL {};
	struct ERROR_FIFO_EMPTY {};
};

class LIFO_IF {
public:
	// agrega un nuevo elemento, excepcion cuando el contenedor esta lleno
	virtual void push(int e) = 0;

	// recupera el elemento m�s nuevo, excepcion cuando el contenedor esta vac�o
	virtual int  pop() = 0;

	// chequea si el contenedor est� vac�o
	virtual bool isEmpty() = 0;

	// vac�a el contenedor
	virtual void clear() = 0;

	struct ERROR_LIFO_FULL {};
	struct ERROR_LIFO_EMPTY {};
};

// TODO
// class VectorAsFIFO;
class VectorAsFIFO: public FIFO_IF{
	public:
		void put(int e){
			try{
				if(contenedor.size() >= n_max)
					throw(ERROR_FIFO_FULL());
				contenedor.push_back(e);
			}catch(ERROR_FIFO_FULL &e){
				cerr << "Pila llena" << endl;
			}
			
		}

		// recupera el elemento m�s nuevo, excepcion cuando el contenedor esta vac�o
		int get(){
			try{
				if(isEmpty())
					throw ERROR_FIFO_EMPTY();
				
				int res = contenedor.at(0);			//Saco el primero
				contenedor.erase(contenedor.begin());	//Elimino el primero del contenedor
				return res;		//Devuelvo el primer elemento

			}catch(ERROR_FIFO_EMPTY &e){
				cerr << "Pila Vacia" << endl;
			}
			return 0;
		}

		// chequea si el contenedor est� vac�o
		bool isEmpty(){ return contenedor.empty();}

		// vac�a el contenedor
		void clear() { contenedor.clear();}
	private:
		vector<int> contenedor;
		const int n_max = 100;

};
// class VectorAsLIFO;
class VectorAsLIFO: public LIFO_IF{
	public:
		// agrega un nuevo elemento, excepcion cuando el contenedor esta lleno
		void push(int e){
			try{
				if(contenedor.size() >= n_max)
					throw ERROR_LIFO_EMPTY();
				contenedor.push_back(e);
			}catch(ERROR_LIFO_EMPTY &e){
				cerr << "Pila vacia" << endl;
			}
		}

		// recupera el elemento m�s nuevo, excepcion cuando el contenedor esta vac�o
		int  pop(){
			try{
				if(isEmpty())
					throw ERROR_LIFO_EMPTY();	//Si no esta vacio
				int res = contenedor.back();	//recupero el ultimo elemento
				contenedor.pop_back();	//Elimino el ultimo elemento
				return res;	//devuelvo el ultimo elemento
			}catch(ERROR_LIFO_EMPTY &e){
				cerr << "Pila vacia" << endl;
			}
			return 0;	//Por defectio, retorno 0 si esta vacia
		}

		// chequea si el contenedor est� vac�o
		bool isEmpty() { return contenedor.empty(); }

		// vac�a el contenedor
		void clear(){ contenedor.clear(); }
	private:
		vector<int> contenedor;
		const int n_max = 100;
};
// class ListAsFIFO;
class ListAsFIFO: public FIFO_IF{
	public:
		// agrega un nuevo elemento, excepcion cuando el contenedor esta lleno
		void put(int e){
			try{
				if(contenedor.size() >= n_max)	//Si la pila esta llena, no sigo poniendo
					throw (ERROR_FIFO_FULL());
				contenedor.push_back(e);
			}catch(ERROR_FIFO_FULL &e){
				cerr << "Pila llena" << endl;
			}
		}

		// recupera el elemento m�s viejo, excepcion cuando el contenedor esta vac�o
		int  get(){
			try{
				if(isEmpty())
					throw (ERROR_FIFO_EMPTY());
				int result = contenedor.front();	//Busco el primero
				contenedor.pop_front();				//Elimino el primer elemento
				return result;		//Devuelvo el primer elemento
			}catch(ERROR_FIFO_EMPTY &e){
				cerr << "Pila vacia" << endl;
			}
			return 0;	//Por defecto devuelvo 0
		}

		// chequea si el contenedor est� vac�o
		bool isEmpty(){ return contenedor.empty();}

		// vac�a el contenedor
		void clear(){ contenedor.clear();}
	private:
		list<int> contenedor;
		const int n_max = 100;
};
// class ListAsLIFO;
class ListAsLIFO: public LIFO_IF{
	public:
		// agrega un nuevo elemento, excepcion cuando el contenedor esta lleno
		void push(int e){
			try{
				if(contenedor.size() >= n_max)
					throw ERROR_LIFO_FULL();	//Si esta llena, levanto excepcion
				contenedor.push_back(e);	//Si no esta llena, meto un elemento
			}catch(ERROR_LIFO_FULL &e){
				cerr << "Pila llena" << endl;
			}
		}

		// recupera el elemento m�s nuevo, excepcion cuando el contenedor esta vac�o
		int pop(){
			try{
				if(isEmpty())
					throw ERROR_LIFO_EMPTY();	//Si esta vacia, levanto excepcion
				int result = contenedor.back();	//Extraigo el ultimo elemento
				contenedor.pop_back();	//Lo elimino
				return result;	//Devuelvo el resultado
			}catch(ERROR_LIFO_EMPTY &e){
				cerr << "Pila vacia" << endl;
			}
			return 0; //devuelvo 0 por defecto
		}

		// chequea si el contenedor est� vac�o
		bool isEmpty(){ return contenedor.empty(); }

		// vac�a el contenedor
		void clear(){ contenedor.clear();}
	private:
		list<int> contenedor;
		int n_max = 100;
};

bool testFIFO(FIFO_IF* pFifo)
{
	pFifo->clear();
	const size_t count = 100;
	for (size_t i = 0; i < count; i++)
		pFifo->put(i);

	try
	{
		for (size_t i = 0; i < count; i++) {
			int ret = pFifo->get();
			if (i != ret)
				return false;
		}
	}
	catch (FIFO_IF::ERROR_FIFO_EMPTY ex)
	{
		return false;
	}
	if (pFifo->isEmpty())
		return true;

	return false;
}

bool testLIFO(LIFO_IF* pLifo)
{
	pLifo->clear();
	const size_t count = 100;
	for (size_t i = 0; i < count; i++)
		pLifo->push(i);

	try
	{
		for (size_t i = 0; i < count; i++) {
			int ret = pLifo->pop();
			if (count - i - 1 != ret)
				return false;
		}
	}
	catch (LIFO_IF::ERROR_LIFO_EMPTY ex)
	{
		return false;
	}
	if (pLifo->isEmpty())
		return true;

	return false;
}


int main()
{
	VectorAsFIFO afifo;
	VectorAsLIFO alifo;
	ListAsFIFO lfifo;
	ListAsLIFO llifo;

	cout << "testing VectorAsFIFO: ";
	if (testFIFO(&afifo))
		cout << "OK\n";
	else
		cout << "FAIL\n";

	cout << "testing ListAsFIFO: ";
	if (testFIFO(&lfifo))
		cout << "OK\n";
	else
		cout << "FAIL\n";

	cout << "testing VectorAsLIFO: ";
	if (testLIFO(&alifo))
		cout << "OK\n";
	else
		cout << "FAIL\n";

	cout << "testing ListAsLIFO: ";
	if (testLIFO(&llifo))
		cout << "OK\n";
	else
		cout << "FAIL\n";

	return 0;
}

