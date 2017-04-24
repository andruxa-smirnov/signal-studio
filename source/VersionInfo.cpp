// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "VersionInfo.h"

bool CVersionInfo::GetFileInfo(VS_FIXEDFILEINFO& Info, LPCTSTR Path)
{
	ZeroMemory(&Info, sizeof(VS_FIXEDFILEINFO));
	TCHAR	module[MAX_PATH];
	if (Path != NULL)
		_tcsncpy(module, Path, MAX_PATH);
	else
		GetModuleFileName(AfxGetInstanceHandle(), module, MAX_PATH);
	DWORD	handle;
	DWORD	size = GetFileVersionInfoSize(module, &handle);
	if (size) {
		CString	buffer;
		LPTSTR	pData = buffer.GetBuffer(size);
		if (GetFileVersionInfo(module, handle, size, pData)) {
			UINT	uInfoSize = 0;
			PVOID	pInfo;
			if (VerQueryValue(pData, _T("\\"), &pInfo, &uInfoSize)) {
				Info = *((VS_FIXEDFILEINFO *)pInfo);
				return(TRUE);
			}
		}
	}
	return(FALSE);
}

bool CVersionInfo::GetModuleInfo(VS_FIXEDFILEINFO& Info, LPCTSTR ModuleName)
{
	TCHAR	Path[MAX_PATH];
	HMODULE	Hand = GetModuleHandle(ModuleName);
	if (Hand != NULL && GetModuleFileName(Hand, Path, MAX_PATH))
		return(GetFileInfo(Info, Path));
	return(FALSE);
}
