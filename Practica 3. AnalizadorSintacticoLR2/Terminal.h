#pragma once
#include "ElementoPila.h"

class Terminal: public ElementoPila
{
public:
	string tipoElemento;
	int numeroTerminal;
	Terminal(string datoPila);
	void mostrarInfoTerminal();
};

