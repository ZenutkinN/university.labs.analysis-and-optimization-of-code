/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./src/syntactical-analyzer/bison.y"

	#include <stdio.h>
	#include <string>
	#include <iostream>
	#include <list>
	#include <vector>
	#include <sstream>

	using namespace std;

	#define YYERROR_VERBOSE 1

	extern int yylineno;
	extern int yylex();

	bool needn = true;
	int cycleCounter = 0;
	string filename;

	void yyerror(char* s) {
		fprintf (stderr, "Line %d - \"%s\"\n", yylineno, s);
		exit(1);
	}

	void yyerror(const char* s) {
		fprintf (stderr, "Line %d - \"%s\"\n", yylineno, s);
		exit(1);
	}

	void yyerror(string str, int gline) {
		const char *s = str.c_str();
		fprintf (stderr, "Line %d - \"%s\"\n", gline, s);
		exit(1);
	}
	
	string curFuncName;

	/*! \class valueForCheck
 	*  \brief Содержит информацию о переменной или функции, которые были инициализированы
 	*/
	class valueForCheck {
		public: 
			int line = yylineno;  
			string val;
			string identifier;
			vector<valueForCheck*> structVal;
			vector<valueForCheck*> funcArgs;
			string size;
			valueForCheck(const string& val, const string& identifier, vector<valueForCheck*> structVal, const string& size = "0") : val(val), identifier(identifier), structVal(structVal), size(size) {}
	};

	
	string getSize(vector<valueForCheck*> values, string identifier, string sidentifier = "", bool arr = false) {
		for (int i = 0; i < values.size(); i++) {
			if (values.at(i)->identifier == identifier) {
				if (sidentifier == "") {
					return values.at(i)->size;
				} else {
					for (int k = 0; k < values.size(); k++) {
						if (!arr) {
							if (values.at(k) -> identifier == values.at(i) -> val) {
								for (int j = 0; j < values.at(k)->structVal.size(); j++) {
									if (values.at(k)->structVal.at(j)->identifier == sidentifier) {
										return values.at(k)->structVal.at(j)->size;
									}
								}
							}
						} else {
							if (values.at(k) -> identifier == values.at(i) -> val.substr(0, values.at(i) -> val.size() - 2)) {
								for (int j = 0; j < values.at(k)->structVal.size(); j++) {
									if (values.at(k)->structVal.at(j)->identifier == sidentifier) {
										return values.at(k)->structVal.at(j)->size;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	string getType(vector<valueForCheck*> values, string identifier, string sidentifier = "") {
		for (int i = 0; i < values.size(); i++) {
			if (values.at(i)->identifier == identifier) {
				if (sidentifier == "") {
					return values.at(i)->val;
				} else {
					for (int k = 0; k < values.size(); k++) {
							if (values.at(k) -> identifier == values.at(i) -> val) {
								for (int j = 0; j < values.at(k)->structVal.size(); j++) {
									if (values.at(k)->structVal.at(j)->identifier == sidentifier) {
										return values.at(k)->structVal.at(j)->val;
									}
								}
							}
					}
				}
			}
		}
	}
	
	bool checkValueExist(vector<valueForCheck*> values, string identifier) {
		for (int i = 0; i < values.size(); i++) {
			if (values.at(i)->identifier == identifier) {
				return true;
			}
		}
		return false;
	}

	bool checkValueExist(vector<valueForCheck*> values, string identifier, string func, string secarg = "", int count = 0) {
		if (func == "func") {
			for (int i = 0; i < values.size(); i++) {
				if (values.at(i)->identifier == identifier && values.at(i)->funcArgs.size() == count && (values.at(i)->val == "int()" || values.at(i)->val == "bool()" || values.at(i)->val == "string()" || values.at(i)->val == "float()" || values.at(i)->val == "void()")) {
					return true;
				}
			}
			return false;
		}

		if (func == "label") {
			for (int i = 0; i < values.size(); i++) {
				if (values.at(i)->identifier == identifier && values.at(i)->val == "label") {
					return true;
				}
			}
			return false;
		}
		
		return false;
	}

	string getArgType(vector<valueForCheck*> values, string identifier, int count, int numberOfArg) {
		for (int i = 0; i < values.size(); i++) {
			if (values.at(i)->identifier == identifier && (values.at(i)->val == "int()" || values.at(i)->val == "bool()" || values.at(i)->val == "string()" || values.at(i)->val == "float()" || values.at(i)->val == "void()") && values.at(i)->funcArgs.size() == count) {
				return values.at(i)->funcArgs.at(numberOfArg)->val;
			}
		}
	}

	/*! \class oper_t
 	*  \brief Реализация операций
 	*/
	class oper_t {
		public: 
			int line = yylineno; 
			oper_t() {}
			virtual ~oper_t() {}
			virtual void print(int indent = 0) = 0;
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) = 0;
	};

	/*! \class expr_t
 	*  \brief Реализация выражений
 	*/	
	class expr_t {
		string type;
		public: 
			int line = yylineno; 
			expr_t() {}
			virtual ~expr_t() {}
			virtual void print() = 0;
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) = 0;
			virtual string checkType() = 0;
	};

	/*! \class boolargs
 	*  \brief Совокупность bool-выражений
 	*
	*  Содержится в условиях while, do-while, if
 	*/	
	class boolargs : public expr_t {
		expr_t* fexp;
		string oper;
		expr_t* sexp;
		public: 
			int line = yylineno;  boolargs(expr_t* fexp, const string& oper, expr_t* sexp) : fexp(fexp), oper(oper), sexp(sexp) {}
			virtual void print() {
				fexp->print();
				if (sexp != NULL) {
					cout << " " << oper << " ";
					sexp->print();
				}
			}
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				fexp->checkValue(values);
				if (sexp != NULL) {
					sexp->checkValue(values);
				}
			}
			virtual string checkType() {
				if (sexp != NULL) {
					if (fexp-> checkType() == "bool") {
						return "bool";
					}
				} else {
					if (fexp->checkType() == sexp->checkType()) {
						return "bool";
					}
				}
			}
	};

	/*! \class initfunc
 	*  \brief Реализация инициализации функции
 	*
 	*/
	class initfunc : public oper_t {
		string var;
		string identifier;
		list<oper_t*> args;
		list<oper_t*> opers;

		public: 
			int line = yylineno;  initfunc(const string& var, const string& identifier, list<oper_t*> args, list<oper_t*> opers) : var(var), identifier(identifier), args(args), opers(opers) {}

			virtual void print(int indent = 0) {
				string str = "";
				for (int i = 0; i < indent; i++) {
					str += "\t";
				}

				cout << str << var << " " << identifier << "(";
				for (oper_t* arg : args) {
					needn = false;
					arg->print(0);
					if (arg != args.back()) {
						cout << ", ";
					}
				}
				
				cout << ")";
				if (opers.size() != 0) {
					cout << " {\n";
					for (oper_t* oper : opers) {
						oper->print(indent + 1);
					}
					cout << "}";
				}
				cout << "\n";
			}

			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				vector<valueForCheck*> newVec;
				newVec.insert(newVec.end(), values.begin(), values.end());
				for (oper_t* arg : args) {
					arg->checkValue(newVec);
				}
				if (checkValueExist(values, identifier)) {
					yyerror("Identifier " + identifier + " already exists!", line);
				}
				vector<valueForCheck*> argVec;
				for (int i = 0; i < newVec.size(); i++) {
					bool exist = false;
					for (int j = 0; j < values.size(); j++) {
						if (newVec.at(i) == values.at(j)) {
							exist = true;
							break;
						}
					}
					if (!exist) {
						argVec.push_back(newVec.at(i));
					}
				}

				curFuncName = identifier;
				valueForCheck* valClass = new valueForCheck(var + "()", identifier, {});
				valClass->funcArgs = argVec;
				values.push_back(valClass);
				newVec.push_back(valClass);
				if (opers.size() != 0) {
					for (oper_t* oper : opers) {
						oper->checkValue(newVec);
					}
				}
			}
	};

	/*! \class returnexp
 	*  \brief Реализация операции return
 	*/
	class returnexp : public oper_t {
		expr_t* arg;
		public: 
			int line = yylineno;  returnexp(expr_t* arg) : arg(arg) {}

			virtual void print(int indent = 0) {
				string str = "";
				for (int i = 0; i < indent; i++) {
					str += "\t";
				}
				cout << str << "return ";
				if (arg != NULL) {
					arg->print();
					cout << "\n";
				} else {
					cout << "NULL\n";
				}
			}

			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				if (arg != NULL) {
					arg->checkValue(values);
					if (arg->checkType() + "()" != getType(values, curFuncName)) {
						yyerror("Wrong type of argument! Expected " + getType(values, curFuncName), line);
					}
				}
			}
	};

	/*! \class ifoper
 	*  \brief Реализация if
 	*/
	class ifoper : public oper_t {
		list<oper_t*> iftrue;
		expr_t* boolarg;
		list<oper_t*> iffalse;
		public: 
			int line = yylineno;  ifoper(list<oper_t*> iftrue, expr_t* boolarg, list<oper_t*> iffalse) : iftrue(iftrue), boolarg(boolarg), iffalse(iffalse) {}
			virtual void print(int indent = 0) {
				string str = "";
				for (int i = 0; i < indent; i++) {
					str += "\t";
				}
				cout << str << "if(";
				boolarg->print();
				cout << ") {\n";
				for (oper_t* iftr : iftrue) {
					iftr->print(indent + 1);
				}
				cout << str << "}";
				if (iffalse.size() != 0) {
					cout << " else {\n";
					for (oper_t* iffl : iffalse) {
						iffl->print(indent + 1);
					}
					cout << str << "}";
				}
				cout << "\n";
			}

			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				vector<valueForCheck*> newVec;
				newVec.insert(newVec.end(), values.begin(), values.end());
				if (boolarg->checkType() != "bool") {
					yyerror("Wrong type of argument! Expected bool", line);
				}
				for (oper_t* iftr : iftrue) {
					iftr->checkValue(newVec);
				}
				boolarg->checkValue(newVec);
				vector<valueForCheck*> newVec2;
				newVec2.insert(newVec2.end(), values.begin(), values.end());
				if (iffalse.size() != 0) {
					for (oper_t* iffl : iffalse) {
						iffl->checkValue(newVec2);
					}
				}
			}
	};

	/*! \class cycleoperwhile
 	*  \brief Реализация while
 	*/
	class cycleoperwhile : public oper_t {
		bool whilefirst;
		expr_t* boolarg;
		list<oper_t*> opers;
		public: 
			int line = yylineno;  cycleoperwhile(bool whilefirst, expr_t* boolarg, list<oper_t*> opers) : whilefirst(whilefirst), boolarg(boolarg), opers(opers) {}
			
			virtual void print(int indent = 0) {
				string str = "";
				for (int i = 0; i < indent; i++) {
					str += "\t";
				}
				cout << str;
				if (whilefirst) {
					cout << "while(";
					boolarg->print();
					cout << ") {\n";
					for (oper_t* oper : opers) {
						oper->print(indent + 1);
					}
					cout << str << "}";
				} else {
					cout << "do {\n";
					for (oper_t* oper : opers) {
						oper->print(indent + 1);
					}
					cout << str << "} while(";
					boolarg->print();
					cout << ")";
				}
				cout << "\n";
			}

			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				cycleCounter++;
				vector<valueForCheck*> newVec;
				newVec.insert(newVec.end(), values.begin(), values.end());
				boolarg->checkValue(newVec);
				for (oper_t* oper : opers) {
					oper->checkValue(newVec);
				}
				if (boolarg->checkType() != "bool") {
					yyerror("Wrong type of argument! Expected bool", line);
				}
				cycleCounter--;
			}
	};

	/*! \class eqoper
 	*  \brief Реализация операции присваивания
 	*/
	class eqoper: public oper_t {
		string identifier;
		expr_t* id;
		string oper;
		expr_t* expr;
		public: 
			int line = yylineno;  eqoper(const string& identifier, expr_t* id, const string& oper, expr_t* expr) : identifier(identifier), id(id), oper(oper), expr(expr) {}
			virtual void print(int indent = 0) {
				string str = "";
				for (int i = 0; i < indent; i++) {
					str += "\t";
				}
				cout << str;
				if (identifier == "") {
					id->print();
				} else {
					cout << identifier;
				}
				cout << " " << oper << " ";
				expr->print();
				cout << "\n";
			}
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				if (identifier != "") {
					if (!checkValueExist(values, identifier)) {
						yyerror("Identifier " + identifier + " doesn't exist!", line);
					}
				} else {
					id->checkValue(values);
				}
				expr->checkValue(values);
				if (identifier != "") {
					if (getType(values, identifier) != expr->checkType()) {
						yyerror("Wrong type of argument! Expected " + getType(values, identifier), line);
					}
				} else {
					if (id->checkType() != expr->checkType()) {
						yyerror("Wrong type of argument! Expected " + id->checkType(), line);
					}
				}
			}
	};

	/*! \class printoper
 	*  \brief Реализация операции вывода
 	*/
	class printoper: public oper_t {
		expr_t* id;
		public: 
			int line = yylineno;  printoper(expr_t* id) : id(id) {  }
			virtual void print(int indent = 0) {
				string str = "";
				for (int i = 0; i < indent; i++) {
					str += "\t";
				}
				cout << str << "stdout(";
				id->print();
				cout << ")\n";
			}
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				id->checkValue(values);
			}
	};

	/*! \class scanoper
 	*  \brief Реализация операции ввода
 	*/
	class scanoper: public oper_t {
		string identifier;
		expr_t* id;
		public: 
			int line = yylineno;  scanoper(const string& identifier, expr_t* id) : identifier(identifier), id(id) {}
			virtual void print(int indent = 0) {
				string str = "";
				for (int i = 0; i < indent; i++) {
					str += "\t";
				}
				cout << str;
				if (identifier == "") {
					id->print();
				} else {
					cout << identifier;
				}
				cout << " = stdin()\n";
			}

			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				if (identifier != "") {
					if (!checkValueExist(values, identifier)) {
						yyerror("Identifier " + identifier + " doesn't exist!", line);
					}
				} else {
					id->checkValue(values);
				}
			}
	};

	/*! \class initvariable
 	*  \brief Реализация инициализацию переменных
 	*/
	class initvariable: public oper_t {
		string var;
		string identifier;
		expr_t* exprs;
		list<oper_t*> opers;

		public: 
			int line = yylineno;  initvariable(const string& var, const string& identifier, expr_t* exprs, list<oper_t*> opers) : var(var), identifier(identifier), exprs(exprs), opers(opers) {}
			virtual void print(int indent = 0) {
				string str = "";
				for (int i = 0; i < indent; i++) {
					str += "\t";
				}
				cout << str << var << " " << identifier;
				
				if (exprs != NULL) {
					cout << " = ";
					exprs->print();
				}
				
				if (needn) {
					cout << "\n";
				} else {
					needn = true;
				}
			}

			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				if (exprs != NULL) {
					exprs->checkValue(values);
				}

				if (add) {
					if (!checkValueExist(values, identifier)) {
						values.push_back(new valueForCheck(var, identifier, {}));
					} else {
						yyerror("Identifier " + identifier + " already exists!", line);
					}
				} else {
					values.push_back(new valueForCheck(var, identifier, {}));
				}
			}
	};

	/*! \class funccall
 	*  \brief Реализация вызова функции
 	*/
	class funccall: public expr_t {
		string identifier;
		list<expr_t*> args;
		vector<valueForCheck*> typeTest;
		public: 
			int line = yylineno;  funccall(const string& identifier, list<expr_t*> args) : identifier(identifier), args(args) {}
			virtual void print() {
				cout << identifier << '(';
				if (args.size() != 0) {
					int i = 0;
					for (expr_t* arg : args) {
						arg->print();
						if ( i != args.size() - 1) {
							cout << ',';
						}
						i++;
					}
				}
				cout << ')';
			}
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				typeTest = values;
				if (!checkValueExist(values, identifier, "func", "", args.size())) {
					yyerror("Wrong count of arguments!", line);
				}
				int i = 0;
				for (expr_t* arg : args) {
					arg->checkValue(values);
				}
				for (expr_t* arg : args) {
					if (getArgType(values, identifier, args.size(), i) != arg->checkType()) {
						ostringstream os;
						os << i + 1;
						string arg = "Argument №" + os.str() + " has wrong type!";
						yyerror(arg, line);
					}
					i++;
				}
			}
			virtual string checkType() {
				string str = getType(typeTest, identifier);
				return str.substr(0, str.size() - 2);
			}
	};

	/*! \class funccalloper
 	*  \brief Реализация вызова функции, содержащейся в выражении
 	*/
	class funccalloper: public oper_t {
		expr_t* func;
		public: 
			int line = yylineno;  funccalloper(expr_t* func) : func(func) {}
			virtual void print(int indent = 0) {
				string str = "";
				for (int i = 0; i < indent; i++) {
					str += "\t";
				}
				cout << str;
				func->print();
				cout << "\n";
			}
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				func->checkValue(values);
			}
	};

	/*! \class binary
 	*  \brief Реализация бинарных операций
 	*/
	class binary : public expr_t {
		expr_t* fexp;
		string oper;
		expr_t* sexp;
		public: 
			int line = yylineno;  binary(expr_t* fexp, const string& oper, expr_t* sexp) : fexp(fexp), oper(oper), sexp(sexp) {}
			virtual void print() {
				fexp->print();
				cout << " " << oper << " ";
				if (sexp != NULL) {
					sexp->print();
				}
			}
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				fexp->checkValue(values);
				if (sexp != NULL) {
					sexp->checkValue(values);
					if (fexp->checkType() != sexp->checkType()) {
						yyerror("Wrong type of argument! Expected " + fexp->checkType(), line);
					}
				}
			}
			virtual string checkType() {
				if (sexp != NULL) {
					if (sexp->checkType() == fexp->checkType()) {
						return fexp->checkType();
					} else {
						yyerror("Wrong type of argument! Expected " + fexp->checkType(), line);
					}
				} else {
					return fexp->checkType();
				}
			}
	};

	/*! \class boolarg
 	*  \brief Реализация bool-выражение
 	*
	*  Содержится в условиях while, do-while, if
 	*/	
	class boolarg : public expr_t {
		string fexps;
		expr_t* fexp;
		string oper;
		expr_t* sexp;
		bool fexpsiden;
		public: 
			int line = yylineno;  boolarg(const string& fexps, expr_t* fexp, const string& oper, expr_t* sexp, const bool& fexpsiden) : fexps(fexps), fexp(fexp), oper(oper), sexp(sexp), fexpsiden(fexpsiden) {}
			virtual void print() {
				if (oper == "!") {
					cout << "!(";
					fexp->print();
					cout << ")";
				} else {
					if (fexps == "") {
						fexp->print();
						if (oper != "") {
							cout << " " << oper << " ";
							sexp->print();
						}
					} else {
						cout << fexps;
					}
				}
			}
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				if (fexps != "") {
					if (fexps != "true" && fexps != "false") {
						if (!checkValueExist(values, fexps)) {
							yyerror("Identifier " + fexps + " doesn't exist!", line);
						}
					}
				} else {
					fexp->checkValue(values);
				}
				if (sexp != NULL) {
					sexp->checkValue(values);
				}
				if (sexp == NULL) {
					if (fexp == NULL && fexpsiden) {
						if (getType(values, fexps) != "bool") {
							yyerror("Wrong type of argument! Expected bool", line);
						}
					} else if (fexp != NULL) {
						if (fexp->checkType() != "bool") {
							yyerror("Wrong type of argument! Expected bool", line);
						}
					} else if (fexps != "true" && fexps != "false") {
						yyerror("Wrong type of argument! Expected bool", line);
					}
				} else {
					if (fexp == NULL && fexpsiden) {
						if (getType(values, fexps) != sexp->checkType()) {
							yyerror("Wrong type of argument! Expected " + getType(values, fexps), line);
						}
					} else if (fexp != NULL) {
						if (fexp->checkType() != sexp->checkType()) {
							yyerror("Wrong type of argument! Expected " + fexp->checkType(), line);
						}
					} else {
						yyerror("Wrong type of argument!", line);
					}
				}
			}
			virtual string checkType() {
				return "bool";
			}
	};

	/*! \class value
 	*  \brief Реализация единичного значения в бинарной операции
 	*/	
	class value : public expr_t {
		string constant;
		string identifier;
		expr_t* id;
		string type;
		vector<valueForCheck*> typeTest;
		public: 
			int line = yylineno;  value(const string& constant, const string& identifier, expr_t* id, const string& type) : constant(constant), identifier(identifier), id(id), type(type) {}
			virtual void print() {
				if (id != NULL) {
					id->print();
				} else if (constant != "") {
					cout << constant;
				} else {
					cout << identifier;
				}
			}
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				typeTest = values;
				if (identifier != "") {
					if (!checkValueExist(values, identifier)) {
						yyerror("Identifier " + identifier + " doesn't exist!", line);
					}
				} else if (id != NULL) {
					id->checkValue(values);
				}
			}
			virtual string checkType() {
				if (id != NULL) {
					return id->checkType();
				}
				if (identifier != "") {
					if (!checkValueExist(typeTest, identifier)) {
						yyerror("Identifier " + identifier + " doesn't exist!", line);
					} else {
						return getType(typeTest, identifier);
					}
				}
				if (constant != "") {
					return type;
				}
			}
	};

	/*! \class unaryoper
 	*  \brief Реализация унарных операции(!,-)
 	*/
	class unaryoper : public expr_t {
		string oper;
		string constant;
		string identifier;
		expr_t* id;
		string argType;
		vector<valueForCheck*> typeTest;
		public: 
			int line = yylineno;  unaryoper(const string& oper, const string& constant, const string& identifier, expr_t* id, const string& argType) : oper(oper), constant(constant), identifier(identifier), id(id), argType(argType) {}
			virtual void print() 	{ 
						if (constant != "") {
							cout << oper << constant;
						} else if (identifier != "") {
							cout << oper << identifier;
						} else {
							cout << oper;
							id->print();
						}
					}
			virtual void checkValue(vector<valueForCheck*>& values, bool add = true) {
				if (identifier != "") {
					if (!checkValueExist(values, identifier)) {
						yyerror("Identifier " + identifier + " doesn't exist!", line);
					}
				} else if (id != NULL) {
					id->checkValue(values);
				}
				if (oper == "-") {
					if (identifier != "") {
						if (getType(values, identifier) != "int" && getType(values, identifier) != "float") {
							yyerror("Wrong type of argument! Expected int or float", line);
						}
					}
					if (id != NULL) {
						if (id->checkType() != "int" && id->checkType() != "float") {
							yyerror("Wrong type of argument! Expected int or float", line);
						}
					}
					if (constant != "") {
						if (argType != "int" && argType != "float") {
						yyerror("Wrong type of argument! Expected int or float", line);
						}
					}
				} else {
					if (identifier != "") {
						if (getType(values, identifier) != "int" && getType(values, identifier) != "bool") {
							yyerror("Wrong type of argument! Expected int or bool", line);
						}
					}
					if (id != NULL) {
						if (id->checkType() != "int" && id->checkType() != "bool") {
							yyerror("Wrong type of argument! Expected int or bool", line);
						}
					}
					if (constant != "") {
						if (argType != "int" && argType != "bool") {
						yyerror("Wrong type of argument! Expected int or bool", line);
						}
					}
				}
			}
			virtual string checkType() {
				if (identifier != "") {
					return getType(typeTest, identifier);
				}
				if (id != NULL) {
					return id->checkType();
				}
				if (constant != "") {
					return argType;
				}
			} 
	};
	
	typedef struct {
		string str;
		oper_t* oper;
		expr_t* expr;
		list<expr_t*> exprs;
		list<string> strs;
		list<oper_t*> opers;
	} YYSTYPE;
	#define YYSTYPE YYSTYPE

