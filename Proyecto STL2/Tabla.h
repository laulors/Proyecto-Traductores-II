#ifndef TABLA
#define TABLA

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctype.h>

using namespace std;

class Tabla
{
public:
    int filas;
    int columnas;
    int cantReglas;

    vector<int> idReglas;
    vector<int> lonReglas;
    vector<string> noTerminales;
    vector<vector<int>> matriz;

    vector<int> reglas;
    vector<string> noTerminalesAux;
    vector<int> matrizNumeros;

    Tabla();
    void leerArchivo(char*);
    void acomodarValores();
    void mostrarMatriz();
    void mostrarIdReglas();
    void mostrarLonReglas();
    void mostrarNoTerminales();
};

#endif
