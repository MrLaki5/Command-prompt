#ifndef _cropper_compare_h
#define _cropper_compare_h

#include "cropper.h"

class Cropper_compare:public Cropper{
	Selections* sels;
public:
	FileSelectionPredicate* name_cropp(stringstream *s, string dir);
	FileSelectionPredicate* size_cropp(stringstream *s, string dir);
	FileSelectionPredicate* time_cropp(stringstream *s, string dir);
	Cropper_compare(Selections* s) :Cropper(), sels(s){}
	~Cropper_compare(){ sels = nullptr; }
};

#endif