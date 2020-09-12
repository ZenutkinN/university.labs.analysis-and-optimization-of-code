%{
#if defined _WIN32
#include <io.h>              
#elif defined _WIN64
#include <io.h>              
#endif
#ifdef MSVC
#define isatty _isatty
#endif
#include <unistd.h>
#include <string>
#include <list>

class oper_t {
	protected: oper_t() {};
	public: virtual ~oper_t() {}
};	

class expr_t {
	protected: expr_t() {};
	public: virtual ~expr_t() {}
};	

typedef struct {
	std::string str;
	oper_t* oper;
	expr_t* expr;
	std::list<expr_t*> args;
} YYSTYPE;

#define YYSTYPE YYSTYPE
#include "bison.tab.h"

void yyerror(char* s);
int numOfChars = 0;
%}

%option yylineno

%%
if		                                    { 
                                                return IF;
                                            }

else	                                    { 
                                                return ELSE;
                                            }

do		                                    { 
                                                return DO;
                                            }

while	                                    { 
                                                return WHILE;
                                            }

return	                                    { 
                                                return RETURN;
                                            }

string|int|float|bool	                    {
                                                yylval.str = yytext;
		                                        return VALUETYPE;
                                            }

true|false	                                {
		                                        yylval.str = yytext;
		                                        return BOOL;
		                                    }

void	                                    {
                                                return VOID;
                                            }

stdout                                      {
                                                return OUTPUT;
                                            }

stdin                                       {
                                                return INPUT;
                                            }
                                            
null|NULL                                   { 
		                                        return NIL;
		                                    }

"!"|"&"|"|"|"("|")"|"{"|"}"|";"|","|"."     {
		                                        numOfChars = numOfChars + strlen(yytext);
		                                        return *yytext;
		                                    }

[a-zA-Z_][a-zA-Z0-9_]*                      {
		                                        yylval.str = yytext;
		                                        return IDENTIFIER;;
		                                    }

[ \t\r\n]                                   ;

"-"?[0-9][0-9]*	                            { 
                                                const char *min = "-2147483648";
                                                const char *max = "2147483647";

                                                int error = 0;

                                                if (yytext[0] == '-') {
                                                    if (strlen(yytext) >= 3) {
                                                        if (yytext[1] == '0' && yytext[2] == '0') {
                                                                printf("Error at line %d: %s - more than one zero at start of number %d.\n", yylineno, yytext, yyleng);
                                                                exit(1);
                                                                error = -1;
                                                        }
                                                    }
                                                    if (strlen(yytext) == 11) {
                                                        for (int i = 1; i < strlen(yytext); i++) {
                                                            if (max[i] > yytext[i]) {
                                                                break;
                                                            } else {
                                                                if (max[i] < yytext[i]) {
                                                                    printf("Error at line %d: %s - out of int bounds %d.\n", yylineno, yytext, yyleng);
                                                                    exit(1);
                                                                    error = -1;
                                                                    break;
                                                                } else {
                                                                    continue;
                                                                }
                                                            }
                                                        }
                                                    } else if (strlen(yytext) > 11) {
                                                        printf("Error at line %d: %s - out of int bounds %d.\n", yylineno, yytext, yyleng);
                                                        exit(1);
                                                        error = -1;
                                                    }
                                                } else {
                                                    if (strlen(yytext) >=2) {
                                                        if (yytext[0] == '0' && yytext[1] == '0') {
                                                                printf("Error at line %d: %s - more than one zero at start of number %d.\n", yylineno, yytext, yyleng);
                                                                exit(1);
                                                                error = -1;
                                                        }
                                                    }
                                                    if (strlen(yytext) == 10) {
                                                        for (int i = 0; i < strlen(yytext); i++) {
                                                            if (min[i] > yytext[i]) {
                                                                break;
                                                            } else {
                                                                if (min[i] < yytext[i]) {
                                                                    printf("Error at line %d: %s - out of int bounds %d.\n", yylineno, yytext, yyleng);
                                                                    exit(1);
                                                                    error = -1;
                                                                    break;
                                                                } else {
                                                                    continue;
                                                                }
                                                            }
                                                        }
                                                    } else if (strlen(yytext) > 10) {
                                                        printf("Error at line %d: %s - out of int bounds %d.\n", yylineno, yytext, yyleng);
                                                        exit(1);
                                                        error = -1;
                                                    }
                                                }
                                                if (error == 0) {
                                                    yylval.str = yytext;
                                                    return CONSTANT;
                                                }
                                            }

