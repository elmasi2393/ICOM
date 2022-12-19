#include <iostream>
#include <vector>

using namespace std;

const int N=100;

struct Estructura_1
{
	int miembro_1;
	
	Estructura_1(int i): miembro_1(i)
	{
	}
	
	bool tarea_1a(int x)
	{
		if (miembro_1<x)
		{
			return true;
		}
		return false;
	}
	
	int tarea_1b(int x)
	{
		return x-miembro_1;
	}
	
	bool tarea_1c(int x)
	{
		if (miembro_1>x)
		{
			return true;
		}
		return false;
	}
};

struct Estructura_2: public Estructura_1
{
	int miembro_2;
	
	Estructura_2(int i): Estructura_1(i-rand()%N),miembro_2(i)
	{
	}	
	
	bool tarea_2a()
	{
		if (tarea_1a(miembro_2))
		{
			miembro_1++;
			return false;
		}
		else if (tarea_1c(miembro_2))
		{
			miembro_1--;
			return false;
		}
		return true;
	}
	
	bool tarea_2b()
	{
		if (tarea_1b(miembro_2))
			return false;
		return true;
	}
};

struct Estructura_3
{
	Estructura_2 miembro_3;
	bool tarea_terminada=false;
	
	Estructura_3(): miembro_3(rand()%N)
	{
	}
	
	bool tarea_3()
	{
		if (miembro_3.tarea_2a() && miembro_3.tarea_2b())
		{
			tarea_terminada = true;
			cout << "Tarea 3 terminada satisfactoriamente!" << endl;
		}
		else
			cout << "Tarea 3 sin finalizar..." << endl;
		return tarea_terminada;
	}
};

struct Estructura_4
{
	Estructura_3 miembro_4;
	
	bool tarea_iterada()
	{
		if (tarea_4a())
		{
			tarea_4b();
			return false;
		}
		return true;
	}
	
	
	bool tarea_4a()
	{
		return miembro_4.tarea_3();
	}
	
	void tarea_4b()
	{
		cout << "¡Se ha logrado el objetivo de este programa!" << endl << "¿Cual es ese objetivo?" << endl;
	}
	
};
 

int main()
{
	srand(time(0));
	
	Estructura_4 Objeto_interfaz;
	
	do
	{
		cout << "Trabajando..." << endl;
	} while (Objeto_interfaz.tarea_iterada());
	
	return 0;
}
