#ifndef REGLAS
#define REGLAS
#include "Pila.h"
#include "TablaSimbolos.h"
#include "NoTerminal.h"
#include "Simbolo.h"
#include "TablaErrores.h"
#include <fstream>
#include <sstream>

TablaSimbolos *tablaSimbolos = new TablaSimbolos();
TablaErrores *tablaError = new TablaErrores();
char vectParametros[20], vectArgumentos[20];
int contParam, contArgs, contador = 0;

class Nodo
{
protected:
    char tipoCh;
    string ambito;
public:
    virtual void muestra(int numeroTab) {}
    virtual char validaTipo(string) {}
    virtual char validaTipo(string,string) {}
    virtual void validaTipo(char,string) {}
    virtual string generarCodigo() {}

    void tabuladorNombre(int numeroTab, string Nombre)
    {
        for (int i = 0; i < numeroTab-1; i++)
            cout << "   " ;
        cout << Nombre << endl;
    }

    void tabsTerminal(int numeroTab, string terminal)
    {
        for (int i = 0; i < numeroTab; i++)
            cout << "   " ;
        cout << terminal << endl;
    }

    string getSaltoIgualdad(string operador)
    {
        string tipoSalto;
        if(operador ==">=")
            tipoSalto = "jge";
        else if(operador == "<=")
            tipoSalto = "jle";
        else if(operador == "==")
            tipoSalto = "je";
        else if(operador == "!=")
            tipoSalto = "jne";
        else if(operador == ">")
            tipoSalto = "jg";
        else if(operador == "<")
            tipoSalto = "jl";
        return tipoSalto;
    }

    string getLabelNumber()
    {
        std::stringstream etiqueta;
        etiqueta << contador;
        return etiqueta.str();
    }
};

class nullNodo: public Nodo
{
protected:
    Nodo* nulo;
public:
    nullNodo()
    {
        nulo = NULL;
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"Nullo");
    }

    char validaTipo(string ambito)
    {
        cout << "" << endl;
    }

    string generarCodigo()
    {
        return "";
    }
};

//R1 <programa> ::= <Definiciones>
class Programa_R1: public Nodo
{
protected:
    Nodo* definiciones;
public:
    Programa_R1(Pila &p)
    {
        ambito = "global";
        p.pop(); // estado
        definiciones = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Programa_R1>");
        definiciones->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Programa_R1>");
        validaTipo(ambito);
        tablaSimbolos->muestra();
        tablaError->muestra();
    }

    char validaTipo(string ambito)
    {
        definiciones->validaTipo(ambito);
    }

    string generarCodigo()
    {
        string encabezadoEnsamblador;

        encabezadoEnsamblador = ".386\n.model flat, stdcall\noption casemap:none\n";
        encabezadoEnsamblador += "include \\masm32\\macros\\macros.asm\ninclude \\masm32\\include\\masm32.inc\ninclude \\masm32\\include\\kernel32.inc\n";
        encabezadoEnsamblador += "includelib \\masm32\\lib\\masm32.lib\nincludelib \\masm32\\lib\\kernel32.lib\n\n";
        encabezadoEnsamblador += ".data\n";

        for (int i = 0; i < tablaSimbolos->dametamTabla(); i++)
        {
            if(tablaSimbolos->buscarSimbolo(tablaSimbolos->dameVariable(i),"global")->getFuncion())
                continue;// si es funcion no se agrega al .data
            else
                encabezadoEnsamblador += tablaSimbolos->dameVariable(i) + " dword 0\n" ;
        }

        encabezadoEnsamblador += "\n.code\n";
        encabezadoEnsamblador += definiciones->generarCodigo();
        cout << encabezadoEnsamblador  << endl;

        ofstream texto("STL2.asm");
        if(texto.is_open())
            texto << encabezadoEnsamblador ;
        texto.close();
        return encabezadoEnsamblador;
    }
};


//R3 <Definiciones> ::= <Definicion> <Definiciones>
class Definiciones_R3: public Nodo
{
protected:
    Nodo* definicion;
    Nodo* definiciones;
public:
    Definiciones_R3(Pila &p)
    {
        p.pop(); // elimino estado
        definicion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //elimino estado
        definiciones = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Definiciones_R3>");
        definicion->muestra(numeroTab+1);
        definiciones->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Definiciones_R3>");
    }

    char validaTipo(string ambito)
    {
        definiciones->validaTipo(ambito);
        definicion->validaTipo(ambito);
    }

    string generarCodigo()
    {
        string codigo;
        codigo = definiciones->generarCodigo();
        codigo += definicion->generarCodigo();
        return codigo;
    }
};

