#include "comm_info.h"
#include "selection.h"
#include <windows.h> 
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <winioctl.h>


void DisplayVolumePaths(PWCHAR VolumeName){
	DWORD  CharCount = MAX_PATH + 1;
	PWCHAR Names = NULL;
	PWCHAR NameIdx = NULL;
	BOOL   Success = FALSE;
	for (;;){
		Names = (PWCHAR) new BYTE[CharCount * sizeof(WCHAR)];	//  Allocate a buffer to hold the paths.
		if (!Names){		//  If memory can't be allocated, return.
			throw bad_alloc();
		}
		Success = GetVolumePathNamesForVolumeNameW(VolumeName, Names, CharCount, &CharCount);  //  Obtain all of the paths  for this volume.
		if (Success){
			break;
		}
		if (GetLastError() != ERROR_MORE_DATA){
			break;
		}
		delete[] Names;		//  Try again with the new suggested size.
		Names = NULL;
	}
	if (Success){
		for (NameIdx = Names;NameIdx[0] != L'\0';NameIdx += wcslen(NameIdx) + 1){	//  Display the various paths.
			wprintf(L"  %s", NameIdx);
		}
		wprintf(L"\n");
	}
	if (Names != NULL){
		delete[] Names;
		Names = NULL;
	}
	return;
}

void Info::runC(string s, Aliases *al, Selections *se, int *n, int *permision){
	DWORD  CharCount = 0;
	WCHAR  DeviceName[MAX_PATH] = L"";
	DWORD  Error = ERROR_SUCCESS;
	HANDLE FindHandle = INVALID_HANDLE_VALUE;
	BOOL   Found = FALSE;
	size_t Index = 0;
	WCHAR  VolumeName[MAX_PATH] = L"";

	if ((FindHandle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName))) == INVALID_HANDLE_VALUE)//  Enumerate all volumes in the system.
		throw new last_error_cond(GetLastError(),"FindFirstVolumeW");
	for (;;){
		Index = wcslen(VolumeName) - 1;	//  Skip the \\?\ prefix and remove the trailing backslash.
		if (VolumeName[0] != L'\\' ||VolumeName[1] != L'\\' ||VolumeName[2] != L'?' ||VolumeName[3] != L'\\' ||VolumeName[Index] != L'\\'){
			FindVolumeClose(FindHandle);
			throw new last_error_cond(ERROR_BAD_PATHNAME, "FindFirstVolumeW/FindNextVolumeW");
		}
		VolumeName[Index] = L'\0';	//  QueryDosDeviceW does not allow a trailing backslash, so temporarily remove it.
		CharCount = QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));
		VolumeName[Index] = L'\\';
		if (CharCount == 0){
			FindVolumeClose(FindHandle);
			throw new last_error_cond(GetLastError(), "QueryDosDeviceW");
		}
		wprintf(L"\nFound a device:\n %s", DeviceName);
		wprintf(L"\nVolume name: %s", VolumeName);
		wprintf(L"\nPaths:");
		try{
			DisplayVolumePaths(VolumeName);
		}
		catch (bad_alloc obj){
			FindVolumeClose(FindHandle);
			throw obj;
		}
		if (!(FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName)))){	//  Move on to the next volume.
			if (GetLastError() != ERROR_NO_MORE_FILES){
				FindVolumeClose(FindHandle);
				throw new last_error_cond(GetLastError(), "FindNextVolumeW");
			}
			break;	//  Finished iterating through all the volumes.
		}
	}
	FindVolumeClose(FindHandle);
	FindHandle = INVALID_HANDLE_VALUE;
	return;
}
