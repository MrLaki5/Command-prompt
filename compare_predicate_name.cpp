#include "compare_predicate_name.h"


Selection* FileNamePredicateCompare::start(){
	string sel_dir = select->getpath()->getFullName();
	if (sel_dir == "-")
		throw new multy_selection();
	Selection* cur_sel_p = new Selection("", (char*)sel_dir.c_str());
	char a[MAX_PATH];
	//char* tempch = "*.*";
	sprintf(a, "%s\\%s", (char*)sel_dir.c_str(), name);
	wchar_t wtext[MAX_PATH];
	mbstowcs(wtext, a, strlen(a) + 1);
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(wtext, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			wcstombs(a, fd.cFileName, sizeof(a));
			if ((!(((a[0]) == '.') && ((a[1] == '\0') || ((a[2] == '\0') && (a[1] == '.'))))) && (select->check_if_exsist(a)))
				cur_sel_p->add(a);
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return cur_sel_p;
}
