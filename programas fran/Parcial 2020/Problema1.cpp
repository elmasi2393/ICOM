#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum carrera { fisica, mecanica, nuclear, telecomunicaciones };

enum cursada { Mate2, Electro, Exp2, Termo };

ostream & operator << (ostream &out, const cursada &c);
ostream & operator << (ostream &out, const carrera &c);

class Persona
{
    private:
    	string nombre;
    	string ciudad;
    	unsigned short edad;
    	unsigned int dni;
	
	public:
	
    	Persona(string nombre_, string ciudad_, unsigned short edad_,unsigned int dni_){
            nombre = nombre_;
            ciudad = ciudad_;
            edad = edad_;
            dni = dni_;
        }; //TO DO
    	
    	const string &get_nombre() const{
            return nombre;
        };  //TO DO
    
    	const string &get_ciudad() const{
            return ciudad;
        };  //TO DO
    
    	unsigned short get_edad() const{
            return edad;
        };  //TO DO
    
    	unsigned int get_dni() const{
            return dni;
        };  //TO DO
    
    	//Las implementaciones de este metodo deben imprimir en la pantalla toda la informacion relativa a cada Persona
    	virtual	void print_info() = 0; //TO DO donde corresponda
};

class Alumno : public Persona
{
    	carrera especialidad;
    	float calificacion;
	
	public:
	
    	Alumno (string nombre_, string ciudad_, unsigned short edad_,unsigned int dni_,carrera especialidad_)
        :Persona(nombre_,ciudad_,edad_,dni_)
        {
            especialidad = especialidad_;
        }; //TO DO
    	
    	void set_calificacion(float cal)
    	{
    		calificacion=cal;
    	}
    	
    	float get_calificacion() const 
    	{
    		return calificacion;
    	}
    	
    	carrera get_especialidad() const{
            return especialidad;
        }; //TO DO

    	virtual void print_info(){
            cout<<"Nombre: "<< get_nombre()<<endl;
            cout<<"Ciudad: "<< get_ciudad()<<endl;
            cout<<"Edad: " << get_edad()<<endl;
            cout<<"DNI: "<<get_dni()<<endl;
            cout<<"Especialidad: "<<especialidad <<endl;
            cout<<"Calificacion: "<<calificacion<<endl;
        }; //TO DO

};

class Docente : public Persona
{
	public:
    	Docente (string nombre_, string ciudad_, unsigned short edad_,unsigned int dni_)
        : Persona(nombre_,ciudad_,edad_,dni_)
        {}; //TO DO

    void print_info(){
            cout<<"Nombre: "<< get_nombre()<<endl;
            cout<<"Ciudad: "<< get_ciudad()<<endl;
            cout<<"Edad: " << get_edad()<<endl;
            cout<<"DNI: "<<get_dni()<<endl;
        }; //TO DO

};

class Catedra
{
    	cursada curso; 
    	vector<Docente> docentes;
    	vector<Alumno> alumnos;
	
	public:
	
    	Catedra(cursada curso_,const vector<Docente> &docentes_, const vector<Alumno> &alumnos_){
            curso = curso_;
            docentes = docentes_;
            alumnos = alumnos_;
        }; //TO DO
    	
    	//busca al alumno por dni y le asigna la calificacion cal.
    	void set_calificacion(unsigned int dni_alumno, float cal){
            int n = alumnos.size();
            for(int i = 0; i<n; i++){
                if(alumnos[i].get_dni() == dni_alumno){
                    alumnos[i].set_calificacion(cal);
                    return;
                }
            }
            cout<< "No existe  con DNI: "<<dni_alumno<<endl;
        }; //TO DO
    	
    	virtual void print_all_info() const
    	{
    		float promedio=0;
    		cout << endl << "Materia: " << curso << endl << endl;
    		cout << "***********PLANTEL DOCENTE************ "<< endl << endl;
    		
    		for (auto d:docentes)
    		{
    			d.print_info();
    			cout << endl;
    		}
    		cout << "***************ALUMNOS**************** "<< endl << endl;
    		
    		for (auto a:alumnos)
    		{
    			promedio+=a.get_calificacion();
    			a.print_info();
    			cout << endl;
    		}
    		promedio/=alumnos.size();
    		cout << "PROMEDIO GLOBAL: " << promedio << endl;
    		cout << "====================================== "<< endl << endl;
    	}
};




int main()
{
    vector<Docente> profes = {
        {"Pedro Picapiedras","Piedra del Aguila",50,20000000},
        {"Pancho Villa","Villa la Angostura",35,30000000}
    };
    vector<Alumno> chicos =	{
        {"Maria del Carmen","Mar del Plata",23,40000000,fisica},
        {"Juan Carlos","Carlos Paz",25,42000000,mecanica},
        {"Paul Atreides","Arrakis",22,39000000,nuclear},
        {"Bernardo Santos","Bariloche",27,35000000,telecomunicaciones}
    };
	
    Catedra catedra1(Mate2,profes,chicos);
    Catedra catedra2(Electro,profes,chicos);
	
    catedra1.set_calificacion(40000000,7.5);
    catedra1.set_calificacion(42000000,5.0);
    catedra1.set_calificacion(39000000,10.);
    catedra1.set_calificacion(35000000,8.5);
	
    catedra2.set_calificacion(40000000,7.0);
    catedra2.set_calificacion(42000000,7.0);
    catedra2.set_calificacion(39000000,10.);
    catedra2.set_calificacion(35000000,6.5);
	
    catedra1.print_all_info();
    catedra2.print_all_info();
	
    cin.get();
    return 1;
}


ostream & operator << (ostream &out, const cursada &c)
{
	string s;
	
	switch (c)
	{
		case Mate2:
			s="MATEMATICAS II";
			break;
		case Electro:
			s="ELECTROMAGNETISMO";
			break;
		case Exp2:
			s="FISICA EXPERIMENTAL II";
			break;
		case Termo:
			s="TERMODINAMICA Y FISICOQUIMICA";
			break;
		default:
			s="ERROR EN LA CURSADA!";
	};
	
    out << s;
    return out;
}


ostream & operator << (ostream &out, const carrera &c)
{
	string s;
	switch (c)
	{
		case fisica:
			s="Fisica";
			break;
		case mecanica:
			s="Mecanica";
			break;
		case nuclear:
			s="Nuclear";
			break;
		case telecomunicaciones:
			s="Telecomunicaciones";
			break;
		default:
			s="ERROR EN LA CARRERA!";
	};
	
    out << s;
    return out;
}