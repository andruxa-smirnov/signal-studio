// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_HistoryTool_H__1E61CD05_C1F0_49C5_89EA_653327F7C1C7__INCLUDED_)
#define AFX_HistoryTool_H__1E61CD05_C1F0_49C5_89EA_653327F7C1C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistoryTool.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistoryTool window

#include "SizingControllerBar.h"
#include "ResultsReportControl.h"
#include "ProgressDlg.h"

class CHistoryTool : public CSizingControllerBar
{
	DECLARE_DYNAMIC(CHistoryTool);
// Construction
public:
	CHistoryTool();

// Attributes
public:
	bool	SetUndoPos(int Pos);

// Operations
public:
	void	UpdateList();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryTool)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHistoryTool();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistoryTool)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg	void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg	void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Types
	class CListCtrlEx : public CListCtrl {
	public:
		virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	};
	class CProgressDlgEx : public CProgressDlg {
	public:
		CProgressDlgEx(UINT nIDTemplate = IDD_PROGRESS, CWnd* pParent = NULL);
		~CProgressDlgEx();
	};

// Constants
	enum {	// columns
		COL_ACTION,
		COLUMNS
	};
	enum {
		DEF_VERT_DOCK_WIDTH = 120	// default width when vertically docked
	};

// Member data
	CListCtrlEx	m_List;			// undo history list control
	CImageList	m_StateImgList;	// state image list for undo position marker
	CProgressDlgEx	*m_ProgressDlg;	// pointer to progress dialog during undo/redo
	int		m_ProgressPos;		// progress position during undo/redo
	friend class CProgressDlgEx;
};

inline CHistoryTool::CProgressDlgEx::CProgressDlgEx(UINT nIDTemplate, CWnd* pParent) :
	CProgressDlg(nIDTemplate, pParent)
{
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HistoryTool_H__1E61CD05_C1F0_49C5_89EA_653327F7C1C7__INCLUDED_)