#line 946 "bison.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    DO = 260,
    WHILE = 261,
    RETURN = 262,
    VALUETYPE = 263,
    BOOL = 264,
    VOID = 265,
    OUTPUT = 266,
    INPUT = 267,
    NIL = 268,
    IDENTIFIER = 269,
    CONSTANT = 270,
    FCONSTANT = 271,
    STRING = 272,
    MULOPERATOR = 273,
    DIVOPERATOR = 274,
    SUMOPERATOR = 275,
    SUBOPERATOR = 276,
    COMPAREOPERATOR = 277,
    BOOLOPERATOR = 278,
    ASSIGNOPERATOR = 279
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

#define YYUNDEFTOK  2
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,     2,     2,     2,     2,     2,
      30,    31,     2,     2,    35,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   911,   911,   923,   924,   927,   928,   931,   932,   935,
     936,   939,   940,   941,   942,   943,   944,   945,   946,   949,
     950,   953,   954,   957,   958,   959,   960,   963,   964,   965,
     966,   969,   972,   975,   978,   979,   982,   985,   986,   987,
     990,   991,   992,   995,   996,   999,  1000,  1001,  1002,  1005,
    1006,  1007,  1008,  1009,  1010,  1011,  1012,  1015,  1016,  1017,
    1018,  1021,  1022,  1023,  1026,  1027,  1030
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "DO", "WHILE", "RETURN",
  "VALUETYPE", "BOOL", "VOID", "OUTPUT", "INPUT", "NIL", "IDENTIFIER",
  "CONSTANT", "FCONSTANT", "STRING", "MULOPERATOR", "DIVOPERATOR",
  "SUMOPERATOR", "SUBOPERATOR", "COMPAREOPERATOR", "BOOLOPERATOR",
  "ASSIGNOPERATOR", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"%\"", "'('",
  "')'", "'{'", "'}'", "'!'", "','", "$accept", "file", "program",
  "programelem", "initfunc", "operations", "operation", "initargs",
  "returnexp", "ifoperation", "cycleoperationwhile", "eqoperation",
  "printoper", "scanoper", "initvariable", "funccall", "expression",
  "term", "boolargs", "boolarg", "value", "unaryoper", "args",
  "initvariablesforfunc", "initemptyvariable", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      40,    41,   123,   125,    33,    44
};
# endif

