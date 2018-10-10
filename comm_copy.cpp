#include "comm_copy.h"
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


void Copy::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	if (*permision == 0)
		throw new perm_denied();
	char c[BUFSIZE];
	char b[BUFSIZE];
	char a[BUFSIZE];
	int k = 0;
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
		cout << "Warrning, selection is about to be copied" << endl;
	}
	int all = 0;
	int skip_all = 0;
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
		BOOL ba = FALSE;
		if (CopyFileEx(ptr, ptr1, lpProgressRoutine, aaa, &ba, COPY_FILE_FAIL_IF_EXISTS))
			cout << "			Copied" << endl;
		else{
			if (GetFileAttributes(ptr1) != INVALID_FILE_ATTRIBUTES){
				string word;
				if (!(all || skip_all)){
					cout << "File already exists, (Y- yes, A- yes all, S- skip, K- skip all, B- cancel): ";
					getline(cin, word);
				}
				if (all)
					word = "A";
				if (skip_all)
					word = "K";
				switch (word[0]){
				case 'Y':
					CopyFileEx(ptr, ptr1, lpProgressRoutine, aaa, &ba, 0);
					cout << "			Copied" << endl;
					break;
				case 'A':
					all = 1;
					CopyFileEx(ptr, ptr1, lpProgressRoutine, aaa, &ba, 0);
					cout << "			Copied" << endl;
					break;
				case 'K':
					skip_all = 1;
					break;
				case 'S':
					break;
				case 'B':
					cout << "Copy canceled\n";
					if (k)
						delete sel;
					return;
				}
			}
			else
				cout << "			Not copied" << endl;
		}
	}
	if (k)
		delete sel;
}