//R4 <Definicion> ::= <DefVar>
class Definicion_R4: public Nodo
{
protected:
    Nodo* defVar;
public:
    Definicion_R4(Pila &p)
    {
        p.pop(); // estado
        defVar = ((NoTerminal*)p.top())->getNodo(); // defVar
        delete(p.pop());
    }
    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Definicion_R4>");
        defVar->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Definicion_R4>");
    }
    char validaTipo(string ambito)
    {
        defVar->validaTipo(ambito);
    }
    string generarCodigo()
    {
        return defVar->generarCodigo();
    }
};

//R5 <Definicion> ::= <DefFunc>
class Definicion_R5: public Nodo
{
protected:
    Nodo* defFunc;
public:
    Definicion_R5(Pila &p)
    {
        p.pop();//estado
        defFunc = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Definicion_R5>");
        defFunc->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Definicion_R5>");
    }

    char validaTipo(string ambito)
    {
        defFunc->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return defFunc->generarCodigo();
    }
};

//R6 <DefVar> ::= tipo identificador <ListaVar> ;
class DefVar_R6: public Nodo
{
protected:
    string id;
    string tipo;
    Nodo* listaVar;
public:
    DefVar_R6(Pila& p)
    {
        p.pop(); // estado
        p.pop(); // punto coma
        p.pop(); // estado
        listaVar = (p.top())->getNodo(); // listavar
        delete(p.pop());
        p.pop(); // estado
        id = p.top()->getTerminal(); // id
        delete(p.pop());
        p.pop(); // estado
        tipo = p.top()->getTerminal(); // tipo
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<DefVar_R6>");
        tabsTerminal(numeroTab,tipo);
        tabsTerminal(numeroTab,id);
        listaVar->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</DefVar_R6>");
    }

    char validaTipo(string ambito)
    {
        if(!tablaSimbolos->buscarTablaSim(id,ambito))
        {
            tipoCh = tipo[0];
            Simbolo *s = new Simbolo(tipoCh,id,ambito,false);
            tablaSimbolos->insert(s);
        }
        else
            tablaError->insert(1,id);

        listaVar->validaTipo(tipoCh,ambito);
    }

    string generarCodigo()
    {
        return ""; // no se necesita declarar tipo
    }
};


//R8 <ListaVar> ::= , identificador <ListaVar>
class ListaVar_R8: public Nodo
{
protected:
    Nodo* listaVar;
    string id;
public:
    ListaVar_R8(Pila &p)
    {
        p.pop(); //estado
        listaVar =  ((NoTerminal*)p.top())->getNodo(); //listavar
        delete(p.pop());
        p.pop();// estado
        id = p.top()->getTerminal(); // id
        delete(p.pop());
        p.pop(); //estado
        p.pop(); //coma
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<ListaVar_R8>");
        tabsTerminal(numeroTab,id);
        listaVar->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</ListaVar_R8>");
    }

    void validaTipo(char tipoCh,string ambito)
    {
        //cout << "listaVar: R8" << endl;
        if(!tablaSimbolos->buscarTablaSim(id))
        {
            Simbolo *s = new Simbolo(tipoCh,id,ambito,false);
            tablaSimbolos->insert(s);
            //cout << "Se inserto a la tabla: " << id << endl;
        }
        else
            tablaError->insert(1,id);

        listaVar->validaTipo(tipoCh,ambito);
    }

    string generarCodigo()
    {
        return "";
    }
};

//R9 <DefFunc> ::= tipo identificador ( <Parametros> ) <BloqFunc>
class DefFunc_R9: public Nodo
{
protected:
    Nodo* parametros;
    Nodo* bloqFunc;
    string tipo;
    string id;
public:
    DefFunc_R9(Pila &p)
    {
        p.pop(); // estado
        bloqFunc = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        p.pop(); // )
        p.pop(); // estado
        parametros = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); // estado
        p.pop();// (
        p.pop(); // estado
        id = p.top()->getTerminal();
        delete(p.pop());
        p.pop();// estado
        tipo = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<DefFunc_R9>");
        tabsTerminal(numeroTab,tipo);
        tabsTerminal(numeroTab,id);
        parametros->muestra(numeroTab+1);
        bloqFunc->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</DefFunc_R9>");
    }

    char validaTipo(string ambito)
    {
        //cout << "defFunc: R9" << endl;
        if(!tablaSimbolos->buscarTablaSim(id))
        {
            for (int i = 0; i < 20; i++)
            {
                vectParametros[i]=0;
            }
            contParam=0;
            tipoCh = tipo[0];
            //cout << "Se inserto a la tabla: " << id << endl;
        }
        else
            tablaError->insert(1,id);

        parametros->validaTipo(id);
        Simbolo *s = new Simbolo(tipoCh,id,ambito,vectParametros,true);
        tablaSimbolos->insert(s);
        bloqFunc->validaTipo(id); /// en una funcion el mismo id sera su ambito
    }

    string generarCodigo()
    {
        string codigo;
        codigo = id+":\n";
        codigo += parametros->generarCodigo();
        codigo += bloqFunc->generarCodigo();
        codigo += "print str$(eax)\nprint chr$(10)\nexit\n";
        codigo += "end " + id + "\n";
        return codigo;
    }
};

