#include <iostream>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct GeoPoint
{
    // obtiene la distancia a otro GeoPoint. Suponga que la tierra es plana (?), es decir, que
    // las latitudes toman valores entre -90 y 90
    // las longitudes toman valores entre -180 y 180
    double getDistance(GeoPoint gp){
        return (sqrt((gp.lat - lat)*(gp.lat - lat) + (gp.lon - lon)*(gp.lon - lon)));
    }
    bool operator==(const GeoPoint a) const{ return (a.lat == lat) && (a.lon == lon);}
    double lat;
    double lon;
};

struct City
{
    string name;
    long population;
    GeoPoint pos;
    
    City & operator=(const City &a){    //Sobrecargo operador para la igualacion
        this->name = a.name;
        this->population = a.population;
        this->pos = a.pos;
        return *this;
    }
    bool operator<(const City &a)const { return population < a.population; }  //Sobrecargo operador por mayor para que el sort ordene
};

typedef string Province;
typedef string Country;

typedef list<City> Cities;
typedef map<Province, Cities> Provinces;
typedef map<Country, Provinces> World;

typedef enum
{
    COUNTRY,
    COUNTRY_PROV,
    COUNTRY_PROV_CITY
} line_type_t;

class CosmopolitanHelper
{
public:
    // Construye una instancia de CosmopolitanHelper, cargando el World desde el archivo file
    CosmopolitanHelper(const string &file)
    { 
        ifstream f(file);
        string string_aux;
        Country country_aux;
        Province prov_aux;
        string city_aux, lat_aux, lon_aux, pop_aux;
        City city;
        line_type_t i;
        if (f.is_open())
        {
            while (getline(f, string_aux))
            {
                i = COUNTRY;
                stringstream stream_aux(string_aux);

                stream_aux >> country_aux;

                if (stream_aux >> prov_aux)
                {
                    i = COUNTRY_PROV;
                    if (stream_aux >> city_aux)
                    {
                        i = COUNTRY_PROV_CITY;
                        stream_aux >> lat_aux >> lon_aux >> pop_aux;
                        city.name = city_aux;
                        city.population = stoi(pop_aux);
                        city.pos = {stod(lat_aux), stod(lon_aux)};
                    }
                }

                auto country_it = myWorld.find(country_aux);
                if (country_it == myWorld.end()) // si no existe pais, lo creo
                {
                    // mapa vacío de provincias
                    country_it = myWorld.insert(make_pair(country_aux, Provinces())).first;
                }
                if (i == COUNTRY_PROV || i == COUNTRY_PROV_CITY)
                {
                    auto prov_it = (country_it->second).find(prov_aux);
                    if (prov_it == (country_it->second).end()) // si no existe provincia, la creo
                    {
                        // lista vacía de ciudades
                        prov_it = (country_it->second).insert(make_pair(prov_aux, Cities())).first;
                    }
                    if (i == COUNTRY_PROV_CITY)
                    {
                        prov_it->second.push_back(city);
                    }
                }
            }
            f.close();
            return;
        }
        throw runtime_error("CosmopolitanHelper(): no se pudo abrir archivo");
    }

    // Evaluar la necesidad de un destructor e implementarlo si hace falta
    //No necesito ningun delete ya que no pedi memoria dinamica
    ~CosmopolitanHelper()
    { 
        myWorld.clear();    //Lo unico que hago es borrar todos los elementos que tenia dentro del mapa
    }


    // devuelve una lista de todos los Countries visitados
    list<Country> getVisitedCountries(){
        list<Country> result;
        int i = 0;
        for(auto a: myWorld)
            result.push_back(a.first);

        return result;
    }

    // devuelve una lista de todas las Provinces visitadas. Si no se pasa argumentos, debe buscarse
    // sobre todo el World
    list<Province> getVisitedProvinces(Country country = "")
    {
        list<Province> result;
        if(country == ""){  //Si no me pasan ningun pais en particular, busco sobre todo mi mundo
            for(auto a: myWorld){   
                map<Province, Cities> p = a.second; //Busco en el mundo, el mapa de provincias y ciudades
                for(auto b : p)
                    result.push_back(b.first);  //Saco solo las provincias

            }
        }else{
            auto pos = myWorld.find(country);    //Sino, busco el pais en particular
            if(pos == myWorld.end())
            	return list<Province>(); //Si no estaba, retorno una lista vacia
            for(auto a: (*pos).second)    //Si estaba, saco las provincias del pais
                result.push_back(a.first); 
        }

        return result;
    }

    // devuelve una lista de todas las Cities visitadas.
    // Si no se pasa el argumento de Country, debe buscarse sobre todo el World.
    // Si no se pasa el argumento de Province, debe buscarse sobre todo el Country especificado.

