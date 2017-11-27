#include "NoTerminal.h"

NoTerminal::NoTerminal(string datoPila)//es una reduccion
{
	this->elementoPila = datoPila;
	this->tipoElemento = "No Terminal. ";
}

void NoTerminal::mostrarInfoNoTerminal() {
	cout <<tipoElemento<< elementoPila << endl;
}