#ifndef CPP_COVID_METRICS_PRINT_INCIDENTS_PER_AGE_H
#define CPP_COVID_METRICS_PRINT_INCIDENTS_PER_AGE_H

#include "HashMap.h"
#include "Casos.h"

const std::string ListaProvincias[] = {"Buenos Aires", "CABA", "Catamarca", "Chaco", "Chubut", "Córdoba", "Corrientes",
                                  "Entre Ríos", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                  "Neuquén", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                  "Santiago del Estero", "Tierra del Fuego", "Tucumán", "Sin Provincia"};

unsigned int miHF(std::string provincia) {
    for (int i = 0; i < 25; i++) {
        if (provincia == ListaProvincias[i]) {
            return i;
        }
    }
}

void printIncidentsPerAge(std::string filename, int age) {
    if (age == 0) throw "Error!";

    std::string root_folder = std::__fs::filesystem::current_path().parent_path().string();
    std::string path = root_folder + '/' + filename;
    std::cout << "Current file path is: " <<  path << '\n';
    std::ifstream fin;
    fin.open(path, std::ios::in);
    if (fin.fail()) {
        throw "Error!";
    }

    HashMap<std::string, Casos> HashCasos(25, miHF);
    HashEntry<std::string, Casos> *aux;
    Casos caso;

    std::string line;
    std::getline(fin, line);
    while (fin.good()) {
        std::getline(fin, line);
        caso.ProcesarDato(line);
        if (caso.Anios_Meses() == "Años" && caso.edad() == age && caso.clasificacion() == "Confirmado") {
            HashCasos.put(caso.provincia(), caso);
        }
    }

    for (int i = 0; i < 25; i++) {
        try {
            aux = HashCasos.get(ListaProvincias[i]);
            cout << "La lista de la provincia: " << ListaProvincias[i] << endl;
            while (aux != nullptr) {
                cout << aux->getData() << endl;
                aux = aux->getnext();
            }
        } catch ( ... ) {
            cout << "La Provincia: " << ListaProvincias[i] << " esta vacia" << endl;
        }
    }
}

#endif //CPP_COVID_METRICS_PRINT_INCIDENTS_PER_AGE_H
