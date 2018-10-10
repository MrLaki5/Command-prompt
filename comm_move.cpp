#include "comm_move.h"
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


void Move::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	if (*permision == 0)
		throw new perm_denied();
	char c[BUFSIZE];
	char b[BUFSIZE];
	char a[BUFSIZE];
	int k = 0, t;
	Selection *sel;
	stringstream(s) >> c >> b >> c;
	al->Switch(c);
	strcpy(a, c);
	sel = se->find(b);
	if (!sel){
		sel = new Selection("", b, 1);
		k = 1;
	}
	if (sel->getlength() > 1){
		cout << "Warrning, selection is about to be moved" << endl;
	}
	for (int i = 0; i < sel->getlength(); i++){
		cout << sel->getelem(i) << endl;
		strcpy(c, a);
		wchar_t wtext[BUFSIZE];
		strcpy(b, sel->getelem(i).c_str());
		if (k){
			int k1;
			for (k1 = strlen(b) - 1; k1>0; --i)
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
		else {
			sprintf(c, "%s\\%s", c, sel->getelemname(i).c_str());
		}
		mbstowcs(wtext, b, strlen(b) + 1);
		LPCWSTR ptr = wtext;
		wchar_t wtext1[BUFSIZE];
		mbstowcs(wtext1, c, strlen(c) + 1);
		LPCWSTR ptr1 = wtext1;
		LPVOID *aaa = nullptr;
		LPPROGRESS_ROUTINE lpProgressRoutine = &CopyProgressRoutine;
		if (MoveFileWithProgress(ptr, ptr1, lpProgressRoutine, aaa, MOVEFILE_COPY_ALLOWED))
			cout << "			Moved" << endl;
		else
			cout << "			Not moved" << endl;
	}
	if (k)
		delete sel;
}