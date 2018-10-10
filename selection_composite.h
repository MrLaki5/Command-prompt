#ifndef _composite_h
#define _composite_h

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

class CompositePredicate :public FileSelectionPredicate{
protected:
	FileSelectionPredicate **list;
};


#endif