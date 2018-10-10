#include "comm_dir.h"
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




void Dir::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	char c[BUFSIZE];
	stringstream(s) >> c >> c;
	if (c[0] == '\0'){
		cur_dir(c);
	}
	else
		al->Switch(c);
	sprintf(c, "%s/*.*", c);
	wchar_t wtext[BUFSIZE];
	mbstowcs(wtext, c, strlen(c) + 1);
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(wtext, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				wcout << "       <dir>       " << fd.cFileName << endl;
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	hFind = ::FindFirstFile(wtext, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				LPSYSTEMTIME lpSystemTime = new SYSTEMTIME();
				FileTimeToSystemTime(&(fd.ftLastWriteTime), lpSystemTime);
				cout << lpSystemTime->wDay << "-" << lpSystemTime->wMonth << "-" << lpSystemTime->wYear << "  ";
				cout << lpSystemTime->wHour << ":" << lpSystemTime->wMinute;
				wcout << "   " << fd.cFileName << "        ";
				cout << fd.nFileSizeLow << " bytes" << "        " << endl;
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return;
}