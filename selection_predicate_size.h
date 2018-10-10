#ifndef _predicate_size_h
#define _predicate_size_h

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

class FileSizePredicate : public FileSelectionPredicate{
	char dir[MAX_PATH];
	long low;
	long high;
public:
	FileSizePredicate(char* d, long l, long h = 0) {
		strcpy(dir, d);
		low = l;
		high = h;
	}
	Selection* start();
	bool check_redy(){ return true; }
};

#endif