#define YYPACT_NINF (-79)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-49)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      16,   -11,    -4,    33,    16,   -79,   -79,   -79,   -23,    13,
     -79,   -79,   190,    47,    47,   -79,    32,   -79,   -79,   -79,
     187,   190,    51,   -79,   170,   223,   -79,   -79,    63,    49,
      61,   -79,    53,   190,   -79,   -79,   -79,    39,   -79,   190,
     190,   190,   190,   -79,    89,    47,   102,   170,    40,   -79,
     223,   223,   -79,   -79,   222,   -79,   222,   -79,   190,   101,
     112,   111,   179,   137,   134,    28,    34,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,    99,   170,   201,   222,
     201,   -79,   170,   143,   190,     2,   -79,   -79,   -79,    -1,
      26,   -10,   217,    30,    58,   109,    70,    80,    98,   139,
     170,   201,   190,   201,   129,   201,   145,   168,   155,   180,
     -79,   153,   166,   170,   -79,   222,   -79,   222,   184,   222,
     222,   -79,   -79,   119,   132,   201,   142,   152,   215,   219,
     105,   131,   -79,   -79,   189,   194,   -79,   -79,   222,   222,
     165,   175,   -79,   -79
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     3,     6,     5,    34,     0,
       1,     4,     0,    19,    19,    52,    55,    50,    51,    49,
       0,     0,     0,    54,    35,    37,    40,    56,     0,     0,
      20,    64,     0,    61,    59,    57,    58,     0,    60,     0,
       0,     0,     0,    66,     0,     0,     0,    62,     0,    53,
      38,    39,    41,    42,     0,    65,     0,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,    16,    12,
      11,    13,    17,    18,    15,    14,     0,    63,     0,     0,
       0,    22,    21,    34,     0,     0,     7,    10,     8,    52,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      32,     0,     0,    46,    44,     0,    43,     0,     0,     0,
       0,    33,    45,     0,     0,     0,     0,     0,    25,    23,
       0,     0,    27,    29,     0,     0,    28,    30,     0,     0,
       0,     0,    26,    24
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   -79,   228,   -79,   -51,   -32,   220,   -79,   -79,
     -79,   -79,   -79,   -79,     8,   -41,   -12,   204,   -78,   -74,
     205,   -79,   -79,   -79,   195
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    66,    67,    29,    68,    69,
      70,    71,    72,    73,    74,    23,    92,    25,    93,    94,
      26,    27,    48,    30,    31
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      24,    12,    96,     8,    38,    76,    97,    13,     7,    37,
       9,    15,     7,    75,    99,    75,    16,    17,    18,    19,
     101,    47,   -47,    20,     1,    75,     2,   112,    95,   114,
     -47,   116,    21,    10,    87,    75,    22,    59,    75,    60,
      61,    62,    63,    14,    87,    64,    77,   130,    65,   -48,
      82,   131,    85,   103,    75,    28,    33,   -48,    33,    39,
      40,   104,    33,    87,   123,    38,   124,    86,   126,   127,
      49,    57,    98,   100,    75,    58,    75,    43,    75,    75,
      44,   105,    75,    75,    46,    75,    75,   140,   141,   106,
     113,    87,    87,   103,    87,    87,    45,    75,    75,    75,
      75,   108,    59,   105,    60,    61,    62,    63,    87,    87,
      64,   109,    59,    65,    60,    61,    62,    63,    39,    40,
      64,    54,    59,    65,    60,    61,    62,    63,   103,   110,
      64,    78,    88,    65,    56,    59,   136,    60,    61,    62,
      63,    80,   107,    64,    79,    59,    65,    60,    61,    62,
      63,    83,   128,    64,   105,    59,    65,    60,    61,    62,
      63,   115,   137,    64,    84,   129,    65,    12,    59,   111,
      60,    61,    62,    63,   118,   132,    64,   117,    59,    65,
      60,    61,    62,    63,   121,   133,    64,   119,    15,    65,
      39,    40,    81,    16,    17,    18,    19,   122,   142,    15,
      20,    34,    35,    36,    16,    17,    18,    19,   143,    21,
      89,    20,   120,    22,   125,    90,    17,    18,    19,   134,
      21,   138,    20,   135,    22,    59,   139,    60,    61,    62,
      63,    21,    11,    64,    32,    91,    65,    39,    40,   102,
      55,    41,    42,    50,    51,     0,    52,    53
};

