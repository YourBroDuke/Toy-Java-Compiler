target = lavac
CC = g++

$(target):y.tab.o lex.yy.o
	$(CC) -o $(target)  y.tab.o lex.yy.o -lfl -ly

y.tab.c:ToyParser.y
	yacc ToyParser.y -d -v --debug

lex.yy.c:lexer.l
	lex lexer.l

y.tab.o:y.tab.c
	$(CC) -c y.tab.c -ly

lex.yy.o:lex.yy.c
	$(CC) -c lex.yy.c -lfl

clean:
	rm *.o $(target) *.c *.h
