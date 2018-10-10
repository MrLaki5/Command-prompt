#ifndef _commands_father_h
#define _commands_father_h

#include "command.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>


class Commands_father{
protected:
	virtual void write(ostream& os)=0;
public:
	virtual ~Commands_father(){};
	virtual command* get(char* c)=0;
	virtual void add_elem(command *obj)=0;
	virtual void remove(string s) = 0;
	friend ostream& operator <<(ostream& os, Commands_father* c){
		c->write(os);
		return os;
	}
};


#endif