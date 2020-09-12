#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
extern int yylineno;
extern string curFuncName;
/*! \class valueForPrint
 	*  \brief Содержит информацию о переменной или функции, которые были инициализированы (использутся во время трансляции)
 	*/
    class valueForPrint {
		public:
			string identifier;
			string index = "";
			bool isGlobal = curFuncName == "";
			string type = "";
			int size = 0;
			int sSize = 0;
			vector<valueForPrint*> prints;
			valueForPrint(const string& identifier, const string& index, const string& type, int size = 0, int sSize = 0);
	};
	/*! \class valueForCheck
 	*  \brief Содержит информацию о переменной или функции, которые были инициализированы
 	*/
    class valueForCheck {
		public: 
			int line = yylineno;  
			string val;
			string identifier;
			bool inited;
			vector<valueForCheck*> structVal;
			vector<valueForCheck*> funcArgs;
			string size;
			valueForCheck(const string& val, const string& identifier, vector<valueForCheck*> structVal, const bool inited, const string& size = "0");
	};
    string replaceAll(string str, const string& from, const string& to, int *size);
	string getLLVMType(string var);
	string getLLVMSize(string var);
	valueForPrint* getValue(string identifier);
	string getSize(vector<valueForCheck*> values, string identifier, string sidentifier = "", bool arr = false);
	string getType(vector<valueForCheck*> values, string identifier, string sidentifier = "");
	bool checkValueInited(vector<valueForCheck*> values, string identifier);
	bool checkValueInited(vector<valueForCheck*> values, string identifier, string func, string secarg);
	bool checkValueExist(vector<valueForCheck*> values, string identifier);
	bool checkValueExist(vector<valueForCheck*> values, string identifier, string func, string secarg = "", int count = 0);
	string getArgType(vector<valueForCheck*> values, string identifier, int count, int numberOfArg);
#endif