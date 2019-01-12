## Command prompt implementation
* password for higher user usage (command sudo): password
* for information about how to use commands type help in application
* all extra tasks have been implemented. (compare, new (complexed commands), saving complexed commands)…


### Help menu:
* cd path #path can be alias or path
* dir path #path can be alias or path, if left blank prints from current dir
* info #no arguments
* sudo #no arguments, gives admin permission to user
* makedir path name #if name left blank, path must be alias
* copy file destination #file can be selection or path, destination can be alias or path
* move file destination #file can be selection or path, destination can be alias or path
* setts name date time #name can be select, alias or path. Date DD.MM.YYYY. time HH:MM:SS, time can be blank.
* assign n name path #creates new alias assign r name new_path #changes path of existing alias. 
    assign d name #deletes alias
* delete d arg #arg can be selection or path or alias
    delete a #deletes all existing aliases and selections
    delete c arg #delets custom made command, arg is name of command
* quit #with no arg, quits program and saves to config
    quit q #quits program with no save
    quit s #quits program with option to save where user wants
    quit u #returns to user mode, if admin mode was on
* select n name dir comm_expr# name of select: name, dir is path, comm_expr more on "help expr"
    select d name #deletes selection
* compare name comm_expr #compare selects, name: name of new select, more about comm_expr on "help expr"
* new name_comm #creates new command. Later usage of command: "name_comm arg1 | arg2 | ... | argn |", where all argi are           arguments of basic commands

### Help expr:
* Expression in select:
	* AND(arg1,arg2)
	* OR(arg1,arg2)
	* XOR(arg1,arg2)
	* NOT(arg)
	* name="arg_string"
	* size="arg_int"
	* size="arg1_int-arg1_int"
	* time="DD.MM.YYYY."
	* time="DD.MM.YYYY.-HH:MM:SS"
	* time="spec_arg" #spec_arg is made from one number and one char (H-hour, D-day, M-Month, Y-year)
* Expression in compare:
        * AND(arg1,arg2)
	* OR(arg1,arg2)
	* XOR(arg1,arg2)
	* NOT(arg)
	* name="arg_string,name_of_select"
	* size="arg_int,name_of_select"
	* size="arg1_int-arg1_int,name_of_select"
	* time="DD.MM.YYYY.,name_of_select"
	* time="DD.MM.YYYY.-HH:MM:SS,name_of_select"
	* time="spec_arg,name_of_select" #spec_arg is made from one number and one char (H-hour, D-day, M-Month, Y-year)
* All args in AND,OR,XOR,NOT are one of name,size,time expressions.

