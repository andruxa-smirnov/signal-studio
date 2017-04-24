// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// CodeViewResults.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeViewResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeViewResults

IMPLEMENT_DYNAMIC(CCodeViewResults, CSizingControllerBar);

CCodeViewResults::CCodeViewResults()
{
	m_szVert = CSize(265, 0);	// default width when vertically docked
	m_View = NULL;
}

CCodeViewResults::~CCodeViewResults()
{
}

void CCodeViewResults::OnDestroyView(CSignalStudioView *View)
{
	if (View == m_View) {	// if our owner view was destroyed
		m_Report.SetEmpty();	// delete report
		m_View = NULL;
	}
}

bool CCodeViewResults::ReportClipping(CSignalProcess::CClipSpanArray& ClipSpan, CSignalStudioView *View)
{
	if (m_Report.IsEmpty())
		m_Report.CreateObj();	// create new report control instance
	m_View = View;	// set our owner view
	if (m_Report->m_hWnd == NULL) {	// if control doesn't exist, create it
		CRect	rc;
		GetClientRect(rc);
		UINT	style = WS_CHILD | WS_VISIBLE | LVS_OWNERDATA	// virtual list
			| LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS;
		if (!m_Report->Create(style, rc, this, 0))	// create report control
			return(FALSE);
	}
	m_Report->Update(ClipSpan, View);	// transfer clip span array to control
	return(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CCodeViewResults message map

BEGIN_MESSAGE_MAP(CCodeViewResults, CSizingControllerBar)
	//{{AFX_MSG_MAP(CCodeViewResults)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeViewResults message handlers

int CCodeViewResults::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControllerBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CCodeViewResults::OnSize(UINT nType, int cx, int cy) 
{
	CSizingControllerBar::OnSize(nType, cx, cy);
	if (m_IsSizeValid) {	// if size is valid
		if (!m_Report.IsEmpty())	// if report control exists
			m_Report->MoveWindow(0, 0, cx, cy);
	}
}
