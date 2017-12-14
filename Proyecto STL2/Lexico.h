#ifndef LEXICO
#define LEXICO

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

class TipoSimbolo
{
public:

    static const int ERROR = -1;
    static const int IDENTIFICADOR = 0;
    static const int ENTERO = 1;
    static const int REAL = 2;
    static const int CADENA = 3;
    static const int TIPO = 4;
    static const int OPADIC = 5;
    static const int OPMULT = 6;
    static const int OPRELAC = 7;
    static const int OPOR = 8;
    static const int OPAND = 9;
    static const int OPNOT = 10;
    static const int OPIGUALDAD = 11;
    static const int PUNTO_COMA = 12;
    static const int COMA = 13;
    static const int PARENT_IZQ = 14;
    static const int PARENT_DER = 15;
    static const int LLAVE_IZQ = 16;
    static const int LLAVE_DER = 17;
    static const int ASIGNACION = 18;
    static const int IF = 19;
    static const int WHILE = 20;
    static const int RETURN = 21;
    static const int ELSE = 22;
    static const int PESOS = 23;
};


class Lexico
{
private:
    string fuente;
    int ind;
    bool continua;
    char c;
    int estado;

    char sigCaracter();
    void sigEstado(int estado);
    void aceptacion(int estado);
    bool esLetra(char c);
    bool esDigito(char c);
    bool esEspacio(char c);
    void retroceso();

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
