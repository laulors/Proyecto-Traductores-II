#include "Terminal.h"

Terminal::Terminal(string datoPila)
{
	this->elementoPila = datoPila;
	this->tipoElemento = "Terminal";
}

void Terminal::mostrarInfoTerminal()
{
	cout << elementoPila << endl;
}
