#ifndef _logicalop_or_h
#define _logicalop_or_h

#include "selection_LogicalOp.h"
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

class Or :public LogicalOp{
public:
	Selection* start();
	bool check_redy(){ return ((list[0] != nullptr) && (list[1] != nullptr)); }
	Or() :LogicalOp(){
		list[0] = nullptr;
		list[1] = nullptr;
	}
	void getarg(FileSelectionPredicate* obj);
};



#endif