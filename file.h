#ifndef _file_h
#define _file_h


#include <iostream>
#include <string>
using namespace std;

class File{
	char *path;
public:
	string getName();
	string getFullName();
	bool isDir();
	File(char *c){
		path = new char[strlen(c)+1];
		strcpy(path, c);
	}
	~File(){
		delete[] path;
	}
	void chpath(char* c);
};





#endif