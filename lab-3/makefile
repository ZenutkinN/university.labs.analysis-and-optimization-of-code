all:	
	flex lexer.l
	bison -d bison.y
	c++ lex.yy.c bison.tab.c utils.cpp classes.cpp
	