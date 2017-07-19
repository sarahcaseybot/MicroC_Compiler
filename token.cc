//Sarah Botwinick
//Prog4
//token.cc

#include "token.h"
using namespace std;

//constructor
Token::Token(int type, string lexeme, int line, int pos){
  this -> types = type;
  this -> lexemes = lexeme;
  this -> lines = line;
  this -> poss = pos;
}

Token::Token(){
 
}

//destructor
Token::~Token(){
}


//getters
int Token::type(){
  return this -> types;
}

string Token::lexeme(){
  return this -> lexemes;
}

int Token::line(){
  return this -> lines;
}
  
int Token::pos(){
  return this -> poss;
}
