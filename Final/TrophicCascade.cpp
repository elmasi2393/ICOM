#include <iostream>
#include <fstream>
#include <utility> 
#include <vector>
#include <deque>
#include <list>
#include <map>


//tiempo simulado
const unsigned int maximo_iteraciones = 2000;

//maxima cantidad de pastizal disponible en cada ubicacion
const unsigned int pastizal_maximo = 5;

//cantidad maxima de pastizal renovado por turno en cada ubicacion
const unsigned int rate_pasto = 3;

//tiempo minimo de gestacion de animales
const unsigned int t_gestacion_depredador = 2;
const unsigned int t_gestacion_presa = 3;

//tiempo que soporta sin comer un animal
const unsigned int h_depredador = 2;
const unsigned int h_presa = 3; 

//maxima vida de animales
const unsigned int esperanza_vida_depredador = 20;
const unsigned int esperanza_vida_presa = 13;

//maxima cantidad de crias que produce un animal
const unsigned int camadas_depredador = 5;
const unsigned int camadas_presa = 4;

const char D_char = 'D'; 
const char P_char = 'P';

using namespace std;

//UDT que representa una casilla en un mapa bidimensional
struct Punto2D
{   
	     
    void set(int x_, int y_)
    {
        x = x_;
        y = y_;
    }
    
    //inicializa x,y aleatoriamente dentro del mapa de tamaño tamano_mapa*tamano_mapa
    void set_random()
    {
        int x_ = rand() % tamano_mapa;
        int y_ = rand() % tamano_mapa;

        set(x_, y_);
    }

    Punto2D(unsigned int t_mapa)
    {
        tamano_mapa = t_mapa;
        set_random();
    }

    Punto2D(const Punto2D &p)
    {
        x = p.x;
        y = p.y;
        tamano_mapa = p.tamano_mapa;
    }
    
    Punto2D(unsigned int t_mapa, int x_, int y_)
    {
        x = x_;
        y = y_;
        tamano_mapa = t_mapa;
    }

    //mueve el Punto2D una casilla, en una direccion al azar. El mapa tiene condiciones de borde periodicas
    void mover()
    {
        Direccion d = static_cast<Direccion>(rand() % NUM_DIRS);

        switch (d)
        {
            case IZQ:
                x = indice_periodico(x-1);
                break;
            case DER:
                x = indice_periodico(x + 1);
                break;
            case ARRIBA:
                y = indice_periodico(y + 1);
                break;
            case ABAJO:
                y = indice_periodico(y - 1);
                break;
            default:
                break;
        }
    }
    
    int modulo() const
    {
    	return x*x+y*y;
    }
    
    bool operator<(const Punto2D &otro) const
    {
    	if (modulo()<otro.modulo())
    		return true;
    	else if (modulo() == otro.modulo())
    	{
    		return (y<otro.y);
    	}
    	else
    		return false;
    }

private:

    enum Direccion { QUIETO=0, IZQ, DER, ARRIBA, ABAJO, NUM_DIRS };
    unsigned int tamano_mapa;
    int x, y;
    
    //fuerza condiciones periodicas de contorno
    int indice_periodico(int z_)
    {
        if (z_ < 0)
            return (z_ + tamano_mapa);
        if (z_ >= tamano_mapa)
            return (z_ - tamano_mapa);
        return z_;
    }
};

//UDT que representa la base de la cadena, el pastizal
struct Pasto
{
	//construye un pastizal, con una disponibilidad inicial maxima (TODO)
    Pasto(): disponibilidad(pastizal_maximo) {};
    
    //el pastizal crece un maximo de rate_pasto por iteracion, no superando nunca el valor maximo posible, pastizal_maximo (TODO)
    void crecer(){
        if((disponibilidad + rate_pasto) >= pastizal_maximo) //Si es mayor al maximo
            disponibilidad = pastizal_maximo; //no supero el maximo
        else
        	disponibilidad += rate_pasto; //sino incremento en 3
    }
    
