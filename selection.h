#ifndef _selection_h
#define _selection_h

#include "file.h"
#include <iostream>
#include <string>
using namespace std;

class Selection{
	struct Elem{
		File *file;
		Elem *next;
		Elem(char*b, Elem *f = nullptr){
			file = new File(b);
			next = f;
		}
		~Elem(){
			delete file;
		}
	};
	Elem *first, *last;
	char *name;
	File *path;
	int length=0;
public:
	Selection(char* c, char *b, int i=0);
	void add(char *c);
	void delete_();
	int getlength(){ return length; }
	File* getpath(){ return path; }
	string getelem(int i);
	string getelemname(int ii);
	void setname(char *s){
		delete[] name;
		name = new char[strlen(s) + 1];
		strcpy(name, s);
	}
	bool check_if_exsist(char* a);
	~Selection(){
		delete_();
		delete[] name;
	}
	char* getname(){
		return name;
	}
	void write(ostream& os);
	void putpath(char* p);
};




#endif