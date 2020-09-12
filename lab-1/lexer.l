%{
#if defined _WIN32
    #include <io.h>
#elif defined _WIN64
    #include <io.h>
#endif

#if defined MSVC
    #define isatty _isatty
#endif
%}

%option yylineno

%%
if		                                    { 
                                                printf("%-20s%s\n", "IF", yytext);
                                            }

else	                                    { 
                                                printf("%-20s%s\n", "ELSE", yytext);
                                            }

do		                                    { 
                                                printf("%-20s%s\n", "DO", yytext);
                                            }

while	                                    { 
                                                printf("%-20s%s\n", "WHILE", yytext);
                                            }

return	                                    { 
                                                printf("%-20s%s\n", "RETURN", yytext);
                                            }

string|int|float|bool	                    {
                                                printf("%-20s%s\n", "VALUETYPE", yytext);
                                            }

true|false	                                {
		                                        printf("%-20s%s\n", "BOOL", yytext);
		                                    }

function	                                {
                                                printf("%-20s%s\n", "FUNCTION", yytext);
                                            }

stdout                                      {
                                                printf("%-20s%s\n", "OUTPUT", yytext);
                                            }

stdin                                       {
                                                printf("%-20s%s\n", "INPUT", yytext);
                                            }

"!"|"&"|"|"|"("|")"|"{"|"}"|";"|","|"."     {
		                                        printf("%-20s%s\n", "PUNCTUATOR", yytext);
		                                    }

[a-zA-Z_][a-zA-Z0-9_]*                      {
		                                        printf("%-20s%s\n", "IDENTIFIER", yytext);
		                                    }

[ \t\r\n]                                   ;

"-"?[0-9][0-9]*	                            { 
                                                const char *min = "-2147483648";
                                                const char *max = "2147483647";

                                                int error = 0;

                                                if (yytext[0] == '-') {
                                                    if (strlen(yytext) == 11) {
                                                        for (int i = 1; i < strlen(yytext); i++) {
                                                            if (min[i] > yytext[i]) {
                                                                break;
                                                            } else {
                                                                if (min[i] < yytext[i]) {
                                                                    printf("Error at line %d: %s - out of int bounds %d.\n", yylineno, yytext, yyleng);
                                                                    error = -1;
                                                                    break;
                                                                } else {
                                                                    continue;
                                                                }
                                                            }
                                                        }
                                                    } else if (strlen(yytext) > 11) {
                                                        printf("Error at line %d: %s - out of int bounds %d.\n", yylineno, yytext, yyleng);
                                                        error = -1;
                                                    }
                                                } else {
                                                    if (strlen(yytext) == 10) {
                                                        for (int i = 0; i < strlen(yytext); i++) {
                                                            if (max[i] > yytext[i]) {
                                                            break;
                                                            } else {
                                                                if (max[i] < yytext[i]) {
                                                                    printf("Error at line %d: %s - out of int bounds %d.\n", yylineno, yytext, yyleng);
                                                                    error = -1;
                                                                    break;
                                                                } else {
                                                                    continue;
                                                                }
                                                            }
                                                        }
                                                    } else if (strlen(yytext) > 10) {
                                                        printf("Error at line %d: %s - out of int bounds %d.\n", yylineno, yytext, yyleng);
                                                        error = -1;
                                                    }
                                                }
                                                
                                                if (error == 0) {
                                                    printf("%-20s%s\n", "CONSTANT", yytext);;
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
                                                    if (integerPartLen == 40) {
                                                        for (int i = 1; i < integerPartLen; i++) {
                                                            if (min[i] > integerPart[i]) {
                                                                break;
                                                            } else {
                                                                if (min[i] < integerPart[i]) {
                                                                    printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                                    error = -1;
                                                                    break;
                                                                } else {
                                                                    continue;
                                                                }
                                                            }
                                                        }
                                                    } else if (integerPartLen > 40) {
                                                        printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                        error = -1;
                                                    }
                                                } else {
                                                    if (integerPartLen == 39) {
                                                        for (int i = 0; i < integerPartLen; i++) {
                                                            if (max[i] > integerPart[i]) {
                                                                break;
                                                            } else {
                                                                if (max[i] < integerPart[i]) {
                                                                    printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                                    error = -1;
                                                                    break;
                                                                } else {
                                                                    continue;
                                                                }
                                                            }
                                                        }
                                                    } else if (integerPartLen > 39) {
                                                        printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                        error = -1;
                                                    }
                                                }
                                                if (fractionalPartLen > 10) {
                                                    printf("Error at line %d: %s - out of float bounds %d.\n", yylineno, yytext, yyleng);
                                                    error = -1;
                                                }
                                                if (error == 0) {
                                                    printf("%-20s%s\n", "FCONSTANT", yytext);
                                                }
                                            }

\"[^"\n]*\" 	                            {
		                                        printf("%-20s%s\n", "STRING", yytext);
                                            }

[/][/].*\n                                  ; // Комментарий

"*"	                                        { 
	                                            printf("%-20s%s\n", "MULOPERATOR", yytext);
	                                        }

"/"|"%"	                                    {  
		                                        printf("%-20s%s\n", "DIVOPERATOR", yytext);
		                                    }

"+"	                                        { 
	                                            printf("%-20s%s\n", "SUMOPERATOR", yytext);
	                                        }

"-"	                                        { 
	                                            printf("%-20s%s\n", "SUBOPERATOR", yytext);
	                                        }

">="|"<="|"<"|">"|"=="|"!="	                { 
		                                        printf("%-20s%s\n", "COMPAREOPERATOR", yytext);
		                                    }
                                            
"&&"|"||"	                                { 
		                                        printf("%-20s%s\n", "BOOLOPERATOR", yytext);
		                                    }

"="                                         {
		                                        printf("%-20s%s\n", "ASSIGNOPERATOR", yytext);
		                                    }
%%

int yywrap () { return 1; }

int main(int argc, char* argv[])
{
    FILE *infile;

    if(argc < 2)
    {
        printf("Too few parameters in command line.\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("Too much parameters in command line.\n");
        return 1;
    }

    infile = fopen(argv[1], "r");

    if (NULL == infile)
        {
            printf("Cannot open file.\n");
            return 1;
        }
    
    yyin = infile;
    yylex();
    fclose(infile);
    return 0;
}