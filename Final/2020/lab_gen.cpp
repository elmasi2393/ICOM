#include <iostream>
#include <string>
#include <vector>
#include <iostream>    
#include <fstream> 
#include <list>
#include <sstream>
#include <fstream> 

using namespace std;

// estos son los caracteres que se pueden encontrar en el laberinto
const char pared = '#';
const char espacio = ' ';
const char espacio_visitado = 'o';
const char entrada = 'E';
const char entrada_visitada = 'e';
const char salida = 'S';
const char salida_visitada='s';
const char espacio_resaltado = '*';

struct Celda
{
    int f, c;
    bool operator==(const Celda & a) const{ return ((f == a.f) && (c == a.c)) ;}
    Celda & operator=(const Celda & a) { 
        f = a.f; 
        c = a.c; 
        return *this;
        }
};

struct Camino{
    Camino(Celda & a){
        camino.push_back(a);
    }
    Camino ();
    vector<Celda> camino;
};

struct genLab_error : public runtime_error{
    genLab_error(const char *p) : runtime_error(p) {}
};

class Laberinto
{
public:
    enum posiciones {ARRIBA, ABAJO, IZQUIERDA, DERECHA};    //Enumeracion de posiciones
    
	// constructor del laberinto que implementa el algoritmo descripto en el enunciado
    Laberinto(size_t nf_, size_t nc_){
        try{
            if((nf_ % 2) == 0 || (nc_ % 2) == 0 || (nf_ * nc_) < 15)    //Si no son validos, levanto una excepcion
                throw genLab_error("Argumentos invalidos");
            
            //Si son validos
            nf = nf_;
            nc = nc_;


            generate_template();
            push_E_S();
            generate_path(begin);
            clear_map();

        }catch(genLab_error e){
            cout << e.what() << endl;
        }
    }
    Laberinto(string path){
        ifstream file(path);
        if (!file.is_open()){
            cout << "Error: " << path << endl;
        }else{
            string line;
            while(getline(file, line)){
                txtrep.push_back(line);
                // cout << line.size() << endl;
                line.clear();
            }
        }
        nc = txtrep.at(0).size();
        nf = txtrep.size();

        //Busco inicio y fin
        for(int i=0; i<nf; i++){
            for(int j=0; j<nc; j++){
                if(txtrep.at(i).at(j) == entrada)
                    begin = Celda{i, j};
                if(txtrep.at(i).at(j) == salida)
                	end = Celda{i, j};
            }
        }
        // cout << txtrep.size() << endl;
    }
	// imprime el laberinto (es idéntica a la del parcial)
    void print() const
    {
        for(size_t i=0; i<nf; ++i )
            cout << txtrep[i] << endl;
    }
    bool save_lab(string path){
        //Guarda el laberinto en un archivo txt
        ofstream out(path);
        if(!out)
            return false;
        for(size_t i=0; i<nf; ++i )
            out << txtrep[i] << endl;
        out.close();
        return true;
    }
    list<Camino*> * resolver(Celda begin){
        // cout << "resolver" << endl;
        list<Camino*> * res = new list<Camino*>();    //Pedimos para un nuevo camino
        // print();
        // cout <<"f: "<<  begin.f << "c: " << begin.c << endl;

        char c =  txtrep.at(begin.f).at(begin.c);
        if((c == pared) || (c == espacio_visitado) || (c == entrada_visitada)) //Si pasamos o estamos en una pared
        	return nullptr;
        if(c == salida){
            Camino * cam = new Camino(begin);
            res->push_back(cam);
            return res;
        }
        if(c == entrada)    //Visito ambos espacios
        	txtrep[begin.f][begin.c] = entrada_visitada;
        if(c == espacio)
            txtrep[begin.f][begin.c] = espacio_visitado;
        
        //Creo caminos para los 4 lados posibles
        list<Camino*> * cams_1 = resolver(Celda{begin.f + 1, begin.c});   //Caminos a la derecha
        list<Camino*> * cams_2 = resolver(Celda{begin.f -1 , begin.c});   //Caminos a la izqueirda
        list<Camino*> * cams_3 = resolver(Celda{begin.f , begin.c + 1});  //Caminos hacia arriba
        list<Camino*> * cams_4 = resolver(Celda{begin.f , begin.c - 1});  //Caminos hacia abajo
        vector<list<Camino*>*> caminos = {cams_1, cams_2, cams_3, cams_4};   //Guardo todos los caminos en un vector

        //Recorro todos los caminos a ver cual esta vacio
        for(auto a: caminos){
            if(a == nullptr) continue;  //Si una lista esta vacia, no tiene caminos
            
            for(auto b : *a){   //Si no esta vacia, le agrego la celda en la que estoy y agrego a mi lista de retorno
                b->camino.push_back(begin);
                res->push_back(b);
            }
        }
        //Antes de volver despinto
        if(c == entrada || c == entrada_visitada)    //Visito ambos espacios
        	txtrep[begin.f][begin.c] = entrada;
        else    
            txtrep[begin.f][begin.c] = espacio;

        return res;
    }
    void print_solucion(){
        // print();  //Primero imprimo el laberinto
    
        list<Camino*> * soluciones = resolver(begin);
        cout << "resuelto" << endl;
        int i = 1;
        for(auto a: *soluciones){
            cout << "Camino: " << i << endl;
            cout << a->camino.size() << endl;
            for(auto b: a->camino){
                if(b == begin || b == end) continue;
                txtrep.at(b.f).at(b.c) = espacio_visitado;
            }
            print();
            clear_map();
            i++;
            
        }

    }
private:
    // numero de filas y columnas, deben ser impar y nf * nc >=15
    size_t nf, nc;
	// representacion textual del laberinto como matriz de caracteres.
    vector<string> txtrep;
    Celda begin, end;

