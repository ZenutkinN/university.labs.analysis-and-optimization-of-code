#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include "utils.h"
#include "classes.h"

using namespace std;

extern string curFuncName;
extern string filename;
extern string cycleStr;
extern int yylineno;
extern int gIndexForInitGlob;
extern int gMarkCurIndex;
extern int gMarkIndex;
extern int cycleCounter;
extern int boolargIndex;
extern int gIndex;
extern int gVarIndex;
extern int cycleIndex;
extern int argsSize;

extern bool needn;
extern bool mainExists;
extern bool cycle;
extern bool retValue;
extern bool labelExist;

extern vector<valueForPrint *> valuesPrint;

extern stringstream initGlobalVars;
extern stringstream globalVars;
extern stringstream funcArgs;

void yyerror(char *s)
{
	fprintf(stderr, "Line %d - \"%s\"\n", yylineno, s);
	exit(1);
}

void yyerror(const char *s)
{
	fprintf(stderr, "Line %d - \"%s\"\n", yylineno, s);
	exit(1);
}

void yyerror(string str, int gline)
{
	const char *s = str.c_str();
	fprintf(stderr, "Line %d - \"%s\"\n", gline, s);
	exit(1);
}

/*! \class oper_t
*  \brief Реализация операций
*/
oper_t::oper_t() {}
oper_t::~oper_t(){};
void oper_t::print(stringstream &file) {}
void oper_t::checkValue(vector<valueForCheck *> &values, bool add) {}

/*! \class expr_t
*  \brief Реализация выражений
*/
expr_t::expr_t() {}
expr_t::~expr_t() {}
string expr_t::print(stringstream &file) {}
void expr_t::checkValue(vector<valueForCheck *> &values, bool add) {}
string expr_t::checkType() {}
int expr_t::getIndex() {}

/*! \class boolargs
*  \brief Совокупность boolean-выражений
*
*  Содержится в условиях while, do-while, if
*/
boolargs::boolargs(expr_t *fexp, const string &oper, expr_t *sexp) : fexp(fexp), oper(oper), sexp(sexp) {}
string boolargs::print(stringstream &file)
{
	string fexpIndex = fexp->print(file);
	string sexpIndex = "";

	if (sexp != NULL)
	{
		sexpIndex = sexp->print(file);

		file << "\t%" << gIndex << " = load " << getLLVMType(fexp->checkType()) << ", ";
		file << getLLVMType(fexp->checkType()) << "* " << fexpIndex << ", align " << getLLVMSize(fexp->checkType()) << "\n";
		file << "\t%" << gIndex + 1 << " = trunc " << getLLVMType(fexp->checkType()) << " %" << gIndex << " to i1\n";
		file << "\t%" << gIndex + 2 << " = load " << getLLVMType(sexp->checkType()) << ", ";
		file << getLLVMType(sexp->checkType()) << "* " << sexpIndex << ", align " << getLLVMSize(sexp->checkType()) << "\n";
		file << "\t%" << gIndex + 3 << " = trunc " << getLLVMType(fexp->checkType()) << " %" << gIndex + 2 << " to i1\n";
		file << "\t%" << gIndex + 4 << " = alloca i8, align 1\n";
		file << "\tbr label %boolargNoJS" << boolargIndex << "\n";
		file << "boolargNoJS" << boolargIndex << ":\n";

		if (oper == "||")
		{
			file << "\tbr i1 %" << gIndex + 1 << ", label %boolargNoJS" << boolargIndex + 2 << ", label %boolargNoJS" << boolargIndex + 1 << "\n";
			file << "boolargNoJS" << boolargIndex + 1 << ":\n";
			file << "\tbr i1 %" << gIndex + 3 << ", label %boolargNoJS" << boolargIndex + 2 << ", label %boolargNoJS" << boolargIndex + 3 << "\n";
			file << "boolargNoJS" << boolargIndex + 2 << ":\n";
			file << "\tstore i8 1, i8* %" << gIndex + 4 << ", align 1\n";
			file << "\tbr label %boolargNoJS" << boolargIndex + 4 << "\n";
			file << "boolargNoJS" << boolargIndex + 3 << ":\n";
			file << "\tstore i8 0, i8* %" << gIndex + 4 << ", align 1\n";
			file << "\tbr label %boolargNoJS" << boolargIndex + 4 << "\n";
			file << "boolargNoJS" << boolargIndex + 4 << ":\n";
			boolargIndex += 5;
		}
		else if (oper == "&&")
		{
			file << "\tbr i1 %" << gIndex + 1 << ", label %boolargNoJS" << boolargIndex + 1 << ", label %boolargNoJS" << boolargIndex + 3 << "\n";
			file << "boolarg" << boolargIndex + 1 << ":\n";
			file << "\tbr i1 %" << gIndex + 3 << ", label %boolargNoJS" << boolargIndex + 2 << ", label %boolargNoJS" << boolargIndex + 3 << "\n";
			file << "boolargNoJS" << boolargIndex + 2 << ":\n";
			file << "\tstore i8 1, i8* %" << gIndex + 4 << ", align 1\n";
			file << "\tbr label %boolargNoJS" << boolargIndex + 4 << "\n";
			file << "boolargNoJS" << boolargIndex + 3 << ":\n";
			file << "\tstore i8 0, i8* %" << gIndex + 4 << ", align 1\n";
			file << "\tbr label %boolargNoJS" << boolargIndex + 4 << "\n";
			file << "boolargNoJS" << boolargIndex + 4 << ":\n";
			boolargIndex += 5;
		}
		
		index = gIndex + 4;
		gIndex = gIndex + 5;

		return "%" + to_string(index);
	}
	else
	{
		file << "\t%" << gIndex << " = load " << getLLVMType(fexp->checkType()) << ", ";
		file << getLLVMType(fexp->checkType()) << "* " << fexpIndex << ", align " << getLLVMSize(fexp->checkType()) << "\n";
		index = gIndex;
		gIndex = gIndex + 1;
		return "%" + to_string(index);
	}
}

void boolargs::checkValue(vector<valueForCheck *> &values, bool add)
{
	fexp->checkValue(values);
	if (sexp != NULL)
	{
		sexp->checkValue(values);
	}
}

string boolargs::checkType()
{
	if (sexp != NULL)
	{
		if (fexp->checkType() == "bool")
		{
			return "bool";
		}
	}
	else
	{         
		if (fexp->checkType() == sexp->checkType())
		{
			return "bool";
		}
	}
}

int boolargs::getIndex()
{
	return 0;
}

