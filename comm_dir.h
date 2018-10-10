#ifndef _comm_dir_h
#define _comm_dir_h

#include "aliases.h"
#include "selection.h"
#include "command.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>


class Dir : public command{
	bool checkC(char* c) override{
		return strcmp(c, "dir") == 0;
	};
	void runC(string s, Aliases *al, Selections *se, int *n, int *permision) override;
	void write(ostream& os) {
		os << "dir";
	}
};


#endif