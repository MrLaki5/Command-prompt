#ifndef _batch_command_builder_h
#define _batch_command_builder_h

#include "command.h"
#include "comm_batch.h"
#include "errors.h"
#include "commands.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
using namespace std;

class BatchCommandBuilder{
	static BatchCommandBuilder* s_instance;
	BatchCommandBuilder(){};
public:
	static BatchCommandBuilder* instance();
	command* build(string s, Commands_father *commands);
	BatchCommand* build_dat(string s, Commands_father *commands);
};



#endif