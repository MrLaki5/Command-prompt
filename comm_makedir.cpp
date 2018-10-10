#include "comm_makedir.h"
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

void Makedir::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	if (*permision == 0)
		throw new perm_denied();
	char c[BUFSIZE];
	char b[20];
	stringstream(s) >> c >> c >> b;
	if ((strcmp(b, "") != 0)){
		al->Switch(c);
		sprintf(c, "%s/%s", c, b);
	}
	if (_mkdir(c) != 0)
		throw new creat_fail();
	cout << "		Created" << endl;
}