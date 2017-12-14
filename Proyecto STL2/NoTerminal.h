#include "pila.h"
#ifndef NOTERMINAL_H_INCLUDED
#define NOTERMINAL_H_INCLUDED

class NoTerminal: public ElementoPila
{
protected:
    string noTerminal;
    Nodo* nodo;
public:
    NoTerminal(string noTerminal, Nodo* nuevoNodo);
    string getNoTerminal();
    Nodo* getNodo();
    void muestra();
};

#endif // NOTERMINAL_H_INCLUDED
