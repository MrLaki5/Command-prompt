#include "selection_LogicalOp_and.h"


void And::getarg(FileSelectionPredicate* obj){
	if (!(list[0]))
		list[0] = obj;
	else
		if (!(list[1]))
			list[1] = obj;
}

Selection* And::start(){
	Selection *obj1 = list[0]->start();
	Selection *obj2 = list[1]->start();
	string dir=obj1->getpath()->getFullName();
	Selection *fin_sel = new Selection("", (char*)dir.c_str());
	for (int i = 0; i < obj1->getlength(); i++){
		if (obj2->check_if_exsist((char*)obj1->getelemname(i).c_str()))
			fin_sel->add((char*)obj1->getelemname(i).c_str());
	}
	delete obj1;
	delete obj2;
	return fin_sel;
}
