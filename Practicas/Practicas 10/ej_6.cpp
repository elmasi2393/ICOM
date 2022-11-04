#include <iostream>
#include <vector>
#include <array>

using namespace std;

class SimMatrix {
    public:
        SimMatrix(size_t dim); // define una matriz de dim x dim 
        SimMatrix(const SimMatrix &); // copy-constructor 
        ~SimMatrix();
        void setElement(int i, int j, double val);
        double getElement(int i, int j) const;
        int getDim() const;
        void print() const;

        //Operadores
        SimMatrix &operator=(const SimMatrix &);
    private:
        vector <double> *values;
        size_t dim;
};


//Implementation
/**
 * @brief Construct a new Sim Matrix:: Sim Matrix object
 * @p Reserva los elementos neccesarios para almacenar una matriz simetrica
 * @param dim 
 */
SimMatrix::SimMatrix(size_t dim_){
    dim = dim_;

    values = new vector<double>[dim];   //Asigno memoria para los vectores
    for(int i = 0; i < dim; i++){
        values[i].resize(i+1);          //Asigno cada dimension de los vectores
    }
}
SimMatrix::SimMatrix(const SimMatrix &other){
    this->dim = other.dim;

    this->values = new vector<double>[dim]; //Asigno memoria para los vectores
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            values[i].push_back(other.values[i][j]);
        }
    }
}
/**
 * @brief Destroy the Sim Matrix:: Sim Matrix object
 * @p libera la memoria de un vector
 */
SimMatrix::~SimMatrix(){
    delete [] this->values;
}

/**
 * @brief setElement
 * @p setea un elemento de la matriz
 * @param i filas
 * @param j columnas
 * @param val valor
 */
void SimMatrix::setElement(int i, int j, double val) {
    if(i < j){
        this->values[j].at(i) = val;
    }else{
        this->values[i].at(j) = val;
    }
    return;
}
/**
 * @brief getElement
 * @p devuelve el elemento i, j
 * @param i 
 * @param j 
 * @return double 
 */
double SimMatrix::getElement(int i, int j) const{
    if(i < j){
        return this->values[j].at(i);
    }else{
        return this->values[i].at(j);
    }
}
/**
 * @brief getDim
 * @p devuelve la dimension
 * @return int 
 */
int SimMatrix::getDim() const{ return this->dim; }

/**
 * @brief print
 * @p imprime la matriz
 */
void SimMatrix::print() const{

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << this->getElement(i, j) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
SimMatrix & SimMatrix::operator=(const SimMatrix & other){
    this->dim = other.getDim();

    for(int i = 0; i < this->getDim(); i++){
        for(int j = i; j < this->getDim(); j++){
            this->setElement(i, j, other.getElement(i, j));
        }
    }

    return *this;    

}
SimMatrix *sumaSimMatrix(const SimMatrix &m1, const SimMatrix &m2){

    SimMatrix * result = new (nothrow) SimMatrix(m1.getDim());

    for (int i = 0; i < m1.getDim(); i++){
        for (int j = 0; j < m2.getDim(); j++){
            result->setElement(i, j, m1.getElement(i, j) + m2.getElement(i, j));
        }
    }

    return result;
}


int main(){
    SimMatrix matrix(4);

    //Seteo la matrix
    for(int i = 0; i < 4; i++){
        for(int j = i; j < 4; j++){
            matrix.setElement(i, j, 1);
        }
    }

    SimMatrix m2(matrix);   //Construyo una matriz por copia


    //Imprimo la matriz
    matrix.print();

    cout << "--------------------------------" << endl;

    //Iprimo la matriz copiada
    m2.print();

    cout << "-------------- SUMA ------------------" << endl;
    SimMatrix * m3 = sumaSimMatrix(matrix, m2);
    m3->print();

    SimMatrix m4(4);
    m4 = m2;
    m4.print();
    cout << "--------------------------------" << endl;

    cout << &m4 << "  " << &m2 << endl;
    return 0; 
}