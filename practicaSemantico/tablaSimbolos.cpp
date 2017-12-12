#include "tablaSimbolos.h"
#include "arbolSintactico.h"


void TablaSimbolos::agrega(DefVar *defVar) {
	/*
	char tipo = defVar->tipo->dimeTipo();
	Identificador *identificador = defVar->listaVar;
	ElementoTabla *elementoTabla;
	Nodo *temporal; //este lo utilizo para recorrer la lista
	temporal = identificador;
	while (temporal->sig != NULL) {

		elementoTabla = new Variable(tipo, temporal->simbolo, Nodo::ambito);
		if (varGlobalDefinida(elementoTabla->simbolo))
		{
			Nodo::tablaSimbolos->listaErrores->push_back("Error: variable local \"" +
				elementoTabla->simbolo + "\" redefinida");
		}
		else
			agrega(elementoTabla);

		temporal = temporal->sig;
	}
	elementoTabla = new Variable(tipo, temporal->simbolo, Nodo::ambito);
	if (varGlobalDefinida(elementoTabla->simbolo))
	{
		Nodo::tablaSimbolos->listaErrores->push_back("Error: variable local \"" +
			elementoTabla->simbolo + "\" redefinida");
	}
	else
		agrega(elementoTabla);
		*/


	if (defVar->sig != NULL)
	{
		char tipo = defVar->tipo->dimeTipo();
		Identificador *identificador = defVar->listaVar;
		ElementoTabla *elementoTabla;
		defVar->sig->validaTipos();
		//char tipo = defVar->sig->tipoDato;
		Nodo *temporal; //este lo utilizo para recorrer la lista
		temporal = identificador;
		while (temporal->sig != NULL) {

			elementoTabla = new Variable(tipo, temporal->simbolo, Nodo::ambito);
			if (varGlobalDefinida(elementoTabla->simbolo))
			{
				Nodo::tablaSimbolos->listaErrores->push_back("Error: variable local \"" +
					elementoTabla->simbolo + "\" redefinida");
			}
			else
				agrega(elementoTabla);

			temporal = temporal->sig;
		}
		elementoTabla = new Variable(tipo, temporal->simbolo, Nodo::ambito);
		if (varGlobalDefinida(elementoTabla->simbolo))
		{
			Nodo::tablaSimbolos->listaErrores->push_back("Error: variable local \"" +
				elementoTabla->simbolo + "\" redefinida");
		}
		else
			agrega(elementoTabla);
	}
	else
	{
		char tipo = defVar->tipo->dimeTipo();
		Identificador *identificador = defVar->listaVar;
		ElementoTabla *elementoTabla;
		Nodo *temporal; //este lo utilizo para recorrer la lista
		temporal = identificador;
		while (temporal->sig != NULL) {
			elementoTabla = new Variable(tipo, temporal->simbolo, Nodo::ambito);
			if (varGlobalDefinida(elementoTabla->simbolo))
			{
				Nodo::tablaSimbolos->listaErrores->push_back("Error: variable local \"" +
					elementoTabla->simbolo + "\" redefinida");
			}
			else
				agrega(elementoTabla);

			temporal = temporal->sig;
		}
		elementoTabla = new Variable(tipo, temporal->simbolo, Nodo::ambito);
		if (varGlobalDefinida(elementoTabla->simbolo))
		{
			Nodo::tablaSimbolos->listaErrores->push_back("Error: variable local \"" +
				elementoTabla->simbolo + "\" redefinida");
		}
		else
			agrega(elementoTabla);
	}
}

void TablaSimbolos::agrega(Parametro *parametros) {

	char tipo = parametros->tipo->dimeTipo();
	Identificador * identificador = parametros->id;
	ElementoTabla *elementoTabla;
	Nodo *temporal; //este lo utilizo para recorrer la lista ID
	temporal = parametros;
	temporal->simbolo = parametros->id->simbolo;

	while (temporal->sig != NULL) {
		tipo = temporal->tipoDato;
		elementoTabla = new Variable(tipo, temporal->simbolo, Nodo::ambito);
		agrega(elementoTabla);
		temporal = temporal->sig;
	}
	elementoTabla = new Variable(tipo, temporal->simbolo, Nodo::ambito);
	agrega(elementoTabla);

}

