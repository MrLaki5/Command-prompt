#include"selection.h"
#include <iostream>
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>



Selection::Selection(char* c, char *b, int i){	//ako se stavi i=1 onda se pravi select sa samo jednim fajlom koji je dat kao drugi operand, prvi je ime, stvoreno radi lakseg stvaranja privremenih objekata
	name = new char[strlen(c) + 1];
	strcpy(name, c);
	path = new File(b);
	if (i){
		first = last = new Elem(c);
		length++;
	}
	else
		first = last = nullptr;
}

void Selection::add(char *c){
	if (last){
		last->next = new Elem(c);
		last = last->next;
	}
	else
		last = new Elem(c);
	if (!first)
		first = last;
	length++;
}

void Selection::delete_(){
	while (first){
		last = first;
		first = first->next;
		delete last;
	}
	first = last = nullptr;
	delete path;
	length = 0;
}

string Selection::getelem(int ii){
	char a[MAX_PATH];
	Elem *temp = first;
	while (ii){
		temp = temp->next;
		ii--;
	}
	sprintf(a, "%s\\%s", path->getFullName().c_str(), temp->file->getFullName().c_str());
	return a;
}

string Selection::getelemname(int ii){
	char a[MAX_PATH];
	Elem *temp = first;
	while (ii){
		temp = temp->next;
		ii--;
	}
	sprintf(a, "%s", temp->file->getFullName().c_str());
	return a;
}

void Selection::write(ostream& os){
	Elem *temp=first;
	os << name << endl;
	os << path->getFullName() << endl;
	while (temp){
		os << temp->file->getFullName() << endl;
		temp = temp->next;
	}
}

bool Selection::check_if_exsist(char* a){
	Elem *temp = first;
	while (temp){
		if (strcmp(a, temp->file->getFullName().c_str()) == 0)
			return true;
		temp = temp->next;
	}
	return false;
}

void Selection::putpath(char* p){
	delete path;
	path = new File(p);
}
