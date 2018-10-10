#include "file.h"
#include <iostream>
#include <sys/stat.h>

using namespace std;

string File::getName(){
	string str(path);
	unsigned found = str.find_last_of("/\\");
	if ((str.substr(found + 1)) != "")
		return str.substr(found + 1);
	else
		return str;
}


string File::getFullName(){
	string str(path);
	return str;
}

bool File::isDir(){
	struct stat s;
	if (stat(path, &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
			return true;
		else if (s.st_mode & S_IFREG)
			return false;
		else
			return false;
	}
	else
		cout << "Check was not successful" << endl;
		return false;
	/*
	wchar_t wtext[MAX_PATH];
	mbstowcs(wtext, path, strlen(path) + 1);
	LPWSTR ptr = wtext;
	DWORD nDword = (DWORD)path;
	return (GetFileAttributes(wtext)==16);
	*/
}


void File::chpath(char* c){
	delete[] path;
	path = new char[strlen(c) + 1];
	strcpy(path, c);
}