//R11 <Parametros> ::= tipo identificador <ListaParam>
class Parametros_R11: public Nodo
{
protected:
    Nodo* listaParam;
    string id;
    string tipo;
public:
    Parametros_R11(Pila &p)
    {
        p.pop(); // estado
        listaParam = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); // estado
        id = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        tipo = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Parametros_R11>");
        tabsTerminal(numeroTab,tipo);
        tabsTerminal(numeroTab,id);
        listaParam->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Parametros_R11>");
    }

    char validaTipo(string ambito)
    {
        //cout << "parametros: R11"<<endl;
        if(!tablaSimbolos->buscarTablaSim(id,ambito))
        {
            tipoCh=tipo[0];
            Simbolo *s = new Simbolo(tipoCh,id,ambito,false);
            tablaSimbolos->insert(s);
            //cout << "Se inserto a la tabla: " << id << endl;
            vectParametros[contParam++]=tipoCh;
            //cout << "CONTADOR PARAMETROS uno: " << vectParametros << endl;
        }
        else
            tablaError->insert(1,id);

        listaParam->validaTipo(tipoCh,ambito);
    }


    string generarCodigo()
    {
        return listaParam->generarCodigo();
    }
};

//R13 <ListaParam> ::= , tipo identificador <ListaParam>
class ListaParam_R13: public Nodo
{
protected:
    Nodo* listaParam;
    string id;
    string tipo;
public:
    ListaParam_R13(Pila &p)
    {
        p.pop(); // estado
        listaParam = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); // estado
        id = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        tipo = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        p.pop(); // coma
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<ListaParam_R13>");
        tabsTerminal(numeroTab,tipo);
        tabsTerminal(numeroTab,id);
        listaParam->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</ListaParam_R13>");
    }

    void validaTipo(char tipoCh, string ambito)
    {
        //cout << "listaParam: R13" << endl;
        if(!tablaSimbolos->buscarTablaSim(id))
        {
            tipoCh = tipo[0];
            vectParametros[contParam++]=tipoCh;
            Simbolo *s = new Simbolo(tipoCh,id,ambito,false);
            tablaSimbolos->insert(s);
            //cout << "Se inserto a la tabla: " << id << endl;
        }
        else
            tablaError->insert(1,id);

        listaParam->validaTipo(tipoCh, ambito);

    }

    string generarCodigo()
    {
        return "";
    }
};

//R14 <BloqFunc> ::= { <DefLocales> }
class BloqFunc_R14: public Nodo
{
protected:
    Nodo* defLocales;
public:
    BloqFunc_R14(Pila &p)
    {
        p.pop(); //estado
        p.pop(); // }
        p.pop(); // estado
        defLocales = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); // estado
        p.pop();// {
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<BloqFunc_R14>");
        defLocales->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</BloqFunc_R14>");
    }

    char validaTipo(string ambito)
    {
        defLocales->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return defLocales->generarCodigo();
    }
};

//R16 <DefLocales> ::= <DefLocal> <DefLocales>
class DefLocales_R16: public Nodo
{
protected:
    Nodo* defLocal;
    Nodo* defLocales;
public:
    DefLocales_R16(Pila &p)
    {
        p.pop();// estado
        defLocales = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); // estado
        defLocal = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<DefLocales_R16>");
        defLocal->muestra(numeroTab+1);
        defLocales->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</DefLocales_R16>");
    }

    char validaTipo(string ambito) //necesario
    {
        defLocal->validaTipo(ambito);
        defLocales->validaTipo(ambito);
    }

    string generarCodigo()
    {
        string codigo;
        codigo = defLocal->generarCodigo();
        codigo += defLocales->generarCodigo();
        return codigo;
    }
};

//R17 <DefLocal> ::= <DefVar>
class DefLocal_R17: public Nodo
{
protected:
    Nodo* defVar;
public:
    DefLocal_R17(Pila &p)
    {
        p.pop(); // estado
        defVar = ((NoTerminal*)p.top())->getNodo(); // defVar
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<DefLocal_R17>");
        defVar->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</DefLocal_R17>");
    }

    char validaTipo(string ambito)
    {
        defVar->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return defVar->generarCodigo();
    }
};

//R18 <DefLocal> ::= <Sentencia>
class DefLocal_R18: public Nodo
{
protected:
    Nodo* sentencia;
public:
    DefLocal_R18(Pila &p)
    {
        p.pop();//estado
        sentencia = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<DefLocal_R18>");
        sentencia->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</DefLocal_R18>");
    }

    char validaTipo(string ambito)
    {
        sentencia->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return sentencia->generarCodigo();
    }
};

