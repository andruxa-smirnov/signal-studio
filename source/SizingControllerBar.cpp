// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// SizingControllerBar.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "SizingControllerBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSizingControllerBar dialog

IMPLEMENT_DYNAMIC(CSizingControllerBar, CSizingControlBarG);

CSizingControllerBar::CSizingControllerBar()
{
	//{{AFX_DATA_INIT(CSizingControllerBar)
	//}}AFX_DATA_INIT
	m_IsSizeValid = FALSE;
}

BEGIN_MESSAGE_MAP(CSizingControllerBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CSizingControllerBar)
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSizingControllerBar message handlers

void CSizingControllerBar::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	if (!(lpwndpos->flags & SWP_NOSIZE))	// if size is being changed
		m_IsSizeValid = TRUE;	// OnSize arguments are valid from now on
	CSizingControlBarG::OnWindowPosChanged(lpwndpos);
}

LRESULT CSizingControllerBar::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
	AfxGetApp()->WinHelp(GetDlgCtrlID());
	return TRUE;
}
