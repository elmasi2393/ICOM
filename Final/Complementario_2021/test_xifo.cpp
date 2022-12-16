#include <iostream>

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
// class VectorAsLIFO;
// class ListAsFIFO;
// class ListAsLIFO;

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
}

