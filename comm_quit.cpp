#include "comm_quit.h"
#include "comm_move.h"
#include "comm_delete.h"
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

void save(char *c, Aliases *al, Selections *se,Commands_father* com){
	ofstream dat;
	dat.open(c);
	dat << "<aliases>" << endl;
	dat << al;
	dat << "</aliases>" << endl;
	dat << "<selections>" << endl;
	dat << se;
	dat << "</selections>" << endl;
	dat << "<commands>" << endl;
	dat << com;
	dat << "</commands>" << endl;
	dat.close();
}

void Quit::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	char c[BUFSIZE];
	char b[BUFSIZE];
	int k = 0;
	string st;
	Selection *sel;
	stringstream(s) >> c >> b >> c;
	if (b[1] == '\0')
		switch (b[0]){
		case 's':
			cout << "Save (0-N): ";
			getline(cin, st);
			if (!(st == "0")){
				cout << "Name: ";
				getline(cin, st);
				st += ".txt";
				stringstream(st) >> b;
				save(b, al, se,commands_t);
			}
			*n = 0;
			return;
		case'q':
			*n = 0;
			return;
		case'u':
			if (*permision == 1){
				cout << "Permission downgraded\n";
				*permision = 0;
			}
			return;
	}
	command *del = new Delete(commands_t);
	command *m = new Move();
	string str = "move save_cmd.txt save_cmd_backup.txt";
	*permision = 1;
	del->runC("delete d save_cmd_backup.txt", al, se, n,permision);
	m->runC(str, al, se, n,permision);
	save("save_cmd.txt", al, se,commands_t);
	*n = 0;
	delete m;
	delete del;
}