    //si hay disponibilidad de pastizal, al ser comido pierde 1 de disponibilidad y devuelve verdadero. Si no hay, devuelve falso (TODO)
    bool ser_comido(){
        if(disponibilidad > 0){ //Si hay, decremento la disponibilidad y devuelvo true
            disponibilidad--;
            return true;
        }
        return false;   //Sino, devuelvo false porque no hay disponibilidad
    }
    
    //cuanto pasto disponible hay en el pastizal? (TODO)
    unsigned int disponible() const { return disponibilidad; }

private:
    unsigned int disponibilidad; //cantidad de pasto disponible en el pastizal. Valor maximo posible: pastizal_maximo
};


//UDT que representa las funciones basicas de un animal, ya sea depredador o presa 
struct Animal
{
	//(TODO)
	const Animal & operator=(const Animal &a){  //Igualo cada uno de los atributos
        sexo = a.sexo;
        t_hambre = a.t_hambre;
        esperanza_vida = a.esperanza_vida;
        hambre = a.hambre;
        edad = a.edad;
        vivo = a.vivo;
        embarazada = a.embarazada;
        ubicacion = a.ubicacion;
        gestacion = a.gestacion;
        t_gestacion = a.t_gestacion;

        return *this;   //retorno la referncia al onjeto en cuestion
    }
	
	//devuelve la ubicación del animal en el mapa (TODO)
    Punto2D get_p() const{ return ubicacion; }
    
    //si esta embarazada, devuelve verdadero (TODO)
    bool con_crias(){ return embarazada; }
    
    //preparando la siguiente generacion de animales
    void reproducirse()
    {
        embarazada = true;
    }
    
    //si el animal esta decentemente alimentado, suma a gestacion. Si supero el tiempo de gestacion, da a luz y devuelve verdadero (sino devuelve falso)
    bool parir()
    {
    	if ((t_hambre-hambre)>=t_hambre/2)
    		gestacion++;
    		
        if (gestacion >= t_gestacion)
        {
            embarazada = false;
            gestacion = 0;
            return true;
        }
        return false;
            
    }
	
	//el animal es macho? (TODO)
    bool es_macho() const{ return (!sexo);}   //Niego porque si es macho es false
    
    //el animal se mueve una casilla en una direccion al azar. (TODO)
    void moverse(){ ubicacion.mover(); }    //mueve el punto en una direccion aleatoria
    
    //el animal deja de estar vivo (TODO)
    void morir(){
        if(edad > esperanza_vida)
            vivo = false;
    }
    
    //al escapar, el animal consume recursos, lo que se rpresenta con un aumento significativo del hambre
    void escapar()
    {
        hambre+=2;
    }
	
	//el animal esta muerto? (TODO)
    bool esta_muerto(){ return (!vivo);}  //Devuelve true si el animal esta muerto
    
    //cuanta hambre tiene el animal? (TODO)
    bool hambriento(){ return (hambre > t_hambre); }    //Si el tiempo que esta sin comer es mayor al t_hambre, entonces esta hambiento
    
    //devuelve la fuerza vital del animal, proporcional a su edad (es maxima a la mitad de su vida util)
    unsigned int fuerza()
    {
    	if (edad < esperanza_vida/2)
    		return edad;
    	else
    		return (esperanza_vida - edad);
    }
    
 	//declarar y definir en donde corresponda. Los metodos deberian devolver un caracter que indique qué es el animal. Si es presa deberia devolver P_char, y si es depredador deberia devolver D_char (fijarse que al principio del codigo estan definidas estos char constantes) (TODO)
    virtual char que_es() = 0;
 
    //todos los animales pueden subsistir con pasto, en principio
    bool comer_pasto(Pasto *p)
    {
        if (p->ser_comido())
            return true;
        return false;
    }
    
    //el animal envejece y aumenta su hambre. Si esta desnutrido o muy viejo, muere 
    void envejecimiento_y_hambre()
    {
        edad++;

        if (edad == esperanza_vida)
        {
            morir();
            return;
        }

        if (hambre == t_hambre)
        {
            morir();
            return;
        }

        hambre++;
    }
    
