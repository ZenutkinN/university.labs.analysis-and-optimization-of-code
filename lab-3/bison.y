%{
	#include <stdio.h>
	#include <string>
	#include <iostream>
	#include <fstream>
	#include <list>
	#include <vector>
	#include <sstream>
	#include <algorithm>
	#include "utils.h"
	#include "classes.h"

	using namespace std;

	#define YYERROR_VERBOSE 1

	extern int yylineno;
	extern int yylex();
	extern int yylineno;

	string filename;
	stringstream initGlobalVars;
	stringstream globalVars;
	stringstream funcArgs;
	string cycleStr = "";
	string curFuncName;

	int argsSize = 0;
	int gIndexForInitGlob = 1;
	int gMarkCurIndex = 0;
	int gMarkIndex = 0;
	int cycleCounter = 0;
	int boolargIndex = 0;
	int gIndex = 1;
	int gVarIndex = 0;
	int cycleIndex = 0;
	bool needn = true;
	bool mainExists = false;
	bool cycle = false;
	bool retValue = false;
	bool labelExist = false;
	
	vector <valueForPrint*> valuesPrint;
	
	typedef struct {
		string str;
		oper_t* oper;
		expr_t* expr;
		list<expr_t*> exprs;
		list<string> strs;
		list<oper_t*> opers;
	} YYSTYPE;

	#define YYSTYPE YYSTYPE
%}



%token IF
%token ELSE
%token DO
%token WHILE
%token RETURN
%token VALUETYPE
%token BOOL
%token VOID
%token OUTPUT
%token INPUT
%token NIL
%token IDENTIFIER
%token CONSTANT
%token FCONSTANT
%token STRING
%token MULOPERATOR
%token DIVOPERATOR
%token SUMOPERATOR
%token SUBOPERATOR
%token COMPAREOPERATOR
%token BOOLOPERATOR
%token ASSIGNOPERATOR

%left "+" "-"
%left "*" "/" "%"

%type<str> VALUETYPE VOID BOOL IDENTIFIER CONSTANT FCONSTANT STRING MULOPERATOR DIVOPERATOR SUMOPERATOR SUBOPERATOR COMPAREOPERATOR BOOLOPERATOR ASSIGNOPERATOR NIL
%type<expr> boolarg boolargs unaryoper funccall value term expression   
%type<oper> initvariable initemptyvariable scanoper printoper eqoperation cycleoperationwhile ifoperation returnexp initfunc operation programelem
%type<exprs> args
%type<opers> operations initargs initvariablesforfunc program

%%

file: 	program {
	vector<valueForCheck*> values;
	for(oper_t* progel : $1) {
		progel->checkValue(values);
	}
	if (!mainExists) {
		yyerror("Function main doesn't exist!");
	}
	curFuncName = "";
	stringstream file;
	ofstream fileWrite;
	fileWrite.open(filename + ".ll");
	if (fileWrite.is_open()) {
		globalVars << "@.str.d = private unnamed_addr constant [3 x i8] c\"%d\\00\", align 1\n";
		globalVars << "@.str.s = private unnamed_addr constant [3 x i8] c\"%s\\00\", align 1\n";
		globalVars << "@.str.f = private unnamed_addr constant [3 x i8] c\"%f\\00\", align 1\n\n";
		initGlobalVars << "\ndefine void @NoJSInitglobalVars() {\n";
		for(oper_t* progel : $1) {
			progel->print(file);
		}
		initGlobalVars << "\tret void\n}\n";
		file << "\ndeclare i32 @printf(i8*, ...) #0\n";
		file << "declare i32 @scanf(i8*, ...) #0\n";
		file << "declare void @llvm.memcpy.p0i8.p0i8.i64(i8*, i8*, i64, i32, i1)\n";
		file << "declare i8* @strcat(i8*, i8*)\n";
		file << "\nattributes #0 = { \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+fxsr,+mmx,+sse,+sse2,+sse3,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n";
		file << "\n!llvm.module.flags = !{!0}\n";
		file << "\n!0 = !{i32 1, !\"wchar_size\", i32 4}\n";
		fileWrite << globalVars.str();
		fileWrite << initGlobalVars.str();
		fileWrite << file.str();
		fileWrite.close(); 
		string str = "llvm-as ./" + filename + ".ll";
		int result = system(str.c_str());
		if (result == 0) {
			str = "lli ./" + filename + ".bc";
			system(str.c_str());
		}
	} 
}
;

program: 					programelem { $$.clear(); $$.push_back($1); }
|							program programelem { $$ = $1; $$.push_back($2); }
;

programelem: 				initvariable {  }
|							initfunc {  }
;

initfunc:					VALUETYPE IDENTIFIER '(' initargs ')' '{' operations '}' { $$ = new initfunc($1, $2, $4, $7); }
|							VOID IDENTIFIER '(' initargs ')' '{' operations '}' { $$ = new initfunc($1, $2, $4, $7); }
;

