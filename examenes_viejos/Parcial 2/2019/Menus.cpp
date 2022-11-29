#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <vector>

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class OptionMenu {
public:
    // debe crear la opcion leyendo el label y la cantidad de hijos desde el ifstream
    // reservar espacio para las suboptions de acuerdo a la cantidad de hijos y
    // mandar a crear esos hijos desde el mismo ifstream y pushearlos en suboptions.
    // (queda recursivo)
    OptionMenu(ifstream &in) {  
        int n_hijos;

        in >> label >> n_hijos;         //Guardo el label y la cantidad de hijos

        for (int i = 0; i < n_hijos; i++)   //Guardo cada uno de los hijos en un menu option
        {
            suboptions.push_back(new OptionMenu(in));
        }
    }

    ~OptionMenu() {
        for(auto i : suboptions){   //Libero cada uno de la memoria reservada
            delete i;
        }
    }

    // debe visualizar la opcion del men� como
    // label : option1  option2  option3
    // donde label es la etiqueta de la opci�n y optionX son las etiquetas de las subopciones hijas
    void display() {
        cout << label << endl;
        for(auto a : suboptions){
            cout << a->label << endl;
        }
    }

    // debe retornar la subopcion que tiene la etiqueta reqOption o nullptr si no existe esa subopcion
    OptionMenu *browse(const string &reqOption) {
        for (auto c : suboptions){
            if(c->label == reqOption){
                return c;
            }
        }
        return nullptr;
    }


private:
    string label;
    vector<OptionMenu *> suboptions;
};

class MenuBrowser {
public:
    // constructor que carga el men� de opciones desde el archivo fname
    // y hace que tanto root como current apunten a la opci�n ra�z del menu
    MenuBrowser(const char *fname) {
        ifstream in(fname);
        assert(in);
        root = current = new OptionMenu(in);
    }
    ~MenuBrowser() {
        delete root;
        delete current;
    }

    // m�todo que debe imprimir la opcion actual (current->display()), 
    // pedir la opcion deseada (cin >> opcion) e intentar navegar a esa subopci�n deseada
    // (current->browse(opcion)). 
    // Si esa opcion existe se debe cambiar current, 
    // si no existe se debe emitir un mensaje informandolo,
    // se debe imprimir nuevamente la opcion actual (current->display())
    // se debe reservar la opci�n "TOP" para que en caso de ser la opcion deseada, se haga que current sea nuevamente root.
    void prompt() {
        string opcion;

        current->display();
        cin >> opcion;
        OptionMenu *search = current->browse(opcion);
        if(opcion == "TOP") {
            current = root;
        }
        else if(search != nullptr) {
            current = search;
        }else{
            cout << "No existe ese menu, ingrese nuevamente" << endl;
        }
    }

private:
    OptionMenu *root;       // define la opci�n ra�z del sistema de men�s
    OptionMenu *current;    // opci�n activa
};

int main()
{
    MenuBrowser mb("menus.txt");

    while (true) {
        mb.prompt();
    }
}
