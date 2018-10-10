#include "comm_compare.h"
#include "selection_custom_predicate_builder.h"
#include "cropper_compare.h"
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


void Compare::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	string name;
	stringstream *ss_temp =new stringstream(s);
	stringstream ss;
	(*ss_temp) >> name>>name;
	string temp;
	getline(*ss_temp, temp);
	delete ss_temp;
	ss << name << " " << name << " " << name << " - " << temp;
	getline(ss, temp);
	Cropper_compare crop = Cropper_compare(se);
	Selection *sel_temp=CustomPredicateBuilder::instance()->build(temp, &crop)->start();
	sel_temp->putpath("-");
	se->add1(sel_temp);
}