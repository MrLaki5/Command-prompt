#ifndef _command_h
#define _command_h

#include "aliases.h"
#include "selection.h"
#include "selections.h"
#include "errors.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
using namespace std;

#define BUFSIZE MAX_PATH


class command{
private:
	virtual void write(ostream& os) = 0;
public:
	virtual bool checkC(char* c) = 0;
	virtual void runC(string s, Aliases *al, Selections *se, int *n, int *permision) = 0;
	virtual ~command(){}
	virtual bool deletable(){ return false; }
	friend ostream& operator <<(ostream& os, command* c){
		c->write(os);
		return os;
	}
};



typedef DWORD(WINAPI *LPPROGRESS_ROUTINE)(
	_In_     LARGE_INTEGER TotalFileSize,
	_In_     LARGE_INTEGER TotalBytesTransferred,
	_In_     LARGE_INTEGER StreamSize,
	_In_     LARGE_INTEGER StreamBytesTransferred,
	_In_     DWORD         dwStreamNumber,
	_In_     DWORD         dwCallbackReason,
	_In_     HANDLE        hSourceFile,
	_In_     HANDLE        hDestinationFile,
	_In_opt_ LPVOID        lpData
	);

DWORD CALLBACK CopyProgressRoutine(LARGE_INTEGER TotalFileSize, LARGE_INTEGER TotalBytesTransferred, LARGE_INTEGER StreamSize, LARGE_INTEGER StreamBytesTransferred, DWORD dwStreamNumber, DWORD dwCallbackReason, HANDLE hSourceFile, HANDLE hDestinationFile, LPVOID lpData);
void cur_dir(char *c);
void father_dir(char *c);

#endif