/*! \class initfunc
*  \brief Реализация операции инициализации функции
*/
initfunc::initfunc(const string &var, const string &identifier, list<oper_t *> args, list<oper_t *> opers) : var(var), identifier(identifier), args(args), opers(opers) {}
void initfunc::print(stringstream &file)
{
	vector<valueForPrint *> newVec;
	newVec.insert(newVec.end(), valuesPrint.begin(), valuesPrint.end());
	curFuncName = identifier;

	if (args.size() == 0)
	{
		gIndex = 1;
	}
	else
	{
		gIndex = 0;
	}

	file << "define " << getLLVMType(var);
	file << " @" << identifier << "(";

	needn = false;
	argsSize = args.size();

	int argsIndex = 0;

	for (oper_t *arg : args)
	{
		arg->print(file);

		if (argsIndex != args.size() - 1)
		{
			argsIndex++;
			file << ", ";
		}
	}

	if (args.size() != 0)
	{
		gIndex++;
		gIndex = gIndex + args.size();
	}

	needn = true;
	file << ") {\n";

	if (identifier == "main")
	{
		file << "\tcall void @NoJSInitglobalVars()\n";
	}

	file << funcArgs.str();

	funcArgs.str("");

	if (opers.size() != 0)
	{
		for (oper_t *oper : opers)
		{
			oper->print(file);
		}
	}

	file << "}\n";
	curFuncName = "";
	valuesPrint = newVec;
}

void initfunc::checkValue(vector<valueForCheck *> &values, bool add)
{
	vector<valueForCheck *> newVec;
	newVec.insert(newVec.end(), values.begin(), values.end());

	if (identifier == "main")
	{
		mainExists = true;
	}

	for (oper_t *arg : args)
	{
		arg->checkValue(newVec);
	}

	if (checkValueExist(values, identifier))
	{
		yyerror("Identifier " + identifier + " already exists!", line);
	}

	vector<valueForCheck *> argVec;

	for (int i = 0; i < newVec.size(); i++)
	{
		bool exist = false;
		for (int j = 0; j < values.size(); j++)
		{
			if (newVec.at(i) == values.at(j))
			{
				exist = true;
				break;
			}
		}
		if (!exist)
		{
			argVec.push_back(newVec.at(i));
		}
	}

	curFuncName = identifier;
	valueForCheck *valClass = new valueForCheck(var + "()", identifier, {}, true);
	valClass->funcArgs = argVec;

	values.push_back(valClass);
	newVec.push_back(valClass);

	if (opers.size() != 0)
	{
		for (oper_t *oper : opers)
		{
			oper->checkValue(newVec);
		}
	}

	if (retValue == false)
	{
		yyerror("No return value in function " + identifier + "!", line);
	}

	retValue = false;
	curFuncName = "";
}

/*! \class returnexp
*  \brief Реализация операции return
*/
returnexp::returnexp(expr_t *arg) : arg(arg) {}
void returnexp::print(stringstream &file)
{
	if (arg != NULL)
	{
		string argIndex = arg->print(file);
		file << "\t%" << gIndex << " = load " << getLLVMType(arg->checkType()) << ", " << getLLVMType(arg->checkType()) << "* " << argIndex << ", align " << getLLVMSize(arg->checkType()) << "\n";
		file << "\tret " << getLLVMType(arg->checkType()) << " %" << gIndex << "\n";
		gIndex++;
	}
	else
	{
		file << "\tret void\n";
	}

	labelExist = true;
}

void returnexp::checkValue(vector<valueForCheck *> &values, bool add)
{
	retValue = true;

	if (arg != NULL)
	{
		arg->checkValue(values);
		if (arg->checkType() + "()" != getType(values, curFuncName))
		{
			yyerror("Wrong type of argument! Expected " + getType(values, curFuncName), line);
		}
	}
}

/*! \class ifoper
*  \brief Реализация if
*/
ifoper::ifoper(list<oper_t *> iftrue, expr_t *boolarg, list<oper_t *> iffalse) : iftrue(iftrue), boolarg(boolarg), iffalse(iffalse) {}
void ifoper::print(stringstream &file)
{
	markIndex = gMarkIndex;
	gMarkIndex++;
	string fexpIndex = boolarg->print(file);

	file << "\t%" << gIndex << " = load i8, i8* " << fexpIndex << ", align 1\n";
	file << "\t%" << gIndex + 1 << " = trunc i8 %" << gIndex << " to i1\n";
	file << "\tbr i1 %" << gIndex + 1 << ", label %markNoJSiftrue" << markIndex;

	gIndex = gIndex + 2;

	if (iffalse.size() != 0)
	{
		file << ", label %markNoJSiffalse" << markIndex;
	}
	else
	{
		file << ", label %markNoJSendIf" << markIndex;
	}

	file << "\n\nmarkNoJSiftrue" << markIndex << ":\n";

	labelExist = false;

	for (oper_t *iftr : iftrue)
	{
		iftr->print(file);
	}

	if (labelExist == false)
	{
		file << "\tbr label %markNoJSendIf" << markIndex << "\n";
	}
	else
	{
		labelExist = false;
	}

	if (iffalse.size() != 0)
	{
		file << "\nmarkNoJSiffalse" << markIndex << ":\n";

		for (oper_t *iffl : iffalse)
		{
			iffl->print(file);
		}

		if (labelExist == false)
		{
			file << "\tbr label %markNoJSendIf" << markIndex << "\n";
		}
		else
		{
			labelExist = false;
		}
	}

	file << "\nmarkNoJSendIf" << markIndex << ":\n";
}

void ifoper::checkValue(vector<valueForCheck *> &values, bool add)
{
	vector<valueForCheck *> newVec;
	newVec.insert(newVec.end(), values.begin(), values.end());

	if (boolarg->checkType() != "bool")
	{
		yyerror("Wrong type of argument! Expected boolean", line);
	}

	for (oper_t *iftr : iftrue)
	{
		iftr->checkValue(newVec);
	}

	boolarg->checkValue(newVec);
	vector<valueForCheck *> newVec2;
	newVec2.insert(newVec2.end(), values.begin(), values.end());

	if (iffalse.size() != 0)
	{
		for (oper_t *iffl : iffalse)
		{
			iffl->checkValue(newVec2);
		}
	}
}

