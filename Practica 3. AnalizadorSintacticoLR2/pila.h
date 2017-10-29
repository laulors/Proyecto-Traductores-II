#ifndef _PILA
#define _PILA

#include <list>
#include <iostream>
#include <string>
#include "ElementoPila.h"

using namespace std;

class Pila{

   private:      
      list <ElementoPila*> lista;      
      
   public:
      void push(ElementoPila *x);
      ElementoPila* top();
      ElementoPila* pop();
      void muestra();
};


#endif
