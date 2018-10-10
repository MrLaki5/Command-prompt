Command prompt implementation


1. password for higher user usage (command sudo): password
2. for information about how to use commands type help in application
3. all extra tasks have been implemented. (compare, new (complexed commands), saving complexed commands)…


	Help menu:
		1. cd path #path can be alias or path
		2. dir path #path can be alias or path, if left blank prints from current dir
		3. info #no arguments
		4. sudo #no arguments, gives admin permission to user
		5. makedir path name #if name left blank, path must be alias
		6. copy file destination #file can be selection or path, destination can be alias or path
		7. move file destination #file can be selection or path, destination can be alias or path
		8. setts name date time #name can be select, alias or path. Date DD.MM.YYYY. time HH:MM:SS, time can be blank.
		9. assign n name path #creates new alias assign r name new_path #changes path of existing alias. 
		   assign d name #deletes alias
		10. delete d arg #arg can be selection or path or alias
		    delete a #deletes all existing aliases and selections
		    delete c arg #delets custom made command, arg is name of command
		11. quit #with no arg, quits program and saves to config
		    quit q #quits program with no save
		    quit s #quits program with option to save where user wants
		    quit u #returns to user mode, if admin mode was on
		12. select n name dir comm_expr# name of select: name, dir is path, comm_expr more on "help expr"
		    select d name #deletes selection
		13. compare name comm_expr #compare selects, name: name of new select, more about comm_expr on "help expr"
		14. new name_comm #creates new command. Later usage of command: "name_comm arg1 | arg2 | ... | argn |", where all argi are arguments of basic commands



	Help expr:
		Expression in select:
		   1. AND(arg1,arg2)
		   2. OR(arg1,arg2)
		   3. XOR(arg1,arg2)
		   4. NOT(arg)
		   5. name="arg_string"
		   6. size="arg_int"
		   6. size="arg1_int-arg1_int"
		   7. time="DD.MM.YYYY."
		   8. time="DD.MM.YYYY.-HH:MM:SS"
		   9. time="spec_arg" #spec_arg is made from one number and one char (H-hour, D-day, M-Month, Y-year)
		Expression in compare:
	       	   1. AND(arg1,arg2)
		   2. OR(arg1,arg2)
		   3. XOR(arg1,arg2)
		   4. NOT(arg)
		   5. name="arg_string,name_of_select"
		   6. size="arg_int,name_of_select"
		   6. size="arg1_int-arg1_int,name_of_select"
		   7. time="DD.MM.YYYY.,name_of_select"
		   8. time="DD.MM.YYYY.-HH:MM:SS,name_of_select"
		   9. time="spec_arg,name_of_select" #spec_arg is made from one number and one char (H-hour, D-day, M-Month, Y-year)

		All args in AND,OR,XOR,NOT are one of name,size,time expressions.

