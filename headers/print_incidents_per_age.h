#ifndef CPP_COVID_METRICS_PRINT_INCIDENTS_PER_AGE_H
#define CPP_COVID_METRICS_PRINT_INCIDENTS_PER_AGE_H

#include "Caso.h"
#include "Lista.h"
#include <unordered_map>
#include <vector>

const int PROVINCIAS = 25;
const std::string listaProvincias[PROVINCIAS] = {"Buenos Aires", "CABA", "Catamarca", "Chaco", "Chubut", "Córdoba", "Corrientes",
                                  "Entre Ríos", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                  "Neuquén", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                  "Santiago del Estero", "Tierra del Fuego", "Tucumán", "Sin Provincia"};

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

    std::unordered_map<std::string, vector<Caso>> HashCasos;
    Caso caso;
    int counter = 1;

    std::string line;
    std::getline(fin, line);
    while (fin.good()) {
        std::getline(fin, line);
        caso.ProcesarDato(line);
        if (caso.Anios_Meses() == "Años" && caso.edad() == age && caso.clasificacion() == "Confirmado") {
            if (HashCasos.find(caso.provincia()) == HashCasos.end()) {
                vector<Caso> list;
                list.push_back(caso);
                HashCasos[caso.provincia()] = list;
            } else {
                HashCasos.at(caso.provincia()).push_back(caso);
            }
            counter++;
        }
    }

    for (int i = 0; i < PROVINCIAS; i++) {
        if (HashCasos.find(listaProvincias[i]) != HashCasos.end()) {
            vector<Caso> vector = HashCasos[listaProvincias[i]];
            cout << "===============================================" << endl;
            cout << "La lista de la provincia: " << listaProvincias[i] << ", casos: " << vector.size() << endl;
            for (auto & provincia : vector) {
                std::cout << provincia << std::endl;
            }
            cout << endl;
        }
    }
}

#endif //CPP_COVID_METRICS_PRINT_INCIDENTS_PER_AGE_H
