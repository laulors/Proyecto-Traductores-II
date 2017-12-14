#include "TablaErrores.h"
using namespace std;

TablaErrores::TablaErrores() {}

void TablaErrores::insert(int error, string id)
{
    string errorStr="";
    switch(error)
    {
    case 1:
        cout << "\tERROR 1: \""<< id << "\""" Esta variable ya esta repetida" << endl;
        errorStr = "\tERROR 1: \"" + id + "\""" Esta variable ya esta definida";
        break;
    case 2:
        cout << "\tERROR 2: \"" << id << "\""" Esta variable no se ha declarado anteriormente " << endl;
        errorStr = "\tERROR 2: \"" + id + "\""" Esta variable no se ha declarado anteriormente ";
        break;
    case 3:
        cout << "\tERROR 3: La expresion NO fue del mismo tipo " << endl;
        errorStr = "\tERROR 3: La expresion NO fue del mismo tipo ";
        break;
    case 4:
        cout << "\tERROR 4: La expresion NO fue del mismo tipo de dato que: " << id << endl;
        errorStr = "\tERROR 4: La expresion NO fue del mismo tipo de dato que: " + id ;
        break;
    case 5:
        cout << "\tERROR 5: \""<< id << "\""" Esta funcion no se ha declarado anteriormente" << endl;
        errorStr = "\tERROR 5: \"" + id + "\""" Esta funcion no se ha declarado anteriormente";
        break;
    case 6:
        cout << "\tERROR 6: \""<< id << "\""" El Valor Regresa NO es del mismo tipo que la funcion" << endl;
        errorStr = "\tERROR 6: \"" + id + "\"""  El Valor Regresa NO es del mismo tipo que la funcion";
        break;
    case 7:
        cout << "\tERROR 7: \""<< id << "\""" No hay suficientes argumentos para la definicion de la funcion" << endl;
        errorStr = "\tERROR 7: \"" + id + "\""" No hay suficientes argumentos para la definicion de la funcion";
        break;
    case 8:
        cout << "\tERROR 8: \""<< id << "\""" La llamada a funcion no concuerda en argumentos con la declaracion de la Funcion " << endl;
        errorStr = "\tERROR 8: \"" + id + "\""" La llamada a funcion no concuerda en argumentos con la declaracion de la Funcion ";
        break;

    }
    vectorErrores.push_back(errorStr);
}

void TablaErrores::muestra()
{
    cout << endl;
    cout << " ~~~~~~~~~~~~ Tabla Errores ~~~~~~~~~~~ " << endl;
    for (int i = 0; i < vectorErrores.size(); i++)
        cout << vectorErrores[i] << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl;
}
