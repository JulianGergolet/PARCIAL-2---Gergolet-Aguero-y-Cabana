#include <iostream>
#include "headers/print_stats.h"
#include "headers/print_incidents.h"
#include "headers/print_incidents_per_age.h"
#include "headers/print_incidents_cui.h"

int main(int argc, char **argv) {
    auto inicio = std::chrono::high_resolution_clock::now();

    // Obtenemos el path del archivo CSV para abrirlo
    std::string filename = "";
    if (argc > 1) {
        filename = argv[argc-1];
    }

    if (filename.empty()) { // Si el path no existe
        std::cout << "Ningun archivo fue proporcionado. Por favor especifique el nombre del Archivo al time_2." << std::endl;
        std::cout << "Ejemplo: ./cpp-covid-metrics.exe CovidFile.csv" << std::endl;
        std::cout << "Ejemplo: ./cpp-covid-metrics -argumento_ejemplo CovidFile.csv" << std::endl;
        return 0;
    }

    int i = 1;
    if (strcmp(argv[i], "-estad") == 0) { // Comparar dos cadenas de caracteres strcmp()
        try {
            printStats(filename);
        } catch ( ... ) {
            std::cout << "Error -estad: No se pudo cargar la informacion." << std::endl;
        }
    } else if (strcmp(argv[i],"-p_casos") == 0 || strcmp(argv[i],"-p_muertes") == 0) {
        int total;
        bool only_deceased = strcmp(argv[i],"-p_muertes") == 0;
        try {
            total = std::stoi(argv[i + 1]);
            printIncidents(filename, total, only_deceased);
        } catch ( ... ) {
            try {
                total = 24;
                printIncidents(filename, total, only_deceased);
            } catch ( ... ) {
                std::cout << "Error -p_casos: No se pudo cargar la informacion." << std::endl;
            }
        }
    } else if (strcmp(argv[i],"-casos_edad") == 0) {
        try {
            int edad = std::stoi(argv[i + 1]);
            printIncidentsPerAge(filename, edad);
        } catch ( ... ) {
            std::cout << "Error -casos_edad: No se pudo cargar la informacion." << std::endl;
        }
    } else if (strcmp(argv[i],"-casos_cui") == 0) {
        string fecha = "2019-09-01";
        if (argv[i + 1][0] == '2') {
            fecha = argv[i + 1];
            i++;
        }
        printIncidentsCui(filename, fecha);
    }

    auto final = std::chrono::high_resolution_clock::now();
    auto milli = duration_cast<std::chrono::milliseconds>(final - inicio);
    cout<<"Tiempo de ejecucion: "<< ((float)milli.count()/1000) << " segundos." << std::endl;
    cout<<"Tiempo de ejecucion: "<< ((float)milli.count()) << " milisegundos." << std::endl;
    return 0;
}
