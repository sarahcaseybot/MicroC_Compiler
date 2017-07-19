#Sarah Botwinick
#make file for Compiler



OPTS= -c -g -Wall -Werror -Wno-non-template-friend

microc: microc.o token.o lexer.o parser.o symbolTable.o hashTable.o link.o stack.o hash.o
	g++ -o microc microc.o lexer.o token.o parser.o symbolTable.o stack.o hashTable.o link.o hash.o 


microc.o: microc.cc token.h lexer.h parser.h x.h link.h hashTable.h stack.h hash.h
	g++ $(OPTS) microc.cc

token.o: token.h token.cc 
	g++ $(OPTS) token.cc

lexer.o: lexer.h lexer.cc token.h
	g++ $(OPTS) lexer.cc

parser.o: parser.h parser.cc x.h token.h lexer.h
	g++ $(OPTS) parser.cc

symbolTable.o: x.h symbolTable.cc hashTable.h stack.h link.h hash.h 
	g++ $(OPTS) symbolTable.cc

stack.o: stack.h stack.cc hashTable.h
	g++ $(OPTS) stack.cc

hashTable.o: hashTable.cc hashTable.h link.h stack.h hash.h
	g++ $(OPTS) hashTable.cc

hash.o: hash.h hash.cc
	g++ $(OPTS) hash.cc

link.o: link.cc link.h
	g++ $(OPTS) link.cc





clean:
	rm -f *.o *~