#ifndef CPP_COVID_METRICS_PRINT_INCIDENTS_H
#define CPP_COVID_METRICS_PRINT_INCIDENTS_H

#include <fstream>
#include "Provincia.h"
#include "Caso.h"
#include "print_incidents.h"
#include "utils.h"

void printIncidents(std::string filename, int limit, bool only_deceased) {
    std::string path = std::__fs::filesystem::current_path().parent_path().string() + '/' + filename;
    std::cout << "Current file path is: " <<  path << '\n';
    std::fstream fin;
    fin.open(path, std::ios::in);
    if (fin.fail()) {
        throw "Error!";
    }

    const std::string ListaProvincias[] = {"CABA", "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Córdoba", " Corrientes",
                                           "Entre Ríos", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                           "Neuquén", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                           "Santiago del Estero", "Tierra del Fuego", "Tucumán"};
    Provincia ProvinciasContagiado[24];
    Provincia ProvinciasFallecido[24];
    for (int i = 0; i < 24; i++) {
        ProvinciasContagiado[i] = Provincia(ListaProvincias[i], 0);
        ProvinciasFallecido[i] = Provincia(ListaProvincias[i], 0);
    }

    Caso casos;
    if (fin.fail()) {
        cout << "No se pudo abrir el csv" << endl;
    } else {
        std::string line;
        getline(fin, line);
        while (getline(fin, line)) {
            casos.ProcesarDato(line);
            if (!only_deceased) {
                if (casos.clasificacion() == "Confirmado") {
                    for (int k = 0; k < 24; k++) {
                        if (casos.provincia() == ProvinciasContagiado[k].getNombre()) {
                            ProvinciasContagiado[k].IncrementarContador();
                            break;
                        }
                    }
                }
            } else {
                if (casos.fallecido() == "SI") {
                    casos.ProcesarDato(line);
                    for (int k = 0; k < 24; k++) {
                        if (casos.provincia() == ProvinciasFallecido[k].getNombre()) {
                            ProvinciasFallecido[k].IncrementarContador();
                            break;
                        }
                    }
                }
            }
        }
        if (!only_deceased) {
            QuickSortProvincia(ProvinciasContagiado, 0, 23);
            cout << "Caso confirmados por provincias: " << endl;
            for (int i = 0; i < limit; i++) {
                cout << ProvinciasContagiado[i] << endl;
            }
        } else {
            QuickSortProvincia(ProvinciasFallecido, 0, 23);
            cout << "Caso fallecidos por Provincia: " << endl;
            for (int i = 0; i < limit; i++) {
                cout << ProvinciasFallecido[i] << endl;
            }
        }
    }
}

#endif //CPP_COVID_METRICS_PRINT_INCIDENTS_H
