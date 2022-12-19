#include<iostream>

using namespace std;

class Tipo_Objeto_Conectable
{
	Tipo_Objeto_Conectable *puntero_a_otro_Objeto=nullptr;
	bool conectado=false;
	
	public:
	
	Tipo_Objeto_Conectable *get_conexion()
	{
		return puntero_a_otro_Objeto;
	}
	
	bool esta_Conectado()
	{
		return conectado;
	}
	
	void conectar(Tipo_Objeto_Conectable *that)
	{
		if (!conectado && !(that->esta_Conectado()))
		{
			puntero_a_otro_Objeto=that;
			conectado=true;
			cout << "Conexion 1 finalizada: " << this << "--->" << that << endl;
			that->conectar(this);
		}
		else if (!conectado && (that->get_conexion()==this))
		{
			puntero_a_otro_Objeto=that;
			conectado=true;
			cout << "Conexion 2 finalizada: "  << this << "--->" << that << endl;
		}
		else
		{
			cout << "Al menos uno de los objetos ya estaba conectado" << endl;
			return;
		}
	}
	
	void borrar_conexiones()
	{
		Tipo_Objeto_Conectable *puntero_auxiliar;
		if (puntero_a_otro_Objeto!=nullptr)
		{
			cout << "Conexion borrada: " << this << "--->" << puntero_a_otro_Objeto << endl;
			puntero_auxiliar=puntero_a_otro_Objeto;
			puntero_a_otro_Objeto = nullptr;
			conectado=false;
			if (puntero_auxiliar!=nullptr)
			{
				puntero_auxiliar->borrar_conexiones();
			}	
			else
				return;
		}
		else
			return;
	}
};

//INFO IMPORTANTE:
//La palabra reservada this devuelve la direccion de memoria de la instancia en la que se activa. Se utiliza desde adentro de UDTs (class o struct), como forma generica de acceder a las direcciones de las distintas instancias que se vayan a crear, para llevar a cabo operaciones entre ellas.
//Fijense bien como this vale una u otra cosa en los cout. Es importante que puedan darse cuenta rapidamente adentro de que instancia se va a activar cada vez que usen esto. Para eso tienen que tener un mapa mental (o si prefieren puede ser escrito) de como se pasa de una instancia a la otra (esto siempre se va a dar mediante punteros y activando metodos desde alli)

int main()
{
	Tipo_Objeto_Conectable Objeto_1,Objeto_2,Objeto_3,Objeto_4;
	
	Objeto_1.conectar(&Objeto_2);
	
	Objeto_3.conectar(&Objeto_1);
	
	Objeto_2.conectar(&Objeto_4);
	
	Objeto_1.borrar_conexiones();
	
	Objeto_3.conectar(&Objeto_1);	
	
	Objeto_2.conectar(&Objeto_4);
	
	return 0;
}
