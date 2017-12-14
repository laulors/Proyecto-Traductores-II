#include "pila.h"
#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

class Terminal: public ElementoPila
{
protected:
    string terminal;
public:
    Terminal(string terminal);

    string getTerminal();

    void muestra();
};


#endif // TERMINAL_H_INCLUDED