    void generate_template(){
        string result, result2;

        for(size_t i = 0; i <nc; i++){
            result += pared;
            if(i == 0 || i == nc-1)
            	result2 += pared;
            else if(!(i%2))
                result2 += pared;
            else
            	result2 += espacio;
        }
        for(size_t i = 0; i <nf; i++){
            if(!(i%2))
            	txtrep.push_back(result);
            else
            	txtrep.push_back(result2);
        }
    }
    void push_E_S(){
        Celda in = free_cel();  //Busco celda para entrada libre
        Celda out;
        do{
            out = free_cel();   //Busco celda para salida libre diferente a entrada
        }while(in == out);
        begin = in;
        end = out;
        //reemplazo en la fila, columna de la celda por entrada
        txtrep[in.f][in.c] = entrada;
        txtrep[out.f][out.c] = salida;

    }
    Celda free_cel(){
        int i, j;
        do{
            i = rand() % (nf-1);    //Selecciono una fila al azar
        }while(i == 0 && i == nc-1);
        do{
            j = rand() % (nc-1); //Selecciono una columna al azar
        }while((j%2) == 0);

        return Celda{i, j};
    }
    vector<int> aleatory_secuence(){
        bool flag = true;   //Inicio un flag en true
        vector<int> result; //Creo un vector para contener el resultado
        
        do{
            int i = rand() % 4;     //Genero numeros aleatorios
            for(auto a : result) {  //Pregunto si es igual a alguno de los que ya tengo
                if(a == i){
                    flag = false;   //Si es igual, bajo el flag y rompo el ciclo
                    break;
                }
            }
            if(flag)
                result.push_back(i); //Si no es igual a ninguno, lo agrego
            flag = true;    //levantamos el flag para el siguiente
        }while(result.size() < 4);
        return result;
    }
    void generate_path(Celda i){
        //Genero caminos que resuelven el laberinro, destruyendo las paredes necesarias de manera aleatoria
        //Genero un camino aleatorio hasta que llegue a la salida
        // cout << "fila: " << i.f  << " columna: " << i.c << endl;
        // print();
        if(i.c < 0 || i.c >= nc || i.f < 0 || i.f >= nf)    //Si me voy de los limites, retorno
        	return;
        // if(i == end){    //Si llegue al final, dejo de pisar caminos
        //     txtrep[i.f][i.c] = salida_visitada; //Visito la salida
        // 	// return;
        // }
        char c = txtrep.at(i.f).at(i.c);
        if(c == espacio_visitado || c == entrada_visitada)  //Si la la visite, retorno
        	return;
        //Si no es ninguna de las soluciones triviales, recorro de manera aleatoria las posiciones a una distancia de 2
        //desde mi celda actual
        //marco mi actua como visitada
        if(c == entrada)
            txtrep[i.f][i.c] = entrada_visitada;
        else if (c == salida)
            txtrep[i.f][i.c] = salida_visitada;
        else
        	txtrep[i.f][i.c] = espacio_visitado;
        //voy de manera aleatoria a las celdas a una distancia de 2
        
        vector<int> secuence = aleatory_secuence();
        for(auto a : secuence){
            // cout << a << endl;
            switch (a)
            {
            case DERECHA:
                if(txtrep[i.f+2][i.c] == espacio || txtrep[i.f+2][i.c] == salida){          //Si el vecino de +2 esta libre
                    txtrep[i.f+1][i.c] = espacio_visitado;  //Rompo la pared o marco el camino entre medio
                    generate_path(Celda{i.f+2, i.c});        //Busco caminos a partir del vecino
                }
                break;
            case IZQUIERDA:
                if(txtrep[i.f-2][i.c] == espacio || txtrep[i.f-2][i.c] == salida){          //Si el vecino de +2 esta libre
                    txtrep[i.f-1][i.c] = espacio_visitado;  //Rompo la pared o marco el camino entre medio
                    generate_path(Celda{i.f-2, i.c});        //Busco caminos a partir del vecino
                }
                break;
            case ABAJO:
                if(txtrep[i.f][i.c-2] == espacio || txtrep[i.f][i.c-2] == salida){          //Si el vecino de +2 esta libre
                    txtrep[i.f][i.c-1] = espacio_visitado;  //Rompo la pared o marco el camino entre medio
                    generate_path(Celda{i.f, i.c-2});        //Busco caminos a partir del vecino
                }
            	break;
            case ARRIBA:
                if(txtrep[i.f][i.c+2] == espacio || txtrep[i.f][i.c+2] == salida){          //Si el vecino de +2 esta libre
                    txtrep[i.f][i.c+1] = espacio_visitado;  //Rompo la pared o marco el camino entre medio
                    generate_path(Celda{i.f, i.c+2});        //Busco caminos a partir del vecino
                }
            	break;
            
            default:
                break;
            }
        }
    }
    void clear_map(){
        for(auto &a : txtrep){
            for(auto &b : a){
                if (b == espacio_visitado)
                	b = espacio;
            }
        }
        txtrep[begin.f][begin.c] = entrada;
        txtrep[end.f][end.c] = salida;
    }
};

int main(){
    // srand(time(0));
    Laberinto a(51, 51);
    // Laberinto a("laberinto_tomi.txt");

    a.print();
    // a.save_lab("laberinto.txt");
    a.print_solucion();
    // a.print();
    

    return 0;
}

