#ifndef _PILA
#define _PILA

#include <list>
#include <iostream>
#include <string>

using namespace std;
class Nodo;

class ElementoPila
{
protected:

public:
    virtual void muestra() {}
    virtual int getEstado() {}
    virtual string getTerminal() {}
    virtual string getNoTerminal() {}
    virtual Nodo* getNodo() {}
};

class Estado: public ElementoPila
{
protected:
    int estado;
public:
    Estado(int estado)
    {
        this->estado= estado;
    }

    int getEstado()
    {
        return this->estado;
    }

    void muestra()
    {
        //cout << "Estado: " << estado << endl;
        cout << estado << " " ;
    }
};

class Pila
{

private:
    list <ElementoPila*> lista;

public:
    void push( ElementoPila*);
    ElementoPila* top();
    ElementoPila* pop();
    void muestra();
};


#endif
