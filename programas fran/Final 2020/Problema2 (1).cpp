#include "icom_helpers.h"

// estos son los caracteres que se pueden encontrar en el laberinto
const char pared = '#';
const char espacio = ' ';
const char espacio_visitado = 'o';
const char entrada = 'E';
const char entrada_visitada = 'e';
const char salida = 'S';
const char salida_visitada='s';

struct Celda
{
    int f, c;
};

class Laberinto
{
public:
	// constructor del laberinto que implementa el algoritmo descripto en el enunciado
    Laberinto(size_t nf_, size_t nc_){
        // Paso 1
        if( (nf_ < 3) || (nc_ < 3) || (nf_*nc_ < 15) || (nf_ % 2 == 0 ) || (nc_ % 2 == 0 ))
            throw(int(1));

        nf = nf_; nc = nc_;


        // Paso 2
        txtrep.reserve(nf);
        string fila_par = string(nc, pared);
        string fila_impar = fila_par;
        
        for(int i = 1; i < nc; i += 2 )
            fila_impar[i] = espacio;      
        
        for(int i = 0; i< nf; i +=2 ){
            txtrep.push_back(fila_par);
            txtrep.push_back(fila_impar);
        }
        //Pasos 3 y 4
        int Entrada[2] = {(rand()%(int(nf)/2))*2+1, (rand()%(int(nc)/2))*2+1};    // Formato: {Fila, columna}
        int Salida [2];
        do{
            Salida [0] = (rand()%(int(nf)/2))*2+1;
            Salida [1] = (rand()%(int(nc)/2))*2+1;
        }while((Entrada[0] == Salida[0]) || (Entrada[1] == Salida[1]) );

        txtrep[Entrada[0]][Entrada[1]] = entrada;
        txtrep[Salida[0]][Salida[1]] = salida;

    
        // Paso 5
        Visito_Vecino(Entrada[1],Entrada[0],4);
        
        
        // Paso 6
        for(int i = 0; i < nf; i++){
            for(int j = 0; j < nc; j++){
                switch (txtrep[i][j]){
                case pared:                                     continue;
                case espacio_visitado: txtrep[i][j] = espacio;  continue;
                case espacio:                                   continue;
                case entrada_visitada: txtrep[i][j] = entrada;  continue;
                case salida_visitada: txtrep[i][j]  = salida;   continue;
                }
            }
        }

    }; //TODO ok

    // imprime el laberinto (es idéntica a la del parcial)
    void print()
    {
        for(size_t i=0; i<nf; ++i )
            cout << txtrep[i] << endl;
    }

private:
    // numero de filas y columnas, deben ser impar y nf * nc >=15
    size_t nf, nc;
	// representacion textual del laberinto como matriz de caracteres.
    vector<string> txtrep;

    void Visito_Vecino(int x, int y, int direccion){
        if( (x >= nf) || ( x < 0) || ( y < 0) || ( y >= nc))
            return ;

        switch (txtrep[x][y])
        {
        case espacio_visitado:  return;
        case espacio:           txtrep[x][y] = espacio_visitado; break;
        case entrada_visitada:  return;
        case entrada:           txtrep[x][y] = entrada_visitada; break;
        case salida_visitada:   return;
        case salida:            txtrep[x][y] = salida_visitada; break;
        case pared:             assert(1);  // Nunca deberia llegar aca 
        }

        // direccion corresponde a de donde vine: 0 abajo, 1 arriba, 2 izquierda, 3 derecha, 4 solo se usa la primera vez (direccion nula)
        //No es necesario un enum porque solo lo usa aca
        switch (direccion)
        {
        case 0: //Elimino la pared de abajo 
            txtrep[x][y-1] = espacio_visitado;
            break;
        case 1: //Elimino la pared de arriba 
            txtrep[x][y+1] = espacio_visitado;
            break;
        case 2: //Elimino la pared de la izquierda 
            txtrep[x-1][y] = espacio_visitado;
            break;
        case 3: //Elimino la pared de la derecha 
            txtrep[x+1][y] = espacio_visitado;
        case 4: 
            break;
        }
        
        vector<int> Array = {0,1,2,3};
        random_shuffle ( Array.begin(), Array.end() );

        for(int i = 0; i< 4; i++){
            switch (Array[i])
            {
                case 0: Visito_Vecino(x+2,  y , 2); break;  // Derecha   -> vengo de la izquierda
                case 1: Visito_Vecino(x  , y+2, 0); break;  // Subo -> vengo de abajo
                case 2: Visito_Vecino(x  , y-2, 1); break;  // Bajo -> vengo de arriba
                case 3: Visito_Vecino(x-2,  y , 3); break;  // Izquierda -> vengo de la derecha
            }
        }      

        return;
    }
};

int main(){
    int nf,nc;
    bool laberinto_invalido = 1;
    Laberinto* laberinto;
    while(laberinto_invalido){
        try{
        cout<<"Ingrese el Numero de Filas de su Laberinto:  ";
        cin>> nf;
        cout<<"Ingrese el Numero de Columnas de su Laberinto:  ";
        cin>> nc;
        laberinto = new Laberinto(nf,nc);
        laberinto_invalido = 0;
        }
        catch(int n){
            laberinto_invalido = 1;
            cout<< "Laberinto invalido!!!"<<endl;
        }
    }
    laberinto->print();
    delete laberinto;
    system("pause");
    return 0;
} // TODO

