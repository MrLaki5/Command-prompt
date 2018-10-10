#ifndef _selections_h
#define _selections_h

#include "selection.h"

class Selections {
	struct Elem{
		Selection *file;
		Elem *next;
		Elem(){
			file = nullptr;
			next = nullptr;
		}
		~Elem(){
			delete file;
		}
	};
	Elem *first, *last;
public:
	Selections(){ first = last = nullptr; }
	void add(char* c, char *b, char *d); //dodaje novi select, pri ucitavanju iz komande
	void add1(Selection *sel);		//dodaje novi select, ali pri ucitavanju iz dat
	void deleteall();				//brise sve
	bool delspec(char* c);		//brise select odredjenog imena
	void rename(char* c, char *b, char *d);					//menja sadrzaj
	Selection* find(char *c);					//pronalazi odredjenu selekciju
	~Selections(){ deleteall(); }
	friend ostream& operator <<(ostream&os, Selections *se);
	void write(ostream& os);
};

#endif