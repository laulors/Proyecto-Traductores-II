#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include "lexico.h"
#include "pila.h"
#include "Estado.h"
#include "Terminal.h"
#include "NoTerminal.h"

using namespace std;
//ORDENAR Ctrl A, Ctrl K, Ctrl F
int rectificarTipo(int tipodato)
{
	switch (tipodato) {
	case 0://id
		tipodato = 0;
		break;
	case 23://$ fin 
		tipodato = 2;
		break;
	case 5: //+
		tipodato = 1;
		break;
	}
	return tipodato;

}
string intToString(int datoConvertir) {
	stringstream ss;
	ss << datoConvertir;
	string cadena = ss.str();
	return cadena;
}
string queAccion(int accion) {
	if (accion == -1)
		return "aceptacion";
	else if (accion > 0)
		return "transicion";
	else if (accion < -1)
		return "desplazamiento";
}
int main(int argc, char *argv[]) {

	int tablaLR[5][4] = {
		2,0,0,1,
		0,0,-1,0,
		0,3,-3,0,
		2,0,0,4,
		0,0,-2,0
	};
	/*
	  identificador = 0
	  suma = 1
	  pesitos = 2

	  terminal NO PRODUCEN COSAS
	  No terminal PRODUCEN COSAS
	  estado DESPLAZAMIENTO-CABEZA PILA
	*/
	Pila pila;
	int fila, columna, accion, posicion;
	int idReglas[2] = { 3,3 };
	int lonReglas[2] = { 3,1 };
	int terminales[4] = { 0,1,2,3 };
	bool aceptacion = false;

	string cadena = "";
	Lexico lexico("a+b+c$");
	ElementoPila *elementopila;
	Estado *estado;
	NoTerminal *nt;
	Terminal *t;


	elementopila = new ElementoPila();//inicializo pila
	pila.push(elementopila);
	elementopila = new ElementoPila("0", 0);//tipo id
	pila.push(elementopila);
	nt = new NoTerminal(elementopila->elementoPila);

	lexico.sigSimbolo(); //busca sig simbolo a leer por el momento el primero

	fila = pila.top()->tipoElementoPila;
	columna = rectificarTipo(lexico.tipo);
	cout << "Entrada: " << lexico.simbolo << endl;
	cout << "[" << fila << "] [" << columna << "]" << endl;
	accion = tablaLR[fila][columna];
	cadena = intToString(accion);
	nt->mostrarInfoNoTerminal();
	estado = new Estado(pila.top()->elementoPila, cadena, queAccion(accion));
	estado->MostrarEstado();
	pila.muestra();

	while (!aceptacion) {
		if (accion == -1) {//en caso de aceptacion
			cout << " Aceptada " << endl;
			nt->mostrarInfoNoTerminal();
			aceptacion = true;
			break;
		}
		if (accion > 0) {
			elementopila = new ElementoPila(lexico.simbolo, lexico.tipo);
			pila.push(elementopila);
			t = new Terminal(lexico.simbolo);
			elementopila = new ElementoPila(cadena, 0);
			pila.push(elementopila);
			if (lexico.simbolo.compare("$") != 0)
				lexico.sigSimbolo();
			fila = accion;//ultima accion hasta el momento
			columna = rectificarTipo(lexico.tipo);
			cout << "Entrada: " << lexico.simbolo << endl;
			t->mostrarInfoTerminal();
			cout << "[" << fila << "] [" << columna << "]" << endl;
			accion = tablaLR[fila][columna];
			cadena = intToString(accion);
			estado = new Estado(pila.top()->elementoPila, cadena, queAccion(accion));
			estado->MostrarEstado();
		}
		else if (accion < -1) {//si se necesita hacer un desplazamiento

			if (accion == -2)
				posicion = 0;
			else if (accion == -3)
				posicion = 1;

			for (int i = 0; i < lonReglas[posicion] * 2; i++)
			{
				pila.pop();
			}

			fila = std::stoi(pila.top()->elementoPila);
			columna = idReglas[posicion];
			cout << "Entrada: " << lexico.simbolo << endl;
			cout << "[" << fila << "] [" << columna << "]" << endl;
			accion = tablaLR[fila][columna];
			cadena = intToString(accion);
			estado = new Estado(pila.top()->elementoPila, cadena, queAccion(accion));
			estado->MostrarEstado();
			pila.muestra();

			if (accion == 1) {

				elementopila = new ElementoPila();
				elementopila->elementoPila = "E";
				nt = new NoTerminal(elementopila->elementoPila);
				pila.push(elementopila);

				elementopila = new ElementoPila(cadena, 0);
				pila.push(elementopila);
			}
			else {
				elementopila = new ElementoPila();
				elementopila->elementoPila = intToString(terminales[columna]);
				t->elementoPila = elementopila->elementoPila;
				pila.push(elementopila);
				elementopila = new ElementoPila(cadena, 0);
				pila.push(elementopila);
			}

			if (lexico.simbolo.compare("$") != 0)
				lexico.sigSimbolo();
			fila = std::stoi(pila.top()->elementoPila);
			columna = rectificarTipo(lexico.tipo);
			cout << "Entrada: " << lexico.simbolo << endl;
			t->mostrarInfoTerminal();
			cout << "[" << fila << "] [" << columna << "]" << endl;
			accion = tablaLR[fila][columna];
			cadena = intToString(accion);
			estado = new Estado(pila.top()->elementoPila, cadena, queAccion(accion));
			estado->MostrarEstado();
		}
		else
		{
			break;// En caso de error
			estado = new Estado(pila.top()->elementoPila, cadena, "ERROR");
			estado->MostrarEstado();
		}
		pila.muestra();
	}

	cin.get();
	return 0;
}
