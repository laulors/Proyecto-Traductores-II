#include "Lexico.h"

Lexico::Lexico(string fuente)
{
    ind = 0;
    this->fuente = fuente;
}

Lexico::Lexico()
{
    ind = 0;
}

string Lexico::tipoAcad(int tipo)
{
    string cad = "";

    switch (tipo)
    {
    case TipoSimbolo::IDENTIFICADOR:
        cad = "Identificador";
        break;

    case TipoSimbolo::ENTERO:
        cad = "Entero";
        break;

    case TipoSimbolo::REAL:
        cad = "Real";
        break;

    case TipoSimbolo::CADENA:
        cad = "Cadena";
        break;

    case TipoSimbolo::TIPO:
        cad = "Tipo de Dato";
        break;

    case TipoSimbolo::OPADIC:
        cad = "Op. Adicion";
        break;

    case TipoSimbolo::OPMULT:
        cad = "Op. Multiplicacion";
        break;

    case TipoSimbolo::OPRELAC:
        cad = "Op. Relacional";
        break;

    case TipoSimbolo::OPOR:
        cad = "Op. OR";
        break;

    case TipoSimbolo::OPAND:
        cad = "Op. AND";
        break;

    case TipoSimbolo::OPNOT:
        cad = "Op. Not";
        break;

    case TipoSimbolo::OPIGUALDAD:
        cad = "Op. Igualdad";
        break;

    case TipoSimbolo::PESOS:
        cad = "Fin de la Entrada";
        break;

    case TipoSimbolo::PUNTO_COMA:
        cad = "Punto y Coma";
        break;

    case TipoSimbolo::COMA:
        cad = "Coma";
        break;

    case TipoSimbolo::PARENT_IZQ:
        cad = "Parentesis Izquierdo";
        break;

    case TipoSimbolo::PARENT_DER:
        cad = "Parentesis Derecho";
        break;

    case TipoSimbolo::LLAVE_IZQ:
        cad = "Llave Izquierda";
        break;

    case TipoSimbolo::LLAVE_DER:
        cad = "Llave Derecha";
        break;

    case TipoSimbolo::ASIGNACION:
        cad = "Asignacion";
        break;

    case TipoSimbolo::IF:
        cad = "Reservada IF";
        break;

    case TipoSimbolo::WHILE:
        cad = "Reservada WHILE";
        break;

    case TipoSimbolo::RETURN:
        cad = "Reservada RETURN";
        break;

    case TipoSimbolo::ELSE:
        cad = "Reservada ELSE";
        break;

    }
    return cad;
}

void Lexico::entrada(string archivo)
{
    ifstream file(archivo);
    char cadena[1000];

    if (!file.good())
    {
        cout << "Error al leer el archivo!!!" << endl;
    }
    else
    {
        file.getline((char*)&cadena, 1000, file.eof());
        file.close();
    }

    ind = 0;
    this->fuente = (char*)cadena;
    cout << cadena << endl << endl;
}

