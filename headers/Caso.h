#ifndef CPP_COVID_METRICS_CASO_H
#define CPP_COVID_METRICS_CASO_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Caso {
private:
    int Id_Casos;
    int Edad;
    string AniosOMeses;
    string CUI;
    string FechaCUI;
    string Fallecio;
    int IdProvincia;
    string Provincia;
    string Clasificacion;

public:
    friend ostream &operator<<(ostream &os, const Caso &casos);

    Caso();

    Caso(string line);

    void ProcesarDato(string line);

    int edad();

    string Anios_Meses();

    string Cui();

    string Fecha_CUI();

    string fallecido();

    int Provincia_Id();

    string provincia();

    string clasificacion();

    bool operator<(const Caso &rhs) const;

    bool operator>(const Caso &rhs) const;

    bool operator<=(const Caso &rhs) const;

    bool operator>=(const Caso &rhs) const;
};

Caso::Caso() {
    Id_Casos = 0;
    Edad = 0;
    AniosOMeses = "Anios";
    CUI = "NO";
    FechaCUI = "2000-01-01";
    Fallecio = "NO";
    IdProvincia = 0;
    Provincia = "SinEspecif";
    Clasificacion = "N/A";
}

Caso::Caso(string line) {
    ProcesarDato(line);
}

void Caso::ProcesarDato(string line) {
    stringstream s(line);
    string word;
    for (int columnas = 0; getline(s, word, ','); columnas++) {
        if (word.size() <= 0) {
            if(columnas==7) {
                word="SinProvincia";
            }
            if (columnas == 2 || columnas == 0 || columnas == 17) {
                word = "404";
            } else {
                word = "NA";
            }
        } else {
            word = word.substr(1, word.size() - 2);
        }
        switch (columnas) {
            case 0: // ID
                Id_Casos = (stoi(word));
                break;
            case 2: // Edad
                Edad = (stoi(word));
                break;
            case 3: // AnioOMes
                AniosOMeses = (word);
                break;
            case 7:
                Provincia = (word);
                break;
            case 12: //CUI
                CUI = (word);
                break;
            case 13: // FECHACUI
                FechaCUI = (word);
                break;
            case 14: // FALLECIDO
                Fallecio = (word);
                break;
            case 17: // PROVINCIA ID
                IdProvincia = (stoi(word));
                break;
            case 20: //CLASIFICACION
                Clasificacion = (word);
                break;
            default:
                break;
        }
    }
}

int Caso::edad() {
    return Edad;
}

string Caso::Anios_Meses() {
    return AniosOMeses;
}

string Caso::Cui() {
    return CUI;
}

string Caso::Fecha_CUI() {
    return FechaCUI;
}

string Caso::fallecido() {
    return Fallecio;
}

int Caso::Provincia_Id() {
    return Provincia_Id();
}

string Caso::clasificacion() {
    return Clasificacion;
}

ostream &operator<<(ostream &os, const Caso &casos) {
    os << "Id_Casos:" << casos.Id_Casos << " Edad:" << casos.Edad << " Anios/Meses:" << casos.AniosOMeses << " CUI:"
       << casos.CUI << " FechaCUI:" << casos.FechaCUI << " Fallecio:" << casos.Fallecio << " IdProvincia:"
       << casos.IdProvincia<< " Provincia:"
       << casos.Provincia << " Clasificacion:" << casos.Clasificacion;
    return os;
}

string Caso::provincia() {
    return Provincia;
}

bool Caso::operator<(const Caso &rhs) const {
    return FechaCUI < rhs.FechaCUI;
}

bool Caso::operator>(const Caso &rhs) const {
    return FechaCUI > rhs.FechaCUI;
}

bool Caso::operator<=(const Caso &rhs) const {
    return !(rhs < *this);
}

bool Caso::operator>=(const Caso &rhs) const {
    return !(*this < rhs);
}


#endif //CPP_COVID_METRICS_CASO_H