    //forma minima de alimentación de un animal, a base de pasto.
    virtual void comer(Pasto *p)
    {
        if (comer_pasto(p))
        {
            hambre--;
            return;
        }
    }

protected:    
    bool sexo; //si es hembra vale true, sino vale false
    unsigned int t_hambre; //tiempo que puede pasar sin comer
    unsigned int esperanza_vida; //maximo tiempo que puede vivir
    unsigned int hambre; //tiempo que paso sin comer
    unsigned int edad; //tiempo que vivio
    bool vivo; //esta vivo?
    bool embarazada; //esta con crias?
    Punto2D ubicacion; //posicion en el mapa
    unsigned int gestacion; //tiempo que paso desde la ultima reproduccion
    unsigned int t_gestacion; //tiempo necesaria para parir 
	
	//el animal aparece en una ubicacion aleatoria
    Animal(bool sexo_, unsigned int t_hambre_,unsigned int esp_vida, unsigned int t_mapa, unsigned int t_gestacion_)
        :sexo(sexo_),t_hambre(t_hambre_),esperanza_vida(esp_vida),ubicacion(t_mapa),t_gestacion(t_gestacion_)
    {
        embarazada = false;
        gestacion = 0;
        vivo = true;         
        hambre = 0;
        edad = 0;
    }
	
	//el animal aparece en una ubicacion determinada
    Animal(bool sexo_, unsigned int t_hambre_, unsigned int esp_vida, Punto2D p, unsigned int t_gestacion_)
        :sexo(sexo_), t_hambre(t_hambre_), esperanza_vida(esp_vida),ubicacion(p),t_gestacion(t_gestacion_)
    {
        embarazada = false;   
        gestacion = 0;
        vivo = true;
        hambre = 0;
        edad = 0;
    }

};

//UDT que representa una presa
struct Presa : public Animal
{
	//la presa aparece en una ubicacion aleatoria (TODO)
    Presa(bool sexo, unsigned int t_mapa): Animal(sexo, h_presa, esperanza_vida_presa, t_mapa, t_gestacion_presa) {}
	
	//la presa aparece en una ubicacion determinada (TODO)
    Presa(bool sexo, Punto2D p): Animal(sexo, h_presa, esperanza_vida_presa, p, t_gestacion_presa) {}

    Presa(const Presa& P)
        :Animal(!P.es_macho(), h_presa, esperanza_vida_presa, P.get_p(),t_gestacion_presa)
    {
        hambre=0;
        edad=0;
        vivo=true;
        embarazada=false;
        gestacion = 0;
    }
    
    //intenta comer pasto.
    void comer(Pasto *p)
    {
        if (comer_pasto(p))
        {
            hambre = 0;
            return;
        }
    }
    char que_es(){ return P_char; }
	
};

//UDT que representa un depredador
struct Depredador : public Animal
{   
	//el depredador aparece en una ubicacion aleatoria (TODO)
    Depredador(bool sexo, unsigned int t_mapa): Animal(sexo, h_depredador, esperanza_vida_depredador, t_mapa, t_gestacion_depredador) {}
    
    //el depredador aparece en una ubicacion determinada (TODO)
    Depredador(bool sexo, Punto2D p): Animal(sexo, h_depredador, esperanza_vida_depredador, p , t_gestacion_depredador) {}

    Depredador(const Depredador& D)
        :Animal(!D.es_macho(), h_depredador, esperanza_vida_depredador, D.get_p(),t_gestacion_depredador)
    {
        hambre = 0;
        edad = 0;
        vivo = true;
        embarazada = false;
        gestacion = 0;
    }
    
    //intenta comerse una presa. Si tiene exito, la presa muere y la funcion devuelve verdadero, sino devuelve falso.
    bool comer_carne(Animal *p)
    {	
    	if (rand() % fuerza() > rand() % p->fuerza())
    	{
		    if (!p->esta_muerto())
		    {
		        p->morir();
		    }
		    return true;
        }
        else
        	return false;
    }
    
    //intenta comer una presa. Si tiene exito, devuelve verdadero, sino falso
    bool comer(Animal *p)
    {
        if (comer_carne(p))
        {
            hambre = 0;
            return true;
        }              
        return false; 
    }
    char que_es(){ return D_char; }
    
};