//R20 <Sentencias> ::= <Sentencia> <Sentencias>
class Sentencias_R20: public Nodo
{
protected:
    Nodo* sentencias;
    Nodo* sentencia;
public:
    Sentencias_R20(Pila &p)
    {
        p.pop();//estado
        sentencias = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        sentencia = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Sentencias_R20>");
        sentencia->muestra(numeroTab+1);
        sentencias->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Sentencias_R20>");
    }

    char validaTipo(string ambito)
    {
        sentencia->validaTipo(ambito);
        sentencias->validaTipo(ambito);
    }

    string generarCodigo()
    {
        string codigo;
        codigo = sentencia->generarCodigo();
        codigo += sentencias->generarCodigo();
        return codigo;
    }
};

//R21 <Sentencia> ::= identificador = <Expresion> ;
class Sentencia_R21: public Nodo
{
protected:
    Nodo* expresion;
    string id;
    string igual;
public:
    Sentencia_R21(Pila &p)
    {
        p.pop();//estado
        p.pop();// ;
        p.pop(); // estado
        expresion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        igual = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        id = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Sentencia_R21>");
        tabsTerminal(numeroTab,id);
        tabsTerminal(numeroTab,igual);
        expresion->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Sentencia_R21>");
    }

    char validaTipo(string ambito)
    {
        char tipoexp = expresion->validaTipo(ambito);
        cout << "\t\tTIPOS:  " << tipoexp << " vs " << tablaSimbolos->dameTipo(id,ambito) << endl;
        if(tablaSimbolos->buscarTablaSim(id) == false) // si no esta en la tabla
        {
            tablaError->insert(2,id); // Error: variable NO declarada
        }
        else if(tipoexp == tablaSimbolos->dameTipo(id,ambito))
        {
            cout << "la sentencia 21 es del mismo tipo " << tipoexp << "\n\n" << endl;
            return tipoexp;
        }
        else if((tablaSimbolos->dameTipo(id,"global") !='@') && (tablaSimbolos->dameTipo(id,"global")==tipoexp) )
        {
            cout << "la sentencia 21 es del mismo tipo  se usa una global " << tipoexp << "\n\n" << endl;
            return tipoexp;
        }
        else
            tablaError->insert(4,id);
    }

    string generarCodigo()
    {
        string codigo;
        codigo = expresion->generarCodigo();
        codigo += "pop eax\nmov " + id + ", eax\n";
        return codigo;
    }
};

//R22 <Sentencia> ::= if ( <Expresion> ) <SentenciaBloque> <Otro>
class Sentencia_R22: public Nodo
{
protected:
    Nodo* otro;
    Nodo* sentenciaBloque;
    Nodo* expresion;
    string ifS;
public:
    Sentencia_R22(Pila &p)
    {
        p.pop();//estado
        otro = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        sentenciaBloque = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        p.pop();// )
        p.pop();//estado
        expresion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        p.pop();//(
        p.pop();//estado
        ifS = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Sentencia_R22>");
        tabsTerminal(numeroTab,ifS);
        expresion->muestra(numeroTab+1);
        sentenciaBloque->muestra(numeroTab+1);
        otro->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Sentencia_R22>");
    }

    char validaTipo(string ambito)
    {
        expresion->validaTipo(ambito);
        sentenciaBloque->validaTipo(ambito);
        otro->validaTipo(ambito);
    }

    string generarCodigo()
    {

        contador++;
        string codigo, labelI; // se puede implementar

        codigo = expresion->generarCodigo();
        codigo += "pop eax\ncmp eax,0\n";
        codigo += "je If_" + getLabelNumber() + "\n";

        labelI = "If_" + getLabelNumber();

        codigo += sentenciaBloque->generarCodigo();
        codigo += labelI + ":\n";
        codigo += otro->generarCodigo();
        return codigo;
    }
};

//R23 <Sentencia> ::= while ( <Expresion> ) <Bloque>
class Sentencia_R23: public Nodo
{
protected:
    Nodo* bloque;
    Nodo* expresion;
    string whileS;
public:
    Sentencia_R23(Pila &p)
    {
        p.pop();//estado
        bloque = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        p.pop(); // )
        p.pop();//estado
        expresion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        p.pop();//(
        p.pop();//estado
        whileS = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Sentencia_R23>");
        tabsTerminal(numeroTab,whileS);
        expresion->muestra(numeroTab+1);
        bloque->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Sentencia_R23>");
    }

    char validaTipo(string ambito)
    {
        expresion->validaTipo(ambito);
        bloque->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return "";
    }
};

//R24 <Sentencia> ::= return <ValorRegresa> ;
class Sentencia_R24: public Nodo
{
protected:
    Nodo* valorRegresa;
    string returnS;
public:
    Sentencia_R24(Pila &p)
    {
        p.pop();//estado
        p.pop();//;
        p.pop();//estado
        valorRegresa = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        returnS = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Sentencia_R24>");
        tabsTerminal(numeroTab,returnS);
        valorRegresa->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Sentencia_R24>");
    }