void TablaSimbolos::agrega(DefFunc *defFunc) {

	char tipo = defFunc->tipo->dimeTipo();
	Identificador * identificador = defFunc->id;
	Parametro *p = defFunc->parametros;
	//parametro tiene tipo id y sig     defFunc->parametros->id->simbolo
	ElementoTabla *et;
	Nodo *temp;
	if (p->sig == NULL) {
		et = new Funcion(tipo, identificador->simbolo, p->id->simbolo);
		if (!funcionDefinida(defFunc->simbolo)) {
			agrega(et);
			agrega(p);
		}
		else
		{
			Nodo::tablaSimbolos->listaErrores->push_back("Error: funcion \"" +
				et->simbolo + "\" redefinida");
		}
	}
	else
	{
		temp = p;
		string caracter;
		while (temp->sig != NULL) {
			caracter = caracter + temp->simbolo;
			cout << temp->simbolo << endl << endl;
			temp = temp->sig;
		}
		caracter = caracter + temp->simbolo;

		et = new Funcion(tipo, identificador->simbolo, caracter);
		if (!funcionDefinida(defFunc->simbolo)) {
			agrega(et);
			agrega(p);
		}
		else
		{
			Nodo::tablaSimbolos->listaErrores->push_back("Error: funcion \"" +
				et->simbolo + "\" redefinida");
		}
	}
}

int TablaSimbolos::dispersion(string simbolo) {
	unsigned int h = 0;
	unsigned char c;
	unsigned char alfa = 4;

	for (int i = 0; i < simbolo.length(); i++) {
		c = simbolo[i];
		//		h= (h << 4) + c;
		h += alfa*c;
		h = h % TAM;
	}

	return h%TAM;
}

void TablaSimbolos::agrega(ElementoTabla *elemento) {
	int ind = dispersion(elemento->simbolo);
	tabla[ind].push_back(elemento);
	tabla->size();
}

void TablaSimbolos::muestra() {
	list<ElementoTabla*>::iterator it;
	ElementoTabla *elem;

	cout << endl << "*** Tabla de Simbolos ***" << endl;

	for (int i = 0; i < TAM; i++) {
		if (tabla[i].size() > 0) {

			for (it = tabla[i].begin(); it != tabla[i].end(); it++) {
				elem = (ElementoTabla *)*it;
				cout << "Lista = " << i << endl;
				elem->muestra();
			}
		}
	}
}

bool TablaSimbolos::funcionDefinida(string funcion) {
	int ind = dispersion(funcion);
	list<ElementoTabla*>::iterator it;
	ElementoTabla *elem;

	for (it = tabla[ind].begin(); it != tabla[ind].end(); it++) {
		elem = (ElementoTabla *)*it;
		if (elem->esFuncion()) {
			if (elem->simbolo.compare(funcion) == 0) return true;
		}
	}

	return false;
}

bool TablaSimbolos::varGlobalDefinida(string variable) {
	int ind = dispersion(variable);
	list<ElementoTabla*>::iterator it;
	ElementoTabla *elem;

	for (it = tabla[ind].begin(); it != tabla[ind].end(); it++) {
		elem = (ElementoTabla *)*it;
		if (elem->esVariable() && !elem->esVarLocal()) {
			if (elem->simbolo.compare(variable) == 0) return true;
		}
	}

	return false;
}

bool TablaSimbolos::varLocalDefinida(string variable, string funcion) {
	int ind = dispersion(variable);
	list<ElementoTabla*>::iterator it;
	ElementoTabla *elem;

	for (it = tabla[ind].begin(); it != tabla[ind].end(); it++) {
		elem = (ElementoTabla *)*it;
		if (elem->esVariable() && elem->esVarLocal()) {
			if (((Variable*)elem)->ambito.compare(funcion) == 0 && elem->simbolo.compare(variable) == 0) return true;
		}
	}

	return false;
}

void TablaSimbolos::buscaIdentificador(string simbolo) {
	int ind = dispersion(simbolo);
	list<ElementoTabla*>::iterator it;
	ElementoTabla *elem;

	varGlobal = NULL;
	varLocal = NULL;
	funcion = NULL;

	for (it = tabla[ind].begin(); it != tabla[ind].end(); it++) {
		elem = (ElementoTabla *)*it;

		if (elem->simbolo.compare(simbolo) == 0) {
			if (elem->esVariable()) {
				if (elem->esVarLocal()) varLocal = (Variable*)elem;
				else
					varGlobal = (Variable*)elem;
			}
			else
				funcion = (Funcion*)elem;
		}

	}

}

void TablaSimbolos::buscaFuncion(string simbolo) {
	int ind = dispersion(simbolo);
	list<ElementoTabla*>::iterator it;
	ElementoTabla *elem;

	varGlobal = NULL;
	varLocal = NULL;
	funcion = NULL;

	for (it = tabla[ind].begin(); it != tabla[ind].end(); it++) {
		elem = (ElementoTabla *)*it;

		if (elem->simbolo.compare(simbolo) == 0 && elem->esFuncion()) {
			funcion = (Funcion*)elem;
			return;
		}
	}

}
