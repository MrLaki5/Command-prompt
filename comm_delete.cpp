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

int remove_directory(const char *path){
	DIR *d = opendir(path);
	size_t path_len = strlen(path);
	string s;
	int r = -1;
	if (d){
		struct dirent *p;
		r = 0;
		int k = 1, t = 0;
		while (!r && (p = readdir(d))){
			int r2 = -1;
			char buf[BUFSIZE];
			size_t len;
			if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")){	// Skip the names "." and ".." as we don't want to recurse on them.
				continue;
			}
			struct stat statbuf;
			sprintf(buf, "%s/%s", path, p->d_name);
			if (!stat(buf, &statbuf)){
				if (k){
					cout << "Folder " << path << " not empty, proceed (0-N): ";
					getline(cin, s);
					k = 0;
					if (s == "0")
						return -1;
				}
				if (S_ISDIR(statbuf.st_mode)){
					r2 = remove_directory(buf);
				}
				else{
					r2 = _unlink(buf);
				}
			}
			if (r2 == -1)
				t = 1;
		}
		if (t)
			r = -1;
		closedir(d);
	}
	if (!r){
		r = _rmdir(path);
	}
	return r;
}


void Delete::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	if (*permision == 0)
		throw new perm_denied();
	char c[BUFSIZE];
	char b[BUFSIZE];
	int k = 0;
	Selection *sel;
	stringstream(s) >> c >> b >> c;
	string ss;
	if (b[1] == '\0'){
		switch (b[0]){
		case 'd':
			if (c != ""){
				al->Switch(c);
				sel = se->find(c);
				if (!sel){
					sel = new Selection("", c, 1);
					k = 1;
				}
				if (sel->getlength() > 1){
					cout << "Warrning, selection is about to be deleted, proceed (0-N): ";
					getline(cin, ss);
					if (s == "0")
						return;
				}
				for (int i = 0; i < sel->getlength(); i++){
					cout << sel->getelem(i) << endl;
					strcpy(b, sel->getelem(i).c_str());
					if (k){
						int k1;
						for (k1 = strlen(b) - 1; k1 > 0; --i)
						{
							if (b[k1] == '\\')
							{
								b[k1] = '\0';
								break;
							}
						}
						if (k1 == 0)
							b[0] = '\0';
					}
					if (remove_directory(b) == -1){
						struct stat statbuf;
						if (!stat(b, &statbuf))
							if (!(S_ISDIR(statbuf.st_mode)))
								_unlink(b);
					}
				}
				if (k)
					delete sel;
			}
			else
				throw new unknown_comm();
			break;
		case 'a':
			al->delall();
			se->deleteall();
			break;
		case 'c':
			commands_t->remove(c);
			break;
		}
	}
	else
		throw new unknown_comm();
}