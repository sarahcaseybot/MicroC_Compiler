//Sarah Botwinick
//parser.cc
//Prog5 - creates a parser    
#include "parser.h"
#include <cstring>
//#include <array>
//#include "stack.cc"

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

/*void postOrder(treeNode node){
  if(node != null){
    postOrder(node->left);
    postOrder(node->right);
    geninst(node);
    //not sure about this
  }
}
*/
/*bool checkVars(string varName, string vars[]){
  int i =0;
  for(i, i < vars.size(), i++){
    if( vars[i] == varName){
      return true;
    }
  }
  return false;
}
*/
					    



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
/*  void instruction(string inst){
    emit("     pop rbx");
    emit("     pop rax");
    emit("     cmp rax,rbx");
    string instFinal = "      " + inst + " j1";
    emit(instFinal);
    emit("     mov rax,0");
    emit("     jmp j2");
    emit("  j1:");
    emit("     mov rax,1");
    emit("  j2:");
    emit("     push rax");
  }
*/

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
  //varNameStack.push(varName);
  //figure out how to add these variables to a data structure
  //where do I declare the data structure
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
  //int counter = 0;
  //string[] varNamesArray = new string[100];
  vardefs(node);
  //i know it's not working right, but gonna code it as if it is

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
  
  //cout << "  section .text" << endl;
  //Stack varNameStack;

  //geninst(node);
 }

//confused about this
Parser::TreeNode* Parser::factor() {
  TreeNode* factorNode;
  int type = token.type();
  if(type == Token::LPAREN){
    token =  lexer.nextToken();
    factorNode = expression();
    // TreeNode* expressionNode;
    check(Token::RPAREN, "need a right parenthesis");
    //      token =lexer.nextToken();
    
  }
  else if(type == Token::INTLIT){
    //    Operation op = PUSHL;
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
    // token = lexer.nextToken();
    }
   
        }
  // else{
      // error("error in factor function");//not sure what to add as op
      //    }
  return factorNode;
}
//is this done correctly? tree made well?
//funcall was not given in h file, but I added it. is that correct?
//check this, did in class
Parser::TreeNode* Parser::funcall(string functionName){
  check(Token::LPAREN, "error in funcall");
   token = lexer.nextToken();
  int tokenType = token.type();
  TreeNode* funcallNode;
  if(tokenType != Token::RPAREN){
    TreeNode* right = new TreeNode(CALL, functionName);
    // tokenType = token.type();
    funcallNode = expression();
    //funcallNode = new TreeNode(SEQ, expression(), right);
    //    token = lexer.nextToken();
          tokenType = token.type();
	  //	   check(Token::COMMA, "error comma");
	    while(tokenType == Token::COMMA){
	        token = lexer.nextToken();
	      TreeNode* right2 = expression();
      funcallNode = new TreeNode(SEQ, funcallNode, right2);//i dont
							  //think this
							  //is right
                  token = lexer.nextToken();
      tokenType = token.type();
      // check(Token::RPAREN, "infinite loop");
	    }
    funcallNode = new TreeNode(SEQ, funcallNode, right);
    //    token = lexer.nextToken();
    //    check(Token::RPAREN, "need a right parenthesis - b");
    
    //token = lexer.nextToken();
  }
  else{
  check(Token::RPAREN, "need a right parenthesis - a");
  //unsure what to put here
  funcallNode = new TreeNode(CALL, functionName);//figure out how to add the name of
				  //the method
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
    // token = lexer.nextToken();
  }
  //    token = lexer.nextToken();//
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
  //   token = lexer.nextToken();
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
  /* TreeNode* logicalExpressionNode = relationalExpression();
  while(token.type() == Token::AND || token.type() == Token::OR){
    Operation op;
    int tokenType = token.type();
    switch (tokenType){
    case Token::AND:
	op = AND;
	break;
    case Token::OR:
      op = OR;
      break;
	
      }
    token = lexer.nextToken();
    TreeNode* rightNode = expression();
    logicalExpressionNode = new TreeNode(op, logicalExpressionNode, rightNode);
  }
  return logicalExpressionNode;
  */
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
     //string x = st.getUniqueSymbol(token.lexeme());
     //TreeNode* right = new TreeNode(op, x);
     //     token = lexer.nextToken();
  TreeNode* returnStatementNode = logicalExpression();
  //  TreeNode* right = new TreeNode(op, token.lexeme());
  returnStatementNode = new TreeNode(SEQ, returnStatementNode, new TreeNode(op)); //unsure
								     //about
								     //this
  //  token = lexer.nextToken();
  check(Token::SEMICOLON, "need a semicolon");
  token = lexer.nextToken();
  return returnStatementNode;
}
//not on grammar sheet
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
  // TreeNode* left = new TreeNode(PUSHL, L1);//
  //  whileStatementNode = new TreeNode(SEQ, left, right);//
  whileStatementNode = new TreeNode(SEQ,left,right);
  // left = whileStatementNode;
  //right = new TreeNode(JUMPF, L1);
  //whileStatementNode = new TreeNode(SEQ,whileStatementNode, right);
  left = whileStatementNode;
  right = new TreeNode(JUMP, L1);
  whileStatementNode = new TreeNode(SEQ, left, right);
  left = whileStatementNode;
  right = new TreeNode(LABEL, L2 + ":");
  whileStatementNode = new TreeNode(SEQ, left, right);

  //string L2 = makeLabel();
  // TreeNode* left = new TreeNode(LABEL, L1);
  // TreeNode* whileStatementNode = new TreeNode(SEQ, left, right);
  //TreeNode* parent = new TreeNode(
  //need a jumpf statement, but not sure how to do it
  //do i need to increment token?
  return whileStatementNode;







}

