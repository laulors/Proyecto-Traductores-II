#include "Estado.h"

Estado::Estado(string datoPila, int nestado)
{
	this->elementoPila = datoPila;
	this->tipoElemento = "Estado. ";
	this->numeroEstado = nestado;
}

void Estado::MostrarEstado()
{
	cout << elementoPila << endl;
	cout << tipoElemento << endl;
}
