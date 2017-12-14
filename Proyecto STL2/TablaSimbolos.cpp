#include "tablaSimbolos.h"
vector<Simbolo*> vectorSimbolos;

TablaSimbolos::TablaSimbolos()
{
}

void TablaSimbolos::insert(Simbolo *s)
{
    vectorSimbolos.push_back(s);
}

void TablaSimbolos::muestra()
{
    cout << endl<<"***************" << endl;
    for (int i = 0; i < vectorSimbolos.size(); i++)
    {
        vectorSimbolos[i]->muestra();
    }
    cout << endl;
}

bool TablaSimbolos::buscarTablaSim(string id)
{
    for (int i = 0; i < vectorSimbolos.size(); i++)
    {
        if(vectorSimbolos[i]->getSimbolo() == id)
        {
            return true;
        }
    }
    return false;
}

bool TablaSimbolos::buscarTablaSim(string id, string ambito)
{
    bool bandera = false;
    for (int i = 0; i < vectorSimbolos.size(); i++)
    {
        if(vectorSimbolos[i]->getSimbolo() == id && vectorSimbolos[i]->getAmbito() == ambito)
            bandera = true;
    }
    return bandera;
}

Simbolo* TablaSimbolos::buscarSimbolo(string id,string ambito)
{
    for (int i = 0; i < vectorSimbolos.size(); i++)
    {
        if(vectorSimbolos[i]->getSimbolo() == id)
        {
            return vectorSimbolos[i];
        }
    }
    return NULL;
}

char TablaSimbolos::dameTipo(string id, string ambito)
{
    for (int i = 0; i < vectorSimbolos.size(); i++)
    {
        if(vectorSimbolos[i]->getSimbolo() == id && vectorSimbolos[i]->getAmbito() == ambito)
            return vectorSimbolos[i]->getTipo();
    }
    return '@';
}

int TablaSimbolos::dametamTabla()
{
    return vectorSimbolos.size();
}

string TablaSimbolos::dameVariable(int indice)
{
    return vectorSimbolos[indice]->getSimbolo();
}
