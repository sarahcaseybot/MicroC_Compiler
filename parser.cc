//Sarah Botwinick
//parser.cc
//creates a parser    
#include "parser.h"
#include <cstring>

Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1) {
  token = lexer.nextToken();
}

Parser::~Parser() {
}

void Parser::error(string message) {
  cerr << message << " Found " << token.lexeme() << " at line " << token.line() << " position " << token.pos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.type() != tokenType)
    error(message);
}

void emit(string text){
  cout << text << endl;
}
					   


string currentFunc;
int nfmts = 0;
string fmts[100];
void Parser::geninst(TreeNode *node){
  if(node != NULL){
    Parser::geninst(node->leftChild);
    Parser::geninst(node->rightChild);
    switch(node->op){
    case ADD:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     add rax,rbx");
      emit("     push rax");
      break;
    case SUB:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     sub rax,rbx");
      emit("     push rax");
      break;
    case AND:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     and rax,rbx");
      emit("     push rax");
      break;
    case OR:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     or rax,rbx");
      emit("     push rax");
      break;
    case MULT:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     imul rbx");
      emit("     push rax");
      break;    case DIV:
      emit("     mov rdx,0");
      emit("     pop rbx");
      emit("     pop rax");
      emit("     idiv rbx");
      emit("     push rax");
      break;
    case LABEL:
      {string x = "     " + node->val;  
	emit(x);}
      break;
    case ISEQ:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     cmp rax,rbx");
      emit("     je j1");
      emit("     mov rax,0");
      emit("     jmp j2");
      emit("  j1:");
      emit("     mov rax,1");
      emit("  j2:");
      emit("     push rax"); 
          
	break;
    case ISNE:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     cmp rax,rbx");
      emit("     jne j1");
      emit("     mov rax,0");
      emit("     jmp j2");
      emit("  j1:");
      emit("     mov rax,1");
      emit("  j2:");
      emit("     push rax");
      break;
    case ISLT:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     cmp rax,rbx");
      emit("     jl j1");
      emit("     mov rax,0");
      emit("     jmp j2");
      emit("  j1:");
      emit("     mov rax,1");
      emit("  j2:");
      emit("     push rax");
           break;
    case ISLE:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     cmp rax,rbx");
      emit("     jle j1");
      emit("     mov rax,0");
      emit("     jmp j2");
      emit("  j1:");
      emit("     mov rax,1");
      emit("  j2:");
      emit("     push rax");
            break;
    case ISGT:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     cmp rax,rbx");
      emit("     jg j1");
      emit("     mov rax,0");
      emit("     jmp j2");
      emit("  j1:");
      emit("     mov rax,1");
      emit("  j2:");
      emit("     push rax");
           break;
    case ISGE:
      emit("     pop rbx");
      emit("     pop rax");
      emit("     cmp rax,rbx");
      emit("     jge j1");
      emit("     mov rax,0");
      emit("     jmp j2");
      emit("  j1:");
      emit("     mov rax,1");
      emit("  j2:");
      emit("     push rax");
           break;
    case JUMP:
      {      string x = "     jmp ";
      x += node->val;
      emit(x);}
      break;
    case JUMPF:
      emit("     pop rax");
      emit("     cmp rax,0");
      {      string x = "     je ";
      x += node->val;
      emit(x);}
      break;
    case PUSHL:
      { string toPrint = "     mov rax,";
	toPrint += node -> val;
	emit(toPrint);}
      emit("     push rax");
      break;
    case PUSHV:
      { string toPrint = "     push qword[";
	toPrint += node -> val;
	toPrint += "]";
	emit(toPrint);
	} break;
    
    case STORE:
      { string toPrint = "     pop qword[";
	toPrint += node -> val;
	toPrint += "]";
	emit(toPrint);}
      break;
    case JUMPT:
      break;
    case CALL:
      { string toPrint = "     call ";
	toPrint += node -> val;
	emit(toPrint);}
      emit("     push rax");
      break;
    case RET:
      emit("     pop rax");
      if(currentFunc != "main:")
	emit("    push r15");
      emit("     ret");
      break;
    case PRINTF:
      fmt = node->val;
      nparams = fmt.at(0) - '0';
      fmt = "`" + fmt.substr(1) + "`";
      fmts[nfmts++] = fmt;
      emit(" mov rdi,fmt" + itos(nfmts));
      if (nparams == 5) {
	emit(" pop r9");
	--nparams;
      }
      if (nparams == 4) {
	emit(" pop r8");
	--nparams;
      }
      if (nparams == 3) {
	emit(" pop rcx");
	--nparams;
      }
      if (nparams == 2) {
	emit(" pop rdx");
	--nparams;
      }
      if (nparams == 1) {
	emit(" pop rsi");
      }
      emit(" mov rax,0");
      emit(" push rbp");
      emit(" call printf");
      emit(" pop rbp");
      break;
    case SEQ:
      break;
    case FUNC:
      currentFunc = node -> val;
      emit(currentFunc);
      if(currentFunc != "main:")
	emit("     pop r15");
      break;
    case PARAM1:
      break;
    case PARAM2:
      break;
    case PARAM3:
      break;
    case PARAM4:
      break;
    case PARAM5:
      break;
    }
  }
}

