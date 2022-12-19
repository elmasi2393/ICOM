#include <iostream>
#include <string>
#include<fstream>
#include <vector>

using namespace std;

//INFO IMPORTANTE:
//getline es una funcion muy usada para leer archivos de forma controlada. La version por defecto tiene 2 argumentos: el archivo y un string donde se guarda lo que se lee. En este string se guardan todos los caracteres HASTA que se llegue a un salto de linea.
//La version con 3 argumentos agrega la opcion de definir un separador de tipo char para frenar la lectura. Usando esta version, en el string pasado por argumento se guardan todos los caracteres HASTA que se llegue a un caracter que sea igual al delimitador elegido, o a un salto de linea.
//Para entender bien como usar la funcion getline no hay nada mejor que probar y probar, hacerse amigos.

int main()
{
	ifstream f("texto_para_jugar_con_getline.txt");
	string string_auxiliar;
	vector<string> vs;
	char delimitador_1 = ',';
	char delimitador_2 = 'x';	
	
	cout <<"Con delimitador por defecto: " << endl << endl;
	if (f.is_open())
	{
		while (getline(f,string_auxiliar))
		{
			vs.push_back(string_auxiliar);
		}
		
		for (auto s : vs)
			cout << s << endl;
		vs.clear();
		f.close();
	}
	else
	{
		cout << "Error al abrir archivo" << endl;
	}
	
	cout << endl<<endl <<"Con delimitador: " << delimitador_1 << endl<< endl;
	f.open("texto_para_jugar_con_getline.txt");
	if (f.is_open())
	{
		while (getline(f,string_auxiliar,delimitador_1))
		{
			vs.push_back(string_auxiliar);
		}
		
		for (auto s : vs)
			cout << s << endl;
		vs.clear();
		f.close();
	}
	else
	{
		cout << "Error al abrir archivo" << endl;
	}
	
	
	cout << endl<<endl <<"Con delimitador: " << delimitador_2 << endl<< endl;
	f.open("texto_para_jugar_con_getline.txt");
	if (f.is_open())
	{
		while (getline(f,string_auxiliar,delimitador_2))
		{
			vs.push_back(string_auxiliar);
		}
		
		for (auto s : vs)
			cout << s << endl;
		vs.clear();
		f.close();
	}
	else
	{
		cout << "Error al abrir archivo" << endl;
	}	
	
	return 0;
}