/*! \class cycleoperwhile
*  \brief Реализация while
*/
cycleoperwhile::cycleoperwhile(bool whilefirst, expr_t *boolarg, list<oper_t *> opers) : whilefirst(whilefirst), boolarg(boolarg), opers(opers) {}
void cycleoperwhile::print(stringstream &file)
{
	vector<valueForPrint *> oldVals;
	oldVals.insert(oldVals.end(), valuesPrint.begin(), valuesPrint.end());

	if (whilefirst)
	{
		markIndex = gMarkIndex;
		gMarkIndex++;

		file << "\tbr label %markNoJS.checkCycle" << markIndex << "\n";
		file << "\nmarkNoJS.checkCycle" << markIndex << ":\n";

		string fexpIndex = boolarg->print(file);

		file << "\t%" << gIndex << " = load i8, i8* " << fexpIndex << ", align 1\n";
		file << "\t%" << gIndex + 1 << " = trunc i8 %" << gIndex << " to i1\n";
		file << "\tbr i1 %" << gIndex + 1 << ", label %markNoJS.cycle" << markIndex << ", label %markNoJS.endCycle" << markIndex << "\n";
		
		gIndex = gIndex + 2;

		file << "\nmarkNoJS.cycle" << markIndex << ":\n";

		gMarkCurIndex = markIndex;

		for (oper_t *oper : opers)
		{
			oper->print(file);
		}

		gMarkCurIndex = markIndex;

		if (labelExist == false)
		{
			file << "\tbr label %markNoJS.checkCycle" << markIndex << "\n";
		}
		else
		{
			labelExist = false;
		}

		file << "\nmarkNoJS.endCycle" << markIndex << ":\n";
	}
	else
	{
		markIndex = gMarkIndex;
		gMarkIndex++;

		file << "\tbr label %markNoJS.cycle" << markIndex << "\n";
		file << "\nmarkNoJS.checkCycle" << markIndex << ":\n";

		string fexpIndex = boolarg->print(file);

		file << "\t%" << gIndex << " = load i8, i8* " << fexpIndex << ", align 1\n";
		file << "\t%" << gIndex + 1 << " = trunc i8 %" << gIndex << " to i1\n";
		file << "\tbr i1 %" << gIndex + 1 << ", label %markNoJS.cycle" << markIndex << ", label %markNoJS.endCycle" << markIndex << "\n";
		
		gIndex = gIndex + 2;

		file << "\nmarkNoJS.cycle" << markIndex << ":\n";

		gMarkCurIndex = markIndex;

		for (oper_t *oper : opers)
		{
			oper->print(file);
		}

		gMarkCurIndex = markIndex;

		if (labelExist == false)
		{
			file << "\tbr label %markNoJS.checkCycle" << markIndex << "\n";
		}
		else
		{
			labelExist = false;
		}

		file << "\nmarkNoJS.endCycle" << markIndex << ":\n";
	}

	vector<valueForPrint *> newVals;

	for (int i = 0; i < valuesPrint.size(); i++)
	{
		for (int j = 0; j < oldVals.size(); j++)
		{
			if (oldVals.at(j)->identifier == valuesPrint.at(i)->identifier)
			{
				newVals.push_back(valuesPrint.at(i));
			}
		}
	}

	valuesPrint = newVals;
}

void cycleoperwhile::checkValue(vector<valueForCheck *> &values, bool add)
{
	cycleCounter++;
	vector<valueForCheck *> newVec;
	newVec.insert(newVec.end(), values.begin(), values.end());
	boolarg->checkValue(newVec);

	for (oper_t *oper : opers)
	{
		oper->checkValue(newVec);
	}

	if (boolarg->checkType() != "bool")
	{
		yyerror("Wrong type of argument! Expected boolean", line);
	}

	cycleCounter--;
}

/*! \class eqoper
*  \brief Реализация операции присваивания
*/
eqoper::eqoper(const string &identifier, expr_t *id, const string &oper, expr_t *expr) : identifier(identifier), id(id), oper(oper), expr(expr) {}

void eqoper::print(stringstream &file)
{
	if (identifier != "")
	{
		valueForPrint *val = getValue(identifier);
		string exprStr = expr->print(file);

		file << "\t%" << gIndex << " = load " << getLLVMType(val->type) << ", " << getLLVMType(val->type) << "* " << val->index << ", align " << getLLVMSize(val->type) << "\n";
		file << "\t%" << gIndex + 1 << " = load " << getLLVMType(val->type) << ", " << getLLVMType(val->type) << "* " << exprStr << ", align " << getLLVMSize(val->type) << "\n";
		file << "\tstore " << getLLVMType(val->type) << " %" << gIndex + 1 << ", " << getLLVMType(val->type) << "* " << val->index << ", align " << getLLVMSize(val->type) << "\n";
		
		gIndex = gIndex + 2;
	}
	else
	{
		string idStr = id->print(file);
		string exprStr = expr->print(file);

		file << "\t%" << gIndex << " = load " << getLLVMType(id->checkType()) << ", " << getLLVMType(id->checkType()) << "* " << idStr << ", align " << getLLVMSize(id->checkType()) << "\n";
		file << "\t%" << gIndex + 1 << " = load " << getLLVMType(id->checkType()) << ", " << getLLVMType(id->checkType()) << "* " << exprStr << ", align " << getLLVMSize(id->checkType()) << "\n";
		file << "\tstore " << getLLVMType(id->checkType()) << " %" << gIndex + 1 << ", " << getLLVMType(id->checkType()) << "* " << idStr << ", align " << getLLVMSize(id->checkType()) << "\n";
		
		gIndex = gIndex + 2;
	}
}

void eqoper::checkValue(vector<valueForCheck *> &values, bool add)
{
	
	if (identifier != "")
	{
		if (!checkValueExist(values, identifier))
		{
			yyerror("Identifier " + identifier + " doesn't exist!", line);
		}
		
		
		if (oper != "=" && !checkValueInited(values, identifier))
		{
			yyerror("Identifier " + identifier + " doesn't initialized!", line);
		}

		for (int i = 0; i < values.size(); i++)
		{
			if (values.at(i)->identifier == identifier)
			{
				values.at(i)->inited = true;
			}
		}
	}
	else
	{
		id->checkValue(values);
	}

	expr->checkValue(values);
}

/*! \class printoper
*  \brief Реализация операции вывода
*/
printoper::printoper(expr_t *id) : id(id) {}

void printoper::print(stringstream &file)
{
	string idIndex = id->print(file);

	file << "\t%" << gIndex << " = load " << getLLVMType(id->checkType()) << ", ";
	file << getLLVMType(id->checkType()) << "* " << idIndex << ", align " << getLLVMSize(id->checkType()) << "\n";
	
	if (id->checkType() == "int")
	{
		file << "\t%" << gIndex + 1 << " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %" << gIndex << ")\n";
		
		gIndex = gIndex + 2;
	}

	if (id->checkType() == "bool")
	{
		file << "\t%" << gIndex + 1 << " = trunc i8 %" << gIndex << " to i1\n";
		file << "\t%" << gIndex + 2 << " = zext i1 %" << gIndex + 1 << " to i32\n";
		file << "\t%" << gIndex + 3 << " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %" << gIndex + 2 << ")\n";
		
		gIndex = gIndex + 4;
	}

	if (id->checkType() == "string")
	{
		file << "\t%" << gIndex + 1 << " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %" << gIndex << ")\n";
		
		gIndex = gIndex + 2;
	}

	if (id->checkType() == "float")
	{
		file << "\t%" << gIndex + 1 << " = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.f, i32 0, i32 0), double %" << gIndex << ")\n";
		
		gIndex = gIndex + 2;
	}
}