string varNamesArray[100];
int counter = 0;
void Parser::vardefs(TreeNode *node){
  if(node != NULL){
  Parser::vardefs(node->leftChild);
  Parser::vardefs(node->rightChild);
  if(node->op == PUSHV || node->op == STORE){
  string varName = node->val;
  if(!checkVars(varName)){
  varNamesArray[counter] = varName;
  counter++;
    }
  }
  }
  return;
}

bool Parser::checkVars(string varName){
  int i =0;
  for(i=0; i < counter; i++){
    if( varNamesArray[i] == varName){
      return true;
    }
  }
  return false;
}


void Parser::genasm(TreeNode *node){
  cout << "  global main" << endl;
  cout << "  extern printf" << endl;
  cout << "  segment .bss" << endl;
  vardefs(node);
	
  int variableName = 0;
  while(variableName< counter){
    string varName = varNamesArray[variableName];
    string toPrint = "     " + varName + " resq 1";
    emit(toPrint);
    variableName++;
  }
  cout << "" << endl;
  cout << "  section .text" << endl;
  geninst(node);
  cout << "  section .data" << endl;
  for(int i = 0; i < nfmts; i++){
    emit("     fmt" + itos(i+1) + ": db " + fmts[i] + ", 0");
  }
 
 }

Parser::TreeNode* Parser::factor() {
  TreeNode* factorNode;
  int type = token.type();
  if(type == Token::LPAREN){
    token =  lexer.nextToken();
    factorNode = expression();
    check(Token::RPAREN, "need a right parenthesis");
    
  }
  else if(type == Token::INTLIT){
    factorNode = new TreeNode(PUSHL, token.lexeme());
    token = lexer.nextToken();
  }
  else if(type == Token::IDENT){
    string lex = token.lexeme();
    token = lexer.nextToken();
    if(token.type() == Token::LPAREN){
      factorNode = funcall(lex);
    }
    else{
      string x = st.getUniqueSymbol(lex);
      if(x == ""){
	error("this variable has not been declared");
      }
    factorNode = new TreeNode(PUSHV, x);
    }
   
        }
  return factorNode;
}

Parser::TreeNode* Parser::funcall(string functionName){
  check(Token::LPAREN, "error in funcall");
   token = lexer.nextToken();
  int tokenType = token.type();
  TreeNode* funcallNode;
  if(tokenType != Token::RPAREN){
    TreeNode* right = new TreeNode(CALL, functionName);
    funcallNode = expression();
   
          tokenType = token.type();
	    while(tokenType == Token::COMMA){
	        token = lexer.nextToken();
	      TreeNode* right2 = expression();
      funcallNode = new TreeNode(SEQ, funcallNode, right2);
                  token = lexer.nextToken();
      tokenType = token.type();
	    }
    funcallNode = new TreeNode(SEQ, funcallNode, right);
    
  }
  else{
  check(Token::RPAREN, "need a right parenthesis - a");
  funcallNode = new TreeNode(CALL, functionName);
  token = lexer.nextToken();
  }
  return funcallNode;
}

Parser::TreeNode* Parser::term() {
  TreeNode* termNode = factor();
  TreeNode* factorNode;
  int tokenType = token.type();
  while (tokenType == Token::TIMES || tokenType == Token::DIVIDE){
    token = lexer.nextToken();
    factorNode = factor();
    Operation op;
    switch (tokenType){
    case Token::TIMES:
      op = MULT;
      break;
    case Token::DIVIDE:
      op = DIV;
      break;
	}
    termNode = new TreeNode(op, termNode, factorNode);
    tokenType = token.type();
  }
  return termNode;
    
}

