#include <iostream>
#include <string>

using namespace std;

class JuegoPrediccion{
    public:
        JuegoPrediccion(): fx(0), fo(0), pg(0), pp(0){
            cout << "****************************************************************" << endl;
            cout << "  JuegoPrediccion: intentare adivinar tu siguiente caracter ;) " << endl;
            cout << "****************************************************************" << endl;
        }

        bool avanzar_turno();
        void finalizar();

    private:
    	string patron;              //patron ingresado
        string estado_fin_juego;    //estado_fin_juego
        int fx, fo;                 //probabilidades
        int pg, pp;                 //puntos del juego y puntos del jugador
        const int puntaje_maximo = 50;

        char leer_secuencia();
        char predccion();

};

bool JuegoPrediccion::avanzar_turno(){
    char pred = predccion();
    char lec = leer_secuencia();

    cout << "-------------------------------" << endl;
    cout << "Lectura: " << lec << endl;
    cout << "Predccion: " << pred << endl;
    
    if(pred == lec) //Veo para quien sumar puntos
        pg++;
    else
        pp++;
    cout << "-------------------------------" << endl;
    cout << "Tus puntos: " << pp << endl;
    cout << "Mis puntos: " << pg << endl;
    cout << "=====================================" << endl;

    if(pg == puntaje_maximo){   //Comparo el puntaje para ver si alguno gano
        estado_fin_juego = "Gane :)";
        return false;
    }else if(pp == puntaje_maximo){
        estado_fin_juego = "Ganaste :(";
        return false;
    }

    patron += lec;  //Agrego el caracter al patron

    return true;
}

char JuegoPrediccion::leer_secuencia(){
    while(true){
        cout << "Ingrese un 'x' o 'o'" << endl;
        char c=cin.get();
		cin.ignore(100,'\n');
        // cin >> c;
        switch (c)
        {
        case 'x':
            return c;
            break;
        case 'o':
            return c;
            break;
        default:
            cout << "Caracter ingresado no valido" << endl;
        }
    }
}

void JuegoPrediccion::finalizar(){
    cout << estado_fin_juego << endl;
}

char JuegoPrediccion::predccion(){
    //Reseteo las probabilidades
    fo = 0;
    fx = 0;
    //Si no tengo sufiicientes caracteres, adivino al azar
    if(patron.size() < 4)
        return ((rand() %2)? 'o' : 'x');

    string last(patron.end() - 4, patron.end());;  //Obtengo los ultimos 4 digitos
    //Obtengo prediccion para x
    auto pos_x = patron.find(last + 'x');
    while(pos_x != string::npos){  
        fx++;
        pos_x = patron.find(last + 'x', pos_x+1);
    }
    //Obtengo prediccion para o
    auto pos_o = patron.find(last + 'o');
    while(pos_o != string::npos){  
        fo++;
        pos_o = patron.find(last + 'o', pos_o+1);
    }

    if(fx > fo)
        return 'x';
    else if(fo > fx)
        return 'o';
    else
        return ((rand() %2)? 'o' : 'x');
}

//========================== MAIN ========================
int main(){
    JuegoPrediccion game;

    while(game.avanzar_turno())
    	;

    game.finalizar();

    // string patron = "oxoxooxxx";

    // string last(patron.end() - 4, patron.end());
    // cout << patron << endl;
    // cout << last << endl;

    return 0;
}

