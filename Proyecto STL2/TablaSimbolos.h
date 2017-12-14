#include <iostream>
#include "Simbolo.h"
#include <vector>

#ifndef TABLASIMBOLOS
#define TABLASIMBOLOS

class TablaSimbolos
{
public:
    TablaSimbolos();
    void insert(Simbolo*);
    void muestra();
    bool buscarTablaSim(string);
    bool buscarTablaSim(string,string);
    Simbolo* buscarSimbolo(string,string);
    char dameTipo(string,string);
    string dameVariable(int);
    int dametamTabla();
};

#endif
