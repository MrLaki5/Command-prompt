#include "selection_LogicalOp_or.h"


void Or::getarg(FileSelectionPredicate* obj){
	if (!(list[0]))
		list[0] = obj;
	else
	if (!(list[1]))
		list[1] = obj;
}

Selection* Or::start(){
	Selection *obj1 = list[0]->start();
	Selection *obj2 = list[1]->start();
	string dir = obj1->getpath()->getFullName();
	Selection *fin_sel = new Selection("", (char*)dir.c_str());
	for (int i = 0; i < obj1->getlength(); i++){
		if (!(fin_sel->check_if_exsist((char*)obj1->getelemname(i).c_str())))
			fin_sel->add((char*)obj1->getelemname(i).c_str());
	}
	for (int i = 0; i < obj2->getlength(); i++){
		if (!(fin_sel->check_if_exsist((char*)obj2->getelemname(i).c_str())))
			fin_sel->add((char*)obj2->getelemname(i).c_str());
	}
	delete obj1;
	delete obj2;
	return fin_sel;
}