Parser::TreeNode* Parser::expression() {
  TreeNode* expressionNode = term();
  TreeNode* termNode;
  int tokenType = token.type();
  while (tokenType == Token::PLUS || tokenType == Token::MINUS){
    token = lexer.nextToken();
    termNode = term();
    Operation op;
    switch(tokenType){
    case Token::PLUS:
      op = ADD;
      break;
    case Token::MINUS:
      op = SUB;
      break;
	}
    expressionNode = new TreeNode(op, expressionNode, termNode);
    tokenType = token.type();
  }
  return expressionNode;
}

Parser::TreeNode* Parser::relationalExpression() {
  TreeNode* relationalExpressionNode = expression();
  if(token.type() == Token::EQ || token.type() == Token::LT || token.type() == Token::LE ||token.type() ==Token::GT || token.type() == Token::GE || token.type() == Token::NE){
    int tokenType = token.type();
    Operation op;
    switch(tokenType){
    case Token::EQ:
      op = ISEQ;
	break;
    case Token::LT:
      op = ISLT;
      break;
    case Token::LE:
      op = ISLE;
      break;
    case Token::GT:
      op = ISGT;
      break;
    case Token::GE:
      op = ISGE;
      break;
    case Token::NE:
	op = ISNE;
      break;
    }
    token = lexer.nextToken();
    TreeNode* rightNode = expression();
    relationalExpressionNode = new TreeNode(op, relationalExpressionNode, rightNode);
    
  }
  return relationalExpressionNode;
}

Parser::TreeNode* Parser::logicalExpression() {
  
  TreeNode* logicalExpressionNode = relationalExpression();
  TreeNode* relationalExpressionNode;;
  int tokenType = token.type();
  while (tokenType == Token::AND || tokenType == Token::OR){
    token = lexer.nextToken();
    relationalExpressionNode = relationalExpression();
    Operation op;
    switch (tokenType){
    case Token::AND:
      op = AND;
      break;
    case Token::OR:
      op = OR;
      break;
    }
    logicalExpressionNode = new TreeNode(op, logicalExpressionNode, relationalExpressionNode);
    tokenType = token.type();
  }
  return logicalExpressionNode;
  }

Parser::TreeNode* Parser::assignmentExpression() {
  check(Token::IDENT, "error - assign1");
  string tokenVal = token.lexeme();
  token = lexer.nextToken();
  
  check(Token::ASSIGN, "error - assign2");
  token = lexer.nextToken();
  TreeNode* assignmentExpressionNode = logicalExpression();
  Operation op = STORE;
  assignmentExpressionNode = new TreeNode(op,tokenVal);
  check(Token::SEMICOLON, "need a semicolon");
  token = lexer.nextToken();
  return assignmentExpressionNode;
}

Parser::TreeNode* Parser::returnStatement() {
   check(Token::RETURN, "error");
     Operation op = RET;
     token = lexer.nextToken();
     
  TreeNode* returnStatementNode = logicalExpression();
  returnStatementNode = new TreeNode(SEQ, returnStatementNode, new TreeNode(op)); 
  check(Token::SEMICOLON, "need a semicolon");
  token = lexer.nextToken();
  return returnStatementNode;
}
Parser::TreeNode* Parser::printfStatement() {
  TreeNode* paramList = NULL;
  int nparams = 0;
  check(Token::PRINTF, "expecting printf");
  token = lexer.nextToken();
  check(Token::LPAREN, "expecting(");
  token = lexer.nextToken();
  check(Token::STRINGLIT, "expecting string literal");
  string formatString = token.lexeme();
  token = lexer.nextToken();
  if(token.type() == Token::COMMA){
    token = lexer.nextToken();
    paramList = expression();
    ++nparams;
    while(token.type() == Token::COMMA){
      token = lexer.nextToken();
      paramList = new TreeNode(SEQ, paramList, expression());
      ++nparams;
    }
  }
  check(Token::RPAREN, "expecting )");
  token = lexer.nextToken();
  check(Token::SEMICOLON, "expecting ;");
  token = lexer.nextToken();
  TreeNode* printStatement = new TreeNode(SEQ, paramList, new TreeNode(PRINTF, itos(nparams) + formatString));
  return printStatement;
}

