%{
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

file: program {
	vector<valueForCheck*> values;
	for(oper_t *progel : $1) {
		progel->checkValue(values);
	}
	
	for(oper_t *progel : $1) {
		progel->print();
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
|							VOID IDENTIFIER '(' initargs ')' '{' operations '}' { $$ = new initfunc("void", $2, $4, $7); }
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

initargs: 					{  }
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
|							WHILE '(' boolarg ')' '{' operations '}' { $$ = new cycleoperwhile (true, $3, $6); }
|							DO '{' operations '}' WHILE '(' boolarg ')' { $$ = new cycleoperwhile (false, $7, $3); }
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

initemptyvariable:			VALUETYPE IDENTIFIER { $$ = new initvariable($1, $2, NULL, {}); }
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
