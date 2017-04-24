// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_RESULTSReportControl_H__84A05433_DB70_434F_A8BB_7D0BC8C17B63__INCLUDED_)
#define AFX_RESULTSReportControl_H__84A05433_DB70_434F_A8BB_7D0BC8C17B63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultsReportControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultsReportControl window

#include "ReportControl.h"
#include "RefPtr.h"
#include "SignalProcess.h"

class CSignalStudioView;

class CResultsReportControl : public CReportControl, public CRefObj
{
	DECLARE_DYNAMIC(CResultsReportControl);
// Construction
public:
	CResultsReportControl();

// Attributes
	void	Update(CSignalProcess::CClipSpanArray& ClipSpan, CSignalStudioView *View);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultsReportControl)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
// Generated message map functions
	//{{AFX_MSG(CResultsReportControl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* result);	
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	LRESULT	OnUpdateItems(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Constants
	enum {	// clipping report columns
		CLIP_COL_START,
		CLIP_COL_LENGTH,
		CLIP_COL_CHANNEL,
		CLIP_COLS
	};
	static const RES_COL	m_ClipColInfo[CLIP_COLS];
	enum {
		UWM_UPDATEITEMS = WM_USER + 100
	};

// Member data
	CSignalProcess::CClipSpanArray	m_ClipSpan;	// array of clipping spans
	CIntArrayEx	m_SortIdx;	// array of clipping span indices for sorting
	CSignalStudioView	*m_View;	// pointer to owner view
	static	CResultsReportControl	*m_This;	// pointer to our instance for sorting

// Overrides
	virtual	void	SortRows();

// Helpers
	void	OnItemSelection(int ItemIdx);
	int		SortCompare(const int *p1, const int *p2) const;
	static	int		SortCompare(const void *p1, const void *p2);
	int		FindItem(int ItemIdx) const;
	void	SelectItem(int ItemIdx);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTSReportControl_H__84A05433_DB70_434F_A8BB_7D0BC8C17B63__INCLUDED_)
