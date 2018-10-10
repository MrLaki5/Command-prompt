#ifndef _predicate_h
#define _predicate_h

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

class FileSelectionPredicate{
public:
	virtual Selection* start() = 0;
	virtual bool check_redy() = 0;
	virtual ~FileSelectionPredicate(){}
	virtual void getarg(FileSelectionPredicate* obj){};
};



#endif