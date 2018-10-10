#include "comm_setts.h"
#include "selection.h"
#include <windows.h> 
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <winioctl.h>
#include <sstream>

void Setts::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	if (*permision == 0)
		throw new perm_denied();
	char c[BUFSIZE];
	char b[BUFSIZE];
	char a[BUFSIZE];
	char d[BUFSIZE];
	int k = 0, t;
	Selection *sel;
	stringstream(s) >> c >> b >> c>>d;
	al->Switch(b);
	sel = se->find(b);
	strcpy(a, b);
	FILETIME ft;
	SYSTEMTIME stime;
	GetLocalTime(&stime);
	if (strcmp(c, "now") == 0){
		SystemTimeToFileTime(&stime, &ft);
	}
	else {
		if (strcmp(d, "") == 0){
			if (strcmp(c, "") == 0){
				if (k)
					delete sel;
				throw unknown_comm();
			}
			stime.wHour = 0;
			stime.wMinute = 0;
			stime.wSecond = 0;
			stime.wMilliseconds = 0;
		}
		else{
			int hour;
			int min;
			int sec;
			char cha1;
			stringstream(s) >> d >> d >> d >> hour >> cha1 >> min >> cha1 >> sec;
			stime.wHour = hour;
			stime.wMinute = min;
			stime.wSecond = sec;
		}
		int day;
		int month;
		int year;
		char cha;
		stringstream(s) >> d >> d >> day >> cha >> month >> cha >> year >> cha;
		stime.wDay = day;
		stime.wMonth = month;
		stime.wYear = year;
		SystemTimeToFileTime(&stime, &ft);
	}
	if (!sel){
		sel = new Selection("", b, 1);
		k = 1;
	}
	for (int i = 0; i < sel->getlength(); i++){
		cout << sel->getelem(i) << endl;
		strcpy(c, a);
		wchar_t wtext[BUFSIZE];
		strcpy(b, sel->getelem(i).c_str());
		if (k){
			int k1;
			for (k1 = strlen(b) - 1; k1>0; --i){
				if (b[k1] == '\\'){
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
		LPCTSTR fname = wtext;
		HANDLE hfile = CreateFile(fname, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (hfile == INVALID_HANDLE_VALUE){
			cout << b << " failed in setting time\n";
			continue;
		}
		if (!(SetFileTime(hfile, (LPFILETIME)NULL, (LPFILETIME)NULL, &ft))){
			cout << b << " failed in seting time\n";
			continue;
		}
		cout << "\tDone\n";
		CloseHandle(hfile);
	}
	if (k)
		delete sel;
}
