#ifndef TRABAJOFINAL_PROVINCIAS_H
#define TRABAJOFINAL_PROVINCIAS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Caso.h"
#include "Lista.h"

using namespace std;

class Provincia {
private:
    string nombre;
    int contador;
    Lista<Caso> casos;
public:
    Provincia(){
        nombre="N/A";
        contador=0;
    }

    Provincia(const string &nombre, int cont) : nombre(nombre) {
        contador=cont;
    }

    const string &getNombre() const {
        return nombre;
    }

    void print() {
        casos.print();
    }

    void setNombre(const string &nombre) {
        Provincia::nombre = nombre;
    }

    void IncrementarContador(){
        contador++;
    }

    void insertarCaso(Caso caso) {
        casos.insertarPrimero(caso);
    }

    void limpiar() {
        nombre = "";
        contador = 0;
        casos.vaciar();
    }


    bool operator==(const Provincia &rhs) const {
        return nombre == rhs.nombre ;
    }

    bool operator!=(const Provincia &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Provincia &rhs) const {
        return contador < rhs.contador;
    }

    bool operator>(const Provincia &rhs) const {
        return contador > rhs.contador;
    }

    bool operator<=(const Provincia &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Provincia &rhs) const {
        return !(*this < rhs);
    }

    friend ostream &operator<<(ostream &os, const Provincia &provincia) {
        os << "Provincia: " << provincia.nombre << "-> Numero de ocurrencias: " << provincia.contador;
        return os;
    }
};

#endif //TRABAJOFINAL_PROVINCIAS_H
