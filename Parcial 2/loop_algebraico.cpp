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
		bool isClosed() const { return closed; }
		// operador de comparaci�n por <
		bool operator<(const AlgebraicLoop & otro) const; //TODO
	private:
		// indica si el loop ya esta cerrado
		bool closed;
		// lista de los bloques que componen el loop en el orden del flujo de se�ales
		list<Block*> al;
		// los mismos bloques, pero ordenada por valor Block*
		set<Block*> ordered;
};

// representa un bloque del diagrama cuyas salidas se conectan con los bloques contenidos en output
class Block
{
	public:
		Block(const string &name, bool dft);
		~Block();
		// conecta la salida de este bloque con la entrada del bloque apuntado por pb
		void connectBlock(Block* pb);
		// retorna el nombre del bloque
		const string& getName() { return name; }
		// busca recursivamente todos los loops algebraicos comenzando desde este bloque
		// y va armando todos los loops que encuentra en la lista que retorna
		list<AlgebraicLoop> getAlgebraicLoops(); //TODO
		// AlgebraicLoop search_loops(Block *block);
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
		Diagram(const char *block_desc_file, const char *adj_matrix_file); 
		~Diagram();
		// retorna todos los loops algebraicos encontraods
		set<AlgebraicLoop> getAlgebraicLoops(); // TODO
	private:
		// contenedor de todos los bloques del diagrama
		vector<Block> blocks;
};

/////////////////////////////////////////////////////////////////////////////////////
AlgebraicLoop::AlgebraicLoop() :closed(false) {}

AlgebraicLoop::~AlgebraicLoop(){}

void AlgebraicLoop::print() const
{
	for (auto pb : al)
	{
		cout << "[" << pb->getName() << "]->";
	}
	cout << "[...]" << endl;
}


void AlgebraicLoop::addBlock(Block* a){
	al.push_back(a);	//Agrego el bloque
	ordered.insert(a);	//Agrego al set

}
bool AlgebraicLoop::operator<(const AlgebraicLoop & otro) const{
	return (al.size() < otro.al.size());	//Compara por cantidad de bloques en el loop	
}

Block::Block(const string &name_, bool dft) :name(name_), direct_feedthrough(dft), visitado(false){}

Block::~Block(){}

void Block::connectBlock(Block*b)
{
	output.push_back(b);
}
//Funcion q busque todos los loops
list<AlgebraicLoop> Block::getAlgebraicLoops(){
	
}

// list<AlgebraicLoop> Block::getAlgebraicLoops(){
// 	static list<AlgebraicLoop> res;	//Creo una lista donde ir metiendo las cosas

// 	for(int i = 0; i < output.size(); i++){	//Chequeo cada una de las salidas
// 		Block * dato = output.at(i);

// 		if(dato == this){		//Si llegamos al bloque de donde partimos, devolvemos este loop
// 			AlgebraicLoop p;
// 			p.addBlock(dato);
// 			list<AlgebraicLoop> r;
// 			r.push_back(p);
// 			return r;
// 		}
// 		if(dato == nullptr)	//Si no hya bloque, devolvemos una lista vacia
// 			return list<AlgebraicLoop>();
		
// 		if(!dato->visitado){		//Si no lo visite, la visito
// 			dato->visitado = true;	//Marco visita
// 			AlgebraicLoop a;
// 			a.addBlock(dato);		//Agregamos el dato
// 			res = dato->getAlgebraicLoops();	//Busco los loops a partir de esta salida
// 			if(res.size() == 0)
// 				return list<AlgebraicLoop>();	//Si no encontro, esta salida no esta en loop

// 			res.push_back(a);	//Agregamos la salida en la que buscamos
// 		}	
// 	}
// 	return res;	//Devuelvo la lista con los loops
// }
// list<AlgebraicLoop> Block::getAlgebraicLoops(){
// 	list<AlgebraicLoop> result;
// 	for(auto &a : output){
// 		if(AlgebraicLoop() < search_loops(a))	//Si no esta vacio, lo agrego
// 			result.push_back(search_loops(a));
// 	}
// 	return result;


// }
// AlgebraicLoop Block::search_loops(Block *block){
// 	static AlgebraicLoop loop;

// 	if(block->direct_feedthrough == 0)	//Pregunta si es de alimentacion directa
// 		return AlgebraicLoop();
// 	if(block == this){
// 		AlgebraicLoop p;
// 		p.addBlock(this);
// 		return p;
// 	}
// 	if(!block->visitado){	//Pregunto si un bloque fue visitado
// 		block->visitado = true;	//Lo visito
// 		for(int i = 0; i < block->output.size(); i++){	//Chequeo en cada una de las salidas del bloque
// 			AlgebraicLoop loop_prov = search_loops(block->output[i]);
// 			if(loop_prov < AlgebraicLoop()){	//Si es mas chico que un loop vacio
// 				return AlgebraicLoop();	//retorno un loop vacio
// 			}
// 			else{
// 				loop_prov.addBlock(block);	//Sino, anado el bloque actual y retorno
// 			}
// 			loop = loop_prov;
// 		}
// 	}
// 	return loop;
// }

Diagram::Diagram(const char *block_desc_file, const char *adj_matrix_file)
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

Diagram::~Diagram(){}

set<AlgebraicLoop> Diagram::getAlgebraicLoops(){
	set<AlgebraicLoop> result;
	for(int i = 0; i < blocks.size(); ++i){
		list<AlgebraicLoop> r = blocks[i].getAlgebraicLoops();	//Busco los loops en cada bloque
		// cout << r.size() << endl;
		for(auto a: r)
			result.insert(a);
	}
	return result;

}

int main()
{
	try {
		const char *bf[] = { "bloques_sin.txt" ,"bloques_con.txt" };

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
		return 1;
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
		return 2;
	}
}
