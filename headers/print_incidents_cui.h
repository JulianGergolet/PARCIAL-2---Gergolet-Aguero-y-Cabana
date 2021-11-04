#ifndef CPP_COVID_METRICS_PRINT_INCIDENTS_CUI_H
#define CPP_COVID_METRICS_PRINT_INCIDENTS_CUI_H

#include "Casos.h"
#include "Lista.h"
#include "utils.h"

void printIncidentsCui(string filename, string fecha) {
    std::string path = std::__fs::filesystem::current_path().parent_path().string() + '/' + filename;
    std::cout << "Current file path is: " <<  path << '\n';
    std::fstream fin;
    fin.open(path, std::ios::in);
    if (fin.fail()) {
        throw "Error!";
    }

    Lista<Casos> ListaCUI;
    Casos caso;

    std::string line;
    std::getline(fin, line);
    while (fin.good()) {
        std::getline(fin, line);
        caso.ProcesarDato(line);
        std::string cui = caso.Cui();
        std::string fecha_cui = caso.Fecha_CUI();

        // cui es un <string>, cui.c_str() es un char*
        // fecha_cui > fecha pasada por parametro
        bool is_caso_cui = ((int)strcmp(cui.c_str(), "SI")) == 0 && ((int)strcmp(fecha_cui.c_str(), fecha.c_str()) > 0);
        if (is_caso_cui) {
            ListaCUI.insertarPrimero(caso);
        }
    }

    if (ListaCUI.getTamanio() < 1) { // revisa si hay casos
        cout << "No existen caso mayores a " << fecha << ". Intente otra fecha." << endl;
        return;
    }

    Casos casos[ListaCUI.getTamanio()]; // [1...]
    for (int i = 0; i < ListaCUI.getTamanio(); i++) {
        casos[i] = ListaCUI.getDato(i);
    }


    QuickSortCasos(casos, 0, ListaCUI.getTamanio());
    cout << "Casos mayores a fecha " << fecha << " en orden:" << endl;
    for (int i = 0; i < ListaCUI.getTamanio(); i++) {
        if (casos[i] > fecha) {
            cout << casos[i] << endl;
        }
    }
}

#endif //CPP_COVID_METRICS_PRINT_INCIDENTS_CUI_H
