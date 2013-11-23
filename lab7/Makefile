# A VERY simple makefile for building alge, the algebra calculator.


OBJS = alge-parser.tab.o lex.yy.o alge.o


alge : parser $(OBJS)
	g++ -g -O0 $(OBJS) -o alge

parser :
	bison alge-parser.yy
	flex alge-scanner.flex

alge-parser.tab.o : parser
	g++ -g -O0 -Wall -c alge-parser.tab.cc

lex.yy.o : parser
	g++ -g -O0 -Wall -c lex.yy.c

alge.o : alge.cc
	g++ -g -O0 -Wall -c alge.cc

clean :
	rm -f *.o alge-parser.tab.* lex.yy.c alge

.PHONY : clean parser