int Lexico::sigSimbolo()
{
    estado = 0;
    continua = true;
    simbolo = "";

    while (continua)
    {
        c = sigCaracter();

        switch (estado)
        {
        case 0:
        {
            if (esLetra(c)) sigEstado(21);
            else if (c == '\"') sigEstado(22);
            else if (esDigito(c)) sigEstado(1);
            else if (c == '+' || c == '-') aceptacion(6);
            else if (c == '*' || c == '/') aceptacion(7);
            else if (c == '<' || c == '>') sigEstado(4);
            else if (c == '|') sigEstado(8);
            else if (c == '&') sigEstado(10);
            else if (c == '!') sigEstado(12);
            else if (c == '=') sigEstado(14);
            else if (c == ';') aceptacion(15);
            else if (c == ',') aceptacion(16);
            else if (c == '(') aceptacion(17);
            else if (c == ')') aceptacion(18);
            else if (c == '{') aceptacion(19);
            else if (c == '}') aceptacion(20);
            else if (c == '$') aceptacion(23);
            else
            {
                if (c != ' ' && c != '\t' &&  c != '\n')
                {
                    return -1; // si no es espacios entonces    ha de ser un simbolo invalido
                }
            }
        }
        break;

        case 1:
        {
            if (esDigito(c)) sigEstado(1);
            else if (c == '.') sigEstado(2);
            else
            {
                retroceso();
            }
        }
        break;
        case 2:
        {
            if (esDigito(c)) sigEstado(3);
        }
        break;

        case 3:
        {
            if (esDigito(c)) sigEstado(3);
            else
            {
                retroceso();
            }
        }
        break;

        case 4:
        {
            if (c == '=') sigEstado(5);
            else
            {
                retroceso();
            }
        }
        break;

        case 5:
        {
            retroceso();
        }
        break;

        case 8:
        {
            if (c == '|') sigEstado(9);
        }
        break;

        case 9:
        {
            retroceso();
        }
        break;

        case 10:
        {
            if (c == '&') sigEstado(11);
        }
        break;

        case 11:
        {
            retroceso();
        }
        break;

        case 12:
        {
            if (c == '=') sigEstado(13);
            else
            {
                retroceso();
            }
        }
        break;

        case 13:
        {
            retroceso();
        }
        break;

        case 14:
        {
            if (c == '=') sigEstado(13);
            else
            {
                retroceso();
            }
        }

        break;

        case 21:
        {
            if (esLetra(c) || esDigito(c)) sigEstado(21);
            else
            {
                retroceso();
            }
        }
        break;

        case 22:
        {
            if (esLetra(c) || esDigito(c) || esEspacio(c)) sigEstado(23);
        }
        break;

        case 23:
        {
            if (esLetra(c) || esDigito(c) || esEspacio(c)) sigEstado(23);
            else
            {
                if (c == '\"') sigEstado(24);
            }
        }
        break;

        case 24:
        {
            retroceso();
        }
        break;

        default:
            ;
            break;
        }
    }
    //Fin del Automata

    switch (estado)
    {
    case 1:
    {
        tipo = TipoSimbolo::ENTERO;
    }
    break;
    case 3:
    {
        tipo = TipoSimbolo::REAL;
    }
    break;
    case 4:
    {
        tipo = TipoSimbolo::OPRELAC;
    }
    break;
    case 5:
    {
        tipo = TipoSimbolo::OPRELAC;
    }
    break;
    case 6:
    {
        tipo = TipoSimbolo::OPADIC;
    }
    break;
    case 7:
    {
        tipo = TipoSimbolo::OPMULT;
    }
    break;
    case 9:
    {
        tipo = TipoSimbolo::OPOR;
    }
    break;
    case 11:
    {
        tipo = TipoSimbolo::OPAND;
    }
    break;
    case 12:
    {
        tipo = TipoSimbolo::OPNOT;
    }
    break;
    case 13:
    {
        tipo = TipoSimbolo::OPIGUALDAD;
    }
    break;
    case 14:
    {
        tipo = TipoSimbolo::ASIGNACION;
    }
    break;
    case 15:
    {
        tipo = TipoSimbolo::PUNTO_COMA;
    }
    break;
    case 16:
    {
        tipo = TipoSimbolo::COMA;
    }
    break;
    case 17:
    {
        tipo = TipoSimbolo::PARENT_IZQ;
    }
    break;
    case 18:
    {
        tipo = TipoSimbolo::PARENT_DER;
    }
    break;
    case 19:
    {
        tipo = TipoSimbolo::LLAVE_IZQ;
    }
    break;
    case 20:
    {
        tipo = TipoSimbolo::LLAVE_DER;
    }
    break;
    case 21:
    {
        if (simbolo == "int" || simbolo == "float" || simbolo == "void" || simbolo == "string")
            tipo = TipoSimbolo::TIPO;
        else if (simbolo == "if") tipo = TipoSimbolo::IF;
        else if (simbolo == "while") tipo = TipoSimbolo::WHILE;
        else if (simbolo == "return") tipo = TipoSimbolo::RETURN;
        else if (simbolo == "else") tipo = TipoSimbolo::ELSE;
        else tipo = TipoSimbolo::IDENTIFICADOR;
    }
    break;
    case 23:
    {
        tipo = TipoSimbolo::PESOS;
    }
    break;
    case 24:
    {
        tipo = TipoSimbolo::CADENA;
    }
    break;
    default:
    {
        tipo = TipoSimbolo::ERROR;
    }
    break;
    }

    return tipo;
}

char Lexico::sigCaracter()
{
    if (terminado()) return '$';

    return fuente[ind++];
}

void Lexico::sigEstado(int estado)
{
    this->estado = estado;
    simbolo += c;
}

void Lexico::aceptacion(int estado)
{
    sigEstado(estado);
    continua = false;
}

bool Lexico::terminado()
{
    return ind >= fuente.length();
}

bool Lexico::esLetra(char c)
{
    return isalpha(c) || c == '_';
}


bool Lexico::esDigito(char c)
{
    return isdigit(c);
}

bool Lexico::esEspacio(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}


void Lexico::retroceso()
{
    if (c != '$') ind--;
    continua = false;
}
