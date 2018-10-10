#include "commands.h"
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

Commands::Commands(){
	first = last = new Elem(new Cd());
	last->next = new Elem(new Makedir());
	last = last->next;
	last->next = new Elem(new Dir());
	last = last->next;
	last->next = new Elem(new Assign());
	last = last->next;
	last->next = new Elem(new Select());
	last = last->next;
	last->next = new Elem(new Move());
	last = last->next;
	last->next = new Elem(new Copy());
	last = last->next;
	last->next = new Elem(new Delete(this));
	last = last->next;
	last->next = new Elem(new Quit(this));
	last = last->next;
	last->next = new Elem(new Sudo());
	last = last->next;
	last->next = new Elem(new Info());
	last = last->next;
	last->next = new Elem(new Setts());
	last = last->next;
	last->next = new Elem(new Help());
	last = last->next;
	last->next = new Elem(new New(this));
	last = last->next;
	last->next = new Elem(new Compare());
	last = last->next;
}

Commands::~Commands(){
	Elem *temp = first;
	while (temp){
		last = temp;
		temp = temp->next;
		delete last;
	}
	first = last = nullptr;
}

command* Commands::get(char *c){
	Elem *temp = first;
	while (temp){
		if (temp->file->checkC(c))
			return temp->file;
		temp = temp->next;
	}
	throw new unknown_comm();
}

void Commands::add_elem(command *obj){
	last->next = new Elem(obj);
	last = last->next;
}

void Commands::remove(string s){
	Elem *temp = first;
	Elem *prev = nullptr;
	while (temp){
		if ((temp->file->checkC((char*)s.c_str())) && temp->file->deletable()){
			prev->next = temp->next;
			delete temp;
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	throw new unknown_comm();
}


void Commands::write(ostream& os){
	Elem* temp = first;
	while (temp){
		if (temp->file->deletable()){
			os << "<command>" << endl;
			os << temp->file;
			os << "</command>"<<endl;
		}
		temp = temp->next;
	}
}