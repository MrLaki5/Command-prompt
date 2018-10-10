#include "comm_assign.h"
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

void Assign::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	char c[BUFSIZE];
	char b[BUFSIZE];
	stringstream(s) >> c >> c;
	if (c[1] == '\0'){
		switch (c[0]){
		case 'n':
			stringstream(s) >> c >> c >> c >> b;
			if (!((strcmp(c, "") != 0) && (strcmp(b, "") != 0)))
				break;
			cout << "				Created" << endl;
			al->add(c, b);
			return;
		case 'r':
			stringstream(s) >> c >> c >> c >> b;
			if (!((strcmp(c, "") != 0) && (strcmp(b, "") != 0)))
				break;
			al->rename(c, b);
			cout << "				Done" << endl;
			return;
		case 'd':
			stringstream(s) >> c >> c >> c;
			if (!(strcmp(c, "") != 0))
				break;
			al->delete_(c);
			cout << "				Deleted" << endl;
			return;
		}
	}
	throw new unknown_comm();
}