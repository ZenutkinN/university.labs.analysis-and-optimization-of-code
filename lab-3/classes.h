#ifndef CLASSES_H
#define CLASSES_H
extern int yylineno;
void yyerror(char *s);
void yyerror(const char *s);
void yyerror(string str, int gline);

/*! \class oper_t
*  \brief Реализация операций
*/
class oper_t
{
public:
	int line = yylineno;
	oper_t();
	virtual ~oper_t();
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class expr_t
*  \brief Реализация выражений
*/
class expr_t
{
	string type;

public:
	int line = yylineno;
	int index = 0;
	expr_t();
	virtual ~expr_t();
	virtual string print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
	virtual string checkType();
	virtual int getIndex();
};

/*! \class boolargs
*  \brief Совокупность boolean-выражений
*
*  Содержится в условиях while, do-while, if
*/
class boolargs : public expr_t
{
	expr_t *fexp;
	string oper;
	expr_t *sexp;

public:
	int line = yylineno;
	boolargs(expr_t *fexp, const string &oper, expr_t *sexp);
	virtual string print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
	virtual string checkType();
	virtual int getIndex();
};

/*! \class initfunc
*  \brief Реализация операции инициализации функции
*/
class initfunc : public oper_t
{
	string var;
	string identifier;
	list<oper_t *> args;
	list<oper_t *> opers;

public:
	int line = yylineno;
	initfunc(const string &var, const string &identifier, list<oper_t *> args, list<oper_t *> opers);
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class returnexp
*  \brief Реализация операции return
*/
class returnexp : public oper_t
{
	expr_t *arg;

public:
	int line = yylineno;
	returnexp(expr_t *arg);
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class ifoper
*  \brief Реализация if
*/
class ifoper : public oper_t
{
	list<oper_t *> iftrue;
	expr_t *boolarg;
	list<oper_t *> iffalse;
	int markIndex;

public:
	int line = yylineno;
	ifoper(list<oper_t *> iftrue, expr_t *boolarg, list<oper_t *> iffalse);
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class cycleoperwhile
*  \brief Реализация while
*/
class cycleoperwhile : public oper_t
{
	bool whilefirst;
	expr_t *boolarg;
	list<oper_t *> opers;
	int markIndex;

public:
	int line = yylineno;
	cycleoperwhile(bool whilefirst, expr_t *boolarg, list<oper_t *> opers);
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class eqoper
*  \brief Реализация операции присваивания
*/
class eqoper : public oper_t
{
	string identifier;
	expr_t *id;
	string oper;
	expr_t *expr;

public:
	int line = yylineno;
	eqoper(const string &identifier, expr_t *id, const string &oper, expr_t *expr);
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class printoper
*  \brief Реализация операции вывода
*/
class printoper : public oper_t
{
	expr_t *id;

public:
	int line = yylineno;
	printoper(expr_t *id);
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class scanoper
*  \brief Реализация операции ввода
*/
class scanoper : public oper_t
{
	string identifier;
	expr_t *id;

public:
	int line = yylineno;
	scanoper(const string &identifier, expr_t *id);
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class initvariable
*  \brief Реализация инициализации переменных
*/
class initvariable : public oper_t
{
	string var;
	string identifier;
	expr_t *exprs;
	list<oper_t *> opers;
	bool inited;
	vector<valueForCheck *> typeTest;

public:
	int line = yylineno;
	initvariable(const string &var, const string &identifier, expr_t *exprs, list<oper_t *> opers, const bool inited = false);
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class funccall
*  \brief Реализация вызова функции
*/
class funccall : public expr_t
{
	string identifier;
	list<expr_t *> args;
	vector<valueForCheck *> typeTest;

public:
	int line = yylineno;
	funccall(const string &identifier, list<expr_t *> args);
	virtual string print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
	virtual string checkType();
	virtual int getIndex();
};

/*! \class funccalloper
*  \brief Реализация вызова функции, содержащейся в выражении
*/
class funccalloper : public oper_t
{
	expr_t *func;

public:
	int line = yylineno;
	funccalloper(expr_t *func);
	virtual void print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
};

/*! \class binary
*  \brief Реализация бинарных операций
*/
class binary : public expr_t
{
	expr_t *fexp;
	string oper;
	expr_t *sexp;

public:
	int line = yylineno;
	binary(expr_t *fexp, const string &oper, expr_t *sexp);
	virtual string print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
	virtual string checkType();
	virtual int getIndex();
};

/*! \class boolarg
*  \brief Реализация boolean-выражение
*
*  Содержится в условиях while, do-while, if
*/
class boolarg : public expr_t
{
	string fexps;
	expr_t *fexp;
	string oper;
	expr_t *sexp;
	bool fexpsiden;

public:
	int line = yylineno;
	boolarg(const string &fexps, expr_t *fexp, const string &oper, expr_t *sexp, const bool &fexpsiden);
	virtual string print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
	virtual string checkType();
	virtual int getIndex();
};

/*! \class value
*  \brief Реализация единичного значение в бинарной операции
*/
class value : public expr_t
{
	string constant;
	string identifier;
	expr_t *id;
	string type;
	vector<valueForCheck *> typeTest;

public:
	int line = yylineno;
	value(const string &constant, const string &identifier, expr_t *id, const string &type);
	virtual string print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
	virtual string checkType();
	virtual int getIndex();
};

/*! \class unaryoper
*  \brief Реализация унарных операций типа !, -
*/
class unaryoper : public expr_t
{
	string oper;
	string constant;
	string identifier;
	expr_t *id;
	string argType;
	vector<valueForCheck *> typeTest;

public:
	int line = yylineno;
	unaryoper(const string &oper, const string &constant, const string &identifier, expr_t *id, const string &argType);
	virtual string print(stringstream &file);
	virtual void checkValue(vector<valueForCheck *> &values, bool add = true);
	virtual string checkType();
	virtual int getIndex();
};

#endif