    char validaTipo(string ambito)
    {
        char valReg = valorRegresa->validaTipo(ambito);
        if(valReg != tablaSimbolos->dameTipo(ambito,"global"))
            tablaError->insert(6,"");
    }

    string generarCodigo()
    {
        return "ret\n";
    }
};

//R25 <Sentencia> ::= <LlamadaFunc> ;
class Sentencia_R25: public Nodo
{
protected:
    Nodo* llamadaFunc;
public:
    Sentencia_R25(Pila &p)
    {
        p.pop();//estado
        p.pop();//;
        p.pop();//estado
        llamadaFunc = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Sentencia_R25>");
        llamadaFunc->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Sentencia_R25>");
    }

    char validaTipo(string ambito)
    {
        llamadaFunc->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return llamadaFunc->generarCodigo();
    }
};

//R27 <Otro> ::= else <SentenciaBloque>
class Otro_R27: public Nodo
{
protected:
    Nodo* sentenciaBloque;
    string elseS;
public:
    Otro_R27(Pila &p)
    {
        p.pop();//estado
        sentenciaBloque = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        elseS = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Otro_R27>");
        tabsTerminal(numeroTab,elseS);
        sentenciaBloque->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Otro_R27>");
    }

    char validaTipo(string ambito)
    {
        sentenciaBloque->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return sentenciaBloque->generarCodigo();
    }
};

//R28 <Bloque> ::= { <Sentencias> }
class Bloque_R28: public Nodo
{
protected:
    Nodo* sentencias;
public:
    Bloque_R28(Pila &p)
    {
        p.pop();//estado
        p.pop();//}
        p.pop();//estado
        sentencias = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        p.pop();//{
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Bloque_R28>");
        sentencias->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Bloque_R28>");
    }

    char validaTipo(string ambito)
    {
        return sentencias->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return sentencias->generarCodigo();
    }
};

//R30 <ValorRegresa> ::= <Expresion>
class ValorRegresa_R30: public Nodo
{
protected:
    Nodo* expresion;
public:
    ValorRegresa_R30(Pila &p)
    {
        p.pop();//estado
        expresion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<ValorRegresa_R30>");
        expresion->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</ValorRegresa_R30>");
    }

    char validaTipo(string ambito)
    {
        return expresion->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return expresion->generarCodigo();
    }
};

//R32 <Argumentos> ::= <Expresion> <ListaArgumentos>
class Argumentos_R32: public Nodo
{
protected:
    Nodo* listaArgumentos;
    Nodo* expresion;
public:
    Argumentos_R32(Pila &p)
    {
        p.pop();//estado
        listaArgumentos = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        expresion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Argumentos_R32>");
        expresion->muestra(numeroTab+1);
        listaArgumentos->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Argumentos_R32>");
    }

    char validaTipo(string ambito)
    {
        char tipoExpresion = expresion->validaTipo(ambito);
        vectArgumentos[contArgs++]= tipoExpresion;
        listaArgumentos->validaTipo(ambito);
    }

    string generarCodigo()
    {
        string codigo;
        codigo = expresion->generarCodigo();
        codigo += listaArgumentos->generarCodigo();
        return codigo;
    }
};

//R34 <ListaArgumentos> ::= , <Expresion> <ListaArgumentos>
class ListaArgumentos_R34: public Nodo
{
protected:
    Nodo* listaArgumentos;
    Nodo* expresion;
public:
    ListaArgumentos_R34(Pila &p)
    {
        p.pop();// estado
        listaArgumentos = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        expresion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        p.pop();//,
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<ListaArgumentos_R34>");
        expresion->muestra(numeroTab+1);
        listaArgumentos->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</ListaArgumentos_R34>");
    }

    char validaTipo(string ambito)
    {
        char tipoExpresion= expresion->validaTipo(ambito);
        vectArgumentos[contArgs++]= tipoExpresion;
        listaArgumentos->validaTipo(ambito);
    }

    string generarCodigo()
    {
        string codigo;
        codigo = expresion->generarCodigo();
        codigo += listaArgumentos->generarCodigo();
        return codigo;
    }
};

//R35 <Termino> ::= <LlamadaFunc>
class Termino_R35: public Nodo
{
protected:
    Nodo* llamadaFunc;
public:
    Termino_R35(Pila &p)
    {
        p.pop(); //estado
        llamadaFunc = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }
    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Termino_R35>");
        llamadaFunc->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Termino_R35>");
    }

    char validaTipo(string ambito)
    {
        return llamadaFunc->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return llamadaFunc->generarCodigo();
    }
};


