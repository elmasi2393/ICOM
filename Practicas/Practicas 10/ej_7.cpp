#include <iostream>

using namespace std;

//INTERNAL FUNCTION
class MyString{
    public:
        MyString(const char *str_new); //Constructor
        MyString(const MyString& other); //Copy constructor
        MyString();
        ~MyString(); //Destructor
        void print() const;

        //Operadores
        MyString operator+(const MyString& other) const;
        bool operator=(const MyString& other);
        // bool operator=(const char &character);
        char & operator[](int i);
    private:
        char *str;
};

//IMPLEMENTATION
/**
 * @brief Construct a new My String:: My String object
 * 
 * @param str_new 
 */
MyString::MyString(const char * str_new){
    int i = 0;

    //Cuento la cantidad de elementos
    while(str_new[i] != '\0'){ i++;}

    //Guardo memoria para los elementos
    this->str = new (nothrow) char[i+1];

    if(this->str == nullptr) { cout << "Error" << endl; }   //Pregunto si se asigno correctamente
    else{
        for(int j = 0; j < i ; j++) {   //Asigno cada valor del vector
            this->str[j] = str_new[j];
        }
        this->str[i] = '\0'; //Agrego el final de cadena
    }
}
/**
 * @brief Copy a new My String:: My String object
 * 
 * @param other 
 */
MyString::MyString(const MyString& other){
    int i = 0;

    //Cuento la cantidad de elementos
    while(other.str[i] != '\0'){ i++;}

    //Guardo memoria para los elementos
    this->str = new (nothrow) char[i+1];

    if(this->str == nullptr) { cout << "Error" << endl; }   //Pregunto si se asigno correctamente
    else{
        for(int j = 0; j < i ; j++) {   //Asigno cada valor del vector
            this->str[j] = other.str[j];
        }
        this->str[i] = '\0'; //Agrego el final de cadena
    }
}
/**
 * @brief Construct a new NULL My String:: My String object
 * 
 * 
 */
MyString::MyString() {
    this->str = NULL;
}
/**
 * @brief Destroy the My String:: My String object
 * 
 */
MyString::~MyString(){
    delete [] this->str;
}

/**
 * @brief print() const
 * @p print string
 */
void MyString::print() const{
    int i = 0;
    while(this->str[i] != '\0'){
        cout << this->str[i];
        i++;
    }
    cout << endl;
    return;
}
/**
 * @brief operator+
 * @p concatena dos strings
 * @param other 
 * @return MyString 
 */
MyString MyString::operator+(const MyString& other) const{
    int i = 0, j = 0;

    //Cuento longitud de ambos string
    while(this->str[i] != '\0'){ i++;}
    while(other.str[j] != '\0'){ j++;}

    // cout << i << " " << j << " " << endl;

    //Pido la memoria necesaria
    char *elements = new (nothrow) char[i+j+1];
    if(elements == NULL){       //Chequeo si se asigno
        cout << "Error" << endl;
    }else{
        for(int k = 0; k < i; k++){         //Agrego los elementos del primer vector
            elements[k] = this->str[k];
        }
        for(int k = 0; k < j; k++){         //Agrego los elementos del segundo vector
            elements[k+i] = other.str[k];
        }
        elements[i+j] = '\0'; //Agrego el final de cadena
    }
    MyString result(elements);
    delete[] elements;

    return result;
}
/**
 * @brief operator=
 * 
 * @param other 
 * @return bool 
 * @retval true si se pudo asignar
 * @retval false si no se pudo asignar
 */
bool MyString::operator=(const MyString& other){
    int i = 0;

    //Cuento la cantidad de elementos
    while(other.str[i] != '\0'){ i++;}

    //Guardo memoria para los elementos
    this->str = new (nothrow) char[i+1];

    if(this->str == nullptr) { cout << "Error" << endl;  return 0;}   //Pregunto si se asigno correctamente
    else{
        for(int j = 0; j < i ; j++) {   //Asigno cada valor del vector
            this->str[j] = other.str[j];
        }
        this->str[i] = '\0'; //Agrego el final de cadena
    }
    return true;
}
/**
 * @brief operator[]
 * 
 * @param i index
 * @return char& 
 */
char & MyString::operator[](int i){
    return this->str[i];
}

//MAIN FUNCTION
int main(int argc, char **argv){

    MyString s1("hola mundo");
    s1.print();
    MyString s2(s1);
    s2.print();
    MyString s3;
    s3 = s1 + s2;
    s3.print();
    s3[4] = 'X';
    s3.print();
    char c = s3[2];
    cout << c << endl;

    return 0;
}