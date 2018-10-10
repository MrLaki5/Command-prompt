#include "comm_batch.h"
#include "selection.h"
#include "aliases.h"
#include "dirent.h"
#include <windows.h> 
#include <iostream>
#include <string>
#include <sstream>





void BatchCommand::add_comm(command *c){
	if (!last)
		last = new Elem(c);
	else{
		last->next = new Elem(c);
		last = last->next;
	}
	if (!first)
		first = last;
}


BatchCommand::~BatchCommand(){
	while (first){
		last = first;
		first = first->next;
		delete last;
	}
	first = last = nullptr;
	delete name;
}

static stringstream* ss_st=nullptr;

void BatchCommand::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	stringstream ss;
	ss << s;
	//ss << '\0';
	string s_temp;
	try{
		stringstream *ss_temp = new stringstream();
		Elem *temp = first;
		ss_st = ss_temp;
		ss >> s_temp;
		//(*ss_temp) << "-" << " ";
		while (temp){
			(*ss_temp) << s_temp << " ";
			ss >> s_temp;
			if (strcmp(s_temp.c_str(),"|")==0){
				s_temp = (*ss_temp).str();
				delete ss_temp;
				if (!temp)
					throw new unknown_comm();
				temp->val->runC(s_temp, al, se, n, permision);
				temp = temp->next;
				ss_temp = new stringstream();
				(*ss_temp) << " - ";
				ss_st = ss_temp;
				ss >> s_temp;
			}
			//if (!temp)
			//return;
		}
	}
	catch (throwable_condition* obj){
		delete ss_st;
		throw obj;
	}
}

void BatchCommand::write(ostream& os) {
	os << name;
	Elem *temp=first;
	while (temp){
		os << "\n" << temp->val;
		temp = temp->next;
	}
	os << "\n";
}