    list<City> getVisitedCities(Country country = "", Province province = ""){
        list<City> result;

        if(country == "" && province == ""){    //Si no me pasan nada como argumento, busco sobre todo my mundo
            for(auto a: myWorld){
                map<Province, Cities> p = a.second; //Obtengo primero el mapa con las provincias
                for(auto b: p){
                    // result.splice(result.end(), b.second);  //VER SI ANDA< SINO SACAR SPLICE
                    list<City> p2 = b.second;
                    for(auto c: p2)
                        result.push_back(c);
                }
            }
        }
        else if(province == ""){    //Si le paso un country pero no una province
            auto pos_country = myWorld.find(country); //Busco el pais
            if(pos_country == myWorld.end())
            	return list<City>();    //Si no encontre, retorno lista vacia
            for(auto a: (*pos_country).second){     //Si encuentro
                for(auto b: a.second)       //Saco en cada una de las provicias
                    result.push_back(b);    //Las ciudades
            }
        }else if(country == ""){    //Si le paso una provinvia pero no un country
            for(auto a: myWorld){   //Busco en todo el mapa las pronvicias con ese nombre
                map<Province, Cities> p = a.second;
                auto pos_prov = p.find(province); //Busco la provincia
                if(pos_prov == p.end()) //Si no encontre, sigo al siguiente pais
                    continue;
                for(auto a: (*pos_prov).second) //Si encontre la provinvia, obtengo todas las ciudades
                    result.push_back(a);
                
            }
        }else{  //Si me pasaron los dos argumentos
            auto pos_country = myWorld.find(country);
            if(pos_country == myWorld.end())
                return list<City>();    //Si no encontre, retorno lista vacia
            map<Province, Cities> p = (*pos_country).second;    //Si encuentro, busco la provincia
            auto pos_province = p.find(province);  
            if(pos_province == p.end())
                return list<City>();    //Si no encontre, retorno lista vacia
            for(auto a: (*pos_province).second)
                result.push_back(a);

        }
        return result;
    }

    // devuelve una lista, ordenada decrecientemente por poblacion, de las 3 ciudades mas cercanas
    // al GeoPoint que se pasa por argumento
    list<City> get3ClosestCities(GeoPoint gp)
    {   
        list <City> result;
        list <City> cities;
        City city;  //Almaceno la ciudad con la localizacion requerida
        //Busco las 3 ciudades mas cercanas y las pongo en una lista
        for(auto a: myWorld){    //Extraigo la lista de ciudades
            map<Province, Cities> p = a.second;
            for(auto b: p){
                for(auto c: b.second){
                    if(c.pos == gp){    //Si coincide con las coordenadas
                        city = c;
                        continue; //Esta ciudad no la agrego
                    }
                    cities.push_back(c);    //Agrego las demas ciudades para comparar
                }
            }
        }
        //Busco las 3 ciudades mas cercanas al punto dado
        if(cities.size() > 3){  //Si tengo al menos 3 ciudades, busco las 3 mas cercanas
        	int i = 0;

            while(cities.size() > 0){
                City c = cities.back(); //Agarro el ultimo elemento
                cities.pop_back();  //Y lo elimino
                if(i > 2){  //Si ya elimine, empiezo a comparar
                    for(auto it = result.begin(); it != result.end(); i++){
                        if(c.pos.getDistance(gp) < (*it).pos.getDistance(gp)){ //Si el nuevo punto es menor
                            result.erase(it);       //Lo elimino
                            result.push_back(c);    //Asigno la nueva ciudad como mas ercana
                        }   
                        
                    }
                }else
                    result.push_back(c);
                
            }
        }else
            result = cities;    //Si no tenia al menos 3, mi resultado son todas las ciudades

        result.sort();      //Ordeno la lista con operador sobrecargado por menor
        result.reverse();   //La doy vuelta para que quede de mayor a menor

        return result;
        
    }

    void print()
    {
        list<Country> visited_countries = getVisitedCountries();
        for (Country c : visited_countries)
        {
            cout << "Country: " << c << endl;
            list<Province> visited_provinces = getVisitedProvinces(c);
            for (Province p : visited_provinces)
            {
                cout << "\t Province: " << p << endl;
                list<City> visited_cities = getVisitedCities(c, p);
                for (City city : visited_cities)
                {
                    cout << "\t\t City: " << city.name << endl;
                    cout << "\t\t\t Latitude: " << city.pos.lat << endl;
                    cout << "\t\t\t Longitude: " << city.pos.lon << endl;
                    cout << "\t\t\t Population: " << city.population << endl;
                }
            }
        }
    }

private:
    World myWorld;
};

int main()
{
    CosmopolitanHelper my_helper("data.txt");

    my_helper.print();
    

    GeoPoint gp = {-40.118631, -69.050284};
    list<City> closest_cities = my_helper.get3ClosestCities(gp);

    for (City c : closest_cities)
    {
        cout << "\t\t City: " << c.name << endl;
        cout << "\t\t\t Latitude: " << c.pos.lat << endl;
        cout << "\t\t\t Longitude: " << c.pos.lon << endl;
        cout << "\t\t\t Population: " << c.population << endl;
    }

    return 0;
}
