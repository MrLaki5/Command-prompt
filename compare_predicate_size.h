#ifndef _predicate_size_compare_h
#define _predicate_size_compare_h

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

class FileSizePredicateCompare : public FileSelectionPredicate{
	Selection* select;
	long low;
	long high;
public:
	FileSizePredicateCompare(Selection* s, long l, long h = 0) {
		select = s;
		low = l;
		high = h;
	}
	Selection* start();
	bool check_redy(){ return true; }
};

#endif