#include "commands.h"
#include "selection_composite.h"
#include "batch_command_builder.h"
#include "comm_batch.h"
#include "file.h"
#include "aliases.h"
#include "selection.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>



using namespace std;


char easytolower(char in){
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

void open(char* c, Aliases *al, Selections *se, Commands *comands){
	ifstream dat;
	string s;
	char a[MAX_PATH];
	char b[MAX_PATH];
	dat.open(c);
	if (dat.is_open()){
		getline(dat, s);
		if (s == "<aliases>"){
			getline(dat, s);
			while (s != "</aliases>"){
				stringstream(s) >> a >> b;
				al->add(a, b);
				getline(dat, s);
			}
			getline(dat, s);
			if (s == "<selections>"){
				getline(dat, s);
				while (s != "</selections>"){
					if (s == "<select>"){
						getline(dat, s);
						stringstream(s) >> a;
						getline(dat, s);
						stringstream(s) >> b;
						Selection *sel = new Selection(a, b);
						se->add1(sel);
						getline(dat, s);
						while (s != "</select>"){
							stringstream(s) >> a;
							sel->add(a);
							getline(dat, s);
						}
					}
					getline(dat, s);
				}
			}
			getline(dat, s);
			if (s == "<commands>"){
				getline(dat, s);
				while (s != "</commands>"){
					if (s == "<command>"){
						getline(dat, s);
						stringstream(s) >> a;
						BatchCommand *com = BatchCommandBuilder::instance()->build_dat(a, comands);
						getline(dat, s);
						while (s != "</command>"){
							stringstream(s) >> a;
							com->add_comm(comands->get(a));
							getline(dat, s);
						}
						comands->add_elem(com);
					}
					getline(dat, s);
				}
			}
		}
		dat.close();
	}
}

int main(){
	try{
		char a[MAX_PATH];
		char lok[MAX_PATH];
		Commands *cs = new Commands();
		command *c;
		Aliases *al;
		Selections *se;
		string pm;
		int n = 1;
		int perm = 0;
		al = new Aliases();
		se = new Selections();
		cur_dir(lok);


		cout << "Load save (0-N): ";
		getline(cin, pm);
		if (pm != "0"){
			open("save_cmd.txt", al, se,cs);
		}
		system("CLS");

		while (n){
			al->Update();
			cur_dir(a);
			cout << a << "> ";
			string s;
			getline(cin, s);
			stringstream(s) >> a;
			for (int i = strlen(a) - 1; i >= 0; i--){
				a[i] = easytolower(a[i]);
			}
			if (s == "quit"){
				string pom = "cd ";
				pom += (string)lok;
				command *cd = new Cd();
				cd->runC(pom, al, se, &n, &perm);
				delete  cd;
			}
			try{
				c = cs->get(a);
				c->runC(s, al, se, &n, &perm);
			}
			catch (unstable_dir obj){
				command *cd = new Cd();
				try{
					cd->runC("#cur", al, se, &n, &perm);
				}
				catch (throwable_condition *cond){
					throw unstable_dir();
				}
				delete  cd;
			}
			catch (throwable_condition *cond){
				cout << cond;
				delete cond;
			}
		}
		delete al;
		delete se;
		delete cs;
	}
	catch (bad_alloc obj){
		cout << "Couldnt allocate memory, press anything to close...";
		string obj_str;
		getline(cin, obj_str);
	}
	catch (unstable_dir obj){
		cout << "Unstable current position, press anything to close...";
		string obj_str;
		getline(cin, obj_str);
	}
}