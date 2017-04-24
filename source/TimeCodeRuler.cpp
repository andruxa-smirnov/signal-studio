// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// TimeCodeRuler.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "TimeCodeRuler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeCodeRuler

IMPLEMENT_DYNAMIC(CTimeCodeRuler, CCodeRuler)

CTimeCodeRuler::CTimeCodeRuler()
{
}

CTimeCodeRuler::~CTimeCodeRuler()
{
}

bool CTimeCodeRuler::CreateRuler() 
{
	ASSERT(m_Ruler == NULL);	// ruler can only be created once
	m_Ruler = new CTimeCodeRulerControl;
	UINT	style = WS_CHILD | WS_VISIBLE | m_dwStyle;	// include bar style
	CRect	r(0, 0, 0, 0);
	return(GetRuler()->Create(style, r, this, 0) != 0);	// derived create
}

BEGIN_MESSAGE_MAP(CTimeCodeRuler, CCodeRuler)
	//{{AFX_MSG_MAP(CTimeCodeRuler)
	ON_WM_PARENTNOTIFY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeCodeRuler message handlers

void CTimeCodeRuler::OnParentNotify(UINT message, LPARAM lParam) 
{
	CCodeRuler::OnParentNotify(message, lParam);
	switch (message) {
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		GetRuler()->GetTarget()->SetFocus();
		break;
	}
}
