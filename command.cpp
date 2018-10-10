#include "command.h"
#include "selection.h"
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


void father_dir(char *c){
	TCHAR Buffer[BUFSIZE];
	DWORD dwRet;
	if (!(dwRet = GetCurrentDirectory(BUFSIZE, Buffer)))
		throw new last_error_cond(GetLastError(),"GetCurrentDirectory");
	if (dwRet > BUFSIZE)
		throw new buffer_small();
	wcstombs(c, Buffer, wcslen(Buffer) + 1);
	int i;
	for (i = strlen(c) - 1; i>0; --i){
		if (c[i] == '\\'){
			c[i] = '\0';
			break;
		}
	}
	if (i == 0)
		c[0] = '\0';
	return;
}

void cur_dir(char *c){
	TCHAR Buffer[BUFSIZE];
	DWORD dwRet;
	if(!(dwRet = GetCurrentDirectory(BUFSIZE, Buffer)))
		throw new last_error_cond(GetLastError(), "GetCurrentDirectory");
	if (dwRet > BUFSIZE)
		throw new buffer_small();
	wcstombs(c, Buffer, wcslen(Buffer) + 1);
	return;
}



DWORD CALLBACK CopyProgressRoutine(LARGE_INTEGER TotalFileSize, LARGE_INTEGER TotalBytesTransferred, LARGE_INTEGER StreamSize, LARGE_INTEGER StreamBytesTransferred, DWORD dwStreamNumber, DWORD dwCallbackReason, HANDLE hSourceFile, HANDLE hDestinationFile, LPVOID lpData){
	char c[BUFSIZE];
	signed hyper brojV1;
	signed hyper brojV2;
	COORD wtfisthis;
	wtfisthis.X = 0;
	CONSOLE_SCREEN_BUFFER_INFO idk;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &idk);
	wtfisthis.Y = idk.dwCursorPosition.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), wtfisthis);
	brojV1 = TotalBytesTransferred.QuadPart;
	brojV2 = TotalFileSize.QuadPart;
	if (brojV2 != 0)
		cout << brojV1 * 100 / brojV2 << "%";
	return 0;
}
