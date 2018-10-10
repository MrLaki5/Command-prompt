#ifndef _comm_assign_h
#define _comm_assign_h

#include "aliases.h"
#include "selection.h"
#include "command.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>


class Assign : public command{
	bool checkC(char* c) override{
		return strcmp(c, "assign") == 0;
	};
	void runC(string s, Aliases *al, Selections *se, int *n, int *permision) override;
	void write(ostream& os) {
		os << "assign";
	}
};


#endif