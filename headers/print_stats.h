#ifndef CPP_COVID_METRICS_PRINT_STATS_H
#define CPP_COVID_METRICS_PRINT_STATS_H

#include <iostream>
#include <fstream>
#include <ios>
#include "Casos.h"
#include "print_stats.h"

void printStats(std::string filename) {
    std::string root_folder = std::__fs::filesystem::current_path().parent_path().string();
    std::string path = root_folder + '/' + filename;
    std::cout << "Current file path is: " <<  path << '\n';
    std::ifstream fin;
    fin.open(path, std::ios::in);
    if (fin.fail()) {
        throw "Error!";
    }

    float contagion = 0, deceased = 0, num_cases = 0;
    int confirmedByAge[10];
    int deceasedByAge[10];
    for (int k = 0; k < 10; k++) { // Inicializo las listas por edad en 0
        confirmedByAge[k] = 0;
        deceasedByAge[k] = 0;
    }

    std::string line;
    std::getline(fin, line); // Saltear el header
    while (fin.good()) {
        std::getline(fin, line);

        Casos casos;
        casos.ProcesarDato(line);

        num_cases++;

        if (casos.clasificacion() == "Confirmado") {
            contagion++;
            if (casos.Anios_Meses() == "Meses") {
                confirmedByAge[0]++;
            } else {
                confirmedByAge[casos.edad() / 10]++;
            }
        } else {
            if (casos.fallecido() == "SI") {
                deceased++;
                if (casos.Anios_Meses() == "Meses") {
                    deceasedByAge[0]++;
                } else {
                    deceasedByAge[casos.edad() / 10]++;
                }
            }
        }
    }

    // Resultado
    std::cout << "Cantidad total de muestras: " << num_cases << std::endl;
    std::cout << "Cantidad total de infectados: " << contagion << std::endl;
    std::cout << "Cantidad de fallecidos: " << deceased << std::endl;
    std::cout << "Porcentaje de infectados por muestra: " << ((contagion / num_cases) * 100) << "%" << std::endl;
    std::cout << "Porcentaje de fallecidos por infectados: " << ((deceased / contagion) * 100) << "%" << std::endl;
    std::cout << "La cantidad de infectados:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "-> entre " << i * 10 << " y " << (i * 10) + 9 << " años es: " << confirmedByAge[i] << std::endl;
    }
    std::cout << "La cantidad de fallecidos:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "-> entre " << i * 10 << " y " << (i * 10) + 9 << " años es: " << deceasedByAge[i] << std::endl;
    }
}

#endif //CPP_COVID_METRICS_PRINT_STATS_H
