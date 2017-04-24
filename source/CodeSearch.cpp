// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// CodeSearch.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "CodeSearch.h"
#include "StubFileLocation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeSearch dialog

IMPLEMENT_DYNAMIC(CCodeSearch, CDialog);

CCodeSearch::CCodeSearch(LPCTSTR Folder, CWnd* pParent)
	: m_Folder(Folder), CDialog(CCodeSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodeSearch)
	//}}AFX_DATA_INIT
	m_Cancel = FALSE;
	m_PathRequest = FALSE;
	m_DriveTypeMask = DTM_FIXED;
}

CCodeSearch::~CCodeSearch()
{
}

void CCodeSearch::SetDriveTypeMask(int Mask)
{
	m_DriveTypeMask = Mask;
}

void CCodeSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeSearch)
	DDX_Control(pDX, IDC_FILE_SEARCH_CURRENT_PATH, m_CurrentPath);
	//}}AFX_DATA_MAP
}

bool CCodeSearch::SearchFolder(LPCTSTR Folder)
{
	CStubFileLocation	sff;
	CFileFind		*ff;
	BOOL	Working = sff.FindFile(CString(Folder) + "\\*.*");
	while (Working) {
		Working = sff.FindNextFile(ff);
		if (!OnFile(ff->GetFilePath()) || m_Cancel)
			return(FALSE);
		if (m_PathRequest) {	// if path was requested
			LPTSTR	path = _tcsdup(ff->GetFilePath());
			if (!PostMessage(UWM_PATH_REPLY, WPARAM(path)))
				free(path);	// post message failed, clean up to avoid leak
			// there's a potential race here, but it's good enough because
			// path requests are evenly spaced at low frequency, and worst
			// possibly case (worker ignores a request) is harmless enough
			m_PathRequest = FALSE;	// clear path request
		}
	}
	return(TRUE);
}

bool CCodeSearch::SearchAllDrives()
{
	DWORD	len = GetLogicalDriveStrings(0, NULL);	// get list size
	CString	DriveList;
	LPTSTR	p = DriveList.GetBufferSetLength(len);
	GetLogicalDriveStrings(len, p);
	while (*p) {
		// if drive type is selected by type mask
		if ((1 << GetDriveType(p)) & m_DriveTypeMask) {
			p[2] = 0;	// remove backslash
			if (!SearchFolder(p))
				return(FALSE);
		}
		p += 4;		// drive letter, colon, backslash, null
	}
	return(TRUE);
}

void CCodeSearch::Search()
{
	if (m_Folder.IsEmpty())
		SearchAllDrives();
	else
		SearchFolder(m_Folder);
	PostMessage(UWM_SEARCH_DONE);
}

UINT CCodeSearch::SearchThread(LPVOID pParam)
{
	((CCodeSearch *)pParam)->Search();
	return(0);
}

BEGIN_MESSAGE_MAP(CCodeSearch, CDialog)
	//{{AFX_MSG_MAP(CCodeSearch)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UWM_SEARCH_DONE, OnSearchDone)
	ON_MESSAGE(UWM_PATH_REPLY, OnPathReply)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeSearch message handlers

BOOL CCodeSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Cancel = FALSE;
	m_PathRequest = TRUE;
	AfxBeginThread(SearchThread, this);
	SetTimer(PATH_TIMER_ID, PATH_TIMER_PERIOD, NULL);
	return(TRUE);
}

void CCodeSearch::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(PATH_TIMER_ID);
}

void CCodeSearch::OnCancel() 
{
	m_Cancel = TRUE;
}

void CCodeSearch::OnTimer(W64UINT nIDEvent) 
{
	m_PathRequest = TRUE;	// request path from worker thread
	CDialog::OnTimer(nIDEvent);
}

LRESULT CCodeSearch::OnSearchDone(WPARAM wParam, LPARAM lParam)
{
	EndDialog(m_Cancel ? IDCANCEL : IDOK);
	return(0);
}

LRESULT CCodeSearch::OnPathReply(WPARAM wParam, LPARAM lParam)
{
	LPTSTR	path = LPTSTR(wParam);
	m_CurrentPath.SetWindowText(path);	// update static control
	free(path);	// allocated via strdup; we're responsible for cleanup
	return(0);
}
