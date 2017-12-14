#ifndef SINTACTICO
#define SINTACTICO

#include <iostream>
#include <vector>
#include "Lexico.h"
#include "Pila.h"
#include "Terminal.h"
#include "Tabla.h"
#include "Reglas.h"

class Sintactico
{
public:
    Pila pila;
    Lexico lexico;
    int accion,fila,columna;
    vector<string> terminalesNoTerminales;
    Tabla tabla;

    Sintactico();
    void mostrarDatos();
    void proceso();
};

Sintactico::Sintactico()
{
    tabla.leerArchivo((char*)"gramatica.lr");
    accion = 0;
}

void Sintactico::mostrarDatos()
{
    pila.muestra();
    cout << "Fila: " << fila << " Columna: " << columna << endl;
    cout << "Entrada: " << lexico.simbolo << endl;
    cout << "Accion: " << accion << endl;
    cout << endl << endl;
}

void Sintactico::proceso()
{
    bool aceptacion = false;
    lexico.entrada("prueba.txt");
    pila.push(new Terminal("$"));
    pila.push(new Estado(0));
    lexico.sigSimbolo();

    fila = pila.top()->getEstado();
    columna = lexico.tipo;
    accion = tabla.matriz[fila][columna];

    while(true)
    {
        if(accion == -1)
        {
            cout << "ACEPTACION"<< endl;
            break;
        }
        if(accion > 0)//DESPLAZAMIENTO
        {
            pila.push(new Terminal(lexico.simbolo));
            pila.push(new Estado(accion));
            lexico.sigSimbolo();

            fila = pila.top()->getEstado();
            columna = lexico.tipo;
            accion = tabla.matriz[fila][columna];

        }
        else if(accion < 0)//REDUCCION
        {

            int opc = (accion*-1)-1;
            int tmp = 0;
            Nodo* nuevoNodo;
            switch(opc)
            {
            case 2:
            case 7:
            case 10:
            case 12:
            case 15:
            case 19:
            case 26:
            case 29:
            case 31:
            case 33:
                nuevoNodo = new nullNodo();
                break;
            case 1:
                nuevoNodo = new Programa_R1(pila);
                nuevoNodo->muestra(1);
                nuevoNodo->generarCodigo();

                break;
            case 3:
                nuevoNodo = new Definiciones_R3(pila);
                break;
            case 4:
                nuevoNodo = new Definicion_R4(pila);
                break;
            case 5:
                nuevoNodo = new Definicion_R5(pila);
                break;
            case 6:
                nuevoNodo = new DefVar_R6(pila);
                break;
            case 8:
                nuevoNodo = new ListaVar_R8(pila);
                break;
            case 9:
                nuevoNodo = new DefFunc_R9(pila);
                break;
            case 11:
                nuevoNodo = new Parametros_R11(pila);
                break;
            case 13:
                nuevoNodo = new ListaParam_R13(pila);
                break;
            case 14:
                nuevoNodo = new BloqFunc_R14(pila);
                break;
            case 16:
                nuevoNodo = new DefLocales_R16(pila);
                break;
            case 17:
                nuevoNodo = new DefLocal_R17(pila);
                break;
            case 18:
                nuevoNodo = new DefLocal_R18(pila);
                break;
            case 20:
                nuevoNodo = new Sentencias_R20(pila);
                break;
            case 21:
                nuevoNodo = new Sentencia_R21(pila);
                break;
            case 22:
                nuevoNodo = new Sentencia_R22(pila);
                break;
            case 23:
                nuevoNodo = new Sentencia_R23(pila);
                break;
            case 24:
                nuevoNodo = new Sentencia_R24(pila);
                break;
            case 25:
                nuevoNodo = new Sentencia_R25(pila);
                break;
            case 27:
                nuevoNodo = new Otro_R27(pila);
                break;
            case 28:
                nuevoNodo = new Bloque_R28(pila);
                break;
            case 30:
                nuevoNodo = new ValorRegresa_R30(pila);
                break;
            case 32:
                nuevoNodo = new Argumentos_R32(pila);
                break;
            case 34:
                nuevoNodo = new ListaArgumentos_R34(pila);
                break;
            case 35:
                nuevoNodo = new Termino_R35(pila);
                break;
            case 36:
                nuevoNodo = new Termino_R36(pila);
                break;
            case 37:
                nuevoNodo = new Termino_R37(pila);
                break;
            case 38:
                nuevoNodo = new Termino_R38(pila);
                break;
            case 39:
                nuevoNodo = new Termino_R39(pila);
                break;
            case 40:
                nuevoNodo = new LlamadaFunc_R40(pila);
                break;
            case 41:
                nuevoNodo = new SentenciaBloque_R41(pila);
                break;
            case 42:
                nuevoNodo = new SentenciaBloque_R42(pila);
                break;
            case 43:
                nuevoNodo = new Expresion_R43(pila);
                break;
            case 44:
                nuevoNodo = new Expresion_R44(pila);
                break;
            case 45:
                nuevoNodo = new Expresion_R45(pila);
                break;
            case 46:
                nuevoNodo = new Expresion_R46(pila);
                break;
            case 47:
                nuevoNodo = new Expresion_R47(pila);
                break;
            case 48:
                nuevoNodo = new Expresion_R48(pila);
                break;
            case 49:
                nuevoNodo = new Expresion_R49(pila);
                break;
            case 50:
                nuevoNodo = new Expresion_R50(pila);
                break;
            case 51:
                nuevoNodo = new Expresion_R51(pila);
                break;
            case 52:
                nuevoNodo = new Expresion_R52(pila);
                break;

            }
            fila = pila.top()->getEstado();
            columna = tabla.idReglas[(-accion)-2];
            tmp = accion;
            accion = tabla.matriz[fila][columna];

            pila.push(new NoTerminal(tabla.noTerminalesAux[(-tmp)-2], nuevoNodo));
            pila.push(new Estado(accion));
            cout << endl;

            fila = pila.top()->getEstado();
            columna = lexico.tipo;
            accion = tabla.matriz[fila][columna];
            continue;
        }
        else break;
    }
}

#endif
