#include "Simbolo.h"

Simbolo::Simbolo(char tipo, string simbolo, string ambito, bool funcion)
{
    this->tipo=tipo;
    this->simbolo=simbolo;
    this->ambito=ambito;
    this->funcion=funcion;
}

Simbolo::Simbolo(char tipo, string simbolo, string ambito, char* vectorParametro, bool funcion)
{
    this->tipo=tipo;
    this->simbolo=simbolo;
    this->ambito=ambito;
    for (int i = 0; i < sizeof(vectorParametro); i++)
    {
        this->vectorParametro[i]=vectorParametro[i];
    }

    this->funcion = funcion;
}


void Simbolo::muestra()
{
    cout << tipo << " <--> " << simbolo << " <--> " << ambito << endl;
    cout << "***************************************" << endl;
}

char Simbolo::getTipo()
{
    return tipo;
}

string Simbolo::getSimbolo()
{
    return simbolo;
}

string Simbolo::getAmbito()
{
    return ambito;
}

int Simbolo::getNumParam()
{
    int i;
    for (i = 0; i < sizeof(vectorParametro) ; i++)
    {
        if (vectorParametro[i]==0)
            return i;
    }
    return i;
}

bool Simbolo::getFuncion()
{
    return funcion;
}

char Simbolo::getVectorParametro(int i)
{
    return vectorParametro[i];
}

