#include "Terminal.h"

Terminal::Terminal(string terminal)
{
    this->terminal= terminal;
}

string Terminal::getTerminal()
{
    return this->terminal;
}

void Terminal::muestra()
{
    cout << terminal << " ";
}