static const yytype_int16 yycheck[] =
{
      12,    24,    80,    14,    14,    56,    80,    30,     0,    21,
      14,     9,     4,    54,    12,    56,    14,    15,    16,    17,
      30,    33,    23,    21,     8,    66,    10,   101,    79,   103,
      31,   105,    30,     0,    66,    76,    34,     3,    79,     5,
       6,     7,     8,    30,    76,    11,    58,   125,    14,    23,
      62,   125,    24,    23,    95,     8,    30,    31,    30,    20,
      21,    31,    30,    95,   115,    14,   117,    33,   119,   120,
      31,    31,    84,    85,   115,    35,   117,    14,   119,   120,
      31,    23,   123,   124,    31,   126,   127,   138,   139,    31,
     102,   123,   124,    23,   126,   127,    35,   138,   139,   140,
     141,    31,     3,    23,     5,     6,     7,     8,   140,   141,
      11,    31,     3,    14,     5,     6,     7,     8,    20,    21,
      11,    32,     3,    14,     5,     6,     7,     8,    23,    31,
      11,    30,    33,    14,    32,     3,    31,     5,     6,     7,
       8,    30,    33,    11,    32,     3,    14,     5,     6,     7,
       8,    14,    33,    11,    23,     3,    14,     5,     6,     7,
       8,    32,    31,    11,    30,    33,    14,    24,     3,    30,
       5,     6,     7,     8,     6,    33,    11,    32,     3,    14,
       5,     6,     7,     8,    31,    33,    11,    32,     9,    14,
      20,    21,    13,    14,    15,    16,    17,    31,    33,     9,
      21,    14,    15,    16,    14,    15,    16,    17,    33,    30,
       9,    21,    32,    34,    30,    14,    15,    16,    17,     4,
      30,    32,    21,     4,    34,     3,    32,     5,     6,     7,
       8,    30,     4,    11,    14,    34,    14,    20,    21,    22,
      45,    18,    19,    39,    40,    -1,    41,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    10,    37,    38,    39,    40,    50,    14,    14,
       0,    39,    24,    30,    30,     9,    14,    15,    16,    17,
      21,    30,    34,    51,    52,    53,    56,    57,     8,    43,
      59,    60,    43,    30,    14,    15,    16,    52,    14,    20,
      21,    18,    19,    14,    31,    35,    31,    52,    58,    31,
      53,    53,    56,    56,    32,    60,    32,    31,    35,     3,
       5,     6,     7,     8,    11,    14,    41,    42,    44,    45,
      46,    47,    48,    49,    50,    51,    41,    52,    30,    32,
      30,    13,    52,    14,    30,    24,    33,    42,    33,     9,
      14,    34,    52,    54,    55,    41,    54,    55,    52,    12,
      52,    30,    22,    23,    31,    23,    31,    33,    31,    31,
      31,    30,    55,    52,    55,    32,    55,    32,     6,    32,
      32,    31,    31,    41,    41,    30,    41,    41,    33,    33,
      54,    55,    33,    33,     4,     4,    31,    31,    32,    32,
      41,    41,    33,    33
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    40,    40,    41,
      41,    42,    42,    42,    42,    42,    42,    42,    42,    43,
      43,    44,    44,    45,    45,    45,    45,    46,    46,    46,
      46,    47,    48,    49,    50,    50,    51,    52,    52,    52,
      53,    53,    53,    54,    54,    55,    55,    55,    55,    56,
      56,    56,    56,    56,    56,    56,    56,    57,    57,    57,
      57,    58,    58,    58,    59,    59,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     8,     8,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     2,     2,     7,    11,     7,    11,     7,     8,     7,
       8,     3,     4,     5,     2,     4,     4,     1,     3,     3,
       1,     3,     3,     3,     3,     4,     3,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     2,     2,     2,
       2,     0,     1,     3,     1,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 911 "./src/syntactical-analyzer/bison.y"
              {
	vector<valueForCheck*> values;
	for(oper_t *progel : (yyvsp[0].opers)) {
		progel->checkValue(values);
	}
	
	for(oper_t *progel : (yyvsp[0].opers)) {
		progel->print();
	} 
}
#line 2311 "bison.tab.c"
    break;

  case 3:
#line 923 "./src/syntactical-analyzer/bison.y"
                                                            { (yyval.opers).clear(); (yyval.opers).push_back((yyvsp[0].oper)); }
#line 2317 "bison.tab.c"
    break;

  case 4:
#line 924 "./src/syntactical-analyzer/bison.y"
                                                                            { (yyval.opers) = (yyvsp[-1].opers); (yyval.opers).push_back((yyvsp[0].oper)); }
#line 2323 "bison.tab.c"
    break;

  case 5:
#line 927 "./src/syntactical-analyzer/bison.y"
                                                     {  }
#line 2329 "bison.tab.c"
    break;

  case 6:
#line 928 "./src/syntactical-analyzer/bison.y"
                                                                 {  }
#line 2335 "bison.tab.c"
    break;

  case 7:
#line 931 "./src/syntactical-analyzer/bison.y"
                                                                                                         { (yyval.oper) = new initfunc((yyvsp[-7].str), (yyvsp[-6].str), (yyvsp[-4].opers), (yyvsp[-1].opers)); }
#line 2341 "bison.tab.c"
    break;

  case 8:
#line 932 "./src/syntactical-analyzer/bison.y"
                                                                                                            { (yyval.oper) = new initfunc("void", (yyvsp[-6].str), (yyvsp[-4].opers), (yyvsp[-1].opers)); }
#line 2347 "bison.tab.c"
    break;

  case 9:
#line 935 "./src/syntactical-analyzer/bison.y"
                                                  { (yyval.opers).clear(); (yyval.opers).push_back((yyvsp[0].oper)); }
#line 2353 "bison.tab.c"
    break;

  case 10:
#line 936 "./src/syntactical-analyzer/bison.y"
                                                                     { (yyval.opers) = (yyvsp[-1].opers); (yyval.opers).push_back((yyvsp[0].oper)); }
#line 2359 "bison.tab.c"
    break;

  case 11:
#line 939 "./src/syntactical-analyzer/bison.y"
                                                                    {  }
#line 2365 "bison.tab.c"
    break;

  case 12:
#line 940 "./src/syntactical-analyzer/bison.y"
                                                                    {  }
#line 2371 "bison.tab.c"
    break;

  case 13:
#line 941 "./src/syntactical-analyzer/bison.y"
                                                                    {  }
#line 2377 "bison.tab.c"
    break;

  case 14:
#line 942 "./src/syntactical-analyzer/bison.y"
                                                                 { (yyval.oper) = new funccalloper((yyvsp[0].expr)); }
#line 2383 "bison.tab.c"
    break;

  case 15:
#line 943 "./src/syntactical-analyzer/bison.y"
                                                                     {  }
#line 2389 "bison.tab.c"
    break;

  case 16:
#line 944 "./src/syntactical-analyzer/bison.y"
                                                                  {  }
#line 2395 "bison.tab.c"
    break;

  case 17:
#line 945 "./src/syntactical-analyzer/bison.y"
                                                                  {  }
#line 2401 "bison.tab.c"
    break;

  case 18:
#line 946 "./src/syntactical-analyzer/bison.y"
                                                                 {  }
#line 2407 "bison.tab.c"
    break;

  case 19:
#line 949 "./src/syntactical-analyzer/bison.y"
                                                {  }
#line 2413 "bison.tab.c"
    break;

  case 20:
#line 950 "./src/syntactical-analyzer/bison.y"
                                                                             {  }
#line 2419 "bison.tab.c"
    break;

  case 21:
#line 953 "./src/syntactical-analyzer/bison.y"
                                                                  { (yyval.oper) = new returnexp((yyvsp[0].expr)); }
#line 2425 "bison.tab.c"
    break;

  case 22:
#line 954 "./src/syntactical-analyzer/bison.y"
                                                                   { (yyval.oper) = new returnexp(NULL); }
#line 2431 "bison.tab.c"
    break;

  case 23:
#line 957 "./src/syntactical-analyzer/bison.y"
                                                                              { (yyval.oper) = new ifoper((yyvsp[-1].opers), (yyvsp[-4].expr), {}); }
#line 2437 "bison.tab.c"
    break;

  case 24:
#line 958 "./src/syntactical-analyzer/bison.y"
                                                                                                                      { (yyval.oper) = new ifoper((yyvsp[-5].opers), (yyvsp[-8].expr), (yyvsp[-1].opers)); }
#line 2443 "bison.tab.c"
    break;

  case 25:
#line 959 "./src/syntactical-analyzer/bison.y"
                                                                                               { (yyval.oper) = new ifoper((yyvsp[-1].opers), (yyvsp[-4].expr), {}); }
#line 2449 "bison.tab.c"
    break;

  case 26:
#line 960 "./src/syntactical-analyzer/bison.y"
                                                                                                                       { (yyval.oper) = new ifoper((yyvsp[-5].opers), (yyvsp[-8].expr), (yyvsp[-1].opers)); }
#line 2455 "bison.tab.c"
    break;

  case 27:
#line 963 "./src/syntactical-analyzer/bison.y"
                                                                          { (yyval.oper) = new cycleoperwhile (true, (yyvsp[-4].expr), (yyvsp[-1].opers)); }
#line 2461 "bison.tab.c"
    break;

  case 28:
#line 964 "./src/syntactical-analyzer/bison.y"
                                                                                                     { (yyval.oper) = new cycleoperwhile (false, (yyvsp[-1].expr), (yyvsp[-5].opers)); }
#line 2467 "bison.tab.c"
    break;

  case 29:
#line 965 "./src/syntactical-analyzer/bison.y"
                                                                                                 { (yyval.oper) = new cycleoperwhile (true, (yyvsp[-4].expr), (yyvsp[-1].opers)); }
#line 2473 "bison.tab.c"
    break;

  case 30:
#line 966 "./src/syntactical-analyzer/bison.y"
                                                                                                    { (yyval.oper) = new cycleoperwhile (false, (yyvsp[-1].expr), (yyvsp[-5].opers)); }
#line 2479 "bison.tab.c"
    break;

  case 31:
#line 969 "./src/syntactical-analyzer/bison.y"
                                                                             { (yyval.oper) = new eqoper((yyvsp[-2].str), NULL, "=", (yyvsp[0].expr)); }
#line 2485 "bison.tab.c"
    break;

  case 32:
#line 972 "./src/syntactical-analyzer/bison.y"
                                                                       { (yyval.oper) = new printoper((yyvsp[-1].expr)); }
#line 2491 "bison.tab.c"
    break;

  case 33:
#line 975 "./src/syntactical-analyzer/bison.y"
                                                                                         { (yyval.oper) = new scanoper((yyvsp[-4].str), NULL); }
#line 2497 "bison.tab.c"
    break;

  case 34:
#line 978 "./src/syntactical-analyzer/bison.y"
                                                             { (yyval.oper) = new initvariable((yyvsp[-1].str), (yyvsp[0].str), NULL, {}); }
#line 2503 "bison.tab.c"
    break;

  case 35:
#line 979 "./src/syntactical-analyzer/bison.y"
                                                                                                       { (yyval.oper) = new initvariable((yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[0].expr), {}); }
#line 2509 "bison.tab.c"
    break;

  case 36:
#line 982 "./src/syntactical-analyzer/bison.y"
                                                                        { (yyval.expr) = new funccall((yyvsp[-3].str), (yyvsp[-1].exprs)); }
#line 2515 "bison.tab.c"
    break;

  case 37:
#line 985 "./src/syntactical-analyzer/bison.y"
                                                     {  }
#line 2521 "bison.tab.c"
    break;

  case 38:
#line 986 "./src/syntactical-analyzer/bison.y"
                                                                                    { (yyval.expr) = new binary((yyvsp[-2].expr), "+", (yyvsp[0].expr));  }
#line 2527 "bison.tab.c"
    break;

  case 39:
#line 987 "./src/syntactical-analyzer/bison.y"
                                                                                    { (yyval.expr) = new binary((yyvsp[-2].expr), "-", (yyvsp[0].expr));  }
#line 2533 "bison.tab.c"
    break;

  case 40:
#line 990 "./src/syntactical-analyzer/bison.y"
                                                      {  }
#line 2539 "bison.tab.c"
    break;

  case 41:
#line 991 "./src/syntactical-analyzer/bison.y"
                                                                               { (yyval.expr) = new binary((yyvsp[-2].expr), "*", (yyvsp[0].expr)); }
#line 2545 "bison.tab.c"
    break;

  case 42:
#line 992 "./src/syntactical-analyzer/bison.y"
                                                                               { (yyval.expr) = new binary((yyvsp[-2].expr), (yyvsp[-1].str), (yyvsp[0].expr)); }
#line 2551 "bison.tab.c"
    break;

  case 43:
#line 995 "./src/syntactical-analyzer/bison.y"
                                                                                { (yyval.expr) = new boolargs((yyvsp[-2].expr), (yyvsp[-1].str), (yyvsp[0].expr)); }
#line 2557 "bison.tab.c"
    break;

  case 44:
#line 996 "./src/syntactical-analyzer/bison.y"
                                                                                        { (yyval.expr) = new boolargs((yyvsp[-2].expr), (yyvsp[-1].str), (yyvsp[0].expr)); }
#line 2563 "bison.tab.c"
    break;

  case 45:
#line 999 "./src/syntactical-analyzer/bison.y"
                                                                 { (yyval.expr) = new boolarg("", (yyvsp[-1].expr), "!", NULL, false); }
#line 2569 "bison.tab.c"
    break;

  case 46:
#line 1000 "./src/syntactical-analyzer/bison.y"
                                                                                              { (yyval.expr) = new boolarg("", (yyvsp[-2].expr), (yyvsp[-1].str), (yyvsp[0].expr), false); }
#line 2575 "bison.tab.c"
    break;

  case 47:
#line 1001 "./src/syntactical-analyzer/bison.y"
                                                             { (yyval.expr) = new boolarg((yyvsp[0].str), NULL, "", NULL, false); }
#line 2581 "bison.tab.c"
    break;

  case 48:
#line 1002 "./src/syntactical-analyzer/bison.y"
                                                                   { (yyval.expr) = new boolarg((yyvsp[0].str), NULL, "", NULL, true); }
#line 2587 "bison.tab.c"
    break;

  case 49:
#line 1005 "./src/syntactical-analyzer/bison.y"
                                                       { (yyval.expr) = new value((yyvsp[0].str), "", NULL, "string"); }
#line 2593 "bison.tab.c"
    break;

  case 50:
#line 1006 "./src/syntactical-analyzer/bison.y"
                                                                 { (yyval.expr) = new value((yyvsp[0].str), "", NULL, "int"); }
#line 2599 "bison.tab.c"
    break;

  case 51:
#line 1007 "./src/syntactical-analyzer/bison.y"
                                                                  { (yyval.expr) = new value((yyvsp[0].str), "", NULL, "float"); }
#line 2605 "bison.tab.c"
    break;

  case 52:
#line 1008 "./src/syntactical-analyzer/bison.y"
                                                             { (yyval.expr) = new value((yyvsp[0].str), "", NULL, "bool"); }
#line 2611 "bison.tab.c"
    break;

  case 53:
#line 1009 "./src/syntactical-analyzer/bison.y"
                                                                           { (yyval.expr) = new value("", "", (yyvsp[-1].expr), ""); }
#line 2617 "bison.tab.c"
    break;

  case 54:
#line 1010 "./src/syntactical-analyzer/bison.y"
                                                                 { (yyval.expr) = new value("", "", (yyvsp[0].expr), ""); }
#line 2623 "bison.tab.c"
    break;

  case 55:
#line 1011 "./src/syntactical-analyzer/bison.y"
                                                                   { (yyval.expr) = new value("" ,(yyvsp[0].str), NULL, ""); }
#line 2629 "bison.tab.c"
    break;

  case 56:
#line 1012 "./src/syntactical-analyzer/bison.y"
                                                                  { (yyval.expr) = new value("", "", (yyvsp[0].expr), ""); }
#line 2635 "bison.tab.c"
    break;

  case 57:
#line 1015 "./src/syntactical-analyzer/bison.y"
                                                                     { (yyval.expr) = new unaryoper("-", (yyvsp[0].str), "", NULL, "int"); }
#line 2641 "bison.tab.c"
    break;

  case 58:
#line 1016 "./src/syntactical-analyzer/bison.y"
                                                                              { (yyval.expr) = new unaryoper("-", (yyvsp[0].str), "", NULL, "float"); }
#line 2647 "bison.tab.c"
    break;

  case 59:
#line 1017 "./src/syntactical-analyzer/bison.y"
                                                                               { (yyval.expr) = new unaryoper("-", "", (yyvsp[0].str), NULL, ""); }
#line 2653 "bison.tab.c"
    break;

  case 60:
#line 1018 "./src/syntactical-analyzer/bison.y"
                                                                       { (yyval.expr) = new unaryoper("!", "", (yyvsp[0].str), NULL, ""); }
#line 2659 "bison.tab.c"
    break;

  case 61:
#line 1021 "./src/syntactical-analyzer/bison.y"
                                                { (yyval.exprs).clear(); }
#line 2665 "bison.tab.c"
    break;

  case 62:
#line 1022 "./src/syntactical-analyzer/bison.y"
                                                                   { (yyval.exprs).clear(); (yyval.exprs).push_back((yyvsp[0].expr)); }
#line 2671 "bison.tab.c"
    break;

  case 63:
#line 1023 "./src/syntactical-analyzer/bison.y"
                                                                           { (yyval.exprs) = (yyvsp[-2].exprs); (yyval.exprs).push_back((yyvsp[0].expr)); }
#line 2677 "bison.tab.c"
    break;

  case 64:
#line 1026 "./src/syntactical-analyzer/bison.y"
                                                  { (yyval.opers).clear(); (yyval.opers).push_back((yyvsp[0].oper)); }
#line 2683 "bison.tab.c"
    break;

  case 65:
#line 1027 "./src/syntactical-analyzer/bison.y"
                                                                                                   { (yyval.opers) = (yyvsp[-2].opers); (yyval.opers).push_back((yyvsp[0].oper)); }
#line 2689 "bison.tab.c"
    break;

  case 66:
#line 1030 "./src/syntactical-analyzer/bison.y"
                                                             { (yyval.oper) = new initvariable((yyvsp[-1].str), (yyvsp[0].str), NULL, {}); }
#line 2695 "bison.tab.c"
    break;


#line 2699 "bison.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1033 "./src/syntactical-analyzer/bison.y"


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
