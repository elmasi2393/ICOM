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
        int getDim() const;

        //Operadores
        MyString &operator+(const MyString& other);
        MyString & operator=(const MyString& other);
        char & operator[](int i);
    private:
        char *str;
        int dim;
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

    this->dim = i + 1;

    //Guardo memoria para los elementos
    this->str = new (nothrow) char[this->dim];

    if(this->str == nullptr) { cout << "Error" << endl; }   //Pregunto si se asigno correctamente
    else{
        for(int j = 0; j < this->dim ; j++) {   //Asigno cada valor del vector
            this->str[j] = str_new[j];
        }
        this->str[this->getDim()] = '\0'; //Agrego el final de cadena
    }
}
/**
 * @brief Copy a new My String:: My String object
 * 
 * @param other 
 */
MyString::MyString(const MyString& other){
    this->dim = other.getDim();

    //Guardo memoria para los elementos
    this->str = new (nothrow) char[other.getDim()];

    if(this->str == nullptr) { cout << "Error" << endl; }   //Pregunto si se asigno correctamente
    else{
        for(int j = 0; j < this->dim ; j++) {   //Asigno cada valor del vector
            this->str[j] = other.str[j];
        }
        this->str[this->getDim()] = '\0'; //Agrego el final de cadena
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
    cout <<"print" << endl;
    for(int i = 0; i < this->dim; i++){
        cout << this->str[i];
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
MyString &MyString::operator+(const MyString& other) {
    int i = this->dim;
    int j = other.getDim();

    //Pido la memoria necesaria
    char *elements = new (nothrow) char[i+j-1];
    if(elements == NULL){       //Chequeo si se asigno
        cout << "Error" << endl;
    }else{
        for(int k = 0; k < i-1; k++){         //Agrego los elementos del primer vector
            elements[k] = this->str[k];
        }
        for(int k = 0; k < j-1; k++){         //Agrego los elementos del segundo vector
            elements[k+i-1] = other.str[k];
        }
        elements[i+j-1] = '\0'; //Agrego el final de cadena
    }
    MyString *new_str = new MyString(elements);

    return *new_str;
}

/**
 * @brief operator=
 * @p asigna un string a otro
 * @param other 
 * @return MyString& 
 */
MyString & MyString::operator=(const MyString& other){
    if(this != &other){
        delete [] this->str;
        this->dim = other.getDim();

        //Guardo memoria para los elementos
        this->str = new (nothrow) char[other.getDim()];

        if(this->str == nullptr) { cout << "Error" << endl; }   //Pregunto si se asigno correctamente
        else{
            for(int j = 0; j < this->dim ; j++) {   //Asigno cada valor del vector
                this->str[j] = other.str[j];
            }
            this->str[this->getDim()] = '\0'; //Agrego el final de cadena
        }
    }
    return *this;
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

int MyString::getDim() const{ return this->dim; }

//MAIN FUNCTION
int main(int argc, char **argv){

    MyString s1("hola mundo");
    s1.print();
    MyString s2(s1);
    s2.print();
    MyString s3;
    s3 = s1 + s2;
    s3.print();
    cout << "----" << endl;
    s3[4] = 'X';
    s3.print();
    char c = s3[2];
    cout << c << endl;

    return 0;
}