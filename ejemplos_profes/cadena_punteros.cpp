#include<iostream>

using namespace std;

struct Tipo_Cadena
{
	
	Tipo_Cadena(unsigned int Numero_eslabones)
	{
		cout << "Construyendo eslabon" << endl;
		if (Numero_eslabones>0)
			eslabon_Siguiente = new Tipo_Cadena(Numero_eslabones-1);
		else
			eslabon_Siguiente = nullptr;
		
		//INFO IMPORTANTE:
		//El operador new devuelve la direccion de memoria del bloque que acaba de reservar (alocar). Por eso un puntero que se quiere que apunte a un pedazo de memoria reservado se iguala a new Constructor();
		//nullptr significa que no apunta a ningun lado. Es como si valiera 0, y se usa, por ejemplo, para saber cuando necesitamos o no liberar memoria de forma automatica. Ver destructor.
	}
	
	~Tipo_Cadena()
	{
		cout << "Destruyendo eslabon" << endl;
		if (eslabon_Siguiente!=nullptr)
		{
			cout << "Intentando desalocar eslabon siguiente" << endl;
			delete eslabon_Siguiente;
		}
		
		//INFO IMPORTANTE:
		//Cuando se llama a delete para liberar memoria asociada a un objeto (struct o class UDT), el destructor del objeto es llamado ANTES de llevar a cabo la liberacion de memoria (si posee un destructor). Ejecutar y observar lo que se imprime en pantalla.
	}

	private:
	Tipo_Cadena *eslabon_Siguiente;
	
	//INFO:
	//Los struct ponen todo como public: por defecto, por lo que si queremos que algo no sea accesible desde fuera del UDT hay que ponerle private:
	//Los class son opuestos en este tema, por defecto todo es private:, asi que hay que poner como public lo que se quiera que lo sea.
};

int main()
{
	unsigned int N;
	cout << "Cuantos eslabones quiere en su cadena? ";
	cin >> N;
	Tipo_Cadena Cadena(N);
	
	return 0;
}

