// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// ChildFrm.h : interface of the CChildFrame class

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__8AAAC8EF_4FC2_4BA9_9D81_545D92487ABD__INCLUDED_)
#define AFX_CHILDFRM_H__8AAAC8EF_4FC2_4BA9_9D81_545D92487ABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TimeCodeRuler.h"
#include "ChannelBar.h"

class CSignalStudioView;

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
	CSignalStudioView	*GetView();

// Operations
public:
	void	ShowChannelBar(bool Enable);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Data members
	CSignalStudioView	*m_View;	// pointer to view
	CTimeCodeRuler	m_TimeBar;	// time ruler bar
	CChannelBar	m_ChannelBar;	// channel bar
};

inline CSignalStudioView *CChildFrame::GetView()
{
	return(m_View);
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__8AAAC8EF_4FC2_4BA9_9D81_545D92487ABD__INCLUDED_)
