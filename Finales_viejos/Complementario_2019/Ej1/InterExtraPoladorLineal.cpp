#include "icom_helpers.h"

class InterExtraPoladorLineal
{
    public:
	// ToDo:
    // Implementar un constructor que lea los puntos de calibracion {x, y} desde un archivo de nombre dado por file_name y los guarde en un
    // contenedor. Los puntos en el contenedor deben terminar ordenados en x crecientes.
    InterExtraPoladorLineal(string file_name);

    // operator(): retorna el valor de y que corresponde al x dado, interpolando o extapolando linealmente
    // según el caso. Para la interpolacion, busque el intervalo que contiene el punto x por "biseccion"
    double operator()(double x);
	
    private:
	// ToDo: elegir un contenedor para los puntos de calibracion 

};



int main()
{
	// Estos son valores para comparar con los obtenidos por su InterExtraPoladorLineal
	double posta[]={0.9320175,2.776779,7.768074,19.91574,47.69798,108.1199,234.52,488.5243,985.1446,1927.985,3682.366,6868.248,12516.99,22469.1,39546.12,68559.94,99884.94};

    string file("calibracion.txt");

    InterExtraPoladorLineal iel(file);

	cout<<scientific;
    for (int i=4; i<=20; ++i)
    {
        cout << i << '\t' << iel(i)<< '\t' << posta[i-4] << endl;
    }

    return 0;
}


