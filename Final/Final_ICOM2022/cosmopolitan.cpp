#include <iostream>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct GeoPoint
{
    // obtiene la distancia a otro GeoPoint. Suponga que la tierra es plana (?), es decir, que
    // las latitudes toman valores entre -90 y 90
    // las longitudes toman valores entre -180 y 180
    double getDistance(GeoPoint gp)
    { // TODO
    }
    double lat;
    double lon;
};

struct City
{
    string name;
    long population;
    GeoPoint pos;
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
    ~CosmopolitanHelper()
    { // TODO
    }

    // devuelve una lista de todos los Countries visitados
    list<Country> getVisitedCountries()
    { // TODO
    }

    // devuelve una lista de todas las Provinces visitadas. Si no se pasa argumentos, debe buscarse
    // sobre todo el World
    list<Province> getVisitedProvinces(Country country = "")
    { // TODO
    }

    // devuelve una lista de todas las Cities visitadas.
    // Si no se pasa el argumento de Country, debe buscarse sobre todo el World.
    // Si no se pasa el argumento de Province, debe buscarse sobre todo el Country especificado.
    list<City> getVisitedCities(Country country = "", Province province = "")
    { // TODO
    }

    // devuelve una lista, ordenada decrecientemente por poblacion, de las 3 ciudades mas cercanas
    // al GeoPoint que se pasa por argumento
    list<City> get3ClosestCities(GeoPoint gp)
    { // TODO
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
    cout << "Closest cities to point (" << gp.lat << " , " << gp.lon << "): " << endl;
    for (City c : closest_cities)
    {
        cout << "\t\t City: " << c.name << endl;
        cout << "\t\t\t Latitude: " << c.pos.lat << endl;
        cout << "\t\t\t Longitude: " << c.pos.lon << endl;
        cout << "\t\t\t Population: " << c.population << endl;
    }

    return 0;
}
