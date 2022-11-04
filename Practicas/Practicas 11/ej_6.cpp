// #include <iostream>
// #include <string>

// using namespace std;

// class Stack {
//     public:
//         void push(char c);  // coloca un nuevo carácter en la pila
//         char pop();         // retira el elemento al tope del stack
//         bool isEmpty();     // retorna true/false indicando si el stack está vacío
//         void print() const;

//     private:
//         string element;
//         int n_elements = 0;
// };

// void Stack::push(char c){
//     this->element += c;
//     this->n_elements++;

//     return;
// }

// char Stack::pop(){
//     if(this->n_elements >0){
//         this->n_elements--;
//         char retval = this->element[n_elements];

//         this-> element = this->element.substr(0, this->n_elements);

//         return retval;
//     }
//     return '\0';
    
// }

// bool Stack::isEmpty(){
//     if(this->n_elements == 0){ return true; }

//     return false;
// }


// void Stack::print() const {
//     cout << "Stack contents:" << this->element << endl;

//     return;
// }

// int main(){

//     Stack pila;

//     pila.push('c');
//     pila.push('d');
//     pila.push('g');

//     for (int i = 0; i < 5; i++) {
//         cout << pila.pop() << endl;
//         pila.print();
//         if(pila.isEmpty()){
//             cout << "Pila vacia" << endl;
//         }
//     }

//     return 0;
// }


#include <iostream>

using namespace std;

class Stack {
    public:
        Stack();
        void push(char c);  // coloca un nuevo carácter en la pila
        char pop();         // retira el elemento al tope del stack
        bool isEmpty();     // retorna true/false indicando si el stack está vacío
        void print() const;

    private:
        char *element;
        int n_elements;
};
/**
 * @brief Construct a new Stack:: Stack object
 * @p inicializa con un puntero nulo y el numero de elementos en 0
 */
Stack::Stack(){
    element = nullptr;
    n_elements = 0;
}

/**
 * @brief push
 * @p mete un elemento en la pila
 * @param c elemento a poner en la pila
 */
void Stack::push(char c){
    char *p = this->element;    //Guardo los elementos en una variable temporal
    n_elements++;


    this->element = new (nothrow) char[n_elements]; //Pido memoria para alocar los elementos
    if(this->element == NULL){
        cout << "ERROR: Unable to allocate" << endl;
        return;
    }else{
        for (int i = 0; i < n_elements-1; i++){     //Si se pudo alocar, guardo los elementos que tenia 
            this->element[i] = p[i];
        }

        this->element[n_elements-1] = c;        //Y luego guardo el elemento nuevo

        delete[] p;     //Elimino los viejos
    }
    return;
}

// void Stack::push(char c){

//     if(this->n_elements > 0){
//         this->element++;
//         this->n_elements += this->n_elements;

//         this->element = new char;
//         *(this->element) = c;

//         this->element -= this->n_elements;

//     }else{

//     }


//     return;
// }


/**
 * @brief pop
 * @p devuelve el ultimo elemento de la pila
 * @return char 
 * @retval '\0' Si no hay elementos en la pila o hay error reasignando
 * @retval 'last' El ultimo elemento de la pila
 */
char Stack::pop(){
    char retval = '\0';     //Establezco como valor de return

    if(this->n_elements > 0){   //Si hay elementos en la pila
        n_elements--;   //resto el numero de elementos

        retval = this->element[n_elements]; //Seteo como retval

        if(this->n_elements >0){        //Si siguen quedando elementos
            char *p = this->element;    //Almaceno en una variable temporal   

            this->element = new (nothrow) char[n_elements];   //Pido memora para los restantes
            if (this->element == nullptr){
                cout << "Error to allocate memory" << endl;
                return '\0';
            }else{
                for (int i = 0; i < n_elements; i++){   //Almaceno los restantes
                    this->element[i] = p[i];
                }
                delete[] p;     //Elimino la variable tempora;
                }
        }else{  //Si no quedan eelemntos
            delete[] this->element; //Si no quedan mas elementos, libero la memoria
        }
    }

    return retval;  //Devuelve el valor correspondiente
}
/**
 * @brief isEmpty
 * @p indica si la pila esta vacia
 * 
 * @return bool
 * @retval true if empty
 * @retval false if not empty
 */
bool Stack::isEmpty(){
    if(this->n_elements == 0) {return true;}

    return false;
}

/**
 * @brief print() const
 * @p imprime los elementos de la pila
 */
void Stack::print() const{
    if(this->n_elements > 0){
        for(int i = 0; i < n_elements; i++){
            cout << this->element[i];
        }
        cout << endl;
    }else
        cout << "Pila vacía" << endl;
    return;
}


int main(){

    Stack pila;

    pila.push('c');
    pila.push('d');
    pila.push('g');

    for (int i = 0; i < 5; i++) {
        pila.print();
        cout << pila.pop() << endl;
        if(pila.isEmpty()){
            cout << "Pila vacia" << endl;
        }
    }

    return 0;
}