#include <string>
#include <string.h>
#include <iostream>
using namespace std;

#ifndef SIMBOLO
#define SIMBOLO

class Simbolo
{
protected:
    char tipo;
    string simbolo;
    string ambito;
    char param;
    char vectorParametro[20];
    bool funcion;
public:
    Simbolo(char, string, string,bool);
    Simbolo(char, string, string,char*,bool);
    void muestra();
    char getTipo();
    string getSimbolo();
    string getAmbito();
    int getNumParam();
    char getVectorParametro(int);
    bool getFuncion();

};

#endif
