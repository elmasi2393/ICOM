#include <iostream>

using namespace std;

struct RGB {
    //DECLARACION DE ATRIBUTOS
    unsigned char red, green, blue;

    //DECLARACION DE METODOS
    /**
     * @brief setFromComponents
     * @p: establece un color por medio de sus componentes
     * @param R 
     * @param G 
     * @param B 
     * @return *1 si se asigno correctamente
     * @return *0 si hubo un error al asignar
     */
    bool setFromComponents(int R, int G, int B){
        if( R > 255 || G > 255 || B > 255){ return 0;}  //Preguntamos si alguna de las componentes es incorrecta
        red = R;
        green = G;
        blue = B;

        return 1;
    }
    /**
     * @brief compositeColor
     * @p :compone los colores en una variable tipo int
     * 
     * @return int 
     */
    int compositeColor(){
        return red << 16 | green << 8 | blue;   //Se componen desplazando y haciendo or
    }
    /**
     * @brief setFromComposite()
     * @p: establece un color por medio de un color compuesto
     * @param color 
     * @return bool: *1 Si el color fue establecido correctamente
     * @return bool: *0 Si el color no pudo ser establecido
     */
    bool setFromComposite(int color){
        if(color > 0xFFFFFF) //preguntamos si tiene digitos no nulos en los 8 bit mas representativos
            return 0;
        //Establecer colores desplazando bits ya que blue tiene solo 1 byte
        blue = color;
        green = color >> 8;
        red = color >> 16;

        return 1;
    }
    /**
     * @brief print()
     * @p: imprime los colores en una sola linea
     * @return void
     */
    void print(){
        cout << hex << (int)red << hex << (int)green << hex <<  (int)blue << endl;  //Convierto a int para que se impriman de manera correcta
    }

};

int main(int argc, char **argv) {
    //Asignacion de color
    RGB color = {0xFA, 0x23, 0x14};     //Se pasan los numero en formato hexa

    //Prueba de print
    color.print();
    
    //Prueba de compositeColor
    cout << hex << color.compositeColor() << endl;

    //Prueba de setFromComposite
    if(color.setFromComposite(0x00567823)) {color.print(); }
    else {cout << "Error de argumentos para establecer un color" << endl;}

    if(color.setFromComposite(0x10567823)) {color.print(); }
    else {cout << "Error de argumentos para establecer un color" << endl;}
    
    //Prueba de setFromComponents
    if(color.setFromComponents(0x1FF, 0x45, 0x78)){ color.print();}
    else{ cout << "Error de argumentos para establecer un color" << endl; }

    if(color.setFromComponents(0xFF, 0x45, 0x78)){ color.print();}
    else{ cout << "Error de argumentos para establecer un color" << endl; }

    return 0;
}