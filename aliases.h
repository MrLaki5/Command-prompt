#ifndef _aliases_h
#define _aliases_h

#include "file.h"
#include <iostream>
using namespace std;

class Aliases{
	struct Elem{
		char*  name;
		File *file;
		short i;
		Elem *next;
		Elem(char*a, char*b, int ii=0, Elem *f=nullptr){
			file = new File(b);
			name = new char[strlen(a) + 1];
			strcpy(name, a);
			i = ii;
			next = f;
		}
		~Elem(){
			delete file;
			delete[] name;
		}
	};
	Elem *first, *last;
public:
	Aliases();
	void Update();
	void Switch(char *c);
	void add(char *c, char *b);
	bool delete_(char *c);
	void rename(char *c, char *b);
	void delall();
	friend ostream& operator <<(ostream&os, Aliases *al);
	void write(ostream& os);
	~Aliases(){
		delall();
		delete first->next;
		delete first;
	}
};




#endif