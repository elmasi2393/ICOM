#include<iostream>

using namespace std;

struct Tipo_Cadena
{
	
	Tipo_Cadena(unsigned int Numero_eslabones)
	{
		idx=0;
		cout << "Construyendo eslabon " << idx << endl;
		
		if (Numero_eslabones>0)
			eslabon_Siguiente = new Tipo_Cadena(Numero_eslabones-1,1);
		else
			eslabon_Siguiente = nullptr;
		
		//INFO IMPORTANTE:
		//El operador new devuelve la direccion de memoria del bloque que acaba de reservar (alocar). Por eso un puntero que se quiere que apunte a un pedazo de memoria reservado se iguala a new Constructor();
		//nullptr significa que no apunta a ningun lado. Es como si valiera 0, y se usa, por ejemplo, para saber cuando necesitamos o no liberar memoria de forma automatica. Ver destructor.
	}
	
	~Tipo_Cadena()
	{
		cout << "Destruyendo eslabon " << idx << endl;
		if (eslabon_Siguiente!=nullptr)
		{
			cout << "Intentando desalocar eslabon siguiente" << endl;
			delete eslabon_Siguiente;
		}
		
		//INFO IMPORTANTE:
		//Cuando se llama a delete para liberar memoria asociada a un objeto (struct o class UDT), el destructor del objeto es llamado ANTES de llevar a cabo la liberacion de memoria (si posee un destructor). Ejecutar y observar lo que se imprime en pantalla.
	}
	
	void imprimir_cadena()
	{
		cout << "Eslabon " << idx << endl;
		if (eslabon_Siguiente!=nullptr)
		{
			eslabon_Siguiente->imprimir_cadena();
		}
	}

	private:
	Tipo_Cadena *eslabon_Siguiente;
	unsigned int idx;
	
	Tipo_Cadena(unsigned int Numero_eslabones, unsigned int indice)
	{
		idx=indice;
		cout << "Construyendo eslabon " << idx << endl;

		if (Numero_eslabones>0)
			eslabon_Siguiente = new Tipo_Cadena(Numero_eslabones-1,indice+1);
		else
			eslabon_Siguiente = nullptr;
			
	//INFO IMPORTANTE: Un constructor privado no sirve desde el main, pero puede ser llamado desde otro constructor publico. No olvidar que se pueden tener tantos constructores como uno quiera, siempre que tengan distintos tipos y/o cantidad de argumentos. 
	}
	
	//INFO:
	//Los struct ponen todo como public: por defecto, por lo que si queremos que algo no sea accesible desde fuera del UDT hay que ponerle private:
	//Los class son opuestos en este tema, por defecto todo es private:, asi que hay que poner como public lo que se quiera que lo sea.
};

int main()
{
	unsigned int N;
	cout << "Cuantos eslabones quiere en su cadena? ";
	cin >> N;
	Tipo_Cadena Cadena(N-1);
	
	Cadena.imprimir_cadena();
	
	return 0;
}