void printoper::checkValue(vector<valueForCheck *> &values, bool add)
{
	id->checkValue(values);
}

/*! \class scanoper
*  \brief Реализация операции ввода
*/
scanoper::scanoper(const string &identifier, expr_t *id) : identifier(identifier), id(id) {}

void scanoper::print(stringstream &file)
{
	if ((id != NULL && id->checkType() == "string") || (identifier != "" && getValue(identifier)->type == "string"))
	{
		string index = "";

		if (identifier == "")
		{
			index = id->print(file);
		}
		else
		{
			index = getValue(identifier)->index;
		}

		file << "\t%" << gIndex << " = load i8*, i8** " << index << ", align 1\n";
		file << "\t%" << gIndex + 1 << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %" << gIndex << ")\n";
		file << "\tstore i8* %" << gIndex << ", i8** " << index << ", align 1\n";
	}
	else if ((id != NULL && id->checkType() == "int") || (identifier != "" && getValue(identifier)->type == "int"))
	{
		string index = "";

		if (identifier == "")
		{
			index = id->print(file);
		}
		else
		{
			index = getValue(identifier)->index;
		}

		file << "\t%" << gIndex << " = load i32, i32* " << index << ", align 4\n";
		file << "\t%" << gIndex + 1 << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i32 %" << gIndex << ")\n";
		file << "\tstore i32 %" << gIndex << ", i32* " << index << ", align 4\n";
	}
	else if ((id != NULL && id->checkType() == "float") || (identifier != "" && getValue(identifier)->type == "float"))
	{
		string index = "";

		if (identifier == "")
		{
			index = id->print(file);
		}
		else
		{
			index = getValue(identifier)->index;
		}

		file << "\t%" << gIndex << " = load double, double* " << index << ", align 8\n";
		file << "\t%" << gIndex + 1 << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.f, i32 0, i32 0), double %" << gIndex << ")\n";
		file << "\tstore double %" << gIndex << ", double* " << index << ", align 8\n";
	}
	else
	{
		string index = "";

		if (identifier == "")
		{
			index = id->print(file);
		}
		else
		{
			index = getValue(identifier)->index;
		}

		file << "\t%" << gIndex << " = load i8, i8* " << index << ", align 1\n";
		file << "\t%" << gIndex + 1 << " = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.d, i32 0, i32 0), i8 %" << gIndex << ")\n";
		file << "\tstore i8 %" << gIndex << ", i8* " << index << ", align 1\n";
	}

	gIndex = gIndex + 2;
}

void scanoper::checkValue(vector<valueForCheck *> &values, bool add)
{
	if (identifier != "")
	{
		if (!checkValueExist(values, identifier))
		{
			yyerror("Identifier " + identifier + " doesn't exist!", line);
		}
	}
	else
	{
		id->checkValue(values);
	}
}

/*! \class initvariable
*  \brief Реализация инициализации переменных
*/
initvariable::initvariable(const string &var, const string &identifier, expr_t *exprs, list<oper_t *> opers, const bool inited) : var(var), identifier(identifier), exprs(exprs), opers(opers), inited(inited) {}

void initvariable::print(stringstream &file)
{
	if (!needn)
	{
		if (!cycle)
		{
			if (var == "int")
			{
				file << "i32";
				funcArgs << "\t%" << gIndex + argsSize + 1 << " = alloca i32, align 4\n";
				funcArgs << "\tstore i32 %" << gIndex << ", i32* %" << gIndex + argsSize + 1 << ", align 4\n";
			}

			if (var == "bool")
			{
				file << "i8";
				funcArgs << "\t%" << gIndex + argsSize + 1 << " = alloca i8, align 1\n";
				funcArgs << "\tstore i8 %" << gIndex << ", i8* %" << gIndex + argsSize + 1 << ", align 1\n";
			}

			if (var == "string")
			{
				file << "i8*";
				funcArgs << "\t%" << gIndex + argsSize + 1 << " = alloca i8*, align 1\n";
				funcArgs << "\tstore i8* %" << gIndex << ", i8** %" << gIndex + argsSize + 1 << ", align 1\n";
			}

			if (var == "float")
			{
				file << "double";
				funcArgs << "\t%" << gIndex + argsSize + 1 << " = alloca double, align 8\n";
				funcArgs << "\tstore double %" << gIndex << ", double* %" << gIndex + argsSize + 1 << ", align 8\n";
			}

			valueForPrint *printVal = new valueForPrint(identifier, "%" + to_string(gIndex + argsSize + 1), var);
			valuesPrint.push_back(printVal);
			gIndex++;
		}
		else
		{
			file << "\t%" << gIndex << " = alloca " << getLLVMType(var) << ", align " << getLLVMSize(var) << "\n";
			int index = gIndex;
			gIndex = gIndex + 1;
			string fexpIndex = exprs->print(file);
			file << "\t%" << gIndex << " = load " << getLLVMType(var) << ", " << getLLVMType(var) << "* " << fexpIndex << ", align " << getLLVMSize(var) << "\n";
			file << "\tstore " << getLLVMType(var) << " %" << gIndex << ", " << getLLVMType(var) << "* %" << index << ", align " << getLLVMSize(var) << "\n";
			gIndex = gIndex + 1;
			valueForPrint *printVal = new valueForPrint(identifier, "%" + to_string(index), var);
			valuesPrint.push_back(printVal);
			cycleStr = identifier;
			cycle = false;
		}
	}
	else
	{
		if (curFuncName == "")
		{
			globalVars << "@" << identifier << " = global " << getLLVMType(var) << " ";

			if (var == "int")
			{
				globalVars << "0";
			}

			if (var == "bool")
			{
				globalVars << "0";
			}

			if (var == "float")
			{
				globalVars << "0.0";
			}

			if (var == "string")
			{
				globalVars << "zeroinitializer";
			}

			globalVars << ", align " << getLLVMSize(var) << "\n";
			
			if (exprs != NULL)
			{
				int oldGIndex = gIndex;
				string fexpIndex = exprs->print(initGlobalVars);
				gIndexForInitGlob = gIndexForInitGlob + (gIndex - oldGIndex);
				gIndex = oldGIndex;
				initGlobalVars << "\t%" << gIndexForInitGlob << " = load " << getLLVMType(var) << ", " << getLLVMType(var) << "* " << fexpIndex << ", align " << getLLVMSize(var) << "\n";
				initGlobalVars << "\tstore " << getLLVMType(var) << " %" << gIndexForInitGlob << ", " << getLLVMType(var) << "* @" << identifier << ", align " << getLLVMSize(var) << "\n";
				gIndexForInitGlob = gIndexForInitGlob + 1;
			}

			valueForPrint *printVal = new valueForPrint(identifier, "@" + identifier, var);
			valuesPrint.push_back(printVal);
		}
		else
		{
			file << "\t%" << gIndex << " = alloca " << getLLVMType(var) << ", align " << getLLVMSize(var) << "\n";

			int index = gIndex;
			gIndex = gIndex + 1;

			if (exprs != NULL)
			{
				string fexpIndex = exprs->print(file);

				file << "\t%" << gIndex << " = load " << getLLVMType(var) << ", " << getLLVMType(var) << "* " << fexpIndex << ", align " << getLLVMSize(var) << "\n";
				file << "\tstore " << getLLVMType(var) << " %" << gIndex << ", " << getLLVMType(var) << "* %" << index << ", align " << getLLVMSize(var) << "\n";
				
				gIndex = gIndex + 1;
			}

			valueForPrint *printVal = new valueForPrint(identifier, "%" + to_string(index), var);
			valuesPrint.push_back(printVal);
		}
	}
}

