#include <iostream>

#define NUM_GRUPS 50
#define NUM_ELEMENTOS 1000

using namespace std;

struct Cumpleanios{
    enum Meses {ENERO, FEBRERO, MARZO, ABRIL, MAYO, JUNIO, JULIO, AGOSTO, SEPTIEMBRE, OCTUBRE, NOVIEMBRE, DICIEMBRE, NUM_TERMINOS};

    int dia;
    int mes;

    void print(){
        cout << "Dia: " << dia << " Mes: " << mes << endl;
    }
};

/**
 * @brief isEqual
 * @p compara si dos cumpleanios son iguales
 * @param c1 
 * @param c2 
 * @return true si dos cupleanos son iguales
 * @return false si dos cumpleanios no son iguales
 */
bool isEqual(Cumpleanios c1, Cumpleanios c2){
    if(c1.dia == c2.dia && c1.mes == c2.mes) { return true; }
    return false;
}
/**
 * @brief equal_inGroup
 * @p Compara si un elemento de un vector es igual a los demas
 * @param c 
 * @param C 
 * @param i 
 * @param n 
 * @return true si un elemento es igual a los demas
 * @return false si ese elemento no es igual a los restantes
 */
bool equal_inGroup(Cumpleanios c, Cumpleanios C[], int i,int n){
    for (int j=i+1; j<n; j++) {
        if(isEqual(c, C[j])){ return true; }
    }
    return false;
} 
/**
 * @brief equals2_Group
 * @p Si al menos dos son iguales en un grupo
* @param c 
 * @param i 
 * @param n 
 * @return true Si hay almenos dos iguales
 * @return false Si no hay dos iguales
 */
bool equals2_Group(Cumpleanios c[], int i, int n) {
    for (i; i < n-1; i++) {
        if(equal_inGroup(c[i], c, i, n)){ return true; }
    }
return false;
}

int main(int argc, char **argv){
    Cumpleanios comp[NUM_ELEMENTOS];

    //Asignamos valores aleatorios de cada mes y cada dia
    for(int i = 0; i < sizeof(comp)/sizeof(Cumpleanios); i++){
        comp[i].mes = rand() % comp[i].NUM_TERMINOS;

        if(comp[i].mes == comp[i].FEBRERO){ //Si es Frebrero solo tengo 28 dias
            comp[i].dia = rand() % 29;
        }
        else if(comp[i].mes == comp[i].ABRIL || comp[i].mes == comp[i].JUNIO || comp[i].mes == comp[i].SEPTIEMBRE || comp[i].mes == comp[i].NOVIEMBRE){    //Si es uno de estos solo tiene 30 dias
            comp[i].dia = rand() % 31;
        }else { comp[i].dia = rand() %31; } //Sino tiene 31 dias

    }
    int iguales_2_fc = 0;
    for(int i = 0; i < sizeof(comp)/sizeof(Cumpleanios); i+=NUM_GRUPS){
        if(equals2_Group(comp, i, i+NUM_GRUPS)) {iguales_2_fc++;}
    }

    cout << "Personas por grupo = " << NUM_GRUPS << endl;
    cout << "Probabilidad: " << iguales_2_fc/double((NUM_ELEMENTOS/NUM_GRUPS)) << endl;

    return 0;
}