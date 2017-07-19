//Sarah Botwinick
//symbolTable class
//prog6

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <string>
#include <iostream>
#include <cstdlib>
#include "stack.h"

using namespace std;

class SymbolTable {
public:
  SymbolTable();
private:
   Stack varScopes;
};

#endif
