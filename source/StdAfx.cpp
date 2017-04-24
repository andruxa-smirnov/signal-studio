// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// stdafx.cpp : source file that includes just the standard includes
//	SignalStudio.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "DLLWrap.h"

void DDV_Fail(CDataExchange* pDX, int nIDC)
{
	ASSERT(pDX != NULL);
	ASSERT(pDX->m_pDlgWnd != NULL);
	// test for edit control via GetClassName instead of IsKindOf,
	// so test works on controls that aren't wrapped in MFC object
	HWND	hWnd = ::GetDlgItem(pDX->m_pDlgWnd->m_hWnd, nIDC);
	ASSERT(hWnd != NULL);
	TCHAR	szClassName[6];
	// if control is an edit control
	if (GetClassName(hWnd, szClassName, 6) && !_tcsicmp(szClassName, _T("Edit")))
		pDX->PrepareEditCtrl(nIDC);
	else	// not an edit control
		pDX->PrepareCtrl(nIDC);
	pDX->Fail();
}
