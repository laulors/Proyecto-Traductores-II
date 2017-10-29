#include "ElementoPila.h"
class NoTerminal: public ElementoPila
{
public:
	string tipoElemento;
	int numeroNoTerminal;
	NoTerminal(string datoPila);
	void mostrarInfoNoTerminal();
};

