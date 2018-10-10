#ifndef _custom_predicate_builder_h
#define _custom_predicate_builder_h


#include "selection_custom_predicate.h"
#include "selection_LogicalOp_and.h"
#include "selection_LogicalOp_or.h"
#include "selection_LogicalOp_xor.h"
#include "selection_LogicalOp_not.h"
#include "selection_predicate_name.h"
#include "selection_predicate_size.h"
#include "selection_predicate_time.h"
#include "cropper.h"
#include "errors.h"
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
using namespace std;

class CustomPredicateBuilder{
	static CustomPredicateBuilder* s_instance;
	CustomPredicateBuilder(){};
public:
	static CustomPredicateBuilder* instance();
	CustomPredicate* build(string s, Cropper *crop_obj);   //cropper je dodat da se sistem klasa iz selection-a mogao koristiti u compare
};



#endif