Parser::TreeNode* Parser::whileStatement() {

  check(Token::WHILE, "error - if");
  token = lexer.nextToken();
  check(Token::LPAREN, "missing a left parenthesis");
  token = lexer.nextToken();
  TreeNode* right = logicalExpression();
  check(Token::RPAREN, "missing a right parenthesis - if");
  token = lexer.nextToken();
  string L1 = makeLabel();
  string L2 = makeLabel();
  //do I need to go to next token here?
    TreeNode* left = new TreeNode(LABEL, L1+ ":");
   TreeNode* whileStatementNode = new TreeNode(SEQ, left, right);
  // check(Token::LPAREN, "missing a left parenthesis");
  left = whileStatementNode;
  right = new TreeNode(JUMPF, L2);
  TreeNode* whileStatementNode2 = new TreeNode(SEQ, left, right);
  left = whileStatementNode2;
  st.enterScope();
  right = block();
  st.exitScope();
  
  whileStatementNode = new TreeNode(SEQ,left,right);
  
  left = whileStatementNode;
  right = new TreeNode(JUMP, L1);
  whileStatementNode = new TreeNode(SEQ, left, right);
  left = whileStatementNode;
  right = new TreeNode(LABEL, L2 + ":");
  whileStatementNode = new TreeNode(SEQ, left, right);

 
  return whileStatementNode;

}

Parser::TreeNode* Parser::ifStatement() {
   check(Token::IF, "error - if");
  token = lexer.nextToken();
  check(Token::LPAREN, "missing a left parenthesis");
  token = lexer.nextToken();
  TreeNode* left = logicalExpression();
  check(Token::RPAREN, "missing a right parenthesis - if");
  token = lexer.nextToken();
  string L1 = makeLabel();
  TreeNode* right = new TreeNode(JUMPF, L1);
  TreeNode* ifStatementNode = new TreeNode(SEQ, left, right);
  left = ifStatementNode;
  st.enterScope();
  right = block();
  st.exitScope();
  ifStatementNode = new TreeNode(SEQ,left,right);
  int tokenType = token.type();
  if(tokenType == Token::ELSE){
    token = lexer.nextToken();  
    left = ifStatementNode;
    string L2 = makeLabel();
    right = new TreeNode(JUMP, L2);
    ifStatementNode = new TreeNode(SEQ, left, right);
    left = ifStatementNode;
    right = new TreeNode(LABEL, L1);
    ifStatementNode = new TreeNode(SEQ, left, right);
    left = ifStatementNode;
    st.enterScope();
    right = block();
    st.exitScope();
    ifStatementNode = new TreeNode(SEQ, left, right);
    left = ifStatementNode;
    right = new TreeNode(LABEL,L2 +":");
    ifStatementNode = new TreeNode(SEQ, left, right);
  }
  else{
    left = ifStatementNode;
    right = new TreeNode(LABEL, L1+":");
    ifStatementNode = new TreeNode(SEQ, left, right);
  }
  return ifStatementNode;
  
}
Parser::TreeNode* Parser::assignStatement() {
  check(Token::IDENT, "error - assign3");
  string s = token.lexeme();
  string x = st.getUniqueSymbol(s);
  if(x == ""){
    error("this variable hasn't been declared");
  }
  token = lexer.nextToken();
  check(Token::ASSIGN, "error - assign4");
   token = lexer.nextToken();
     TreeNode* Node1 = new TreeNode(STORE, x);
   TreeNode* Node2 = expression();
  TreeNode* assignStatementNode = new TreeNode(SEQ, Node2, Node1);
  token = lexer.nextToken();//
  return assignStatementNode;


  }

Parser::TreeNode* Parser::vardefStatement() {
  token = lexer.nextToken();
  check(Token::IDENT, "need an ident");
  st.addSymbol(token.lexeme());
  token = lexer.nextToken();
  int type = token.type();
  while(type == Token::COMMA){
    token = lexer.nextToken();
    check(Token::IDENT, "need an ident");
    st.addSymbol(token.lexeme());
    token = lexer.nextToken();
    type = token.type();
  }
  check(Token::SEMICOLON, "missing semicolon");
  token = lexer.nextToken();
  return new TreeNode(SEQ);
}

