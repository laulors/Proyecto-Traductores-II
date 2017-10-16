#include <cstdlib>
#include <iostream>
#include <string>

#include "lexico.h"
#include "pila.h"

using namespace std;


int main(int argc, char *argv[]){  
        
	int tablaLR[5][4] = {
		2,0,0,1,
		0,0,-1,0,
		0,3,0,0,
		4,0,0,0,
		0,0,-2,0
		};
	
	Pila pila;
	int fila, columna, accion;
	bool aceptacion = false;
	Lexico lexico("a+b$");

	//inicializa la pila
	pila.push(lexico.PESOS);
	pila.push(0);
	lexico.sigSimbolo();

	//encontrar la accion a realizar

	fila = pila.top();
	columna = lexico.tipo;
	accion = tablaLR[fila][columna];

	//mostramos contenido de pila
	pila.muestra();
	cout << "entrada: " << lexico.simbolo << endl;//entrada a
	cout << "accion: " << accion << endl<<endl;

	/*dado que el valor de la accion es numero positivo entonces se debe de realizar desplazamiento. Implica meter
	el simbolo actual en la pila, y pedir un sigSimbolo.
	*/
	if (lexico.tipo == lexico.OP_ADICION)
		lexico.tipo = 1;
	pila.push(lexico.tipo);
	pila.push(accion);
	lexico.sigSimbolo();

	//se vuelve a calc. la accion siguiente accion utilizando el tope y la entrada
	fila = pila.top();
	if (lexico.tipo == lexico.OP_ADICION)
		lexico.tipo = 1;
	columna = lexico.tipo;
	accion = tablaLR[fila][columna];

	//se muestran los datos de la pila entrada y salida
	pila.muestra();
	cout << "-entrada: " << lexico.simbolo << endl;//entrada +
	cout << "-accion: " << accion << endl<<endl;

	//se guarda la informacion en la pila
	if (lexico.tipo == lexico.OP_ADICION)
		lexico.tipo = 1;
	pila.push(lexico.tipo);
	pila.push(accion);
	lexico.sigSimbolo();

	//se calcula la accion a realizar
	fila = pila.top();
	if (lexico.tipo == lexico.OP_ADICION)
		lexico.tipo = 1;
	columna = lexico.tipo;
	accion = tablaLR[fila][columna];

	//se muestra la informacion de la pila
	pila.muestra();
	cout << "*entrada: " << lexico.simbolo << endl;//entrada b
	cout << "*accion: " << accion << endl << endl;

	//se guarda informacion en la pila
	if (lexico.tipo == lexico.OP_ADICION)
		lexico.tipo = 1;
	pila.push(lexico.tipo);
	pila.push(accion);
	lexico.sigSimbolo();

	//se calcula siguiente accion
	fila = pila.top();
	if (lexico.tipo == lexico.OP_ADICION)
		lexico.tipo = 1;
	if (lexico.tipo == lexico.FIN)
		lexico.tipo = lexico.PESOS;
	columna = lexico.tipo;
	accion = tablaLR[fila][columna];

	//se muestra la informacion contenida en la pila
	pila.muestra();
	cout << "++entrada: " << lexico.simbolo << endl;
	cout << "++accion: " << accion << endl << endl;

	
	//ahora obtenemos una reduccion porque el entero es -2
	//lo que indica que es la reduccion 1, como la regla 1 es: E-> <id> + <id> se sacan elementos de la pila
	pila.pop();
	pila.pop();
	pila.pop();
	pila.pop();
	pila.pop();
	pila.pop();
	fila = pila.top();
	columna = 3; 

	//transicion
	pila.push(3);
	accion = tablaLR[fila][columna];
	pila.push(accion);
	pila.muestra();

	cout << "entrada: " << lexico.simbolo << endl;
	cout << "accion: " << accion << endl << endl;

	//se calcula la siguiente accion si es -1 es aceptación
	fila = pila.top();
	if (lexico.tipo == lexico.FIN)
		lexico.tipo = 2;// el $ de pesitos sea 2
	columna = lexico.tipo;
	accion = tablaLR[fila][columna];

	pila.muestra();
	cout << "entrada: " << lexico.simbolo << endl;
	cout << "accion: " << accion << endl;
	if (accion == -1)
		cout << "Aceptacion." << endl;
	cin.get();
    return 0;
}