void initvariable::checkValue(vector<valueForCheck *> &values, bool add)
{
	if (exprs != NULL)
	{
		exprs->checkValue(values);

		if (var != exprs->checkType())
		{
			yyerror("Wrong type of argument! Expected " + var, line);
		}
	}

	if (add)
	{
		if (!checkValueExist(values, identifier))
		{
			values.push_back(new valueForCheck(var, identifier, {}, exprs != NULL || inited));
		}
		else
		{
			yyerror("Identifier " + identifier + " already exists!", line);
		}
	}
	else
	{
		values.push_back(new valueForCheck(var, identifier, {}, exprs != NULL || inited));
	}

	typeTest = values;
}

/*! \class funccall
*  \brief Реализация вызова функции
*/
funccall::funccall(const string &identifier, list<expr_t *> args) : identifier(identifier), args(args) {}

string funccall::print(stringstream &file)
{
	stringstream func;
	stringstream argsStream;

	int argsIndex = 0;

	for (expr_t *arg : args)
	{
		string argIndex = arg->print(file);

		file << "\t%" << gIndex << " = load " << getLLVMType(arg->checkType()) << ", " << getLLVMType(arg->checkType()) << "* " << argIndex << ", align " << getLLVMSize(arg->checkType()) << "\n";
		
		argsStream << getLLVMType(arg->checkType()) << " %" << gIndex;

		if (argsIndex != args.size() - 1)
		{
			argsIndex++;
			argsStream << ", ";
		}

		gIndex++;
	}

	if (getLLVMType(getType(typeTest, identifier).substr(0, getType(typeTest, identifier).size() - 2)) != "void")
	{
		func << "\t%" << gIndex << " = call " << getLLVMType(getType(typeTest, identifier).substr(0, getType(typeTest, identifier).size() - 2)) << " @" << identifier << "(";
		func << argsStream.str();
		func << ")\n";
		file << func.str();
		file << "\t%" << gIndex + 1 << " = alloca " << getLLVMType(getType(typeTest, identifier).substr(0, getType(typeTest, identifier).size() - 2)) << ", align " << getLLVMSize(getType(typeTest, identifier).substr(0, getType(typeTest, identifier).size() - 2)) << "\n";
		file << "\tstore " << getLLVMType(getType(typeTest, identifier).substr(0, getType(typeTest, identifier).size() - 2)) << " %" << gIndex << ", " << getLLVMType(getType(typeTest, identifier).substr(0, getType(typeTest, identifier).size() - 2)) << "* %" << gIndex + 1 << ", align " << getLLVMSize(getType(typeTest, identifier).substr(0, getType(typeTest, identifier).size() - 2)) << "\n";
		
		index = gIndex + 1;
		gIndex = gIndex + 2;

		return "%" + to_string(index);
	}
	else
	{
		func << "\tcall " << getLLVMType(getType(typeTest, identifier).substr(0, getType(typeTest, identifier).size() - 2)) << " @" << identifier << "(";
		func << argsStream.str();
		func << ")\n";
		file << func.str();

		return "0";
	}
}

void funccall::checkValue(vector<valueForCheck *> &values, bool add)
{
	typeTest = values;

	if (!checkValueExist(values, identifier, "func", "", args.size()))
	{
		yyerror("Wrong count of arguments!", line);
	}

	int i = 0;

	for (expr_t *arg : args)
	{
		arg->checkValue(values);
	}

	for (expr_t *arg : args)
	{
		if (getArgType(values, identifier, args.size(), i) != arg->checkType())
		{
			ostringstream os;
			os << i + 1;
			string arg = "Argument №" + os.str() + " has wrong type!";
			yyerror(arg, line);
		}
		i++;
	}
}

string funccall::checkType()
{
	string str = getType(typeTest, identifier);
	return str.substr(0, str.size() - 2);
}

int funccall::getIndex()
{
	return 0;
}

/*! \class funccalloper
*  \brief Реализация вызова функции, содержащейся в выражении
*/
funccalloper::funccalloper(expr_t *func) : func(func) {}

void funccalloper::print(stringstream &file)
{
	func->print(file);
}

void funccalloper::checkValue(vector<valueForCheck *> &values, bool add)
{
	func->checkValue(values);
}

/*! \class binary
*  \brief Реализация бинарных операций
*/
binary::binary(expr_t *fexp, const string &oper, expr_t *sexp) : fexp(fexp), oper(oper), sexp(sexp) {}

