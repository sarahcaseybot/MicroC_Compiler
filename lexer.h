//Sarah Botwinick
//lexer class
//Prog 4

#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <istream>
using namespace std;

class Lexer {
public:
  //constructor
  Lexer(istream& inputs);
  int lines;
  int poss;
  char ch;
  istream& in;
  Token nextToken();
private:
  char nextChar(); 
  
};

#endif
