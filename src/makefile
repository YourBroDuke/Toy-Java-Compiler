target = lavac
CC = g++
CPPFLAG = -std=c++11
OBJS = y.tab.o lex.yy.o node.o context.o Generator.o Jasmin.o

$(target):$(OBJS)
	$(CC) $(CPPFLAG) -o $@ $^ -lfl -ly

y.tab.c:ToyParser.y
	yacc ToyParser.y -d -v --debug

y.tab.h:y.tab.c

lex.yy.c:lexer.l y.tab.h
	lex lexer.l y.tab.h

y.tab.o:y.tab.c node.h
	$(CC) $(CPPFLAG) -c y.tab.c -ly

lex.yy.o:lex.yy.c node.h
	$(CC) $(CPPFLAG) -c lex.yy.c -lfl

node.o:node.cpp node.h
	$(CC) $(CPPFLAG) -c node.cpp

%.o:%.cpp
	$(CC) $(CPPFLAG) -c $<

%.o:codeGen/%.cpp
	$(CC) $(CPPFLAG) -c $<

clean:
	rm *.o $(target) y.tab.c y.tab.h lex.yy.c

test:
	cat testCases/hello.txt | ./lavac
