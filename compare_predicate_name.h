#ifndef _predicate_name_compare_h
#define _predicate_name_compare_h

#include "selection_predicate.h"
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

class FileNamePredicateCompare : public FileSelectionPredicate{
	char name[MAX_PATH];
	Selection* select;
public:
	FileNamePredicateCompare(char* n, Selection* s) {
		strcpy(name, n);
		select = s;
	}
	Selection* start();
	bool check_redy(){ return true; }
};

#endif