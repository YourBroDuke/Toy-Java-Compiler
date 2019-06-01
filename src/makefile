target = lavac
CC = g++

$(target):y.tab.o lex.yy.o
	$(CC) -o $(target)  y.tab.o lex.yy.o 

y.tab.c:parser.y
	yacc -d -Wconflicts-sr parser.y

lex.yy.c:lexer.l
	lex lexer.l

y.tab.o:y.tab.c
	$(CC) -c y.tab.c

lex.yy.o:lex.yy.c
	$(CC) -c lex.yy.c

clean:
	rm *.o $(target) *.c *.h
