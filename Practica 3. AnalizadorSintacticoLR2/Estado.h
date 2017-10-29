#pragma once
#include "ElementoPila.h"
class Estado: public ElementoPila
{
public:
	string tipoElemento;
	int numeroEstado;
	Estado(string datoPila, int nestado);
	void MostrarEstado();
};

