#include "cropper.h"
#include <sstream>
#include "selection_predicate_name.h"
#include "selection_predicate_size.h"
#include "selection_predicate_time.h"

FileSelectionPredicate* Cropper::name_cropp(stringstream *s, string dir){
	char c;
	char word[MAX_PATH] = "";
	int i = 0;
	(*s) >> c;
	if (c == '\"'){
		(*s) >> c;
		while ((c != '\"') && (c)){
			word[i++] = c;
			(*s) >> c;
		}
		if (!c)
			throw new unknown_predicate();
		word[i] = '\0';
		return new FileNamePredicate(word, (char*)dir.c_str());
	}
	throw new unknown_predicate();
}

FileSelectionPredicate* Cropper::size_cropp(stringstream *s, string dir){
	char c;
	int i = 0, j = 0;
	(*s) >> c;
	if (c == '\"'){
		(*s) >> i;
		(*s) >> c;
		if (c == '\"'){
			return new FileSizePredicate((char*)dir.c_str(), i);
		}
		if (c == '-'){
			(*s) >> j;
			(*s) >> c;
			if (c == '\"'){
				return new FileSizePredicate((char*)dir.c_str(), i, j);
			}
			throw new unknown_predicate();
		}
		throw new unknown_predicate();
	}
	throw new unknown_predicate();
}

FileSelectionPredicate* Cropper::time_cropp(stringstream *s, string dir){
	char c;
	SYSTEMTIME time1, time2;
	FILETIME ftime1, ftime2;
	GetLocalTime(&time1);
	int i = 0, j = 0;
	(*s) >> c;
	if (c == '\"'){
		(*s) >> i;
		(*s) >> c;
		switch (c){
		case'.':
			time1.wDay = i;
			(*s) >> i;
			time1.wMonth = i;
			(*s) >> c;
			(*s) >> i;
			time1.wYear = i;
			(*s) >> c;
			(*s) >> c;
			switch (c){
			case'-':
				(*s) >> i;
				time1.wHour = i;
				(*s) >> c;
				(*s) >> i;
				time1.wMinute = i;
				(*s) >> c;
				(*s) >> i;
				time1.wSecond = i;
				(*s) >> c;
				if (c == '\"'){
					SystemTimeToFileTime(&time1, &ftime1);
					return new FileTimePredicate((char*)dir.c_str(), ftime1);
				}
				else
					throw new unknown_predicate();
				break;
			case'\"':
				time2 = time1;
				time1.wHour = 0;
				time1.wMinute = 0;
				time1.wSecond = 0;
				time2.wHour = 23;
				time2.wMinute = 59;
				time2.wSecond = 59;
				SystemTimeToFileTime(&time1, &ftime1);
				SystemTimeToFileTime(&time2, &ftime2);
				return new FileTimePredicate((char*)dir.c_str(), ftime1, ftime2);
			default:
				throw new unknown_predicate();
			}
			break;
		case'Y':
			time2 = time1;
			time1.wYear -= i;
			SystemTimeToFileTime(&time1, &ftime1);
			SystemTimeToFileTime(&time2, &ftime2);
			(*s) >> c;
			if (c == '\"')
				return new FileTimePredicate((char*)dir.c_str(), ftime1, ftime2);
			break;
		case'M':
			time2 = time1;
			while (i){
				time1.wMonth--;
				if (time1.wMonth == 0){
					time1.wYear--;
					time1.wMonth = 12;
				}
				i--;
			}
			SystemTimeToFileTime(&time1, &ftime1);
			SystemTimeToFileTime(&time2, &ftime2);
			(*s) >> c;
			if (c == '\"')
				return new FileTimePredicate((char*)dir.c_str(), ftime1, ftime2);
			break;
		case'D':
			time2 = time1;
			while (i){
				time1.wDay--;
				if (time1.wDay == 0){
					if ((time1.wMonth == 2)){
						if ((time1.wYear % 4) == 0)
							time1.wDay = 29;
						else
							time1.wDay = 28;
					}
					else{
						if ((time1.wMonth >= 7)){
							if (time1.wMonth % 2)
								time1.wDay = 31;
							else
								time1.wDay = 30;
						}
						else{
							if (time1.wMonth % 2)
								time1.wDay = 30;
							else
								time1.wDay = 31;
						}
					}
					time1.wMonth--;
					if (time1.wMonth == 0){
						time1.wYear--;
						time1.wMonth = 12;
					}
				}
				i--;
			}
			SystemTimeToFileTime(&time1, &ftime1);
			SystemTimeToFileTime(&time2, &ftime2);
			(*s) >> c;
			if (c == '\"')
				return new FileTimePredicate((char*)dir.c_str(), ftime1, ftime2);
			break;
		case'H':
			time2 = time1;
			while (i){
				time1.wHour--;
				if (time1.wHour == 0){
					time1.wDay--;
					time1.wHour = 23;
				}
				i--;
			}
			SystemTimeToFileTime(&time1, &ftime1);
			SystemTimeToFileTime(&time2, &ftime2);
			(*s) >> c;
			if (c == '\"')
				return new FileTimePredicate((char*)dir.c_str(), ftime1, ftime2);
			break;
		default:
			throw new unknown_predicate();
		}
	}
	throw new unknown_predicate();
}