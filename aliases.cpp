#include"aliases.h"
#include "errors.h"
#include <iostream>
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>

using namespace std;

#define BUFSIZE MAX_PATH

void father_dir3(char *c){
	TCHAR Buffer[BUFSIZE];
	DWORD dwRet;
	if (!(dwRet = GetCurrentDirectory(BUFSIZE, Buffer)))
		throw new last_error_cond(GetLastError(),"GetCurrentDirectory");
	if (dwRet > BUFSIZE)
		throw new buffer_small();
	wcstombs(c, Buffer, wcslen(Buffer) + 1);
	int i;
	for (i = strlen(c) - 1; i>0; --i){
		if (c[i] == '\\'){
			c[i] = '\0';
			break;
		}
	}
	if ((i == 0))
		c[0] = '\0';
	return;
}

void dir3(char *c){
	TCHAR Buffer[BUFSIZE];
	DWORD dwRet;
	if (!(dwRet = GetCurrentDirectory(BUFSIZE, Buffer)))
		throw new last_error_cond(GetLastError(), "GetCurrentDirectory");
	if (dwRet > BUFSIZE)
		throw new buffer_small();
	wcstombs(c, Buffer, wcslen(Buffer) + 1);
	return;
}

void pathcheck(char* c){
	TCHAR Buffer[BUFSIZE];
	DWORD dwRet;
	wchar_t wtext[BUFSIZE];
	mbstowcs(wtext, c, strlen(c) + 1);
	LPWSTR ptr = wtext;
	dwRet = GetCurrentDirectory(BUFSIZE, Buffer);
	if (dwRet == 0)
		throw unstable_dir();
	if (dwRet > BUFSIZE)
		throw unstable_dir();
	if (!SetCurrentDirectory(wtext)){
		printf("	Path is not valid\n");
		return;
	}
	if (!SetCurrentDirectory(Buffer))
		throw unstable_dir();
	return;
}



Aliases::Aliases(){
	char c[BUFSIZE];
	father_dir3(c);
	last = new Elem("#par", c, 1);
	dir3(c);
	first = new Elem("#cur", c, 1, last);
}

void Aliases::Update(){		//Namesta cur i par u svakoj iteraciji
	Elem *temp = first;
	char c[BUFSIZE];
	while (temp){
		if (temp->i == 1){
			if (strcmp(temp->name,"#par")==0){
				father_dir3(c);
				temp->file->chpath(c);
			}
			if (strcmp(temp->name, "#cur") == 0){
				dir3(c);
				temp->file->chpath(c);
			}
		}
		temp = temp->next;
	}
}


void Aliases::Switch(char *c){		//Funkcija za zamenu pri ulazu ukomande, zamena imena i patha
	Elem *temp = first;
	while (temp){
		if (strcmp(c, temp->name) == 0){
			strcpy(c, temp->file->getFullName().c_str());
			return;
		}
		temp = temp->next;
	}
	return;
}

void Aliases::add(char *c, char *b){		//Dodaj novi alias u grupu aliasa
	pathcheck(b);
	last->next = new Elem(c, b);
	last = last->next;
}

bool Aliases::delete_(char *c){			//Brise odredjen clan 
	Elem *temp = first->next->next, *father = first->next;
	while (temp){
		if ((strcmp(c, temp->name) == 0) && (temp->i == 0)){
			if (temp == last)
				last = father;
			father->next = temp->next;
			delete temp;
			return true;
		}
		father = father->next;
		temp = temp->next;
	}
	return false;
}


void Aliases::rename(char *c, char *b){		//Promeni path odredjenom aliasu
	if (delete_(c))
		add(c, b);
}

void Aliases::delall(){					//brise sve osim prva dva
	Elem *temp = first->next->next;
	while (temp){
		last = temp;
		temp = temp->next;
		delete last;
	}
	last = first->next;
	last->next = nullptr;
	return;
}

ostream& operator <<(ostream&os, Aliases *al){
	al->write(os);
	return os;
}

void Aliases::write(ostream& os){
	Elem *temp = first->next->next;
	while (temp){
		os << temp->name << " " << temp->file->getFullName() << endl;
		temp = temp->next;
	}
}