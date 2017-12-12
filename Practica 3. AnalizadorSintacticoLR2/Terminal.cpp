#include "Terminal.h"

Terminal::Terminal(string datoPila)// es el de aceptacion
{
	this->elementoPila = datoPila;
	this->tipoElemento = "Terminal. ";
}

void Terminal::mostrarInfoTerminal()
{
	cout <<tipoElemento<< elementoPila << endl;
}