//UDT que representa el territorio
struct Mapa
{
	Mapa (int t_mapa)
	{
		 for (unsigned int i=0;i<t_mapa;i++)
            for (unsigned int j = 0; j < t_mapa; j++)
            {
            	coordenadas.push_back(Punto2D(t_mapa,i,j));
                pastizales.insert(make_pair(Punto2D(t_mapa,i,j),Pasto()));
            }

	}
	
	//metodo que devuelve el grupo de animales dentro de una ubicacion determinada
	pair<multimap<Punto2D,Animal *>::iterator,multimap<Punto2D,Animal *>::iterator> get_animales(const Punto2D &p)
	{
		pair<multimap<Punto2D,Animal *>::iterator,multimap<Punto2D,Animal *>::iterator> grupo = animales.equal_range(p);
		return grupo;
	}
	
	//cuenta cuanto pasto disponibles hay en total
	unsigned int contar_pastizales()
	{
		unsigned int N=0;
		for (auto &pt:pastizales)
		{
				N+=pt.second.disponible();
		}
		return N;
	}
	
	//crece los pastizales
	void crecer_pasto()
	{
		for (auto &pt:pastizales)
		 pt.second.crecer();
	}
	
	//devuelve puntero al pastizal en una ubicacion
	Pasto * get_pastizal(const Punto2D &p)
	{
		return &((pastizales.find(p))->second);
	}
	
	//remueve los punteros a animales en el contenedor usado para alimentar y reproducir
	void limpiar_animales()
	{
		animales.clear();
	}
	
	//mete puntero a animal en el contenedor usado para alimentar y reproducir
	void meter_animal(Animal * animal)
	{
		animales.insert(make_pair(animal->get_p(),animal));
	}
	
	//lista con todas las coordenadas del mapa, por comodidad de uso
	list<Punto2D> coordenadas;
	
	private:
	//mapa con los pastizales
	map<Punto2D,Pasto> pastizales;
	//contenedor usado para alimentar y reproducir por ubicacion. Alli se guardan los punteros a animales, ordenados por ubicacion
	multimap<Punto2D,Animal *> animales;	
	
};

//UDT que representa el ecosistema formado por los pastizales, las presas y los depredadores.
struct Ecosistema
{
    Ecosistema(unsigned int t_mapa):tamano_mapa(t_mapa),mapa(t_mapa)
    {      
        unsigned int N_presas = tamano_mapa * tamano_mapa*4; //cantidad inicial de presas
        unsigned int N_depredadores = tamano_mapa * tamano_mapa; //cantidad inicial de depredadores
		
		f_out.open("poblacion.txt");
			
        for (unsigned int i = 0; i < N_presas; i++)
        {
            presas.push_back(Presa(i%2,tamano_mapa));//al comienzo, la mitad de los animales son hembras
        }
            
        for (unsigned int i = 0; i < N_depredadores; i++)
        {
            depredadores.push_back(Depredador(i%2,tamano_mapa));//al comienzo, la mitad de los animales son hembras
        }       
    }
    
    ~Ecosistema()
    {
        f_out.close();
    }
    
    //renueva los pastizales, migran los animales, se pelean los depredadores del mismo sexo, envejecen todos los animales y mueren los que correspondan, se alimentan los que quedan en su nueva locacion, y se reproducen los que puedan.
    void avanzar()
    {
        crecimiento_pasto();
        migracion();
        territorialidad();
        muerte();
        alimentacion();
        reproduccion();      
    }  
    
    //si la poblacion de presas o depredadores llega a 0, colapsa el ecosistema. Es decir, devuelve verdadero (TODO)
    bool extincion(){ return ((presas.size()==0) || (depredadores.size() == 0)); }  //Si el vector esta vacio, no hay ams presas
    
