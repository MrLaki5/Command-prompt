#include "comm_cd.h"
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


void Cd::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	TCHAR Buffer[BUFSIZE];
	DWORD dwRet;
	char c[BUFSIZE];
	stringstream(s) >> c >> c;
	wchar_t wtext[BUFSIZE];
	al->Switch(c);
	mbstowcs(wtext, c, strlen(c) + 1);
	LPWSTR ptr = wtext;

	if(!(dwRet = GetCurrentDirectory(BUFSIZE, Buffer)))
		throw new last_error_cond(GetLastError(), "GetCurrentDirectory");
	if (dwRet > BUFSIZE)
		throw new buffer_small();
	if (!SetCurrentDirectory(wtext))
		throw new last_error_cond(GetLastError(), "SetCurrentDirectory");
	_tprintf(TEXT("		Set current directory to %s\n"), wtext);
	return;
}