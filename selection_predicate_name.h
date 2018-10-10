#ifndef _predicate_name_h
#define _predicate_name_h

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

class FileNamePredicate : public FileSelectionPredicate{
	char name[MAX_PATH];
	char dir[MAX_PATH];
public:
	FileNamePredicate(char* n, char* d) {
		strcpy(name, n);
		strcpy(dir, d);
	}
	Selection* start();
	bool check_redy(){ return true; }
};

#endif