    //imprime la poblacion de depredadores, presas y la cantidad de pasto total disponible en cada iteracion. Esto lo debe hacer tanto en el dispositivo estandar de salida, como en un archivo. (TODO)
    void print(unsigned int t){
        //dispositivo estandar de salida
        cout << "Depredadores: " << depredadores.size() << endl;
        cout << "Presas: " << presas.size() << endl;
        cout << "Pasto disponible: " << mapa.contar_pastizales() << endl;

        //Archivo (Guardo como se anuncia en la consigna separado por espacios)
        f_out << depredadores.size() << ' ' << presas.size() << ' ' << mapa.contar_pastizales() << endl;
    }

private:
	unsigned int tamano_mapa; //tamaño lateral del mapa (mapa tiene tamano_mapa*tamano_mapa casillas)
	Mapa mapa;
    deque<Presa> presas; //aqui se guardan todas las presas
    deque<Depredador> depredadores; //aqui se guardan todos los depredadores
    
    ofstream f_out;
	
	//devuelve puntero a pastizal en una ubicación determinada (TODO)
    Pasto * get_pasto(const Punto2D &p){ return mapa.get_pastizal(p); } //Retorno con la funcion ya definida
    
    //las presas y depredadores intentan alimentarse
    void alimentacion()
    {
    	for (auto &c: mapa.coordenadas)
    	{
			auto animales = mapa.get_animales(c);    		
			for (multimap<Punto2D,Animal *>::iterator it=animales.first; it!=animales.second; it++)
		  	{
		  		if ((it->second)->que_es() == P_char) //si es presa
		  		{	
		  			(static_cast<Presa *>(it->second))->comer(get_pasto(c));
		  		}
		  		else
		  		{	
		  			for (multimap<Punto2D,Animal *>::iterator it2=animales.first; it2!=animales.second; it2++)
		  			{
		  				if ((it2->second)->que_es()==P_char)
		  				{
		  					if ((static_cast<Depredador *>(it->second))->comer(it2->second))
		  					break;
		  				}
		  			}
		  			if ((static_cast<Depredador *>(it->second))->hambriento())
		  					(it->second)->comer(get_pasto(c));
		  		}
		  	}
    	} 
    }
    
    //las presas y depredadores se mueven a una casilla contigua, y se renueva el contenedor usado para alimentar y reproducir animales.
    void migracion()
    {
    	mapa.limpiar_animales();
    	
        for (Presa& p : presas)
        {
            p.moverse();
            mapa.meter_animal(&p);
        }

        for (Depredador& d : depredadores)
        {
            d.moverse();
            mapa.meter_animal(&d);
        }
    }
	
	//los depredadores del mismo sexo se pelean entre si cuando estan en una misma ubicacion
	void territorialidad()
    {
    	for (auto &c: mapa.coordenadas)
    	{
			auto animales = mapa.get_animales(c);
				
			for (multimap<Punto2D,Animal *>::iterator it=animales.first; it!=animales.second; it++)
		  	{	
		  		char especie = (it->second)->que_es();	
		  		if ( especie == D_char && !((it->second)->esta_muerto())) //si esta vivo y es depredador
			  	{
			  		if ((it->second)->es_macho())
			  		{
			  			for (multimap<Punto2D,Animal *>::iterator it2=it; it2!=animales.second; it2++)
			  			{
			  				if (it==it2) //no se pelea consigo mismo!
			  					continue;
			  				if ((((it2->second)->que_es()==especie))&&((it2->second)->es_macho())) //se encuentra con otro macho depredador
			  				{
			  					if ((it2->second)->fuerza()<=(it->second)->fuerza())
			  						(it2->second)->escapar();
			  					else if ((it2->second)->fuerza()>(it->second)->fuerza())
			  					{
			  						(it->second)->escapar();		
			  					}
			  					break; //buscan pelea una sola vez por turno
			  				}
			  			}
			  		}
			  		else
			  		{
			  			for (multimap<Punto2D,Animal *>::iterator it2=it; it2!=animales.second; it2++)
			  			{
			  				if (it==it2) //no se pelea consigo mismo!
			  					continue;
			  				if ((((it2->second)->que_es()==especie)) && !((it2->second)->es_macho())) //se encuentra con otra hembra depredadora
			  				{
			  					if ((it2->second)->fuerza()<=(it->second)->fuerza())
			  						(it2->second)->escapar();
			  					else if ((it2->second)->fuerza()>(it->second)->fuerza())
			  					{
			  						(it->second)->escapar();
			  					}
			  					break; //buscan pelea una sola vez por turno
			  				}
			  			}
			  		}
			  	}
		  	}
    	}
	}
    
