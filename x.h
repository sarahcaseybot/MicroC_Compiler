//Sarah Botwinick
//symbolTable class
//prog6

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <string>
#include <iostream>
#include <cstdlib>
#include "hash.h"
#include "link.h"
#include "hashTable.h"
#include "stack.h"

using namespace std;

class SymbolTable {
public:
  SymbolTable();
  Stack varScopes;
  int counter;
  void enterScope();
  void exitScope();
  int addSymbol(string sym);
  string getUniqueSymbol(string sym);
private:
 
};

#endif
