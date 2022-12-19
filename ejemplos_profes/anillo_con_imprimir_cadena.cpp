#include<iostream>

using namespace std;

struct Tipo_Anillo
{
	
	Tipo_Anillo(unsigned int Numero_eslabones)
	{
		idx=0;
		cout << "Construyendo eslabon " << idx << endl;
		
		if (Numero_eslabones>0)
			eslabon_Siguiente = new Tipo_Anillo(Numero_eslabones-1,1,this);
		else
			eslabon_Siguiente = nullptr;
		
		//INFO IMPORTANTE:
		//El operador new devuelve la direccion de memoria del bloque que acaba de reservar (alocar). Por eso un puntero que se quiere que apunte a un pedazo de memoria reservado se iguala a new Constructor();
		//nullptr significa que no apunta a ningun lado. Es como si valiera 0, y se usa, por ejemplo, para saber cuando necesitamos o no liberar memoria de forma automatica. Ver destructor.
	}
	
	~Tipo_Anillo()
	{
		cout << "Destruyendo eslabon " << idx << endl;
		if (eslabon_Siguiente->get_idx()!=0)
		{
			cout << "Intentando desalocar eslabon siguiente" << endl;
			delete eslabon_Siguiente;
		}
		
		//INFO IMPORTANTE:
		//Cuando se llama a delete para liberar memoria asociada a un objeto (struct o class UDT), el destructor del objeto es llamado ANTES de llevar a cabo la liberacion de memoria (si posee un destructor). Ejecutar y observar lo que se imprime en pantalla.
	}
	
	void imprimir_anillo()
	{
		cout << "Eslabon " << idx << endl;
		if (eslabon_Siguiente->get_idx()!=0)
		{
			eslabon_Siguiente->imprimir_anillo();
		}
	}
	
	int get_idx()
	{
		return idx;
	}

	private:
	Tipo_Anillo *eslabon_Siguiente;
	int idx;
	
	Tipo_Anillo(unsigned int Numero_eslabones, unsigned int indice, Tipo_Anillo *primero)
	{
		idx=indice;
		cout << "Construyendo eslabon " << idx << endl;

		if (Numero_eslabones>0)
			eslabon_Siguiente = new Tipo_Anillo(Numero_eslabones-1,indice+1,primero);
		else
			eslabon_Siguiente = primero;
			
	//INFO IMPORTANTE: Un constructor privado no sirve desde el main, pero puede ser llamado desde otro constructor publico. No olvidar que se pueden tener tantos constructores como uno quiera, siempre que tengan distintos tipos y/o cantidad de argumentos. 
	}
	
	//INFO:
	//Los struct ponen todo como public: por defecto, por lo que si queremos que algo no sea accesible desde fuera del UDT hay que ponerle private:
	//Los class son opuestos en este tema, por defecto todo es private:, asi que hay que poner como public lo que se quiera que lo sea.
};

int main()
{
	unsigned int N;
	cout << "Cuantos eslabones quiere en su anillo? ";
	cin >> N;
	Tipo_Anillo Anillo(N-1);
	
	Anillo.imprimir_anillo();
	
	return 0;
}