    //las presas y depredadores intentan reproducirse, y se dan los nacimientos que correspondan
    void reproduccion()
    {
    	for (auto &c: mapa.coordenadas)
    	{
			auto animales = mapa.get_animales(c);
				
			for (multimap<Punto2D,Animal *>::iterator it=animales.first; it!=animales.second; it++)
		  	{		
		  		if ((!((it->second)->es_macho()))&&(!((it->second)->con_crias()))) //si es hembra y no esta preñada
		  		{
		  			char especie = (it->second)->que_es();
		  			
		  			for (multimap<Punto2D,Animal *>::iterator it2=animales.first; it2!=animales.second; it2++)
		  			{
		  				if ((((it2->second)->que_es()==especie))&&((it2->second)->es_macho()))
		  				{
		  					(it->second)->reproducirse();
		  					break;
		  				}
		  			}
		  		}
		  	}
    	}

        vector<Punto2D> nacimientos;

        for (Presa& p : presas)
        {
            if (p.con_crias())
            {      
                if (p.parir())
                { 
                    unsigned int r = rand() % camadas_presa;
                    for (unsigned int i=0; i<r;i++)
                        nacimientos.push_back(p.get_p());
                }
                    
            }
        }

        for (unsigned int i = 0; i < nacimientos.size(); i++)
        {
            presas.push_back(Presa(i % 2, nacimientos.at(i)));
        }

        nacimientos.clear();

        for (Depredador& d : depredadores)
        {
            if (d.con_crias())
            {
                if (d.parir())
                {
                    unsigned int r = rand() % camadas_depredador;
                    for (unsigned int i = 0; i < r; i++)
                        nacimientos.push_back(d.get_p());
                }
                    
            }
        }

        for (unsigned int i = 0; i < nacimientos.size(); i++)
        {
            depredadores.push_back(Depredador(i % 2, nacimientos.at(i)));
        }
    }
    
    //se envejece y hambrea a los animales y se borran los que esten muertos
    void muerte()
    {
    	for (Presa& p : presas)
        {
            p.envejecimiento_y_hambre();
        }

        for (Depredador& d : depredadores)
        {
            d.envejecimiento_y_hambre();
        } 	
        
        for (std::deque<Presa>::iterator it = presas.begin(); it != presas.end();)
        {
            if (it->esta_muerto())
            {
                it = presas.erase(it);               
            }
            else
                it++;
                
        }
        for (std::deque<Depredador>::iterator it = depredadores.begin(); it != depredadores.end(); )
        {
            if (it->esta_muerto())
            {
                it = depredadores.erase(it);
            }
            else
                it++;               
        }        
        
        mapa.limpiar_animales();          
        
        for (Presa& p : presas)
        {
            mapa.meter_animal(&p);
        }

        for (Depredador& d : depredadores)
        {
            mapa.meter_animal(&d);
        }
    }
    
    //pastizales intentan crecer. (TODO)
    void crecimiento_pasto(){ mapa.crecer_pasto(); }
    
    //devuelve la cantidad de depredadores (TODO)
    unsigned int N_Depredadores() { return depredadores.size(); }
    
    //devuelve la cantidad de presas  (TODO)
    unsigned int N_Presas(){ return presas.size(); }
	
	//devuelve la cantidad total de pasto disponible (TODO)
    unsigned int N_Pastizal(){ return mapa.contar_pastizales(); }
};


int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    Ecosistema eco(30);
    unsigned int i = 0;

    do
    {
        eco.print(i);
        eco.avanzar();

        if (eco.extincion() || i==maximo_iteraciones)
        {
            eco.print(i);
            cout << "Fin" << endl;
            break;
        }
        i++;
    } while (true);

}


