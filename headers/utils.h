#ifndef CPP_COVID_METRICS_UTILS_H
#define CPP_COVID_METRICS_UTILS_H

#include "Provincia.h"
#include "Caso.h"
#include "utils.h"

void QuickSortProvincia(Provincia a[], int primero, int ultimo) {
    int i, j, central;
    Provincia pivote, aux;
    central = (primero + ultimo) / 2;
    pivote = a[central];
    i = primero;
    j = ultimo;
    do {
        while (a[i] > pivote) i++;
        while (a[j] < pivote) j--;
        if (i <= j) {
            aux = a[i];
            a[i] = a[j];
            a[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
    if (primero < j) QuickSortProvincia(a, primero, j); // mismo proceso con sublista izqda
    if (i < ultimo) QuickSortProvincia(a, i, ultimo); // mismo proceso con sublista drcha
}

void QuickSortCasos(Caso a[], int primero, int ultimo) {
    int i, j, central;
    Caso pivote, aux;
    central = (primero + ultimo) / 2;
    pivote = a[central];
    i = primero;
    j = ultimo;
    do {
        while (a[i] < pivote) i++;
        while (a[j] > pivote) j--;
        if (i <= j) {
            aux = a[i];
            a[i] = a[j];
            a[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
    if (primero < j)
        QuickSortCasos(a, primero, j); // mismo proceso con sublista izqda
    if (i < ultimo)
        QuickSortCasos(a, i, ultimo); // mismo proceso con sublista drcha
}



#endif //CPP_COVID_METRICS_UTILS_H
