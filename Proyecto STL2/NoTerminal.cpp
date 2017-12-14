#include "NoTerminal.h"

NoTerminal::NoTerminal(string noTerminal, Nodo* nuevoNodo)
{
    this->noTerminal= noTerminal;
    this->nodo = nuevoNodo;
}

string NoTerminal::getNoTerminal()
{
    return this->noTerminal;
}

Nodo* NoTerminal::getNodo()
{
    return this->nodo;
}

void NoTerminal::muestra()
{
    cout << noTerminal << " ";
}
