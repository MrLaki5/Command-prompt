#include "selection_predicate_time.h"


Selection* FileTimePredicate::start(){
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
				FILETIME time_f;
				//GetFileTime(hFind, (LPFILETIME)NULL, (LPFILETIME)NULL, &time_f);
				time_f = fd.ftLastWriteTime;
				SYSTEMTIME aaa;
				FileTimeToSystemTime(&time_f, &aaa);
				aaa.wMilliseconds = 0;
				SystemTimeToFileTime(&aaa, &time_f);
				FileTimeToSystemTime(&t1, &aaa);
				aaa.wMilliseconds = 0;
				SystemTimeToFileTime(&aaa, &t1);
				FileTimeToSystemTime(&t2, &aaa);
				aaa.wMilliseconds = 0;
				SystemTimeToFileTime(&aaa, &t2);
				if (offset){
					if ((CompareFileTime(&t1, &time_f) == -1) && (CompareFileTime(&time_f, &t2) == -1))
						cur_sel_p->add(a);
				}
				else
					if (CompareFileTime(&t1, &time_f) == 0)
						cur_sel_p->add(a);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return cur_sel_p;
}