target = lavac
CC = g++
CPPFLAG = -std=c++11 -Wno-deprecated-register
OBJS = y.tab.o lex.yy.o node.o context.o Generator.o Jasmin.o utils.o

$(target):$(OBJS)
	$(CC) $(CPPFLAG) -o $@ $^ 

y.tab.c:ToyParser.y
	yacc ToyParser.y -d -v --debug

y.tab.h:ToyParser.y

lex.yy.c:lexer.l y.tab.h
	lex lexer.l y.tab.h

y.tab.o:y.tab.c node.h
	$(CC) $(CPPFLAG) -c y.tab.c

lex.yy.o:lex.yy.c node.h
	$(CC) $(CPPFLAG) -c lex.yy.c

node.o:node.cpp node.h
	$(CC) $(CPPFLAG) -c node.cpp

%.o:%.cpp
	$(CC) $(CPPFLAG) -c $<

%.o:codeGen/%.cpp
	$(CC) $(CPPFLAG) -c $<

%.o:utils/%.cpp
	$(CC) $(CPPFLAG) -c $<
 
.PHONY: clean
clean:
	-rm -f *.o $(target) y.tab.c y.tab.h lex.yy.c *.output

.PHONY: test
test:$(target)
	cat testCases/op.txt | ./lavac

.PHONY: test_all
test_all:$(target)
	cat testCases/little_program.txt | ./lavac