//not too confident about this function
Parser::TreeNode* Parser::ifStatement() {
   check(Token::IF, "error - if");
  token = lexer.nextToken();
  check(Token::LPAREN, "missing a left parenthesis");
  token = lexer.nextToken();
  TreeNode* left = logicalExpression();
  check(Token::RPAREN, "missing a right parenthesis - if");
  token = lexer.nextToken();
  string L1 = makeLabel();
  //do I need to go to next token here?
  TreeNode* right = new TreeNode(JUMPF, L1);
  TreeNode* ifStatementNode = new TreeNode(SEQ, left, right);
  // check(Token::LPAREN, "missing a left parenthesis");
  left = ifStatementNode;
  st.enterScope();
  right = block();
  st.exitScope();
  ifStatementNode = new TreeNode(SEQ,left,right);
  //  token = lexer.nextToken();
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
    //token = lexer.nextToken();//not sure if its here
    st.enterScope();
    right = block();
    st.exitScope();
    ifStatementNode = new TreeNode(SEQ, left, right);
    left = ifStatementNode;
    right = new TreeNode(LABEL,L2 +":");
    ifStatementNode = new TreeNode(SEQ, left, right);
    //do i need to increment token?
  }
  else{
    left = ifStatementNode;
    right = new TreeNode(LABEL, L1+":");
    ifStatementNode = new TreeNode(SEQ, left, right);
    //need a jumpf statement, but not sure how to do it
    //do i need to increment token?
  }
  return ifStatementNode;
  
}
//same as assignment expression, since assignment expression isnt in
//the grammar sheet
Parser::TreeNode* Parser::assignStatement() {
  check(Token::IDENT, "error - assign3");
  string s = token.lexeme();
  string x = st.getUniqueSymbol(s);
  if(x == ""){
    error("this variable hasn't been declared");
  }
  token = lexer.nextToken();
  // string s = token.lexeme();
  check(Token::ASSIGN, "error - assign4");
   token = lexer.nextToken();
   //string s = token.lexeme();
  // token = lexer.nextToken();
  // token = lexer.nextToken();
     TreeNode* Node1 = new TreeNode(STORE, x);
   TreeNode* Node2 = expression();
   // TreeNode* assignStatementNode = new TreeNode(SEQ, Node1, Node2);
   //  TreeNode* Node3 = new TreeNode(STORE, s);
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
  //cout<<token.lexeme()<<endl;  
  //cout<<token.type()<<endl;
  return new TreeNode(SEQ);
}

Parser::TreeNode* Parser::statement() {
  int type = token.type();
  //cout<<type<<endl;
  //cout<<token.lexeme()<<endl;
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
    //cout<<token.lexeme()<<endl;    
    statementNode = assignStatement();
    //    cout<<token.lexeme()<<endl;
    return statementNode;
  }
  else if (type == Token::RETURN){
    statementNode = returnStatement();
    return statementNode;
  }
  //add printf, but not sure if i'm supposed to do this
  else if(type == Token::PRINTF){
    statementNode = printfStatement();
    return statementNode;
  }
  else{
    //    cout<<type<<endl;
    error("error in statement function");
  }
  return 0;
}

Parser::TreeNode* Parser::block() {
  check(Token::LBRACE, "missing a left brace");
  //st.enterScope();
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
      // type = token.type();
      // token = lexer.nextToken();//not sure about this
            type = token.type();
    }
    //st.exitScope();
    token = lexer.nextToken();
    return blockNode;
  
}

Parser::TreeNode* Parser::parameterdef() {
  return 0;
}
/*
Parser::TreeNode* Parser::parameterdefs() {
  TreeNode* parameterdefsNode;
  if(token.type() == Token::IDENT){
    paramaterdefsNode = paramaterDef();
   
    token = lexer.nextToken();
    while(token.type() == Token::COMMA){
      parameterdefsNode = new TreeNode(SEQ, paramaterdefsNode, parameterDef());
    }
  }
  return parameterdefsNode;
}
*/
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
  /*  Operation op = PARAM1;
  TreeNode* functionNode = new TreeNode(FUNC, funcName + ':');
  while(token.type() != Token::RPAREN){
    if(token.type() == Token::COMMA){
      token = lexer.nextToken();
    }
    functionNode = new TreeNode(SEQ, functionNode, new TreeNode(op, token.lexeme()));
    st.addSymbol(token.lexeme());
    switch(op) {
    case PARAM1:
      //      st.addSymbol(token.lexeme());
      op = PARAM2;
      break;
    case PARAM2:
      op = PARAM3;
      break;
    case PARAM3:
      op = PARAM4;
      break;
    case PARAM4:
      op = PARAM5;
      break;
    
    default:
      error("Too Many Params!");
    }
  */
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
  //call block but not sure how to do it to make tree correct

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
