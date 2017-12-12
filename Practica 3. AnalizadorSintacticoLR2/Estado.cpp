#include "Estado.h"

Estado::Estado(string datoPila, string nestado, string telemento)// es un desplazamiento?
{
	this->elementoPila = datoPila;
	this->tipoElemento = telemento;
	this->numeroEstado = nestado;
}

void Estado::MostrarEstado()
{
	cout <<" Estado: " << tipoElemento << " " << numeroEstado << endl;
}
