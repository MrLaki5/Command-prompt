#ifndef _cropper_h
#define _cropper_h

#include "selection_predicate.h"

class Cropper{
public:
	virtual FileSelectionPredicate* name_cropp(stringstream *s, string dir);
	virtual FileSelectionPredicate* size_cropp(stringstream *s, string dir);
	virtual FileSelectionPredicate* time_cropp(stringstream *s, string dir);
	virtual ~Cropper(){}
};



#endif