//R36 <Termino> ::= identificador
class Termino_R36: public Nodo
{
protected:
    string id;
public:
    Termino_R36(Pila &p)
    {
        p.pop(); //estado
        id = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab, "<Termino_R36>");
        tabsTerminal(numeroTab, id);
        tabuladorNombre(numeroTab, "</Termino_R36>");
    }

    char validaTipo(string ambito)
    {
        //cout << "\n\nbusco a: " << id << " con ambito: " << ambito << endl;
        if(!tablaSimbolos->buscarTablaSim(id,ambito))
        {
            if(tablaSimbolos->buscarTablaSim(id,"global"))
            {
                cout << "tipo de Termino_R36:  "<< id << " "  << tablaSimbolos->dameTipo(id,"global")<< endl;
                return tablaSimbolos->dameTipo(id,"global");
            }
            else
                tablaError->insert(2,id);
        }
        cout << "tipo de Termino R36:  "<< id << " "  << tablaSimbolos->dameTipo(id,ambito)<< endl;
        return tablaSimbolos->dameTipo(id,ambito);
    }

    string generarCodigo()
    {
        return "push "+id+"\n";
    }
};

//R37 <Termino> ::= entero
class Termino_R37: public Nodo
{
protected:
    string entero;
public:
    Termino_R37(Pila &p)
    {
        p.pop();//estado
        entero = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Termino_R37>");
        tabsTerminal(numeroTab,entero);
        tabuladorNombre(numeroTab,"</Termino_R37>");
    }

    char validaTipo(string ambito)
    {
        if(!tablaSimbolos->buscarTablaSim(entero,ambito))
        {
            cout << "tipo de Termino_R37:  "<< entero << " "  << 'i' << endl;
            return 'i';
        }
    }

    string generarCodigo()
    {
        return "push "+ entero+ "\n";
    }
};

//R38 <Termino> ::= real
class Termino_R38: public Nodo
{
protected:
    string real;
public:
    Termino_R38(Pila &p)
    {
        p.pop();//estado
        real = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Termino_R37>");
        tabsTerminal(numeroTab,real);
        tabuladorNombre(numeroTab,"</Termino_R37>");
    }

    char validaTipo(string ambito)
    {
        if(!tablaSimbolos->buscarTablaSim(real,ambito))
        {
            cout << "tipo de Termino_R38:  "<< real << " "  << 'f' << endl;
            return 'f';
        }
    }

    string generarCodigo()
    {
        return "push "+ real+ "\n";
    }
};

//R39 <Termino> ::= cadena
class Termino_R39: public Nodo
{
protected:
    string cadena;
public:
    Termino_R39(Pila &p)
    {
        p.pop();//estado
        cadena = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Termino_R39>");
        tabsTerminal(numeroTab,cadena);
        tabuladorNombre(numeroTab,"</Termino_R39>");
    }

    char validaTipo(string ambito)
    {
        if(!tablaSimbolos->buscarTablaSim(cadena,ambito))
        {
            cout << "tipo de Termino R39:  "<< cadena << " "  << 's' << endl;
            return 's';
        }
    }

    string generarCodigo()
    {
        return "push"+ cadena + "\n";
    }
};

//R40 <LlamadaFunc> ::= identificador ( <Argumentos> )
class LlamadaFunc_R40: public Nodo
{
protected:
    Nodo* argumentos;
    string id;
public:
    LlamadaFunc_R40(Pila &p)
    {
        p.pop();//estado
        p.pop();//)
        p.pop();//estado
        argumentos = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop();//estado
        p.pop();//(
        p.pop();//estado
        id = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<LlamadaFunc_R40>");
        tabsTerminal(numeroTab,id);
        argumentos->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</LlamadaFunc_R40>");
    }

    char validaTipo(string ambito)
    {

        for (int i = 0; i < 20; i++)
        {
            vectArgumentos[i]=0;
        }
        contArgs=0;

        if(tablaSimbolos->buscarTablaSim(id,"global"))
        {
            argumentos->validaTipo(ambito);
            //checando cantidad de argumentos
            int cantidadFinalParam = tablaSimbolos->buscarSimbolo(id,ambito)->getNumParam();
            if(cantidadFinalParam != contArgs)
                tablaError->insert(7,id);
            else
            {
                //checando que cada parametro sea del mismo tipo que el argumento
                for (int i = 0; i < cantidadFinalParam; i++)
                {
                    if(tablaSimbolos->buscarSimbolo(id,ambito)->getVectorParametro(i) !=vectArgumentos[i])
                        tablaError->insert(8,id);
                }

            }
            return tablaSimbolos->dameTipo(id,"global");
        }
        else
            tablaError->insert(5,id);
    }

    string generarCodigo()
    {
        return "";
    }
};

//R41 <SentenciaBloque> ::= <Sentencia>
class SentenciaBloque_R41: public Nodo
{
protected:
    Nodo* sentencia;
public:
    SentenciaBloque_R41(Pila &p)
    {
        p.pop();//estado
        sentencia = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<SentenciaBloque_R41>");
        sentencia->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</SentenciaBloque_R41>");
    }

    char validaTipo(string ambito)
    {
        return sentencia->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return sentencia->generarCodigo();
    }
};

