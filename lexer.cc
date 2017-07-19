//Sarah Botwinick
//lexer.cc
//Prog4

#include "lexer.h"
#include "token.h"
#include <istream>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include<fstream>
#include<cstdio>
using namespace std;
//constructor
Lexer::Lexer(istream& inputs) : in(inputs) {
  lines = 1;
  poss = 0;
  ch = nextChar();
}



char Lexer::nextChar(){
  char next = in.get();
  //check if its a newline
  if(next == '\n'){
    lines ++;
    poss = 0;
    return ' ';
  }
  //check if its end of file
  else if(next == EOF){
    return '#';
  }
  else{
    poss++;
    return next;
    
  }
  
}

Token Lexer::nextToken(){

  //skips over the whitespace
  while(isspace(ch)){
    ch = nextChar();
  }
  int line = lines;
  int pos = poss;
 

  //figure out the type of token

  //IDENT or Keyword
  if(isalpha(ch)){
    //read until you read a non-letter or digit
    string word = "";
    word += ch;
    ch = nextChar();
    while(!isspace(ch) && (isalpha(ch) || isdigit(ch))) {
      word += ch;
      ch = nextChar();
    }
    
    if(word == "if"){
      return Token(Token::IF, "if", line, pos);
    }
    else if(word == "while"){
      return Token(Token::WHILE, "while", line, pos);
    }
    else if(word == "else"){
      return Token(Token::ELSE, "else", line, pos);
    }
    else if(word == "function"){
      return Token(Token::FUNCTION, "function", line, pos);
    }
    else if(word == "var"){
      return Token(Token::VAR, "var", line, pos);
    }
    else if(word == "printf"){
      return Token(Token::PRINTF, "printf", line, pos);
    }
    else if(word == "return"){
      return Token(Token::RETURN, "return", line, pos);
    }
    else{
      return Token(Token::IDENT, word, line, pos);
  }
  }

  //INTLIT
  else if(isdigit(ch)){
    //read until non-digit
    string num;
    num = ch;
    ch = nextChar();
    while(isdigit(ch)){
      num += ch;
      ch = nextChar();
    }
    return Token(Token::INTLIT, num, line, pos);
  }

  //operator or punctuation
  else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '='
	  || ch == '!' || ch == '<' || ch == '>' || ch == '&' || ch == '|'
	  || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ','
	  || ch == ';'){
    //read until a non-special character
    switch(ch){
    case '+':
      ch = nextChar();
	return Token(Token::PLUS, "+", line, pos);
    case '-':
      ch = nextChar();
	return Token(Token::MINUS, "-", line, pos);
      
    case '*':
      ch = nextChar();
	return Token(Token::TIMES, "*", line, pos);
    case '/':
      ch = nextChar();
	return Token(Token::DIVIDE, "/", line, pos);
     
    case '=':
      ch = nextChar();
      if(ch == '='){
	ch = nextChar();
	  return Token(Token::EQ, "==", line, pos);
	}
	else{
	  return Token(Token::ASSIGN, "=", line, pos);
	}
      
    case '!':
      ch = nextChar();
      if(ch == '='){
	ch = nextChar();
	    return Token(Token::NE, "!=", line, pos);
      }
	    else{
	    return Token(Token::ERROR, "this is not a valid token", line, pos);
	    }
     
    case '<':
      ch = nextChar();
      if(ch == '='){
	ch = nextChar();
	return Token(Token::LE, "<=", line, pos);
	}
	else{
	  return Token(Token::LT, "<", line, pos);
	}
    case '>':
      ch = nextChar();
      if(ch == '='){
	ch = nextChar();
	  return Token(Token::GE,">=", line, pos);
	}
	else{
	  return Token(Token::GT, ">", line, pos);
	}
    case '&':
      ch = nextChar();
      if(ch == '&'){
	ch = nextChar();
	 return Token(Token::AND,"&&", line, pos);
	}
	else{
	  return Token(Token::ERROR, "this is not a valid token", line, pos);
	  
	}
    case '|':
      ch = nextChar();
      if(ch == '|'){
	ch = nextChar();
	  return Token(Token::OR,"||", line, pos);
	}
	else{
	  return Token(Token::ERROR, "this is not a valid token", line, pos);
	  
	}
 
    case '(':
      ch = nextChar();
      return Token(Token::LPAREN, "(", line, pos);
    case ')':
      ch = nextChar();
      return Token(Token::RPAREN, ")", line, pos);
    case '{':
      ch = nextChar();
      return Token(Token::LBRACE, "{", line, pos);
    case '}':
      ch = nextChar();
      return Token(Token::RBRACE, "}", line, pos);
    case ',':
      ch = nextChar();
      return Token(Token::COMMA, ",", line, pos);
    case ';':
      ch = nextChar();
      return Token(Token::SEMICOLON, ";", line, pos);
    default:
      ch = nextChar();
      return Token(Token::ERROR, "this is not a valid token", line, pos);
      
    
    }
  }
  // CHECK IF NEED TO ESPACE QUOTE
  //STRINGLIT
  //dont return the quotes, just what is inside of them
  else if(ch == '\"'){
    //read until another "
    string lstring;
    lstring = "";
    ch = nextChar();
    while(ch != '\"'){
      lstring += ch;
      ch = nextChar();
    }
    
    ch = nextChar();
    return Token(Token::STRINGLIT, lstring, line, pos);
  }

  //ENDOFFILE
  else if(ch == '#'){
    //end of the file
    return Token(Token::ENDOFFILE, "end of file token", line, pos);
  }

  //ERROR
  else{
    ch = nextChar();
    return Token(Token::ERROR, "this is not a valid token",line, pos);
    
    // exit
  }
  //  return Token(Token::ERROR, "this is not a valid token",lines, poss);
  //exit(1);

}

