#include <cstdlib>
#include <iostream>
#include <string>

#include "lexico.h"
#include "pila.h"

using namespace std;

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
	*/
	Pila pila;
	int fila, columna, accion, posicion;
	int idReglas[2] = { 3,3 };
	int lonReglas[2] = { 3,1 };
	int terminales[4] = { 0,1,2,3 };
	bool aceptacion = false;


	Lexico lexico("a+b+c+$");

	//inicializa la pila
	pila.push(lexico.PESOS);
	pila.push(0);
	lexico.sigSimbolo();//busca el siguiente simbolo a leer Por el momento el primero

	fila = pila.top();
	columna = rectificarTipo(lexico.tipo);
	cout <<"[" <<fila <<"] [" << columna <<"]"<< endl;
	accion = tablaLR[fila][columna];
	pila.muestra();
	cout << "Entrada: "<<lexico.simbolo<<endl;
	cout << "Salida: " << accion << endl;

	while (!aceptacion) {
		if (accion == -1) {//en caso de aceptacion
			cout << "Entrada Aceptada" << endl;
			aceptacion = true;
			break;
		}

		if (accion > 0) {// si se necesita hacer una transicion

			pila.push(rectificarTipo(lexico.tipo));
			pila.push(accion);
			if (lexico.simbolo.compare("$") != 0)
				lexico.sigSimbolo();
			fila = pila.top();
			columna = rectificarTipo(lexico.tipo);
			cout << "[" << fila << "] [" << columna << "]" << endl;
			accion = tablaLR[fila][columna];
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

			fila = pila.top();
			columna = idReglas[posicion];
			cout << "[" << fila << "] [" << columna << "]" << endl;
			accion = tablaLR[fila][columna];//da un -3 en fila y no existe

			pila.muestra();
			cout << "Entrada: " << lexico.simbolo << endl;
			cout << "Salida: " << accion << endl;

			pila.push(terminales[columna]);
			pila.push(accion);
			if (lexico.simbolo.compare("$") != 0)
				lexico.sigSimbolo();
			fila = pila.top();
			columna = rectificarTipo(lexico.tipo);
			cout << "[" << fila << "] [" << columna << "]" << endl;
			accion = tablaLR[fila][columna];
		}
		else break;// En caso de error
		pila.muestra();
		cout << "Entrada: " << lexico.simbolo << endl;
		cout << "Salida: " << accion << endl;
	}
	cin.get();
    return 0;
}