//R42 <SentenciaBloque> ::= <Bloque>
class SentenciaBloque_R42: public Nodo
{
protected:
    Nodo* bloque;
public:
    SentenciaBloque_R42(Pila &p)
    {
        p.pop();//estado
        bloque = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<SentenciaBloque R42>");
        bloque->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</SentenciaBloque R42>");
    }

    char validaTipo(string ambito)
    {
        return bloque->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return bloque->generarCodigo();
    }
};

//R43 <Expresion> ::= ( <Expresion> )
class Expresion_R43: public Nodo
{
protected:
    Nodo* expresion;
public:
    Expresion_R43(Pila &p)
    {
        p.pop(); // estado
        p.pop(); // )
        p.pop(); // estado
        expresion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        p.pop();//(
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R43>");
        expresion->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R43>");
    }

    char validaTipo(string ambito)
    {
        return expresion->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return expresion->generarCodigo();
    }
};

//R44 <Expresion> ::= opSuma <Expresion>
class Expresion_R44: public Nodo
{
protected:
    Nodo* expresion;
    string opSuma;
public:
    Expresion_R44(Pila &p)
    {
        p.pop(); // estado
        expresion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        opSuma = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R44>");
        tabsTerminal(numeroTab,opSuma);
        expresion->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R44>");
    }

    char validaTipo(string ambito)
    {
        return expresion->validaTipo(ambito);
    }

    string generarCodigo()
    {
        string codigo;
        codigo = expresion->generarCodigo();
        if(opSuma == "-")
            codigo += "pop eax\nneg eax\npush eax\n";
        return codigo;
    }
};

//R45 <Expresion> ::= opNot <Expresion>
class Expresion_R45: public Nodo
{
protected:
    Nodo* expresion;
    string opNot;
public:
    Expresion_R45(Pila &p)
    {
        p.pop(); // estado
        expresion = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        opNot = p.top()->getTerminal();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R45>");
        tabsTerminal(numeroTab,opNot);
        expresion->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R45>");
    }

    char validaTipo(string ambito)
    {
        return expresion->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return expresion->generarCodigo();
    }
};

//R46 <Expresion> ::= <Expresion> opMul <Expresion>
class Expresion_R46: public Nodo
{
protected:
    Nodo* expresionDer;
    string opMul;
    Nodo* expresionIzq;
public:
    Expresion_R46(Pila &p)
    {
        p.pop(); // estado
        expresionDer = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        opMul = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        expresionIzq = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R46>");
        expresionIzq->muestra(numeroTab+1);
        tabsTerminal(numeroTab,opMul);
        expresionDer->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R46>");
    }

    char validaTipo(string ambito)
    {
        char tipoizq = expresionIzq->validaTipo(ambito);
        char tipoder = expresionDer->validaTipo(ambito);
        if(tipoizq == tipoder)
        {
            cout << "expresion 46 son del mismo tipo \n" <<  endl;
            return tipoder;
        }
        else
            tablaError->insert(3,"");
    }

    string generarCodigo()
    {
        string codigo;
        codigo = expresionIzq->generarCodigo();
        codigo += expresionDer->generarCodigo();
        if(opMul == "*")
            codigo += "pop ebx\npop eax\nxor edx,edx\nimul ebx\npush eax\n";
        else
            codigo += "pop ebx\npop eax\nxor edx,edx\nidiv ebx\npush eax\n";
        return codigo;
    }
};

//R47 <Expresion> ::= <Expresion> opSuma <Expresion>
class Expresion_R47: public Nodo
{
protected:
    Nodo* expresionDer;
    string opSuma;
    Nodo* expresionIzq;
public:
    Expresion_R47(Pila &p)
    {
        p.pop(); // estado
        expresionDer = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        opSuma = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        expresionIzq = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R47>");
        expresionIzq->muestra(numeroTab+1);
        tabsTerminal(numeroTab,opSuma);
        expresionDer->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R47>");
    }

    char validaTipo(string ambito)
    {
        char tipoizq = expresionIzq->validaTipo(ambito);
        char tipoder = expresionDer->validaTipo(ambito);

        if(tipoizq == tipoder)
        {
            cout << "expresion 47 son del mismo tipo \n" <<  endl;
            return tipoder;
        }
        else
            tablaError->insert(3,"");
    }

    string generarCodigo()
    {
        string codigo;
        codigo = expresionIzq->generarCodigo();
        codigo += expresionDer->generarCodigo();
        if(opSuma == "+")
            codigo += "pop ebx\npop eax\nadd eax, ebx\npush eax\n";
        else
            codigo += "pop ebx\npop eax\nsub eax, ebx\npush eax\n";
        return codigo;
    }
};

//R48 <Expresion> ::= <Expresion> opRelac <Expresion>
class Expresion_R48: public Nodo
{
protected:
    Nodo* expresionDer;
    string opRelac;
    Nodo* expresionIzq;
public:
    Expresion_R48(Pila &p)
    {
        p.pop(); // estado
        expresionDer = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        opRelac = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        expresionIzq = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R48>");
        expresionIzq->muestra(numeroTab+1);
        tabsTerminal(numeroTab,opRelac);
        expresionDer->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R48>");
    }

