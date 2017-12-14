#include <vector>
#include "string.h"
#include "string"
#include <iostream>

using namespace std;

#ifndef TABLAERRORES_H_INCLUDED
#define TABLAERRORES_H_INCLUDED

class TablaErrores
{
protected:
    vector<string> vectorErrores;
public:
    TablaErrores();
    void insert(int, string);
    void muestra();

};

#endif // TABLAERRORES_H_INCLUDED
