#include "lexico.h"

Lexico::Lexico(string fuente) {
	ind = 0;
	this->fuente = fuente;
}
Lexico::Lexico() {
	ind = 0;
}
string Lexico::tipoAcad(int tipo) {
	string cad = "";

	switch (tipo) {
	case TipoSimbolo::IDENTIFICADOR:
		cad = "Identificador";
		break;
	case TipoSimbolo::OPADIC:
		cad = "Op. Adicion";
		break;
	case TipoSimbolo::OPMULT:
		cad = "Op. Multiplicacion";
		break;
	case TipoSimbolo::PESOS:
		cad = "Fin de la Entrada";
		break;
	case TipoSimbolo::ENTERO:
		cad = "Entero";
		break;
	case TipoSimbolo::REAL:
		cad = "Real";
		break;
	case TipoSimbolo::OPOR:
		cad = "Operador OR";
		break;
	case TipoSimbolo::OPAND:
		cad = "Operador AND";
		break;
	case TipoSimbolo::OPNOT:
		cad = "Operador NOT";
		break;
	case TipoSimbolo::CADENA:
		cad = "Cadena";
		break;
	case TipoSimbolo::IGUALDAD:
		cad = "Igualdad";
		break;
	case TipoSimbolo::IF:
		cad = "if";
		break;
	case TipoSimbolo::WHILE:
		cad = "while";
		break;
	case TipoSimbolo::ELSE:
		cad = "else";
		break;
	case TipoSimbolo::RETURN:
		cad = "return";
		break;
	case TipoSimbolo::OPRELACIONAL:
		cad = "Op Relacional";
		break;
	case TipoSimbolo::COMA:
		cad = ",";
		break;
	case TipoSimbolo::PUNTOCOMA:
		cad = ";";
		break;
	case TipoSimbolo::LLAVED:
		cad = "{";
		break;
	case TipoSimbolo::LLAVEI:
		cad = "}";
		break;
	case TipoSimbolo::PARENTESISD:
		cad = "(";
		break;
	case TipoSimbolo::PARENTESISI:
		cad = ")";
		break;
	case TipoSimbolo::ASIGNACION:
		cad = "=";
		break;
	case TipoSimbolo::FINCAD:
		cad = "fin cadena";
		break;
	default: simbolo = "ERROR";
	}
	return cad;
}
void Lexico::entrada(string fuente) {
	ind = 0;
	this->fuente = fuente;
}
int Lexico::sigSimbolo() {

	estado = 0;
	continua = true;
	simbolo = "";

	//Inicio del Automata
	while (continua) {

		if(parteDeToken)
			c = sigCaracter();

		parteDeToken = true;

		switch (estado) {
		case 0: {
			if (esSignoMultiplicacion(c))
				sigEstado(6);
			else if (esSignoAdicion(c))
				sigEstado(5);
			else if (esDigito(c))
				sigEstado(3);
			else if (esLetra(c))
				sigEstado(1);
			else if (esPuntoyComa(c))
				sigEstado(12);
			else if (esComa(c))
				sigEstado(13);
			else if (esParentesisDer(c))
				sigEstado(14);
			else if (esParentesisDer(c))
				sigEstado(15);
			else if (esCorcheteIzq(c))
				sigEstado(16);
			else if (esCorcheteDer(c))
				sigEstado(17);
			else if (esMayorQue(c) || esMenorQue(c))
				sigEstado(6);
			else if (esSignoIgual(c))
				sigEstado(10);
			else if (esEspacio(c) || esTabulacion(c))
				sigEstado(0);
			else if (sonComillas(c))
				sigEstado(11);
			else if (esBarra(c))
				sigEstado(7);
			else if (esYFancy(c))
				sigEstado(8);
			else if (esSignoExclamacion(c))
				sigEstado(9);
			else if (esPesos(c))
				sigEstado(23);
			else
				aceptacion(-1);
			}break;
			case 1: {
				if (esLetra(c))
					sigEstado(1);
				else if (esDigito(c))
					sigEstado(2);
				else {
					parteDeToken = false;
					aceptacion(esPalabraReservada());

				}
			}break;
			case 2:{ 
				if (esLetra(c) || esDigito(c))
					sigEstado(2);
				else {

					parteDeToken = false;
					aceptacion(0);
				}
			}break;
			case 3:{
				if (esDigito(c))
					sigEstado(3);
				else if (esPunto(c))
					sigEstado(4);
				else {
					parteDeToken = false;
					aceptacion(1);
				}
			}break;
			case 4:{
				if (esDigito(c))
					sigEstado(5);
				else {
					parteDeToken = false;
					aceptacion(-1);
				}
			}break;
			case 5: {
				if (esDigito(c))
					sigEstado(5);
				else {
					parteDeToken = false;
					aceptacion(5);
				}
				}break;
			case 6: {
				if (esIgual(c))
					aceptacion(7);
				else {
					parteDeToken = false;
					aceptacion(6);
				}
			}break;
			case 7: {
				if (esBarra(c))
					aceptacion(8);
				else {
					parteDeToken = false;
					aceptacion(-1);
				}
			}break;
			case 8: {
				if (esYFancy(c))
					aceptacion(9);
				else {
					parteDeToken = false;
					aceptacion(-1);
				}
			}break;
			case 9: {
				if (esSignoIgual(c))
					aceptacion(11);
				else {
					parteDeToken = false;
					aceptacion(10);
				}
			}break;
			case 10: {
				if (esSignoIgual(c))
					aceptacion(11);
				else {
					parteDeToken = false;
					aceptacion(18);
				}
			}break;
			case 11: {
				if (sonComillas(c))
					aceptacion(3);
				else if (isascii(c))
					sigEstado(11);
			}break;
			default: break;
			}
		}
	
	//Fin del Automata

	switch (estado) {
	case 0: tipo = TipoSimbolo::IDENTIFICADOR;
		break;
	case 1: tipo = TipoSimbolo::ENTERO;
		break;
	case 2: tipo = TipoSimbolo::REAL;
		break;
	case 3: tipo = TipoSimbolo::CADENA;
		break;
	case 4: tipo = TipoSimbolo::TIPO;
		break;
	case 5: tipo = TipoSimbolo::OPADIC;
		break;
	case 6: tipo = TipoSimbolo::OPMULT;
		break;
	case 7: tipo = TipoSimbolo::OPRELACIONAL;
		break;
	case 8: tipo = TipoSimbolo::OPOR;
		break;
	case 9: tipo = TipoSimbolo::OPAND;
		break;
	case 10: tipo = TipoSimbolo::OPNOT;
		break;
	case 11: tipo = TipoSimbolo::IGUALDAD;
		break;
	case 12: tipo = TipoSimbolo::PUNTOCOMA;
		break;
	case 13: tipo = TipoSimbolo::COMA;
		break;
	case 14: tipo = TipoSimbolo::PARENTESISI;
		break;
	case 15: tipo = TipoSimbolo::PARENTESISD;
		break;
	case 16: tipo = TipoSimbolo::LLAVEI;
		break;
	case 17: tipo = TipoSimbolo::LLAVED;
		break;
	case 18: tipo = TipoSimbolo::ASIGNACION;
		break;
	case 19: tipo = TipoSimbolo::IF;
		break;
	case 20: tipo = TipoSimbolo::WHILE;
		break;
	case 21: tipo = TipoSimbolo::RETURN;
		break;
	case 22: tipo = TipoSimbolo::ELSE;
		break;
	case 23: tipo = TipoSimbolo::FINCAD;
		break;
	default:
		tipo = TipoSimbolo::ERROR;
	}
	return tipo;
}
char Lexico::sigCaracter() {
	if (terminado()) return '$';
	return fuente[ind++];
}
void Lexico::sigEstado(int estado) {
	this->estado = estado;
	simbolo += c;
}
void Lexico::aceptacion(int estado) {
	sigEstado(estado);
	continua = false;
}
bool Lexico::terminado() {//fin de cadena
	return ind >= fuente.length();
}
bool Lexico::esLetra(char c) {
	return isalpha(c) || c == '_';
}
bool Lexico::esDigito(char c) {
	return isdigit(c);
}
bool Lexico::esEspacio(char c) {
	return c == ' ' || c == '\t';
}
bool Lexico::esPunto(char c) {
	return c == '.';
}
bool Lexico::esSignoAdicion(char c){
	return c == '+' || c == '-';
}
bool Lexico::esSignoMultiplicacion(char c) {
	return c == '*' || c == '/';
}
void Lexico::retroceso() {
	if (c != '$') ind--;
	continua = false;
}
bool Lexico::esComa(char c) {
	return c == ',';
}
bool Lexico::esPuntoyComa(char c) {
	return c == ';';
}
bool Lexico::sonComillas(char c) {
	return c == '"';
}
bool Lexico::esParentesisIzq(char c) {
	return c == '(';
}
bool Lexico::esParentesisDer(char c) {
	return c == ')';
}
bool Lexico::esGato(char c) {
	return c == '*';
}
bool Lexico::esSignoExclamacion(char c) {
	return c == '!' || c == '¡';
}
bool Lexico::esSignoPregunta(char c) {
	return c == '?' || c == '¿';
}
bool Lexico::sonDosPuntos(char c) {
	return c == ':';
}
bool Lexico::esGuion(char c) {
	return c == '-';
}
bool Lexico::esGuionBajo(char c) {
	return c == '_';
}
bool Lexico::esMenorQue(char c) {
	return c == '<';
}
bool Lexico::esMayorQue(char c) {
	return c == '>';
}
bool Lexico::esMayorIgual(char c) {
	return c == '>=';
}
bool Lexico::esMenorIgual(char c) {
	return c == '<=';
}
bool Lexico::esIgual(char c) {
	return c == '==';
}
bool Lexico::esSignoIgual(char c) {
	return c == '=';
}
bool Lexico::esDiagonalInvertida(char c) {
	return c=='\'';
}
bool Lexico::esCorcheteIzq(char c) {
	return c == '[';
}
bool Lexico::esCorcheteDer(char c) {
	return c == ']';
}
bool Lexico::esLlaveIzq(char c) {
	return c == '{';
}
bool Lexico::esLlaveDer(char c) {
	return c == '}';
}
bool Lexico::esBarra(char c) {
	return c == '|';
}
bool Lexico::esPesos(char c) {
	return c == '$';
}
bool Lexico::esEspacioBlanco(char c) {
	return c == ' ';
}
bool Lexico::esTabulacion(char c) {
	return c == '\t';
}
bool Lexico::esYFancy(char c) {
	return c == '&';
}
int Lexico::esPalabraReservada() {
	if (simbolo.compare("if")){
		return 19;
	}
	else{
		if (simbolo.compare("else"))
			return 22;
		else {
			if (simbolo.compare("return"))
				return 21;
			else {
				if (simbolo.compare("while"))
					return 20;
				else {
					if (simbolo.compare("int") || simbolo.compare("float") || simbolo.compare("void"))
						return 4;
					else
						return 0;
				}
			}
		}
	}
}