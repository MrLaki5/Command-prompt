#include"selections.h"
#include <iostream>
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>


void Selections::add(char* c, char *b, char *d){
	if (last){
		last->next = new Elem();
		last = last->next;
	}
	else
		last = new Elem();
	last->file = new Selection(c, b);
	char a[MAX_PATH];
	sprintf(a, "%s\\%s", b, d);
	wchar_t wtext[MAX_PATH];
	mbstowcs(wtext, a, strlen(a) + 1);
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(wtext, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			wcstombs(a, fd.cFileName, sizeof(a));
			if (!(((a[0]) == '.') && ((a[1] == '\0') || ((a[2] == '\0') && (a[1] == '.')))))
				last->file->add(a);
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	if (!first)
		first = last;
}



void Selections::add1(Selection *sel){
	if (last){
		last->next = new Elem();
		last = last->next;
	}
	else
		last = new Elem();
	last->file = sel;
	char a[MAX_PATH];
	if (!first)
		first = last;
}



void Selections::deleteall(){
	while (first){
		last = first;
		first = first->next;
		delete last;
	}
	first = last = nullptr;
}


bool Selections::delspec(char *c){
	Elem *temp = first, *father = nullptr;
	while (temp){
		if ((strcmp(c, temp->file->getname()) == 0)){
			if (temp == last)
				last = father;
			if (first == temp){
				first = first->next;
			}
			else
				father->next = temp->next;
			delete temp;
			return true;
		}
		father = father->next;
		temp = temp->next;
	}
	return false;
}


void Selections::rename(char* c, char *b, char *d){
	if (delspec(c))
		add(c, b, d);
}

Selection* Selections::find(char*c){
	Elem *temp = first;
	while (temp){
		if (strcmp(c, temp->file->getname()) == 0){
			return temp->file;
		}
		temp = temp->next;
	}
	return nullptr;
}

ostream& operator <<(ostream&os, Selections *se){
	se->write(os);
	return os;
}

void Selections::write(ostream& os){
	Elem *temp = first;
	while (temp){
		os << "<select>" << endl;
		temp->file->write(os);
		os << "</select>" << endl;
		temp = temp->next;
	}
}