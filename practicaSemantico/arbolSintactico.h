#ifndef _ARBOLSINTACTICO
#define _ARBOLSINTACTICO

#include <string>
#include <iostream>
#include "tablaSimbolos.h"

using namespace std;

class Nodo {
public:
	string simbolo;
	Nodo *sig;
	char tipoDato;
	static TablaSimbolos *tablaSimbolos;
	static string ambito;

	static int sangria;
	void muestraSangria() {
		for (int i = 0; i < sangria; i++)
			cout << " ";
	}

	virtual void muestra() {};

	virtual void validaTipos(){
		tipoDato = 'v';
		if (sig != NULL) sig->validaTipos();
	}

};

class Tipo : public Nodo {
public:

	Tipo(string simbolo) {
		this->simbolo = simbolo;
		this->sig = NULL;
	}

	char dimeTipo() {
		char c;
		if (simbolo.compare("int") == 0)
			c = 'i';
		if (simbolo.compare("float") == 0) 
			c = 'f';
		if (simbolo.compare("string") == 0) 
			c = 's';
		if (simbolo.compare("void") == 0) 
			c = 'v';
		return c;
	}

	void muestra() {
		muestraSangria();
		cout << "<Tipo> " << simbolo << endl;
	}
};

class Expresion : public Nodo {
public:
	Expresion *izq, *der;
	string guardaArbol() {
		return "";
	}

};

class Identificador : public Expresion {
public:
	Identificador(string simbolo, Nodo *sig = NULL) {
		this->simbolo = simbolo;
		this->sig = sig;
	}

	void muestra() {
		muestraSangria();
		cout << "<Identificador> " << simbolo << endl;
		if (sig != NULL) sig->muestra();
	}
};

class DefVar : public Nodo {
public:
	Tipo *tipo;
	Identificador *listaVar;
	friend class TablaSimbolos;

	DefVar(Tipo *tipo, Identificador *listaVar, Nodo *sig) {
		this->tipo = tipo;
		this->listaVar = listaVar;
		this->sig = sig;
	}
	void validaTipos() {
		cout << "AGREGA TIPOS DEFVAR" << endl;
		tablaSimbolos->agrega(this);
		tipoDato = tipo->dimeTipo();
	}
	void muestra() {
		muestraSangria();
		cout << "<DefVar> " << endl;

		Nodo::sangria++;
		tipo->muestra();
		listaVar->muestra();
		Nodo::sangria--;

		if (sig != NULL) sig->muestra();
	}
};

class Parametro : public Nodo {
public:
	Tipo *tipo;
	Identificador *id;
	friend class TablaSimbolos;

	Parametro(Tipo *tipo, Identificador *id, Nodo *sig) {
		this->tipo = tipo;
		this->id = id;
		this->sig = sig;
	}
	Identificador* dameIdentificador() {
		return id;
	}
	Tipo* dameTipo() {
		return tipo;
	}
	void validaTipos() {
		cout << "AGREGA PARAMETRO" << endl;
		tablaSimbolos->agrega(this);
		tipoDato = tipo->dimeTipo();
	}
	void muestra() {
		muestraSangria();
		cout << "<Parametro> " << endl;

		Nodo::sangria++;
		tipo->muestra();
		id->muestra();
		Nodo::sangria--;

		if (sig != NULL) sig->muestra();
	}

	string cadTipos() {
		string cad;
		cad += tipo->dimeTipo();
		Parametro *p = (Parametro*)sig;

		while (p != NULL) {
			cad += p->tipo->dimeTipo();
			p = (Parametro*)p->sig;
		}
		return cad;
	}

};

class DefFunc : public Nodo {
protected:
	Tipo *tipo;
	Identificador *id;
	Parametro *parametros;
	Nodo *bloqueFunc;
	friend class TablaSimbolos;

public:

	DefFunc(Tipo *tipo, Identificador *id, Parametro *parametros, Nodo *bloqueFunc, Nodo *sig) {
		this->tipo = tipo;
		this->id = id;
		this->parametros = parametros;
		this->bloqueFunc = bloqueFunc;
		this->sig = sig;
	}
	void validaTipos() {
		cout << "AGREGA DEF.FUN" << endl;
		tablaSimbolos->agrega(this);
		tipoDato = tipo->dimeTipo();
	}
	void muestra() {
		muestraSangria();
		cout << "<DefFunc> " << endl;

		Nodo::sangria++;
		tipo->muestra();
		id->muestra();
		if (parametros) parametros->muestra();
		if (bloqueFunc) bloqueFunc->muestra();
		Nodo::sangria--;

		if (sig != NULL) sig->muestra();
	}


};


