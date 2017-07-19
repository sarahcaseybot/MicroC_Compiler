//Sarah Botwinick
//symbolTable.cc
//Prog6


#include "x.h"
#include <string>
#include<sstream>
SymbolTable::SymbolTable():varScopes(101) {
  counter = 1;
}

void SymbolTable::enterScope(){
  HashTable* x = new HashTable();
  varScopes.push(x);
}


void SymbolTable::exitScope(){
  if(varScopes.count() > 1){
  varScopes.pop();
  }
  }

int SymbolTable::addSymbol(string sym){
  HashTable* x = varScopes.peek();
  if(x->inTable(sym)){
    return 0;
  }
  string unique = sym;
  unique += "$";
  ostringstream convert;
  convert << counter;
  string uniqueN = convert.str();
  unique += uniqueN;
  x->add(sym,unique);
  counter++;
  return 1;
}

string SymbolTable::getUniqueSymbol(string sym){
  for(int y = varScopes.count();
      y >=0; y--){
    HashTable* x = varScopes[y];
    if (x->inTable(sym)){
      return (*x)[sym];
    }
  }
  return "";
}