    char validaTipo(string ambito)
    {
        char tipoizq = expresionIzq->validaTipo(ambito);
        char tipoder = expresionDer->validaTipo(ambito);
        if(tipoizq == tipoder)
        {
            cout << "expresion 48 son del mismo tipo \n" <<  endl;
            return tipoder;
        }
        else
            tablaError->insert(3,"");
    }

    string generarCodigo()
    {
        string codigo;
        contador++;

        codigo = expresionIzq->generarCodigo();
        codigo += expresionDer->generarCodigo();
        codigo += "pop ebx\npop eax\n";
        codigo += "cmp eax, ebx\n";
        codigo += getSaltoIgualdad(opRelac) + " True_" + getLabelNumber() + "\n";
        codigo += "push 0\njmp End_" + getLabelNumber() + "\n";
        codigo += "True_"+ getLabelNumber() + ":\n";
        codigo += "push 1\n";
        codigo += "End_"+ getLabelNumber() + ":";

        return codigo;
    }
};

//R49 <Expresion> ::= <Expresion> == <Expresion>
class Expresion_R49: public Nodo
{
protected:
    Nodo* expresionDer;
    string opIgualdad;
    Nodo* expresionIzq;
public:
    Expresion_R49(Pila &p)
    {
        p.pop(); // estado
        expresionDer = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        opIgualdad = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        expresionIzq = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R49>");
        expresionIzq->muestra(numeroTab+1);
        tabsTerminal(numeroTab,opIgualdad);
        expresionDer->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R49>");
    }

    char validaTipo(string ambito)
    {
        char tipoizq = expresionIzq->validaTipo(ambito);
        char tipoder = expresionDer->validaTipo(ambito);

        if(tipoizq == tipoder)
        {
            cout << "expresion 49 son del mismo tipo \n" <<  endl;
            return tipoder;
        }
        else
            tablaError->insert(3,"");
    }

    string generarCodigo()
    {
        return ""; // se puede implementar
    }
};

//R50 <Expresion> ::= <Expresion> && <Expresion>
class Expresion_R50: public Nodo
{
protected:
    Nodo* expresionDer;
    string opAnd;
    Nodo* expresionIzq;
public:
    Expresion_R50(Pila &p)
    {
        p.pop(); // estado
        expresionDer = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        opAnd = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        expresionIzq = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R50>");
        expresionIzq->muestra(numeroTab+1);
        tabsTerminal(numeroTab,opAnd);
        expresionDer->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R50>");
    }

    char validaTipo(string ambito)
    {
        char tipoizq = expresionIzq->validaTipo(ambito);
        char tipoder = expresionDer->validaTipo(ambito);

        if(tipoizq == tipoder)
        {
            cout << "expresion 50 son del mismo tipo \n" <<  endl;
            return tipoder;
        }
        else
            tablaError->insert(3,"");
    }

    string generarCodigo()
    {
        return "";
    }
};

//R51 <Expresion> ::= <Expresion> | <Expresion>
class Expresion_R51: public Nodo
{
protected:
    Nodo* expresionDer;
    string opOr;
    Nodo* expresionIzq;
public:
    Expresion_R51(Pila &p)
    {
        p.pop(); // estado
        expresionDer = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
        p.pop(); //estado
        opOr = p.top()->getTerminal();
        delete(p.pop());
        p.pop(); // estado
        expresionIzq = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R51>");
        expresionIzq->muestra(numeroTab+1);
        tabsTerminal(numeroTab,opOr);
        expresionDer->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R51>");
    }

    char validaTipo(string ambito)
    {
        char tipoizq = expresionIzq->validaTipo(ambito);
        char tipoder = expresionDer->validaTipo(ambito);

        if(tipoizq == tipoder)
        {
            cout << "expresion 51 son del mismo tipo \n" <<  endl;
            return tipoder;
        }
        else
            tablaError->insert(3,"");
    }

    string generarCodigo()
    {
        return "";
    }
};


//R52 <Expresion> ::= <Termino>
class Expresion_R52: public Nodo
{
protected:
    Nodo* termino;
public:
    Expresion_R52(Pila &p)
    {
        p.pop();// estado;
        termino = ((NoTerminal*)p.top())->getNodo();
        delete(p.pop());
    }

    void muestra(int numeroTab)
    {
        tabuladorNombre(numeroTab,"<Expresion_R52>");
        termino->muestra(numeroTab+1);
        tabuladorNombre(numeroTab,"</Expresion_R52>");
    }

    char validaTipo(string ambito)
    {
        return termino->validaTipo(ambito);
    }

    string generarCodigo()
    {
        return termino->generarCodigo();
    }
};

#endif
