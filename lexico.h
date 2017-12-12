#ifndef _LEXICO
#define _LEXICO

#include <iostream>
#include <string>
using namespace std;

class TipoSimbolo{
public:
 static const int ERROR= -1;
 static const int IDENTIFICADOR= 0;
 static const int ENTERO = 1;
 static const int REAL = 2;
 static const int CADENA = 3;
 static const int TIPO = 4;
 static const int OPADIC= 5;
 static const int OPMULT= 6;
 static const int OPRELACIONAL = 7;
 static const int OPOR = 8;
 static const int OPAND = 9;
 static const int OPNOT = 10;
 static const int IGUALDAD = 11;
 static const int PUNTOCOMA = 12;
 static const int COMA = 13;
 static const int PARENTESISD = 14;
 static const int PARENTESISI = 15;
 static const int LLAVED = 16;
 static const int LLAVEI = 17;
 static const int ASIGNACION = 18;
 static const int IF = 19;
 static const int WHILE = 20;
 static const int RETURN = 21;
 static const int ELSE = 22;
 static const int PESOS = 23;
 static const int FINCAD = 24;
 
};

class Lexico{
      private:
       string fuente;

       int ind;
       bool continua;
       char c;
       int estado;
	   bool parteDeToken;

       char sigCaracter();
       void sigEstado(int estado);
       void aceptacion(int estado);
       bool esLetra(char c);
       bool esDigito(char c);
       bool esEspacio(char c);
	   bool esPunto(char c);
       bool esSignoAdicion(char c);
       void retroceso();
	   bool esComa(char c);
	   bool esPuntoyComa(char c);
	   bool sonComillas(char c);
	   bool esParentesisIzq(char c);
	   bool esParentesisDer(char c);
	   bool esGato(char c);
	   bool esSignoExclamacion(char c);
	   bool esSignoPregunta(char c);
	   bool sonDosPuntos(char c);
	   bool esGuion(char c);
	   bool esGuionBajo(char c);
	   bool esMenorQue(char c);
	   bool esMayorQue(char c);
	   bool esIgual(char c);
	   bool esMayorIgual(char c);
	   bool esMenorIgual(char c);
	   bool esSignoIgual(char c);
	   bool esDiagonalInvertida(char c);
	   bool esCorcheteDer(char c);
	   bool esCorcheteIzq(char c);
	   bool esLlaveDer(char c);
	   bool esLlaveIzq(char c);
	   bool esBarra(char c);
	   bool esPesos(char c);
	   bool esTabulacion(char c);
	   bool esEspacioBlanco(char c);
	   bool esSignoMultiplicacion(char c);
	   bool esYFancy(char c);
	   int esPalabraReservada();
      public:
       string simbolo;
       int tipo;

       Lexico(string fuente);
       Lexico();

       void entrada(string fuente);
       string tipoAcad(int tipo);

       int sigSimbolo();
       bool terminado();

};

#endif
