#ifndef _commands_h
#define _commands_h

#include "commands_father.h"
#include "aliases.h"
#include "selection.h"
#include "command.h"
#include "comm_cd.h"
#include "comm_makedir.h"
#include "comm_dir.h"
#include "comm_assign.h"
#include "comm_select.h"
#include "comm_move.h"
#include "comm_copy.h"
#include "comm_delete.h"
#include "comm_quit.h"
#include "comm_sudo.h"
#include "comm_info.h"
#include "comm_setts.h"
#include "comm_help.h"
#include "comm_compare.h"
#include "comm_new.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>


class Commands:public Commands_father{
	struct Elem{
		command *file;
		Elem *next;
		Elem(command *f){
			file = f;
			next = nullptr;
		}
		~Elem(){
			delete file;
		}
	};
	Elem *first, *last;
	void write(ostream& os);
public:
	Commands();
	~Commands();
	command* get(char* c);
	void add_elem(command *obj);
	void remove(string s);
};


#endif