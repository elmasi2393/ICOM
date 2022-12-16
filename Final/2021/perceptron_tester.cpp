#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;

//tipos de capa
enum Type {inputLayer,hiddenLayer,outputLayer};

using FunPtr//... //TODO

//numero de pruebas para ver como anda la red
const unsigned int N_runs=100;

double random01(void);

//declaración de funciones de activacion
double ReLu(double );
double Identity(double );
double Sigmoid(double );

//clase base para las distintas "neuronas"
struct Node
{
	double input_sum;
	double output;
	double bias;
	vector<double> weights;	
	
	//funcion de activacion del nodo
	FunPtr activationFunction;
	
	Node(FunPtr actFun); //TODO
	
	virtual ~Node()
	{}
	
	//funcion virtual pura. Setea el input_sum a 0 en capas ocultas y de salida, y no debe hacer
	//nada en capa de entrada 
	//TODO
	virtual void resetInput() = 0; 
	
	//suma al input total
	void addInput(double in_)
	{	input_sum+=in_;	}
	
	//calcula el valor de output del nodo utilizando la funcion de activacion y el input total, y lo
	// guarda para su posterior uso
	void calcOutput();//TODO

};

//nodos adecuados para capa de entrada
struct Input: public Node
{
	Input()
	:Node(Identity)
	{}


};

//nodos adecuados para capas ocultas
struct Hidden: public Node
{	
	Hidden()
	:Node(ReLu)
	{}
	

};

//nodos adecuados para capa de salida
struct Output: public Node
{	
	Output()
	:Node(Sigmoid)
	{}
	
	
};

//capa
struct Layer
{
	vector<Node *> neurons; //nodos de la capa
	Type layer_type; //tipo de la capa
	
	//l_t tipo de capa, N cantidad de nodos en la capa
	Layer(Type l_t,unsigned short int N); //TODO 
	
	~Layer(); //TODO
	
	//para facilitar el acceso al tamaño del vector de "neuronas"
	unsigned int nsize()
	{
		return neurons.size();
	}
	
	//guarda los pesos
	void setWeights(const vector<vector<double>> & w)
	{
		if (layer_type!=inputLayer)
		{
			for (unsigned int i=0; i<neurons.size();i++)
			{
					neurons.at(i)->weights = w.at(i);				
			}
		}
	}
	
	//guarda los bias
	void setBias(const vector<double> & b)
	{
		if (layer_type!=inputLayer)
		{
			for (unsigned int i=0; i<neurons.size();i++)
			{
				neurons.at(i)->bias = b.at(i);				
			}
		}
	}
	
	//resetea el valor de input de los nodos de la capa
	void resetInputs()
	{	
		for (unsigned int i=0; i<neurons.size();i++)
			neurons.at(i)->resetInput();	
	}
	
	//le asigna el valor de input a los nodos de la capa
	void setInputs(Layer * layerIn)
	{	
		for (unsigned int i=0; i<neurons.size();i++)
		{
			for (unsigned int j=0; j<neurons.at(i)->weights.size();j++)
			{
				neurons.at(i)->addInput(neurons.at(i)->weights.at(j) * layerIn->neurons.at(j)->output);
			}
				neurons.at(i)->addInput(neurons.at(i)->bias);	
		}
	}
	
	//calcula el output de los nodos de la capa
	void calculateOutputs(Layer *layerIn)
	{	
		resetInputs();
		setInputs(layerIn);
		for (unsigned int i=0;i<neurons.size();i++)
			neurons.at(i)->calcOutput();
	}
	
};

//RNA
class Network
{
	vector<Layer *> layers; //capas
	
	bool ok; //si se cargo la RNA desde el archivo correctamente, ok es verdadero, sino es falso
	