"-"?[0-9][0-9]*"."[0-9][0-9]*	            { 
                                                char arrChar[256] = "";
                                                strcpy(arrChar, yytext);

                                                char *integerPart = strtok(arrChar, ".");
                                                char *fractionalPart = strtok(NULL, ".");

                                                int integerPartLen = strlen(integerPart);
                                                int fractionalPartLen = strlen(fractionalPart);

                                                const char *min = "-340000000000000000000000000000000000000.0";
                                                const char *max = "340000000000000000000000000000000000000.0";

                                                int error = 0;

                                                if (integerPart[0] == '-') {
                                                    if (integerPartLen >=3) {
                                                        if (integerPart[1] == '0' && integerPart[2] == '0') {
                                                                printf("Error at line %d: %s - more than one zero at start of number %d.\n", yylineno, yytext, yyleng);
                                                                exit(1);
                                                                error = -1;
                                                        }
                                                    }
                                                    if (integerPartLen == 40) {
                                                        for (int i = 1; i < integerPartLen; i++) {
                                                            if (max[i] > integerPart[i]) {
                                                                break;
                                                            } else {
                                                                if (max[i] < integerPart[i]) {
                                                                    printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                                    error = -1;
                                                                    exit(1);
                                                                    break;
                                                                } else {
                                                                    continue;
                                                                }
                                                            }
                                                        }
                                                    } else if (integerPartLen > 40) {
                                                        printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                        exit(1);
                                                        error = -1;
                                                    }
                                                } else {
                                                    if (integerPartLen >= 2) {
                                                        if (integerPart[0] == '0' && integerPart[1] == '0') {
                                                                printf("Error at line %d: %s - more than one zero at start of number %d.\n", yylineno, yytext, yyleng);
                                                                exit(1);
                                                                error = -1;
                                                        }
                                                    }
                                                    if (integerPartLen == 39) {
                                                        for (int i = 0; i < integerPartLen; i++) {
                                                            if (min[i] > integerPart[i]) {
                                                                break;
                                                            } else {
                                                                if (min[i] < integerPart[i]) {
                                                                    printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                                    error = -1;
                                                                    exit(1);
                                                                    break;
                                                                } else {
                                                                    continue;
                                                                }
                                                            }
                                                        }
                                                    } else if (integerPartLen > 39) {
                                                        printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                        exit(1);
                                                        error = -1;
                                                    }
                                                }
                                                if (fractionalPartLen > 10) {
                                                    printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                    exit(1);
                                                    error = -1;
                                                }
                                                if (error == 0) {
                                                    yylval.str = yytext;
                                                    return FCONSTANT;
                                                }
                                            }

\"[^"\n]*\" 	                            {
		                                        yylval.str = yytext;
		                                        return STRING;
                                            }

[/][/].*\n                                  ; // Комментарий

"*"	                                        { 
	                                            yylval.str = yytext;
	                                            return MULOPERATOR;
	                                        }

"/"|"%"	                                    {  
		                                        yylval.str = yytext; 
		                                        return DIVOPERATOR;
		                                    }

"+"	                                        { 
	                                            yylval.str = yytext;
	                                            return SUMOPERATOR;
	                                        }

"-"	                                        { 
	                                            yylval.str = yytext;
	                                            return SUBOPERATOR;
	                                        }

">="|"<="|"<"|">"|"=="|"!="	                { 
		                                        yylval.str = yytext;
		                                        return COMPAREOPERATOR;
		                                    }
                                            
"&&"|"||"	                                { 
		                                        yylval.str = yytext;
		                                        return BOOLOPERATOR;
		                                    }

"="                                         {
		                                        return ASSIGNOPERATOR;
		                                    }
%%

int yywrap () { return 1; }