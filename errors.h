#ifndef _errors_h
#define _errors_h

#include <iostream>
#include <string>
using namespace std;

class throwable_condition{
	virtual void write(ostream& os) = 0;
public:
	friend ostream& operator <<(ostream& os, throwable_condition* throw_c){
		throw_c->write(os);
		return os;
	}
	virtual ~throwable_condition(){};
};

class unknown_comm : public throwable_condition{
	void write(ostream& os){
		os << "Unknown command, type \"help\" for more info\n";
	}
};

class buffer_small : public throwable_condition{
	void write(ostream& os){
		os << "Buffer to small\n";
	}
};

class last_error_cond : public throwable_condition{
	int err_num;
	string name;
	void write(ostream& os){
		os <<"Function "<<name<< " sent error, number of \"GetLastError()\" function: " << err_num;
	}
public:
	last_error_cond(int num, string s) :err_num(num), name(s){}
};

class perm_denied : public throwable_condition{
	void write(ostream& os){
		os << "Permission denied\n";
	}
};

class creat_fail : public throwable_condition{
	void write(ostream& os){
		errno_t _set_errno(0);
		os << "Failed in creaton\n";
	}
};

class unknown_predicate : public throwable_condition{
	void write(ostream& os){
		os << "Wrong predicate condition, type \"help expr\" for more info\n";
	}
};

class multy_selection : public throwable_condition{
	void write(ostream& os){
		os << "Selection doesn\'t have one path\n";
	}
};

class unknown_selection : public throwable_condition{
	void write(ostream& os){
		os << "Selection doesn\'t exists\n";
	}
};

class low_commands : public throwable_condition{
	void write(ostream& os){
		os << "Not enough commands\n";
	}
};

class unstable_dir{};

#endif