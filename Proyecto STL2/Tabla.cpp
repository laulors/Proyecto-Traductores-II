#include "Tabla.h"

Tabla::Tabla()
{
    filas = columnas = 0;
}

void Tabla::leerArchivo(char* nombreArchivo)
{
    long int longIntAux;
    char *end;
    int tamLinea, numeroTemp;
    bool bandera =  false;
    string contenidoArchivo;
    locale local;
    ifstream archivo(nombreArchivo);

    getline(archivo,contenidoArchivo,'\n');
    tamLinea = atoi(contenidoArchivo.c_str());
    numeroTemp = tamLinea ;
    reglas.push_back(tamLinea);

    for (int i = 0; i < numeroTemp; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(j == 2)
            {
                getline(archivo,contenidoArchivo,'\n');
                longIntAux = strtol(contenidoArchivo.c_str(),&end,10);
                if(end == contenidoArchivo)
                    noTerminalesAux.push_back(contenidoArchivo);

                continue;
            }
            getline(archivo,contenidoArchivo,'\t');
            if(archivo.eof())
                break;
            tamLinea = atoi(contenidoArchivo.c_str());
            reglas.push_back(tamLinea);
        }
    }

    getline(archivo,contenidoArchivo,'\t');
    filas = atoi(contenidoArchivo.c_str());
    getline(archivo,contenidoArchivo,'\n');
    columnas = atoi(contenidoArchivo.c_str());

    for(int i = 0; i < filas ; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if(j == columnas - 1)
            {
                getline(archivo,contenidoArchivo,'\n');
                tamLinea = atoi(contenidoArchivo.c_str());
                matrizNumeros.push_back(tamLinea);
                continue;
            }
            getline(archivo,contenidoArchivo,'\t');
            tamLinea = atoi(contenidoArchivo.c_str());
            matrizNumeros.push_back(tamLinea);
        }
    }
    archivo.close();
    acomodarValores();
}

void Tabla::acomodarValores()
{
    cantReglas = reglas[0];

    idReglas.resize(cantReglas);
    lonReglas.resize(cantReglas);
    noTerminales.resize(cantReglas);
    matriz.resize(filas);

    for (int i = 0; i < filas; i++)
        matriz[i].resize(columnas);

    for (int i = 0 ; i < cantReglas ; i++)
        idReglas[i] = reglas[(2*i)+1];

    for (int i = 0; i < cantReglas ; i++)
        lonReglas[i] = reglas[(2*i)+2];

    int cont = 0;
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matriz[i][j] = matrizNumeros[cont];
            cont++;
        }
    }
}

void Tabla::mostrarMatriz()
{
    cout << endl << "matriz Numeros[" << filas << "][" <<columnas<< "] = " << endl;
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
            cout << matriz[i][j] << ",\t" ;
        cout << endl;
    }
}

void Tabla::mostrarIdReglas()
{
    cout <<endl<< "id Reglas[" << cantReglas <<"] = ";
    for (int i = 0; i < cantReglas; i++)
        cout << idReglas[i] << "," ;
}

void Tabla::mostrarLonReglas()
{
    cout << endl << "longitud Reglas["<< cantReglas <<"] = ";
    for (int i = 0; i < cantReglas; i++)
        cout << lonReglas[i] << "," ;
}

void Tabla::mostrarNoTerminales()
{
    cout << "No Terminales["<< cantReglas <<"] = ";
    for (int i = 0; i < cantReglas; i++)
        cout << noTerminalesAux[i] << "," ;
}
