#include "selection_LogicalOp_not.h"
#include "selection_predicate_name.h"


void Not::getarg(FileSelectionPredicate* obj){
	if (!(list[0]))
		list[0] = obj;
}

Selection* Not::start(){
	Selection *obj1 = list[0]->start();
	string dir = obj1->getpath()->getFullName();
	Selection *obj2 = FileNamePredicate("*.*", (char*)dir.c_str()).start();
	Selection *fin_sel = new Selection("", (char*)dir.c_str());
	for (int i = 0; i < obj2->getlength(); i++){
		if (!(obj1->check_if_exsist((char*)obj2->getelemname(i).c_str())))
			fin_sel->add((char*)obj2->getelemname(i).c_str());
	}
	delete obj1;
	delete obj2;
	return fin_sel;
}
