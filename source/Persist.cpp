// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "Persist.h"

LPCTSTR CPersist::WND_PLACE	= _T("WP");

BOOL CPersist::GetWndPlacement(LPCTSTR Section, LPCTSTR Name, WINDOWPLACEMENT& wp)
{
	DWORD	Size = sizeof(WINDOWPLACEMENT);
	memset(&wp, 0, Size);
	return(GetBinary(Section, CString(Name) + WND_PLACE, &wp, &Size));
}

BOOL CPersist::WriteWndPlacement(LPCTSTR Section, LPCTSTR Name, const WINDOWPLACEMENT& wp)
{
	return(WriteBinary(Section, CString(Name) + WND_PLACE, &wp, sizeof(WINDOWPLACEMENT)));
}

void CPersist::SaveWnd(LPCTSTR Section, const CWnd *Wnd, LPCTSTR Name)
{
	WINDOWPLACEMENT	wp;
	Wnd->GetWindowPlacement(&wp);
	WriteWndPlacement(Section, Name, wp);
}

int CPersist::LoadWnd(LPCTSTR Section, CWnd *Wnd, LPCTSTR Name, int Options)
{
	WINDOWPLACEMENT	wp;
	if (!GetWndPlacement(Section, Name, wp))
		return(0);
	if ((wp.showCmd == SW_SHOWMINIMIZED && (Options & NO_MINIMIZE))
	|| (wp.showCmd == SW_SHOWMAXIMIZED && (Options & NO_MAXIMIZE)))
		wp.showCmd = SW_SHOWNORMAL;
	if (Options & NO_RESIZE) {
		CRect	CurRect;
		Wnd->GetWindowRect(CurRect);
		wp.rcNormalPosition.right = wp.rcNormalPosition.left + CurRect.Width();
		wp.rcNormalPosition.bottom = wp.rcNormalPosition.top + CurRect.Height();
	}
	Wnd->SetWindowPlacement(&wp);
	return(wp.showCmd);
}

int CPersist::GetWndShow(LPCTSTR Section, LPCTSTR Name)
{
	WINDOWPLACEMENT	wp;
	if (!GetWndPlacement(Section, Name, wp))
		return(0);
	return(wp.showCmd);
}

BOOL CPersist::GetBinary(LPCTSTR Section, LPCTSTR Entry, LPVOID Buffer, LPDWORD Size)
{
	ASSERT(Buffer != NULL);
	ASSERT(Size != NULL);
	LPBYTE	pData;
	UINT	DataLen;
	if (!AfxGetApp()->GetProfileBinary(Section, Entry, &pData, &DataLen))
		return(FALSE);
	bool	retc;
	if (DataLen > *Size)	// if data too big for buffer
		retc = FALSE;
	else {	// data fits in buffer
		CopyMemory(Buffer, pData, DataLen);	// copy data to buffer
		*Size = DataLen;	// replace buffer size with data length
		retc = TRUE;
	}
	delete [] pData;	// free data regardless
	return(retc);
}

BOOL CPersist::WriteBinary(LPCTSTR Section, LPCTSTR Entry, LPCVOID Buffer, DWORD Size)
{
	return(AfxGetApp()->WriteProfileBinary(Section, Entry, LPBYTE(Buffer), Size));
}

BOOL CPersist::GetFont(LPCTSTR Section, LPCTSTR Entry, CFont *Font)
{
	LOGFONT	lf;
	DWORD	Size = sizeof(LOGFONT);
	if (Font != NULL && GetBinary(Section, Entry, &lf, &Size)
		&& Size == sizeof(LOGFONT))
		return(Font->CreateFontIndirect(&lf));
	return(FALSE);
}

BOOL CPersist::WriteFont(LPCTSTR Section, LPCTSTR Entry, CFont *Font)
{
	LOGFONT	lf;
	DWORD	Size = (Font != NULL && Font->GetSafeHandle() 
		&& Font->GetLogFont(&lf) ? sizeof(LOGFONT) : 0);
	return(WriteBinary(Section, Entry, &lf, Size));
}

float CPersist::GetFloat(LPCTSTR Section, LPCTSTR Entry, float Default)
{
	float	r;
	DWORD	Size = sizeof(float);
	if (GetBinary(Section, Entry, &r, &Size))
		return(r);
	return(Default);
}

BOOL CPersist::WriteFloat(LPCTSTR Section, LPCTSTR Entry, float Value)
{
	return(WriteBinary(Section, Entry, &Value, sizeof(float)));
}

double CPersist::GetDouble(LPCTSTR Section, LPCTSTR Entry, double Default)
{
	double	r;
	DWORD	Size = sizeof(double);
	if (GetBinary(Section, Entry, &r, &Size))
		return(r);
	return(Default);
}

BOOL CPersist::WriteDouble(LPCTSTR Section, LPCTSTR Entry, double Value)
{
	return(WriteBinary(Section, Entry, &Value, sizeof(double)));
}
