#pragma once
#include "ElementoPila.h"

class Terminal: public ElementoPila
{
protected:
	string tipoElemento;
	int numeroTerminal;
	Terminal(string datoPila);
	void mostrarInfoTerminal();
};

