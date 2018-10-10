#include "batch_command_builder.h"



BatchCommandBuilder *BatchCommandBuilder::s_instance = nullptr;

BatchCommandBuilder* BatchCommandBuilder::instance(){
	if (!(s_instance))
		s_instance = new BatchCommandBuilder();
	return s_instance;
}

BatchCommand *comm_st=nullptr;

command* BatchCommandBuilder::build(string s, Commands_father *commands){
	BatchCommand *comm = new BatchCommand((char*)s.c_str());
	comm_st = comm;
	try{
		int i = 0, n = 1;
		string s_temp;
		while (n){
			cout << "Add (0-NO)? ";
			getline(cin, s_temp);
			if (s_temp != "0"){
				cout << "Comm name: ";
				getline(cin, s_temp);
				comm->add_comm(commands->get((char*)s_temp.c_str()));
				i++;
			}
			else
				n = 0;
		}
		if (i < 2){
			throw new low_commands();
		}
		return comm;
	}
	catch (throwable_condition* obj){
		delete comm_st;
		throw obj;
	}
}

BatchCommand* BatchCommandBuilder::build_dat(string s, Commands_father *commands){
	BatchCommand *comm = new BatchCommand((char*)s.c_str());
	return comm;
}