string binary::print(stringstream &file)
{
	if (sexp == NULL)
	{
		return fexp->print(file);
	}
	else
	{
		string fexpIndex = fexp->print(file);
		string sexpIndex = sexp->print(file);

		file << "\t%" << gIndex << " = load " << getLLVMType(fexp->checkType()) << ", " << getLLVMType(fexp->checkType()) << "* " << fexpIndex << ", align " << getLLVMSize(fexp->checkType()) << "\n";
		file << "\t%" << gIndex + 1 << " = load " << getLLVMType(sexp->checkType()) << ", " << getLLVMType(sexp->checkType()) << "* " << sexpIndex << ", align " << getLLVMSize(sexp->checkType()) << "\n";
		
		if (oper == "+")
		{
			if (fexp->checkType() == "float")
			{
				file << "\t%" << gIndex + 2 << " = alloca double, align 8\n";
				file << "\t%" << gIndex + 3 << " = fadd double %" << gIndex << ", %" << gIndex + 1 << "\n";
				file << "\tstore double %" << gIndex + 3 << ", double* %" << gIndex + 2 << ", align 8\n";
				
				index = gIndex + 2;
				gIndex = gIndex + 4;

				return "%" + to_string(index);
			}

			if (fexp->checkType() == "int")
			{
				file << "\t%" << gIndex + 2 << " = alloca i32, align 4\n";
				file << "\t%" << gIndex + 3 << " = add i32 %" << gIndex << ", %" << gIndex + 1 << "\n";
				file << "\tstore i32 %" << gIndex + 3 << ", i32* %" << gIndex + 2 << ", align 4\n";
				
				index = gIndex + 2;
				gIndex = gIndex + 4;

				return "%" + to_string(index);
			}
		}
		else if (oper == "-")
		{
			if (fexp->checkType() == "float")
			{
				file << "\t%" << gIndex + 2 << " = alloca double, align 8\n";
				file << "\t%" << gIndex + 3 << " = fsub double %" << gIndex << ", %" << gIndex + 1 << "\n";
				file << "\tstore double %" << gIndex + 3 << ", double* %" << gIndex + 2 << ", align 8\n";
				
				index = gIndex + 2;
				gIndex = gIndex + 4;

				return "%" + to_string(index);
			}

			if (fexp->checkType() == "int")
			{
				file << "\t%" << gIndex + 2 << " = alloca i32, align 4\n";
				file << "\t%" << gIndex + 3 << " = sub i32 %" << gIndex << ", %" << gIndex + 1 << "\n";
				file << "\tstore i32 %" << gIndex + 3 << ", i32* %" << gIndex + 2 << ", align 4\n";
				
				index = gIndex + 2;
				gIndex = gIndex + 4;

				return "%" + to_string(index);
			}
		}
		else if (oper == "*")
		{
			if (fexp->checkType() == "float")
			{
				file << "\t%" << gIndex + 2 << " = alloca double, align 8\n";
				file << "\t%" << gIndex + 3 << " = fmul double %" << gIndex << ", %" << gIndex + 1 << "\n";
				file << "\tstore double %" << gIndex + 3 << ", double* %" << gIndex + 2 << ", align 8\n";
				
				index = gIndex + 2;
				gIndex = gIndex + 4;

				return "%" + to_string(index);
			}

			if (fexp->checkType() == "int")
			{
				file << "\t%" << gIndex + 2 << " = alloca i32, align 4\n";
				file << "\t%" << gIndex + 3 << " = mul i32 %" << gIndex << ", %" << gIndex + 1 << "\n";
				file << "\tstore i32 %" << gIndex + 3 << ", i32* %" << gIndex + 2 << ", align 4\n";
				
				index = gIndex + 2;
				gIndex = gIndex + 4;
				
				return "%" + to_string(index);
			}
		}
		else if (oper == "%")
		{
			file << "\t%" << gIndex + 2 << " = alloca i32, align 4\n";
			file << "\t%" << gIndex + 3 << " = srem i32 %" << gIndex << ", %" << gIndex + 1 << "\n";
			file << "\tstore i32 %" << gIndex + 3 << ", i32* %" << gIndex + 2 << ", align 4\n";
			
			index = gIndex + 2;
			gIndex = gIndex + 4;
			
			return "%" + to_string(index);
		}
		else if (oper == "/")
		{
			if (fexp->checkType() == "float")
			{
				file << "\t%" << gIndex + 2 << " = alloca double, align 8\n";
				file << "\t%" << gIndex + 3 << " = fdiv double %" << gIndex << ", %" << gIndex + 1 << "\n";
				file << "\tstore double %" << gIndex + 3 << ", double* %" << gIndex + 2 << ", align 8\n";
				
				index = gIndex + 2;
				gIndex = gIndex + 4;
				
				return "%" + to_string(index);
			}
			if (fexp->checkType() == "int")
			{
				file << "\t%" << gIndex + 2 << " = alloca i32, align 4\n";
				file << "\t%" << gIndex + 3 << " = sdiv i32 %" << gIndex << ", %" << gIndex + 1 << "\n";
				file << "\tstore i32 %" << gIndex + 3 << ", i32* %" << gIndex + 2 << ", align 4\n";
				
				index = gIndex + 2;
				gIndex = gIndex + 4;
				
				return "%" + to_string(index);
			}
		}
	}
}
void binary::checkValue(vector<valueForCheck *> &values, bool add)
{
	fexp->checkValue(values);
	if (sexp != NULL)
	{
		sexp->checkValue(values);
		if (fexp->checkType() != sexp->checkType())
		{
			yyerror("Wrong type of argument! Expected " + fexp->checkType(), line);
		}
		if (fexp->checkType() == "string")
		{
			yyerror("Impossible to create such operation!", line);
		}
		if (fexp->checkType() != "int" && oper == "%")
		{
			yyerror("Wrong type of argument! Expected int", line);
		}
		if (fexp->checkType() == "boolean")
		{
			yyerror("Impossible to create such operation!", line);
		}
	}
}
string binary::checkType()
{
	if (sexp != NULL)
	{
		if (sexp->checkType() == fexp->checkType())
		{
			return fexp->checkType();
		}
		else
		{
			yyerror("Wrong type of argument! Expected " + fexp->checkType(), line);
		}
	}
	else
	{
		return fexp->checkType();
	}
}
int binary::getIndex()
{
	return 0;
}

/*! \class boolarg
*  \brief Реализация boolean-выражение
*
*  Содержится в условиях while, do-while, if
*/
boolarg::boolarg(const string &fexps, expr_t *fexp, const string &oper, expr_t *sexp, const bool &fexpsiden) : fexps(fexps), fexp(fexp), oper(oper), sexp(sexp), fexpsiden(fexpsiden) {}

