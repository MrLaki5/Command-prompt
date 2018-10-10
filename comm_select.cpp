#include "comm_select.h"
#include "selection.h"
#include "aliases.h"
#include "dirent.h"
#include "cropper.h"
#include "selection_custom_predicate_builder.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <direct.h>
#include <fstream>



void Select::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	char c[BUFSIZE];
	char b[BUFSIZE];
	char d[BUFSIZE];
	Cropper crop;
	stringstream(s) >> c >> c;
	if (c[1] == '\0'){
		switch (c[0]){
		case 'n':
			stringstream(s) >> c >> c >> d >> c >> b;
			if (!((strcmp(c, "") != 0) && (strcmp(b, "") != 0) && (strcmp(d, "") != 0)))
				break;
			al->Switch(c);
			se->add1(CustomPredicateBuilder::instance()->build(s,&crop)->start());
			//se->dodaj(d, c, b);
			cout << "				Created" << endl;
			return;
		case 'r':
			stringstream(s) >> c >> c >> d >> c >> b;
			if (!((strcmp(c, "") != 0) && (strcmp(b, "") != 0) && (strcmp(d, "") != 0)))
				break;
			al->Switch(c);
			se->rename(d, c, b);
			cout << "				Done" << endl;
			return;
		case 'd':
			stringstream(s) >> c >> c >> c;
			if (!(strcmp(c, "") != 0))
				break;
			al->Switch(c);
			se->delspec(c);
			cout << "				Deleted" << endl;
			return;
		}
	}
	throw new unknown_comm();
}