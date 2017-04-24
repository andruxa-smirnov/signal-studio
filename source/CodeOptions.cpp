// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.


// CodeOptions.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeOptions.h"
#include <afxpriv.h>	// for WM_KICKIDLE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeOptions dialog

IMPLEMENT_DYNAMIC(CCodeOptions, CPropertySheet)

#define OPTIONSPAGEDEF(name) offsetof(CCodeOptions, m_##name##Dlg),
const int CCodeOptions::m_PageOffset[OPTIONS_PAGES] = {
	#include "OptPages.h"	// define offsets of property pages within sheet
};

CCodeOptions::CCodeOptions(UINT nIDCaption, CCodeOptionsInfo& Options, CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(nIDCaption, pParentWnd, iSelectPage),
	#define OPTIONSPAGEDEF(name) m_##name##Dlg(m_oi),
	#include "OptPages.h"		// construct property pages
	m_oi(Options)	// init reference to options data
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	for (int iPage = 0; iPage < OPTIONS_PAGES; iPage++) {
		CObject	*pObj = reinterpret_cast<CObject *>(LPBYTE(this) + m_PageOffset[iPage]);
		AddPage(STATIC_DOWNCAST(CPropertyPage, pObj));	// add property pages
	}
	m_CurPage = iSelectPage;
}

void CCodeOptions::CreateResetAllButton()
{
	CRect	r, rt;
	GetDlgItem(IDOK)->GetWindowRect(r);
	GetTabControl()->GetWindowRect(rt);
	ScreenToClient(r);
	ScreenToClient(rt);
	int	w = r.Width();
	r.left = rt.left;
	r.right = rt.left + w;
	CString	Title(LPCTSTR(IDS_OPT_RESET_ALL));
	m_ResetAll.Create(Title, BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		r, this, IDS_OPT_RESET_ALL);
	m_ResetAll.SetFont(GetFont());
	// adjust tab order so new button comes last
	CWnd	*pCancelBtn = GetDlgItem(IDCANCEL);	// assume cancel is now last
	if (pCancelBtn != NULL)
		m_ResetAll.SetWindowPos(pCancelBtn, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void CCodeOptions::RestoreDefaults()
{
	m_oi = CCodeOptionsInfo::m_Defaults;
}

BEGIN_MESSAGE_MAP(CCodeOptions, CPropertySheet)
	//{{AFX_MSG_MAP(CCodeOptions)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDS_OPT_RESET_ALL, OnResetAll)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeOptions message handlers

BOOL CCodeOptions::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	CreateResetAllButton();	// create reset all button
	SetActivePage(m_CurPage);	// set current page
	return bResult;
}

void CCodeOptions::OnDestroy() 
{
	m_CurPage = GetActiveIndex();
	CPropertySheet::OnDestroy();
}

void CCodeOptions::OnResetAll() 
{
	if (AfxMessageBox(IDS_OPT_RESTORE_DEFAULTS, MB_YESNO | MB_DEFBUTTON2) == IDYES) {
		EndDialog(IDOK);
		RestoreDefaults();
	}
}

LRESULT CCodeOptions::OnKickIdle(WPARAM, LPARAM)
{
	SendMessageToDescendants(WM_KICKIDLE, 0, 0, FALSE, FALSE);
	return 0;
}
