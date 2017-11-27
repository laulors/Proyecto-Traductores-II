#ifndef _ELEMENTOPILA
#define _ELEMENTOPILA

#include <iostream>
#include <string>

using namespace std;

class ElementoPila
{
public:
	string elementoPila;
	int tipoElementoPila;
	ElementoPila();
	ElementoPila(string elemento, int tipo);
	void mostrarElemento();
};

#endif