#include "selection_predicate_size.h"

Selection* FileSizePredicate::start(){
	Selection* cur_sel_p = new Selection("", dir);
	char a[MAX_PATH];
	char *name = "*.*";
	sprintf(a, "%s\\%s", dir, name);
	wchar_t wtext[MAX_PATH];
	mbstowcs(wtext, a, strlen(a) + 1);
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(wtext, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			wcstombs(a, fd.cFileName, sizeof(a));
			if (!(((a[0]) == '.') && ((a[1] == '\0') || ((a[2] == '\0') && (a[1] == '.'))))){
				DWORD file_size = fd.nFileSizeLow;
				if (((high == 0) && (low == file_size)) || (low <= file_size) && (high >= file_size))
					cur_sel_p->add(a);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return cur_sel_p;
}