#include <cstdlib>
#include <iostream>
#include <string>

#include "lexico.h"
#include "pila.h"

using namespace std;


int main(int argc, char *argv[]){  
        
	int tablaLR[3][3] = {
		2,0,1,
		0,-1,0,
		0,-2,0
		};
	
	Pila pila;
	int fila, columna, accion;
	bool aceptacion = false;
	Lexico lexico("a$");

	pila.push(lexico.PESOS);
	pila.push(0);
	lexico.sigSimbolo();

	//encontrar la accion a realizar

	fila = pila.top();
	columna = lexico.tipo;
	accion = tablaLR[fila][columna];

	//mostramos contenido de pila
	pila.muestra();
	cout << "entrada: " << lexico.simbolo << endl;
	cout << "accion: " << accion << endl<<endl;

	/*dado que el valor de la accion es numero positivo entonces se debe de realizar desplazamiento. Implica meter
	el simbolo actual en la pila, ademas del numero 3 y pedir
	un sigSimbolo.
	*/
	pila.push(lexico.tipo);
	pila.push(accion);
	lexico.sigSimbolo();

	//se vuelve a calc. siguiente accion utilizando el tope y la entrada
	fila = pila.top();
	if(lexico.tipo == 23)
		columna = 1;
	accion = tablaLR[fila][columna];

	pila.muestra();
	cout << "entrada: " << lexico.simbolo << endl;
	cout << "accion: " << accion << endl<<endl;

	//ahora obtenemos una reduccion porque el entero es -2
	//lo que indica que es la reduccion 1, como la regla 1 es: E-> <id> se sacan 2 elementos de la pila
	pila.pop();
	pila.pop();
	//calculamos la transicion utilizando el simbolo A, en el caso es 2.
	fila = pila.top();
	columna = 2; //el no terminal que representa E

	//transicion
	pila.push(2);
	accion = tablaLR[fila][columna];
	pila.push(accion);
	pila.muestra();

	cout << "entrada: " << lexico.simbolo << endl;
	cout << "accion: " << accion << endl << endl;

	//se calcula la siguiente accion si es -1 es aceptación
	fila = pila.top();
	if (lexico.tipo == 23)
		columna = 1;// el $ de pesitos sea 1
	accion = tablaLR[fila][columna];

	pila.muestra();
	cout << "entrada: " << lexico.simbolo << endl;
	cout << "accion: " << accion << endl;
	if (accion == -1)
		cout << "Aceptacion." << endl;
	cin.get();
    return 0;
}
