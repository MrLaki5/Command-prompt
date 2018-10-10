#ifndef _logicalop_h
#define _logicalop_h

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

class LogicalOp :public CompositePredicate{
public:
	LogicalOp(){
		list = new FileSelectionPredicate* [2];
	}
	~LogicalOp(){ delete list[0]; delete list[1]; delete[] list; }
};



#endif