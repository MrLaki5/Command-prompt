#include "comm_help.h"
#include "selection.h"
#include "aliases.h"
#include "dirent.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <direct.h>
#include <fstream>

void Help::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	stringstream ss;
	string word;
	ss << s << '\0';
	ss >> word >> word;
	cout << "Help:\n";
	cout << "1. cd path #path can be alias or path\n";
	cout << "2. dir path #path can be alias or path, if left blank prints from current dir\n";
	cout << "3. info #no arguments\n";
	cout << "4. sudo #no arguments, gives admin permission to user\n";
	cout << "5. makedir path name #if name left blank, path must be alias\n";
	cout << "6. copy file destination #file can be selection or path, destination can be \n";
	cout << "        alias or path\n";
	cout << "7. move file destination #file can be selection or path, destination can be \n";
	cout << "        alias or path\n";
	cout << "8. setts name date time #name can be select, alias or path. \n";
	cout << "         Date DD.MM.YYYY. time HH:MM:SS, time can be blank. \n";
	cout << "9. assign n name path #creates new alias\n";
	cout << "   assign r name new_path #changes path of existing alias\n";
	cout << "   assign d name #deletes alias\n";
	cout << "10. delete d arg #arg can be selection or path or alias\n";
	cout << "    delete a #deletes all existing aliases and selections\n";
	cout << "    delete c arg #delets custom made command, arg is name of command\n";
	cout << "11. quit #with no arg, quits program and saves to config\n";
	cout << "    quit q #quits program with no save\n";
	cout << "    quit s #quits program with option to save where user wants\n";
	cout << "    quit u #returns to user mode, if admin mode was on\n";
	cout << "12. select n name dir comm_expr# name of select: name, dir is path\n";
	cout << "           , comm_expr more on \"help expr\" \n";
	cout << "    select d name #deletes selection\n";
	cout << "13. compare name comm_expr #compare selects, name: name of new select, \n";
	cout << "             more about comm_expr on \"help expr\"\n";
	cout << "14. new name_comm #creates new command. Later usage of \n";
	cout << "        command: \"name_comm arg1 | arg2 | ... | argn |\",\n";
	cout << "        where all argi are arguments of basic commands\n";
	if (strcmp(word.c_str(),"expr")==0){
		cout << "Help expr:\n";
		cout << "Expression in select: \n";
		cout << "\t1. AND(arg1,arg2)\n";
		cout << "\t2. OR(arg1,arg2)\n";
		cout << "\t3. XOR(arg1,arg2)\n";
		cout << "\t4. NOT(arg)\n";
		cout << "\t5. name=\"arg_string\"\n";
		cout << "\t6. size=\"arg_int\"\n";
		cout << "\t6. size=\"arg1_int-arg1_int\"\n";
		cout << "\t7. time=\"DD.MM.YYYY.\"\n";
		cout << "\t8. time=\"DD.MM.YYYY.-HH:MM:SS\"\n";
		cout << "\t9. time=\"spec_arg\" #spec_arg is made from \n";
		cout << "\t         one number and one char (H-hour, D-day, M-Month, Y-year)\n";
		cout << "Expression in compare: \n";
		cout << "\t1. AND(arg1,arg2)\n";
		cout << "\t2. OR(arg1,arg2)\n";
		cout << "\t3. XOR(arg1,arg2)\n";
		cout << "\t4. NOT(arg)\n";
		cout << "\t5. name=\"arg_string,name_of_select\"\n";
		cout << "\t6. size=\"arg_int,name_of_select\"\n";
		cout << "\t6. size=\"arg1_int-arg1_int,name_of_select\"\n";
		cout << "\t7. time=\"DD.MM.YYYY.,name_of_select\"\n";
		cout << "\t8. time=\"DD.MM.YYYY.-HH:MM:SS,name_of_select\"\n";
		cout << "\t9. time=\"spec_arg,name_of_select\" #spec_arg is made from \n";
		cout << "\t         one number and one char (H-hour, D-day, M-Month, Y-year)\n";
	}
}