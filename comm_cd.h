#ifndef _comm_cd_h
#define _comm_cd_h

#include "aliases.h"
#include "selection.h"
#include "command.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>


class Cd : public command{
	bool checkC(char* c) override{
		return strcmp(c, "cd") == 0;
	};
	void runC(string s, Aliases *al, Selections *se, int *n, int *permision) override;
	void write(ostream& os) {
		os << "cd";
	}
};


#endif