operations: 				operation { $$.clear(); $$.push_back($1); }
|       					operations operation { $$ = $1; $$.push_back($2); }
;

operation: 					cycleoperationwhile {  }
|							ifoperation {  }
|							eqoperation {  }
|							funccall { $$ = new funccalloper($1); }
|							initvariable {  }
|							returnexp {  }
|							printoper {  }
|							scanoper {  }
;

initargs: 					{ $$.clear(); }
|							initvariablesforfunc {  }
;

returnexp: 					RETURN expression { $$ = new returnexp($2); }
|							RETURN NIL { $$ = new returnexp(NULL); }
;

ifoperation:				IF '(' boolarg ')' '{' operations '}' { $$ = new ifoper($6, $3, {}); }
|							IF '(' boolarg ')' '{' operations '}' ELSE '{' operations '}' { $$ = new ifoper($6, $3, $10); }
|							IF '(' boolargs ')' '{' operations '}' { $$ = new ifoper($6, $3, {}); }
|							IF '(' boolargs ')' '{' operations '}' ELSE '{' operations '}' { $$ = new ifoper($6, $3, $10); }
;

cycleoperationwhile:		WHILE '(' boolargs ')' '{' operations '}' { $$ = new cycleoperwhile (true, $3, $6); }
|							DO '{' operations '}' WHILE '(' boolargs ')' { $$ = new cycleoperwhile (false, $7, $3); }
;

eqoperation:				IDENTIFIER ASSIGNOPERATOR expression { $$ = new eqoper($1, NULL, "=", $3); }
;

printoper:					OUTPUT'('expression')' { $$ = new printoper($3); }
;

scanoper:					IDENTIFIER  ASSIGNOPERATOR INPUT '(' ')' { $$ = new scanoper($1, NULL); }
;

initvariable:				VALUETYPE IDENTIFIER { $$ = new initvariable($1, $2, NULL, {}); }
|							VALUETYPE IDENTIFIER ASSIGNOPERATOR expression { $$ = new initvariable($1, $2, $4, {}); }
;

funccall:					IDENTIFIER '(' args ')' { $$ = new funccall($1, $3); }
;

expression:					term {  }
|							expression SUMOPERATOR term { $$ = new binary($1, "+", $3);  }
|							expression SUBOPERATOR term { $$ = new binary($1, "-", $3);  }
;

term:						value {  }
|							term MULOPERATOR value { $$ = new binary($1, "*", $3); }
|							term DIVOPERATOR value { $$ = new binary($1, $2, $3); }
;

boolargs:					boolarg BOOLOPERATOR boolarg	{ $$ = new boolargs($1, $2, $3); }
|							boolargs BOOLOPERATOR boolarg 	{ $$ = new boolargs($1, $2, $3); }
;

boolarg:					'!''('boolarg')' { $$ = new boolarg("", $3, "!", NULL, false); }
|							expression COMPAREOPERATOR expression { $$ = new boolarg("", $1, $2, $3, false); }
|							BOOL { $$ = new boolarg($1, NULL, "", NULL, false); }
|							IDENTIFIER { $$ = new boolarg($1, NULL, "", NULL, true); }
;

value:						STRING { $$ = new value($1, "", NULL, "string"); }
|							CONSTANT { $$ = new value($1, "", NULL, "int"); }
|							FCONSTANT { $$ = new value($1, "", NULL, "float"); }
|							BOOL { $$ = new value($1, "", NULL, "bool"); }
|							'(' expression ')' { $$ = new value("", "", $2, ""); }
|							funccall { $$ = new value("", "", $1, ""); }
|							IDENTIFIER { $$ = new value("" ,$1, NULL, ""); }
|							unaryoper { $$ = new value("", "", $1, ""); }
;

unaryoper:					SUBOPERATOR CONSTANT { $$ = new unaryoper("-", $2, "", NULL, "int"); }
|							SUBOPERATOR FCONSTANT { $$ = new unaryoper("-", $2, "", NULL, "float"); }
|							SUBOPERATOR IDENTIFIER { $$ = new unaryoper("-", "", $2, NULL, ""); }
|							'!' IDENTIFIER { $$ = new unaryoper("!", "", $2, NULL, ""); }
;

args:	 					{ $$.clear(); } 
|							expression { $$.clear(); $$.push_back($1); } 
|							args',' expression { $$ = $1; $$.push_back($3); } 
;

initvariablesforfunc:		initemptyvariable { $$.clear(); $$.push_back($1); } 
|							initvariablesforfunc ',' initemptyvariable { $$ = $1; $$.push_back($3); } 
;

initemptyvariable:			VALUETYPE IDENTIFIER { $$ = new initvariable($1, $2, NULL, {}, true); }
;

%%

int main(int argc, char** argv)
{
	if (argc == 2) {
		filename = argv[1];
	} else {
		filename = "result";
	}
    int result = yyparse();
    return result;
}
