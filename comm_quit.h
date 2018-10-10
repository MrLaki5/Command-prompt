#ifndef _comm_quit_h
#define _comm_quit_h

#include "commands_father.h"
#include "aliases.h"
#include "selection.h"
#include "command.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>


class Quit : public command{
	Commands_father* commands_t;
	bool checkC(char* c) override{
		return strcmp(c, "quit") == 0;
	};
	void runC(string s, Aliases *al, Selections *se, int *n, int *permision) override;
	void write(ostream& os) {
		os << "quit";
	}
public:
	Quit(Commands_father* c) :commands_t(c){};
};


#endif