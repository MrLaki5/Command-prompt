#include "selection_custom_predicate.h"

bool CustomPredicate::check_redy(){
	if (list[0] != nullptr)
		return list[0]->check_redy();
	return false;
}


Selection* CustomPredicate::start(){
	if (!(check_redy()))
		throw new unknown_predicate();
	Selection *p_sel=list[0]->start();
	p_sel->setname((char*)name.c_str());
	return p_sel;
}
