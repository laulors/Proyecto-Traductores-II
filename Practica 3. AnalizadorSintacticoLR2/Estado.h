#pragma once
#include "pila.h"

class Estado: public ElementoPila
{
public:
	string tipoElemento;
	string numeroEstado;
	Estado(string datoPila, string nestado, string telemento);
	void MostrarEstado();
};