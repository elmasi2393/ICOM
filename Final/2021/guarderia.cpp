/*
    Una guardería
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <list>
#include <map>
#include <cassert>

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
        Pet(const string &name_): name(name_) {}

        const string &getName() const { return name; }

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
        Dog(const string &name_, double weight): Pet(name_), bodyWeight(weight) {}

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
class CatFood : public PetFood{
    public:
        string getFoodName() const { return "CatFood"; }
};

class Cat : public Pet {
    public:
        Cat(const string &name_, double weight): Pet(name_), bodyWeight(weight) {}

        const PetFood *getFoodReq(double *pCount){
            *pCount = bodyWeight * CAT_FOOD_PER_WEIGHT;
            return &cat_food;
        }
        
    private:
        double bodyWeight;
        static CatFood cat_food;
};
CatFood Cat::cat_food;

// TODO: class BirdFood
class BirdFood : public PetFood{
    public:
        string getFoodName() const { return "BirdFood"; }
};

// TODO: class Bird
class Bird : public Pet {
    public:
        Bird(const string &name_, double weight): Pet(name_), bodyWeight(weight) {}

        const PetFood *getFoodReq(double *pCount) {
            *pCount = bodyWeight * BIRD_FOOD_PER_WEIGHT;
            return &bird_food;
        };
    private:
        double bodyWeight;
        static BirdFood bird_food;
};
BirdFood Bird::bird_food;

class PetFactory {
    public:
        // Método que a partir del tipo de la mascota (DOG, CAT o BIRD)
        // crea y retorna una nueva instancia del objeto adecuado al tipo
        static Pet *newPet(const string &pet_type, const string &name, double weight){
            if(pet_type == "DOG")
                return new Dog(name, weight);
            else if(pet_type == "CAT")
                return new Cat(name, weight);
            else if(pet_type == "BIRD")
                return new Bird(name, weight);
            else
                return nullptr;
        }
};

class Guarderia {
    public:
        // Método que carga el inventario de animales desde el archivo con nombre fname
        // Hint: utilizar PetFactory::newPet()
        void loadPetDatabase(const string &fname){
            ifstream file(fname);
            try{
                if(!file.is_open())
                	throw runtime_error("No se pudo abrir el archivo");
                
                string type, name;
                double weight;
                while(file >> type >> name >> weight)
                    inventario.push_back(PetFactory::newPet(type, name, weight));
                // for(auto a: inventario)
                //     cout << a->getName() << endl;
            }catch(const runtime_error &e){
                cout << e.what() << endl;
            }
        }

        // Método que retorna retorna un mapa de nombre de comida - cantidad
        // con los requerimientos de cada tipo de comida
        map<string, double> getBuyList() const{ //VER ESTA FUNCION PARA QUE ME SUME TODAS LAS COMIDAS
            map<string, double> result;
            // double food_dog = 0, foog_cat = 0, food_bird = 0;
            
            for(auto a: inventario){
                double food;
                const PetFood * food_pet = a->getFoodReq(&food);
                string type_food = food_pet->getFoodName();
                if(type_food == "DogFood"){
                    auto it = result.find("DOG");
                    if(it == result.end())      //Si no estaba, la creo y le asigno la comida
                        result["DOG"] = food;
                    else
                        (*it).second += food;   //Sino le sumo lo que necesita otro perro
                }else if(type_food == "CatFood"){
                    auto it = result.find("CAT");
                    if(it == result.end())      //Si no estaba, la creo y le asigno la comida
                        result["CAT"] = food;
                    else
                        (*it).second += food;   //Sino le sumo lo que necesita otro perro
                }else if(type_food == "BirdFood"){
                    auto it = result.find("BIRD");
                    if(it == result.end())      //Si no estaba, la creo y le asigno la comida
                        result["BIRD"] = food;
                    else
                        (*it).second += food;   //Sino le sumo lo que necesita otro perro
                }

            }

            return result;
        }

    private:
        list<Pet *> inventario;
};

int main()
{
    Guarderia grd;

    grd.loadPetDatabase("mascotas.txt");

    auto listaCompra = grd.getBuyList();

    for(auto a: listaCompra)
        cout << a.first << " " << a.second << endl;

    // TODO: imprimir lista de compras

    return 0;
}


