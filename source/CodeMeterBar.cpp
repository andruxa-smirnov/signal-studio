// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// CodeMeterBar.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeMeterBar.h"
#include "CodeViewMeter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeterBar

IMPLEMENT_DYNAMIC(CMeterBar, CSizingControllerBar);

CMeterBar::CMeterBar()
{
	m_szVert = CSize(75, 0);	// default width when vertically docked
	m_View = NULL;
}

CMeterBar::~CMeterBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMeterBar message map

BEGIN_MESSAGE_MAP(CMeterBar, CSizingControllerBar)
	//{{AFX_MSG_MAP(CMeterBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeterBar message handlers

int CMeterBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControllerBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass	*pFactory = RUNTIME_CLASS(CMeterView);
	m_View = DYNAMIC_DOWNCAST(CMeterView, pFactory->CreateObject());
	DWORD	dwStyle = AFX_WS_DEFAULT_VIEW;
    CRect r(0, 0, 0, 0);	// arbitrary initial size
    if (!m_View->Create(NULL, NULL, dwStyle, r, this, 0, NULL))
		return -1;
	m_View->SetTimerFrequency(CMainFrame::GetTimerFrequency());

	return 0;
}

void CMeterBar::OnSize(UINT nType, int cx, int cy) 
{
	CSizingControllerBar::OnSize(nType, cx, cy);
	if (m_IsSizeValid) {	// if size is valid
		if (m_View != NULL)
			m_View->MoveWindow(0, 0, cx, cy);
	}
}
