#ifndef _predicate_time_compare_h
#define _predicate_time_compare_h

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

class FileTimePredicateCompare : public FileSelectionPredicate{
	Selection* select;
	FILETIME t1, t2;
	int offset = 0;
public:
	FileTimePredicateCompare(Selection* s, FILETIME t) {
		select = s;
		t1 = t;
	}
	FileTimePredicateCompare(Selection* s, FILETIME t, FILETIME tt) {
		select = s;
		t1 = t;
		t2 = tt;
		offset = 1;
	}
	Selection* start();
	bool check_redy(){ return true; }
};

#endif