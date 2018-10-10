#ifndef _predicate_time_h
#define _predicate_time_h

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

class FileTimePredicate : public FileSelectionPredicate{
	char dir[MAX_PATH];
	FILETIME t1, t2;
	int offset = 0;
public:
	FileTimePredicate(char* d, FILETIME t) {
		strcpy(dir, d);
		t1 = t;
	}
	FileTimePredicate(char* d, FILETIME t, FILETIME tt) {
		strcpy(dir, d);
		t1 = t;
		t2 = tt;
		offset = 1;
	}
	Selection* start();
	bool check_redy(){ return true; }
};

#endif