	//carga la RNA desde el archivo
	bool load_network(const string &filename)
	{
		ifstream f;
		f.open(filename);
		if (f)
		{
			unsigned int N_layers,N_neurons;
			double aux_weight, aux_bias;
			vector<double> aux_W, aux_B;
			vector<vector<double>> W;
		
			f >> N_layers;
			f.ignore();
			
			f >> N_neurons;
			f.ignore();
			
			layers.push_back(new Layer (inputLayer,N_neurons));
			
			for (unsigned int i=1;i<N_layers-1;i++)
			{
				f >> N_neurons;
				f.ignore();
				
				layers.push_back(new Layer (hiddenLayer,N_neurons));
				
			}
			f >> N_neurons;
			f.ignore();
				
			layers.push_back(new Layer (outputLayer,N_neurons));
			
			//leo los weights y biases
			for (unsigned int i=1;i<layers.size();i++)
			{
				for (unsigned int j=0;j<layers.at(i)->nsize();j++)
				{
					for (unsigned int k=0;k<layers.at(i-1)->nsize();k++)
					{
						f >> aux_weight;
						f.ignore();
						aux_W.push_back(aux_weight);
					}
					W.push_back(aux_W);
					aux_W.clear();
					
					f >> aux_bias;
					f.ignore();
					
					aux_B.push_back(aux_bias);
				}
				layers.at(i)->setWeights(W);
				layers.at(i)->setBias(aux_B);
				W.clear();
				aux_B.clear();				
			}
			f.close();
			return true;	
		}
		else
		{
 		    cout << "Error en la apertura del archivo: " << filename << endl;
 		    return false;
		}
			
	}
	
	
	public:	
	
	Network(const string &filename); //TODO
	
	~Network(); //TODO
	
	bool loaded()
	{
	    return ok;
	}
	
	//este método calcula el resultado para el caso particular presentado en RNA.txt
	bool run(double in_1, double in_2)
	{	
		layers.at(0)->neurons.at(0)->output=in_1;
		layers.at(0)->neurons.at(1)->output=in_2;
		
		cout.precision(4);
		
		for (unsigned int i=1;i<layers.size();i++)
		{
			layers.at(i)->calculateOutputs(layers.at(i-1));
		}
		if (layers.at(layers.size()-1)->neurons.at(0)->output>0.5)
		{
			cout << fixed << in_1 << " > " << fixed << in_2 << "\t\tCerteza: "<< fixed <<100.*layers.at(layers.size()-1)->neurons.at(0)->output << "%" ;
			
			if (in_1>in_2)
			{
				cout << "\tCORRECTO! :)" << endl;
				return true;
			}
			else
			{
				cout << "\tFALSO...  :(" << endl;
				return false;
			}
		}
		else
		{
			cout << fixed << in_1 << " < " << fixed << in_2 << "\t\tCerteza: "<< fixed << 100.*(1-layers.at(layers.size()-1)->neurons.at(0)->output) << "%" ;
			
			if (in_1<in_2)
			{
				cout << "\tCORRECTO! :)" << endl;
				return true;
			}
			else
			{
				cout << "\tFALSO...  :(" << endl;
				return false;
			}
		}
	}
	
	//imprime los pesos de las distintas "sinapsis" y bisases de la RNA
	void print_network()
	{
		cout << "ARQUITECTURA RNA:" << endl;
		for (unsigned int i=1;i<layers.size();i++)
			{
				for (unsigned int j=0;j<layers.at(i)->nsize();j++)
				{
					for (unsigned int k=0;k<layers.at(i-1)->nsize();k++)
					{
						cout << "capa: " << i << " "<< " nodo: " << j << " conexion con nodo "<< k << " de capa " << i-1<< " peso: " << layers.at(i)->neurons.at(j)->weights.at(k) << endl;
					}
					
					cout << "capa: " << i << " nodo: "<< j << " bias: " << layers.at(i)->neurons.at(j)->bias << endl;
				}			
			}
		cout << endl;
	}
	
};

int main() 
{
	srand(time(0));
 
 	Network test("RNA.txt");
 	
 	if (test.loaded())
 	{
 		unsigned int N_true=0;
 		test.print_network();
 		cout << "PRUEBA DE FUNCIONAMIENTO: " << endl;
 		for (unsigned int i=0;i<N_runs;i++)
 		{
 			if (test.run(random01(),random01()))
 				N_true++;
 		}
 		cout.precision(2);
 		cout << endl <<"PRUEBA FINALIZADA. ACIERTOS: " <<fixed<< N_true*100./N_runs<< "%" << endl;
 	}

   	return 0;
}

//devuelve un valor aleatorio entre 0 y 1
double random01(void)
{
    return ((double)rand()/(double)RAND_MAX);
}

//funcion de activaciond e tipo ReLu
double ReLu(double x)
{
	return (x<=0? 0 : x);
}

//funcion de activacion identidad
double Identity(double x)
{
	return (x);
}

//funcion de activacion sigmoide
double Sigmoid(double x)
{
	return(1.0/(1.0+exp(-(x-1.)/1.)));
}
