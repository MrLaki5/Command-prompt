#ifndef _comm_batch_h
#define _comm_batch_h

#include "aliases.h"
#include "selection.h"
#include "command.h" 
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>




class BatchCommand : public command{
	struct Elem {
		command* val;
		Elem* next;
		Elem(command *v, Elem *n = nullptr):val(v),next(n){}
	};
	char* name;
	Elem* first=nullptr;
	Elem* last=nullptr;
	void write(ostream& os);
public:
	bool checkC(char* c) override{
		return (strcmp(c, name) == 0);
	};
	void runC(string s, Aliases *al, Selections *se, int *n, int *permision) override;
	~BatchCommand();
	void add_comm(command *c);
	bool deletable(){ return true; }
	friend class BatchCommandBuilder;
protected:
	BatchCommand(char* n){
		name = new char[strlen(n) + 1];
		strcpy(name, n);
	}
};


#endif