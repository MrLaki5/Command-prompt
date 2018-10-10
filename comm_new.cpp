#include "comm_new.h"
#include "selection.h"
#include "aliases.h"
#include "dirent.h"
#include "batch_command_builder.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <direct.h>
#include <fstream>


void New::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	if (*permision == 0)
		throw new perm_denied();
	string name;
	stringstream(s) >> name >> name;
	command* com_temp=BatchCommandBuilder::instance()->build(name, commands_t);
	commands_t->add_elem(com_temp);
}