string boolarg::print(stringstream &file)
{
	if (oper == "!")
	{
		string fexpIndex = fexp->print(file);
		file << "\t%" << gIndex << " = load " << getLLVMType(fexp->checkType()) << ", ";
		file << getLLVMType(fexp->checkType()) << "* " << fexpIndex << ", align " << getLLVMSize(fexp->checkType()) << "\n";
		file << "\t%" << gIndex + 1 << " = trunc i8 %" << gIndex << " to i1\n";
		file << "\t%" << gIndex + 2 << " = xor i1 %" << gIndex + 1 << ", true\n";
		file << "\t%" << gIndex + 3 << " = zext i1 %" << gIndex + 2 << " to i8\n";
		file << "\tstore i8 %" << gIndex + 3 << ", i8* " << fexpIndex << ", align 1\n";
		gIndex = gIndex + 4;
		index = gIndex - 5;
	}
	else
	{
		if (fexps == "")
		{
			string fexpIndex = fexp->print(file);
			file << "\t%" << gIndex << " = load " << getLLVMType(fexp->checkType()) << ", ";
			file << getLLVMType(fexp->checkType()) << "* " << fexpIndex << ", align " << getLLVMSize(fexp->checkType()) << "\n";
			index = gIndex;
			gIndex = gIndex + 1;
			if (oper != "")
			{
				string sexpIndex = sexp->print(file);
				file << "\t%" << gIndex << " = load " << getLLVMType(sexp->checkType()) << ", ";
				file << getLLVMType(sexp->checkType()) << "* " << sexpIndex << ", align " << getLLVMSize(sexp->checkType()) << "\n";
				file << "\t%" << gIndex + 1 << " = ";
				if (fexp->checkType() == "float")
				{
					if (oper == "==")
					{
						file << "fcmp oeq ";
					}
					else if (oper == ">=")
					{
						file << "fcmp oge ";
					}
					else if (oper == "<=")
					{
						file << "fcmp ole ";
					}
					else if (oper == "!=")
					{
						file << "fcmp une ";
					}
					else if (oper == "<")
					{
						file << "fcmp olt ";
					}
					else if (oper == ">")
					{
						file << "fcmp ogt ";
					}
				}
				else
				{
					if (oper == "==")
					{
						file << "icmp eq ";
					}
					else if (oper == ">=")
					{
						file << "icmp sge ";
					}
					else if (oper == "<=")
					{
						file << "icmp sle ";
					}
					else if (oper == "!=")
					{
						file << "icmp ne ";
					}
					else if (oper == "<")
					{
						file << "icmp slt ";
					}
					else if (oper == ">")
					{
						file << "icmp sgt ";
					}
				}

				file << getLLVMType(fexp->checkType()) << " %" << index << ", %" << gIndex << "\n";
				file << "\t%" << gIndex + 2 << " = zext i1 %" << gIndex + 1 << " to i8\n";
				file << "\t%" << gIndex + 3 << " = alloca i8, align 1\n";
				file << "\tstore i8 %" << gIndex + 2 << ", i8* %" << gIndex + 3 << ", align 1\n";
				
				index = gIndex + 3;
				gIndex = gIndex + 4;
			}
		}
		else
		{
			file << "\t%" << gIndex << " = alloca i8, align 1\n";
			file << "\tstore i8 ";
			if (fexps == "true")
			{
				file << "1";
			}
			else
			{
				file << "0";
			}
			file << ", i8* %" << gIndex << ", align 1\n";
			index = gIndex;
			gIndex = gIndex + 1;
		}
	}

	string ret = "%" + to_string(index);

	return ret;
}

void boolarg::checkValue(vector<valueForCheck *> &values, bool add)
{
	if (fexps != "")
	{
		if (fexps != "true" && fexps != "false")
		{
			if (!checkValueExist(values, fexps))
			{
				yyerror("Identifier " + fexps + " doesn't exist!", line);
			}
			if (!checkValueInited(values, fexps))
			{
				yyerror("Identifier " + fexps + " doesn't initialized!", line);
			}
		}
	}
	else
	{
		fexp->checkValue(values);
	}

	if (sexp != NULL)
	{
		sexp->checkValue(values);
	}

	if (sexp == NULL)
	{
		if (fexp == NULL && fexpsiden)
		{
			if (getType(values, fexps) != "bool")
			{
				yyerror("Wrong type of argument! Expected boolean", line);
			}
		}
		else if (fexp != NULL)
		{
			if (fexp->checkType() != "bool")
			{
				yyerror("Wrong type of argument! Expected boolean", line);
			}
		}
		else if (fexps != "true" && fexps != "false")
		{
			yyerror("Wrong type of argument! Expected boolean", line);
		}
	}
	else
	{
		if (fexp == NULL && fexpsiden)
		{
			if (getType(values, fexps) != sexp->checkType())
			{
				yyerror("Wrong type of argument! Expected " + getType(values, fexps), line);
			}
		}
		else if (fexp != NULL)
		{
			if (fexp->checkType() != sexp->checkType())
			{
				yyerror("Wrong type of argument! Expected " + fexp->checkType(), line);
			}
		}
		else
		{
			yyerror("Wrong type of argument!", line);
		}
	}
}

string boolarg::checkType()
{
	return "bool";
}

int boolarg::getIndex()
{
	return 0;
}

/*! \class value
*  \brief Реализация единичного значение в бинарной операции
*/
value::value(const string &constant, const string &identifier, expr_t *id, const string &type) : constant(constant), identifier(identifier), id(id), type(type) {}

string value::print(stringstream &file)
{
	if (id != NULL)
	{
		string fexpIndex = id->print(file);
		return fexpIndex;
	}
	else if (constant != "")
	{
		if (type != "string")
		{
			file << "\t%" << gIndex << " = alloca " << getLLVMType(type) << ", align " << getLLVMSize(type) << "\n";
			
			if (type == "bool")
			{
				constant = constant == "true" ? to_string(1) : to_string(0);
			}

			if (type != "string")
			{
				file << "\tstore " << getLLVMType(type) << " " << constant << ", " << getLLVMType(type) << "* %" << gIndex << ", align " << getLLVMSize(type) << "\n";
			}

			index = gIndex;
			gIndex = gIndex + 1;

			return "%" + to_string(index);
		}
		else
		{
			gVarIndex++;
			int counter = 0;
			constant = replaceAll(constant, "\\n", "\\0A", &counter);
			int size = constant.size() - 2 - counter * 2 + 1;

			file << "\t%" << gIndex << " = alloca [" << size << " x i8], align " << getLLVMSize(type) << "\n";
			file << "\t%" << gIndex + 1 << " = bitcast [" << size << " x i8]* %" << gIndex << " to i8*\n";
			file << "\tcall void @llvm.memcpy.p0i8.p0i8.i64(i8* %" << gIndex + 1 << ", i8* getelementptr inbounds ([" << size << " x i8], [" << size << " x i8]* @.gVar." << gVarIndex << ", i32 0, i32 0), i64 " << size << ", i32 1, i1 false)\n";
			file << "\t%" << gIndex + 2 << " = getelementptr inbounds [" << size << " x i8], [" << size << " x i8]* %" << gIndex << ", i32 0, i32 0\n";
			file << "\t%" << gIndex + 3 << " = alloca i8*, align 1\n";
			file << "\tstore i8* %" << gIndex + 2 << ", i8** %" << gIndex + 3 << ", align 1\n";
			
			globalVars << "@.gVar." << gVarIndex << " = private unnamed_addr constant [" << size << " x i8] c\"" << constant.substr(1, constant.size() - 2) << "\\00\", align 1\n";
			index = gIndex + 3;
			gIndex = gIndex + 4;

			return "%" + to_string(index);
		}
	}
	else
	{
		valueForPrint *val = getValue(identifier);

		file << "\t%" << gIndex << " = alloca " << getLLVMType(val->type) << ", align " << getLLVMSize(val->type) << "\n";
		file << "\t%" << gIndex + 1 << " = load " << getLLVMType(val->type) << ", " << getLLVMType(val->type) << "* " << val->index << ", align " << getLLVMSize(val->type) << "\n";
		file << "\tstore " << getLLVMType(val->type) << " %" << gIndex + 1 << ", " << getLLVMType(val->type) << "* %" << gIndex << ", align " << getLLVMSize(val->type) << "\n";
		
		index = gIndex;
		gIndex = gIndex + 2;

		return "%" + to_string(index);
	}
}