Parser::TreeNode* Parser::statement() {
  int type = token.type();
  TreeNode* statementNode;
    if(type == Token::VAR){
      statementNode = vardefStatement();
      return statementNode;
    }
  if(type == Token::IF){
    statementNode = ifStatement();
    return statementNode;
  }
  else if(type == Token::WHILE){
    statementNode = whileStatement();
    return statementNode;
  }
  else if(type == Token::IDENT){
    statementNode = assignStatement();
    return statementNode;
  }
  else if (type == Token::RETURN){
    statementNode = returnStatement();
    return statementNode;
  }
  else if(type == Token::PRINTF){
    statementNode = printfStatement();
    return statementNode;
  }
  else{
    error("error in statement function");
  }
  return 0;
}

Parser::TreeNode* Parser::block() {
  check(Token::LBRACE, "missing a left brace");
   token = lexer.nextToken();
    int type = token.type();
    if(type == Token::RBRACE){
      token = lexer.nextToken();
      TreeNode* emptyNode = new TreeNode(SEQ);
      return emptyNode;
    }
    TreeNode* blockNode = NULL;
    while(type != Token::RBRACE){
      TreeNode* right;
      right = statement();
      blockNode = new TreeNode(SEQ, blockNode, right);
            type = token.type();
    }
    token = lexer.nextToken();
    return blockNode;
  
}

Parser::TreeNode* Parser::parameterdef() {
  return 0;
}

Parser::TreeNode* Parser::function() {
  check(Token::FUNCTION, "need a function name");
  token = lexer.nextToken();
  check(Token::IDENT, "need an ident");
  string funcName = token.lexeme() + ":";
  token = lexer.nextToken();
  check(Token::LPAREN, "need a left parenthesis");
  st.enterScope();
  token = lexer.nextToken();
  if(token.type() == Token::RPAREN){
    token = lexer.nextToken();
    TreeNode* blockNode = block();
    TreeNode* functionNode = new TreeNode(FUNC,funcName);
    st.exitScope();
    functionNode = new TreeNode(SEQ, functionNode, blockNode);
    return functionNode;
  }
  
  check(Token::IDENT, "need ident");
  string params[100];
  int counter = 0;
  params[counter] = token.lexeme();
  counter++;
  token = lexer.nextToken();
  while(token.type() == Token::COMMA){
    token = lexer.nextToken();
    check(Token::IDENT, "need ident");
    params[counter] = token.lexeme();
    token = lexer.nextToken();
    
    }

  TreeNode* functionNode = new TreeNode(FUNC, funcName);
  while(counter >=0){
    st.addSymbol(params[counter]);
    TreeNode* paramNode = new TreeNode(STORE, st.getUniqueSymbol(params[counter]));
    counter--;
    functionNode = new TreeNode(SEQ, functionNode, paramNode);
  }
  check(Token::RPAREN, "need a right parenthesis");
  token = lexer.nextToken();
  functionNode = new TreeNode(SEQ, functionNode, block());
  st.exitScope();
  return functionNode;

}

Parser::TreeNode* Parser::compilationunit() {
  TreeNode* compilationNode = NULL;
  
  while(token.type() == Token::FUNCTION){
    compilationNode = new TreeNode(SEQ, compilationNode, function());
  }
  return compilationNode;
}

const string Parser::ops[] = {
  /* ADD, SUB, MULT, DIV, // Arithmetic Operators
  ISEQ, ISNE, ISLT, ISLE, ISGT, ISGE, // Relational Operators
  AND, OR, // Logical Operators
  PUSHL, PUSHV, STORE, // Value Transfer Instructions
  JUMP, JUMPF, JUMPT, CALL, RET, // Location Transfer Instructions
  PRINTF, // Misc
  LABEL, SEQ*/

  "ADD","SUB", "MULT", "DIV",
  "ISEQ", "ISNE", "ISLT", "ISLE", "ISGT", "ISGE",
  "AND", "OR",
  "PUSHL", "PUSHV", "STORE",
  "JUMP", "JUMPF", "JUMPT", "CALL", "RET",
  "PRINTF",
  "LABEL", "SEQ",
  "FUNC", "PARAM1", "PARAM2", "PARAM3", "PARAM4", "PARAM5"

};
