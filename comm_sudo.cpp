#include "comm_sudo.h"
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


void Sudo::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	string word;
	cout << "Password: ";
	getline(cin, word);
	if (strcmp(word.c_str(), "password") == 0){
		cout << "Sucessfull\n";
		*permision = 1;
		return;
	}
	cout << "Wrong password\n";
}