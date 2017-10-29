#include "ElementoPila.h"

ElementoPila::ElementoPila()
{
	this->elementoPila = "$";
	this->tipoElementoPila = 2;
}

ElementoPila::ElementoPila(string elemento, int tipo) {
	this->elementoPila = elemento;
	this->tipoElementoPila = tipo;
}

void ElementoPila::mostrarElemento()
{
	cout << elementoPila << endl;
}