class Asignacion : public Nodo {
public:
	Identificador *id;
	Expresion *expresion;
	friend class TablaSimbolos;

	Asignacion(Identificador *id, Expresion *expresion, Nodo *sig = NULL) {
		this->id = id;
		this->expresion = expresion;
		this->sig = sig;

	}

	void muestra() {
		muestraSangria();
		cout << "<Asignacion> " << endl;

		Nodo::sangria++;
		id->muestra();
		expresion->muestra();
		Nodo::sangria--;

		if (sig != NULL) sig->muestra();
	}


};

class Regresa : public Nodo {
protected:
	Expresion *expresion;
	friend class TablaSimbolos;

public:

	Regresa(Expresion *expresion, Nodo *sig = NULL) {
		this->expresion = expresion;
		this->sig = sig;
	}

	void muestra() {
		muestraSangria();
		cout << "<Regresa> " << endl;

		Nodo::sangria++;
		expresion->muestra();
		Nodo::sangria--;

		if (sig != NULL) sig->muestra();
	}

};

class Entero : public Expresion {
public:
	Entero(string simbolo) {
		this->simbolo = simbolo;
		this->sig = NULL;
	}
	void validacion() {
		if (izq->tipoDato == 'i' && izq->tipoDato == der->tipoDato) tipoDato =
			'i';
	}
	void muestra() {
		muestraSangria();
		cout << "<Entero> " << simbolo << endl;
	}
};

class Real : public Expresion {
public:
	Real(string simbolo) {
		this->simbolo = simbolo;
		this->sig = NULL;
	}
	void validacion() {
		if (izq->tipoDato == 'f' && izq->tipoDato == der->tipoDato) tipoDato =
			'f';
	}
	void muestra() {
		muestraSangria();
		cout << "<Real> " << simbolo << endl;
	}
};

class Cadena : public Expresion {
public:
	Cadena(string simbolo) {
		this->simbolo = simbolo;
		this->sig = NULL;
	}
	void validacion() {
		if (izq->tipoDato == 's' && izq->tipoDato == der->tipoDato) tipoDato =
			's';
	}
	void muestra() {
		muestraSangria();
		cout << "<Cadena> " << simbolo << endl;
	}
};

class Signo : public Expresion {
protected:
public:

	Signo(string simbolo, Expresion *izq) {
		this->simbolo = simbolo;
		this->izq = izq;
		sig = NULL;
	}

	void muestra() {
		muestraSangria();
		cout << "<Signo> " << endl;

		Nodo::sangria++;
		izq->muestra();
		Nodo::sangria--;

		if (sig != NULL) sig->muestra();
	}

};

class Mult : public Expresion {
protected:
public:

	Mult(string simbolo, Expresion *izq, Expresion *der) {
		this->der = der;
		this->simbolo = simbolo;
		this->izq = izq;
		sig = NULL;

	}

	void muestra() {
		muestraSangria();
		cout << "<Multiplicacion> " << simbolo << endl;

		Nodo::sangria++;
		izq->muestra();
		der->muestra();
		Nodo::sangria--;

		if (sig != NULL) sig->muestra();
	}

	string guardaArbol() {
		return "new Mult(" + simbolo + "," + izq->guardaArbol() + ", " + der->guardaArbol() + ") ";
	}
};

class Suma : public Expresion {
protected:
public:

	Suma(string simbolo, Expresion *izq, Expresion *der) {
		this->der = der;
		this->simbolo = simbolo;
		this->izq = izq;
		sig = NULL;

	}

	void muestra() {
		muestraSangria();
		cout << "<Suma> " << simbolo << endl;

		Nodo::sangria++;
		izq->muestra();
		der->muestra();
		Nodo::sangria--;

		if (sig != NULL) sig->muestra();
	}

	string guardaArbol() {
		return "new Suma(" + simbolo + "," + izq->guardaArbol() + ", " + der->guardaArbol() + ") ";
	}

};


#endif
