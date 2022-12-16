#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

const char pared='#';
const char portal_salida='S';
const char libre=' ';

enum Direccion {arriba,abajo,izq,der,quieto,num_dirs};

// "Limpia" la pantalla. Dependiendo del tamaño de su terminal, 
// puede ser que se vea mejor o peor con 50 saltos de linea, 
// si es necesario puede cambiar este numero para que se adecue a su pantalla.
void ClearScreen()
{
	cout << string( 50, '\n' );
}

//Fijese qué elementos necesita este UDT para el correcto funcionamiento 
// del resto del codigo y complete
struct Punto2D //TODO
{
};


class Jugador
{
	Punto2D posicion;
	
	public:
	
	Jugador (Punto2D punto_inicio)
	: posicion{punto_inicio}	
	{
	}	
	
	// Metodo utilizado para cambiar la posicion del Jugador en base 
    // a la direccion que se le paso como argumento, con la precaucion
    // de no salirse de los limites dados por las 4 paredes
	void mover(Direccion d, const int limite);	//TODO
	
	
	Punto2D get_posicion() 
	{
		return posicion;
	}
};

//Clase derivada de Jugador que sera utilizada para el jugador humano
class Humano : public Jugador
{
	const char simbolo='H';	
	
	// Lee la direccion en que se desea mover el jugador humano. 
    // Los caracteres utilizados para moverse son los clasicos de 
    // juegos de computadora. 
    // Es necesario presionar Enter para ingresar la direccion elegida!
	Direccion leer_movimiento()
	{
		char dc;
		
		while (true)
		{
			dc=cin.get();
			cin.ignore(100,'\n');

			switch (dc)
			{
				case 'w':
					return arriba;
				case 's':
					return abajo;
				case 'a':
					return izq;
				case 'd':
					return der;
				default:
					return quieto;
			};
		}
	}
	
	public:
	Humano (Punto2D punto_inicio)
	: Jugador(punto_inicio)
	{	
	}
	
	//Mueve la posicion del jugador humano en la direccion elegida
	void mover(const int limite); //TODO
	
	char get_simbolo() 
	{
		return simbolo;
	}
		
};

//Clase derivada utilizada para los zombies
class Zombie : public Jugador
{
	const char simbolo='Z';	
	
	public:
	Zombie (Punto2D punto_inicio)
	: Jugador(punto_inicio)
	{	
	}
	
	//Mueve la posicion del zombie en una direccion al azar 
    // (arriba, abajo, izq, der o quieto)
	void mover(const int limite); //TODO
	
	char get_simbolo()
	{
		return simbolo;
	}	
};

// Clase que contiene la informacion y metodos necesarios para la 
// visualizacion del juego
class Mapa
{
	int tamano;
	Punto2D salida;
	vector<string> visualizacion;
	
	public:
	Mapa (int tamano_, Punto2D salida_); //TODO
	
	void mostrar() 
	{
		ClearScreen();
		for (int j=0; j < tamano+2; j++)
			cout << pared;
		cout << endl;
		
		for (int i=0; i< visualizacion.size(); i++)
		{
			cout << pared;
			cout << visualizacion.at(i);
			cout <<pared << endl;
		}
		
		for (int j=0; j < tamano+2; j++)
			cout << pared;
		cout << endl;
	}
	
	// Este metodo debe refrescar el mapa, poniendo todo libre, 
    // y agregando la salida en la posicion adecuada. 
    // Sirve para posteriormente agregar los zombies y el humano.
	void init(); //TODO
	
	//Prepara la visualizacion final del juego, dependiendo de si se gano o no.
	void fin(string s)
	{
		for (int i=0; i< visualizacion.size(); i++)
		{
			visualizacion.at(i).clear();
			for (int j=0; j< tamano; j++)
			{
				visualizacion.at(i)+=libre;
			}
		}
		visualizacion.at(tamano/2).replace(tamano/2-s.length()/2,s.length(),s);
	}
	
	//cambia el caracter en una posicion del mapa por otro.
	void actualizar(Punto2D pos, char c)
	{
		visualizacion.at(pos.y).at(pos.x)=c;
	}
	
	int get_tamano()
	{
		return tamano;
	}
	
	Punto2D get_salida()
	{
		return salida;
	}
	
};

//Clase que maneja todo el juego
class Juego
{
	Mapa mapa;
	Humano sobreviviente;
	vector<Zombie> zombies;
	string estado_fin_juego;
	
	//Si el humano es atrapado por un zombie: game over
	bool chequear_zombies()
	{
		for (auto z: zombies)
		{
			if (sobreviviente.get_posicion()==z.get_posicion())
			{
				estado_fin_juego="DERROTA";
				return true;
			}
		}
		return false;
	}
	
	//Si el humano llega a la salida: gana el juego
	bool chequear_salida()
	{
		if (sobreviviente.get_posicion()==mapa.get_salida())
		{
			estado_fin_juego="VICTORIA";
			return true;	
		}
		else
			return false;
	}
	
	//Actualiza la posicion en el mapa de los zombies y el humano
	void actualizar()
	{
		mapa.init();
		
		for (Zombie &z: zombies)
			mapa.actualizar(z.get_posicion(),z.get_simbolo());
		mapa.actualizar(sobreviviente.get_posicion(),sobreviviente.get_simbolo());
		
		mapa.mostrar();
	}
	
	//Mueve a todos los Jugadores
	void mover()
	{
		for (Zombie &z: zombies)
			z.mover(mapa.get_tamano());
		sobreviviente.mover(mapa.get_tamano());
	}
	
	public:
	
	Juego (size_t N_zombies, int mapa_tamano, Punto2D punto_inicio, Punto2D salida_)
	: mapa(mapa_tamano,salida_),sobreviviente{punto_inicio}
	{
		Punto2D r;
		for (int i=0; i<N_zombies; i++)
		{
			r={rand()%mapa_tamano,rand()%mapa_tamano};
			if (!(r==punto_inicio))
				zombies.push_back(Zombie(r));
			else
				i--;
		}
		actualizar();	 
	}
	
	// Mueve a los Jugadores y refresca el mapa. Debe luego chequear 
    // si el juego debe terminar.
	bool avanzar_turno(); //TODO
	
	// Debe poner el mapa en la condicion de finalizacion con estado 
    // de finalizacion adecuado, y mostrarlo en pantalla.
	void finalizar(); //TODO

};

int main()
{
	srand(time(0));
	
	int t_mapa=20;
	int N_zombies=30;
	
	Juego partida(N_zombies,t_mapa,Punto2D{rand()%t_mapa,rand()%t_mapa},Punto2D{rand()%t_mapa,rand()%t_mapa});
	
	while (partida.avanzar_turno())
        ;

    partida.finalizar();
	return 0;
}
