/*
    Una guardería
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <list>
#include <map>

using namespace std;

static const double CAT_FOOD_PER_WEIGHT  = 0.015;
static const double DOG_FOOD_PER_WEIGHT  = 0.020;
static const double BIRD_FOOD_PER_WEIGHT = 0.030;

class PetFood {
    public:
        virtual string getFoodName() const = 0;
};

class Pet {
    public:
        Pet(const string &name_);  // TODO

        const string &getName() const;    // TODO

        virtual const PetFood *getFoodReq(double *pCount) = 0;

    protected:
        string name;
};


class DogFood : public PetFood {
	public:
		string getFoodName() const { return "DogFood";}
};

class Dog : public Pet {
    public:
        Dog(const string &name_, double weight);  // TODO

        const PetFood *getFoodReq(double *pCount) {
            *pCount = bodyWeight * DOG_FOOD_PER_WEIGHT;
            return &dog_food;
        };
        
    private:
        double bodyWeight;
        static DogFood dog_food;
};

DogFood Dog::dog_food;

// TODO: class CatFood

class Cat : public Pet {
    public:
        Cat(const string &name_, double weight);   // TODO

        const PetFood *getFoodReq(double *pCount);      // TODO
        
    private:
        double bodyWeight;
        static CatFood cat_food;
};


// TODO: class BirdFood

// TODO: class Bird

class PetFactory {
    public:
        // Método que a partir del tipo de la mascota (DOG, CAT o BIRD)
        // crea y retorna una nueva instancia del objeto adecuado al tipo
        static Pet *newPet(const string &pet_type, const string &name, double weight);   // TODO
};

class Guarderia {
    public:
        // Método que carga el inventario de animales desde el archivo con nombre fname
        // Hint: utilizar PetFactory::newPet()
        void loadPetDatabase(const string &fname);     // TODO

        // Método que retorna retorna un mapa de nombre de comida - cantidad
        // con los requerimientos de cada tipo de comida
        map<string, double> getBuyList() const;     // TODO

    private:
        list<Pet *> inventario;
};

int main()
{
    Guarderia grd;

    grd.loadPetDatabase("mascotas.txt");

    auto listaCompra = grd.getBuyList();

    // TODO: imprimir lista de compras

    return 0;
}