void value::checkValue(vector<valueForCheck *> &values, bool add)
{
	typeTest = values;
	if (identifier != "")
	{
		if (!checkValueExist(values, identifier))
		{
			yyerror("Identifier " + identifier + " doesn't exist!", line);
		}
		if (!checkValueInited(values, identifier))
		{
			yyerror("Identifier " + identifier + " doesn't initialized!", line);
		}
	}
	else if (id != NULL)
	{
		id->checkValue(values);
	}
}

string value::checkType()
{
	if (id != NULL)
	{
		return id->checkType();

	}
	if (identifier != "")
	{
		if (!checkValueExist(typeTest, identifier))
		{
			yyerror("Identifier " + identifier + " doesn't exist!", line);
		}
		else
		{
			return getType(typeTest, identifier);
		}
	}

	if (constant != "")
	{
		return type;
	}
}

int value::getIndex()
{
	return 0;
}

/*! \class unaryoper
*  \brief Реализация унарных операций типа !, -
*/
unaryoper::unaryoper(const string &oper, const string &constant, const string &identifier, expr_t *id, const string &argType) : oper(oper), constant(constant), identifier(identifier), id(id), argType(argType) {}
string unaryoper::print(stringstream &file)
{
	if (constant != "")
	{
		if (argType == "int")
		{
			file << "\t%" << gIndex << " = alloca i32, align 4\n";
			file << "\t%" << gIndex + 1 << " = sub nsw i32 0, i32 " << constant;
			file << "store i32 %" << gIndex + 1 << ", i32* %" << gIndex;
			index = gIndex;
			gIndex = gIndex + 2;
		}
		if (argType == "float")
		{
			file << "\t%" << gIndex << " = alloca double, align 8\n";
			file << "\t%" << gIndex + 1 << " = sub nsw float 0, float " << constant;
			file << "store float %" << gIndex + 1 << ", float* %" << gIndex;
			index = gIndex;
			gIndex = gIndex + 2;
		}
	}

	if (identifier != "")
	{
		valueForPrint *val = getValue(identifier);

		file << "\t%" << gIndex << " = load " << getLLVMType(val->type) << ", " << getLLVMType(val->type) << "* " << val->index << ", align " << getLLVMSize(val->type) << "\n";
		
		if (val->type == "int")
		{
			file << "\t%" << gIndex + 1 << " = alloca i32, align 4\n";
			file << "\t%" << gIndex + 2 << " = add i32 %" << gIndex << ", -1\n";
		}
		else if (val->type == "float")
		{
			file << "\t%" << gIndex + 1 << " = alloca double, align 8\n";
			file << "\t%" << gIndex + 2 << " = fadd double %" << gIndex << ", -1.0\n";
		}
		else if (val->type == "bool")
		{
			file << "\t%" << gIndex + 1 << " = alloca i8, align 1\n";
			file << "\t%" << gIndex + 2 << " = trunc i8 %" << gIndex << " to i1\n";
			file << "\t%" << gIndex + 3 << " = xor i1 %" << gIndex + 2 << ", true\n";
			file << "\t%" << gIndex + 4 << " = zext i1 %" << gIndex + 3 << " to i8\n";
			file << "\tstore i8 %" << gIndex + 4 << ", i8* %" << gIndex + 1 << ", align 1\n";
			index = gIndex + 1;
			gIndex = gIndex + 5;
		}

		if (val->type != "bool")
		{
			file << "\tstore " << getLLVMType(val->type) << " %" << gIndex + 1 << ", " << getLLVMType(val->type) << "* %" << gIndex + 1 << ", align " << getLLVMSize(val->type) << "\n";
			index = gIndex + 1;
			gIndex = gIndex + 3;
		}
	}

	if (id != NULL)
	{
		string idIndex = id->print(file);
		file << "\t%" << gIndex << " = load " << getLLVMType(id->checkType()) << ", ";
		file << getLLVMType(id->checkType()) << "* " << idIndex << ", align " << getLLVMSize(id->checkType()) << "\n";
		
		if (id->checkType() == "int")
		{
			file << "\t%" << gIndex + 1 << " = alloca i32, align 4\n";
			file << "\t%" << gIndex + 2 << " = sub nsw i32 0, i32 %" << gIndex;
			file << "store i32 %" << gIndex + 2 << ", i32* %" << gIndex + 1;
		}

		if (id->checkType() == "float")
		{
			file << "\t%" << gIndex + 1 << " = alloca double, align 8\n";
			file << "\t%" << gIndex + 2 << " = sub nsw double 0, double %" << gIndex;
			file << "store double%" << gIndex + 2 << ", double* %" << gIndex + 1;
		}

		index = gIndex + 1;
		gIndex = gIndex + 3;
	}

	string ret = "%" + to_string(index);

	return ret;
}

void unaryoper::checkValue(vector<valueForCheck *> &values, bool add)
{
	if (identifier != "")
	{
		if (!checkValueExist(values, identifier))
		{
			yyerror("Identifier " + identifier + " doesn't exist!", line);
		}
		if (!checkValueInited(values, identifier))
		{
			yyerror("Identifier " + identifier + " doesn't initialized!", line);
		}
	}
	else if (id != NULL)
	{
		id->checkValue(values);
	}

	if (oper == "-")
	{
		if (identifier != "")
		{
			if (getType(values, identifier) != "int" && getType(values, identifier) != "float")
			{
				yyerror("Wrong type of argument! Expected int or float", line);
			}
		}

		if (id != NULL)
		{
			if (id->checkType() != "int" && id->checkType() != "float")
			{
				yyerror("Wrong type of argument! Expected int or float", line);
			}
		}

		if (constant != "")
		{
			if (argType != "int" && argType != "float")
			{
				yyerror("Wrong type of argument! Expected int or float", line);
			}
		}
	}
	else
	{
		if (identifier != "")
		{
			if (getType(values, identifier) != "bool")
			{
				yyerror("Wrong type of argument! Expected boolean", line);
			}
		}

		if (id != NULL)
		{
			if (id->checkType() != "bool")
			{
				yyerror("Wrong type of argument! Expected boolean", line);
			}
		}

		if (constant != "")
		{
			if (argType != "bool")
			{
				yyerror("Wrong type of argument! Expected boolean", line);
			}
		}
	}
}

string unaryoper::checkType()
{
	if (identifier != "")
	{
		return getType(typeTest, identifier);
	}

	if (id != NULL)
	{
		return id->checkType();
	}

	if (constant != "")
	{
		return argType;
	}
}

int unaryoper::getIndex()
{
	return 0;
}