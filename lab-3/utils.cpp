
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
using namespace std;
	extern string curFuncName;
			valueForPrint::valueForPrint(const string& identifier, const string& index, const string& type, int size, int sSize) : identifier(identifier), index(index), type(type), size(size), sSize(sSize) {}

	extern int yylineno;
	extern vector <valueForPrint*> valuesPrint;
	
			valueForCheck::valueForCheck(const string& val, const string& identifier, vector<valueForCheck*> structVal, const bool inited, const string& size) : val(val), identifier(identifier), structVal(structVal), inited(inited), size(size) {}
    string replaceAll(string str, const string& from, const string& to, int *size) {
		size_t start_pos = 0;
		while((start_pos = str.find(from, start_pos)) != std::string::npos) {
			*size = *size + 1;
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
		return str;
	}
	string getLLVMType(string var) {
		if (var == "int") {
			return "i32";
		} else if (var == "string") {
			return "i8*";
		} else if (var == "float") {
			return "double";
		} else if (var == "bool") {
			return "i8";
		} if (var == "int[]") {
			return "i32";
		} else if (var == "void") {
			return "void";
		} else {
			bool exist = false;
			for (int i = 0; i < valuesPrint.size(); i++) {
				if (valuesPrint.at(i)->identifier == var) {
					exist = true;
					break;
				}
			}
			
			return "%" + var;
			
		}
	}
	string getLLVMSize(string var) {
		if (var == "int") {
			return "4";
		} else if (var == "string") {
			return "1";
		} else if (var == "float") {
			return "8";
		} else if (var == "bool") {
			return "1";
		} else {
			return "1";
		}
	}
	valueForPrint* getValue(string identifier) {
		for (int i = 0; i < valuesPrint.size(); i++) {
			if (valuesPrint.at(i)->identifier == identifier) {
				return valuesPrint.at(i);
			}
		}
	}
	string getSize(vector<valueForCheck*> values, string identifier, string sidentifier, bool arr) {
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
	string getType(vector<valueForCheck*> values, string identifier, string sidentifier) {
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
	bool checkValueInited(vector<valueForCheck*> values, string identifier) {
		for (int i = 0; i < values.size(); i++) {
			
			if (values.at(i)->identifier == identifier && values.at(i)->inited == true) {
				return true;
			}
		}
		return false;
	}
	
	bool checkValueExist(vector<valueForCheck*> values, string identifier, string func, string secarg, int count) {
		if (func == "func") {
			for (int i = 0; i < values.size(); i++) {
				if (values.at(i)->identifier == identifier && values.at(i)->funcArgs.size() == count && (values.at(i)->val == "int()" || values.at(i)->val == "bool()" || values.at(i)->val == "string()" || values.at(i)->val == "float()" || values.at(i)->val == "void()")) {
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