#ifndef _custom_predicate_h
#define _custom_predicate_h


#include "selection_composite.h"
#include "aliases.h"
#include "selection.h"
#include "selections.h"
#include "errors.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
using namespace std;

class CustomPredicate :public CompositePredicate{
	friend class CustomPredicateBuilder;
	string name;
public:
	~CustomPredicate(){ delete list[0]; delete[] list; }
	Selection* start();
	bool check_redy();
protected:
	CustomPredicate(FileSelectionPredicate* obj, string nname){
		name = nname;
		list = new FileSelectionPredicate*[1];
		list[0] = obj;
	}
};



#endif