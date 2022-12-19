#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <set>

using namespace std;

class Block;

class AlgebraicLoop
{
	public:
		AlgebraicLoop();
		~AlgebraicLoop(); 
		// agrega un puntero a bloque al loop algebraico
		void addBlock(Block*); //TODO
		// imprime el loop 
		void print() const;
		// retorna verdadero si el loop ya esta cerrado
		bool isClosed() const;
		// operador de comparación por <
		bool operator<(const AlgebraicLoop & otro) const; //TODO
	private:
		// indica si el loop ya esta cerrado
		bool closed;
		// lista de los bloques que componen el loop en el orden del flujo de señales
		list<Block*> al;
		// los mismos bloques, pero ordenada por valor Block*
		set<Block*> ordered;
};

// representa un bloque del diagrama cuyas salidas se conectan con los bloques contenidos en output
class Block
{
	public:
		Block(string name, bool dft);
		~Block(); 
		// conecta la salida de este bloque con la entrada del bloque apuntado por pb
		void connectBlock(Block* pb);
		// retorna el nombre del bloque
		const string& getName() { return name; }
		// busca recursivamente todos los loops algebraicos comenzando desde este bloque
		// y va armando todos los loops que encuentra en la lista que retorna
		list<AlgebraicLoop> getAlgebraicLoops(); //TODO
	private:
		// nombre del bloque
		string name;
		// verdadero si la salida a tiempo t depende de la entrada a tiempo t
		bool direct_feedthrough;
		// para marcar que ya lo visite en la busqueda de loops algebraicos
		bool visitado;
		// solo me interesa con que bloques se conecta a la salida
		vector<Block *> output;
};


// representa un diagrama de bloques completo
class Diagram
{
	public:
		// el constructor recibe los nombres de los archvios con la descripcion de los bloques y con la matriz de adyacencia
		Diagram(string block_desc_file, string adj_matrix_file); 
		~Diagram();
		// retorna todos los loops algebraicos encontraods
		set<AlgebraicLoop> getAlgebraicLoops(); // TODO
	private:
		// contenedor de todos los bloques del diagrama
		vector<Block> blocks;
};

/////////////////////////////////////////////////////////////////////////////////////
AlgebraicLoop::AlgebraicLoop() :closed(false)
{
}

AlgebraicLoop::~AlgebraicLoop() // capcioso
{
}

void AlgebraicLoop::addBlock(Block *pb)
{
	// si pb es igual al primer bloque del loop, se cerro y ya no debo agregarlo
	if (!al.empty() && pb == al.back())
		closed = true;
	else
	{
		al.push_front(pb);
		ordered.insert(pb);
	}
}

void AlgebraicLoop::print() const
{
	for (auto pb : al)
	{
		cout << "[" << pb->getName() << "]->";
	}
	cout << "[...]" << endl;
}

bool AlgebraicLoop::isClosed() const
{
	return closed;
}

bool AlgebraicLoop::operator<(const AlgebraicLoop & otro) const
{
	return (ordered < otro.ordered);
}

Block::Block(string name, bool dft) :name(name), direct_feedthrough(dft), visitado(false)
{
}

Block::~Block()
{
}

void Block::connectBlock(Block*b)
{
	output.push_back(b);
}

list<AlgebraicLoop> Block::getAlgebraicLoops()
{
	// la lista que voy a retornar
	list<AlgebraicLoop> als;
	// casos particulares:
	// 1) ya fui visitado => se cerro un loop algebraico
	if (visitado)
	{
		AlgebraicLoop al;
		al.addBlock(this);
		als.push_front(al);
		// lo desmarco cuando pegue la vuelta
		return als;
	}

	//2) si no soy direct feedthrough se rompe el loop algebraico
	if (!direct_feedthrough)
		return als; // retorno lista vacia

	// caso general: (es dft y no fue visitado antes)
	// lo marco como visitado 
	visitado = true;
	
	// para cada uno de los bloques conectados a la salida busco loops algebraicos
	for (Block * p : output)
	{
		list<AlgebraicLoop> alsp= p->getAlgebraicLoops();
		//recorro todos los loops que encontre y me agrego a los que no esten cerrados
		for (auto &al : alsp)
		{
			if (!al.isClosed())
				al.addBlock(this);
		}
		for (auto &al:alsp)
			als.push_back(al);
	}

	// desmarco el visitado
	visitado = false;
	return als;
}

Diagram::Diagram(string block_desc_file, string adj_matrix_file)
{
	string name;
	int dft;

	ifstream bf(block_desc_file);
	if (!bf.is_open())
		throw (string("Error abriendo archivo: ") + block_desc_file);
	while (bf >> name >> dft)
	{
		blocks.push_back({ name,dft == 1 });
	}
	bf.close();

	int con;
	ifstream adjf(adj_matrix_file);
	if (!adjf.is_open())
		throw (string("Error abriendo archivo: ") + adj_matrix_file);
	for (size_t i = 0; i < blocks.size(); ++i)
		for (size_t j = 0; j < blocks.size(); ++j)
		{
			adjf >> con;
			if (con)
				blocks[i].connectBlock(&blocks[j]);
		}
	adjf.close();
}

Diagram::~Diagram()
{
}

set<AlgebraicLoop> Diagram::getAlgebraicLoops()
{
	set<AlgebraicLoop> ret;
	list<AlgebraicLoop> als;
	for (Block& b : blocks)
	{
		als=b.getAlgebraicLoops();
		for (auto al : als)
		{
				ret.insert(al);
		}
	}

	return ret;
}

int main()
{
	try {
		vector<string>bf = { "bloques_sin.txt" ,"bloques_con.txt" };

		for (auto f : bf)
		{
			Diagram diag(f, "matriz_adyacencia.txt");
			set<AlgebraicLoop> als = diag.getAlgebraicLoops();
			if (als.size() == 0)
				cout << "No hay loops algebraicos en el diagrama " << f << endl;
			else
				cout << "Encontre " << als.size() << " loops algebraicos en el diagrama " << f << endl;
			for (auto al : als)
				al.print();
		}
		return 0;
	}
	catch (string & e)
	{
		cout << e << endl;
		return -1;
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
		return -2;
	}
}
