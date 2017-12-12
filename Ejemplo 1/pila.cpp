#include "pila.h"
#include "lexico.h"
#include <sstream>


  void Pila::push( int x){
       lista.push_front(x);
  }
       
 int  Pila::pop(){

     int x= *lista.begin();
     lista.erase ( lista.begin() );
     
     return x;
  }

   int Pila::top(){
     return *lista.begin();     
  }
  
  void Pila::muestra(){

     list <int>::reverse_iterator  it;

     cout << "Pila: ";   
     
     for (it= lista.rbegin(); it != lista.rend(); it++){
         cout << (*it) << " ";         
     } 
  
     cout << endl;
  }

  void Pila::ejemplo1() {
	  Pila p;
	  p.push(2);
	  p.push(3);
	  p.push(4);
	  p.push(5);
	  p.muestra();

	  cout<< p.top() << endl;
	  cout<< p.top()<<endl;

	  cout<< p.pop() <<endl;
	  cout<< p.pop() <<endl<<endl;
  }
