all:	
	flex ./src/lexical-analyzer/lexer.l
	bison -d ./src/syntactical-analyzer/bison.y
	g++ lex.yy.c bison.tab.c
	