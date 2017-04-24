// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodePeakStats_H__9F98DAD8_98F2_43BD_8C09_0C821BDFE7DB__INCLUDED_)
#define AFX_CodePeakStats_H__9F98DAD8_98F2_43BD_8C09_0C821BDFE7DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodePeakStats.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodePeakStats dialog

#include "CodePersist.h"
#include "SignalProcess.h"
#include "ReportControl.h"
#include "ControlResizer.h"

class CSignalStudioView;

class CCodePeakStats : public CCodePersist
{
// Construction
public:
	CCodePeakStats(CSignalProcess::CPeakStats& Stats, CSignalStudioView *View, CWnd* pParent = NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodePeakStats)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CCodePeakStats)
	enum { IDD = IDD_PEAK_STATS };
	CReportControl	m_List;
	//}}AFX_DATA

// Generated message map functions
	//{{AFX_MSG(CCodePeakStats)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnGoto();
	afx_msg void OnUpdateGoto(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Constants
	enum {	// columns
		COL_CHANNEL,
		COL_MIN_SAMPLE,
		COL_MIN_PCT,
		COL_MAX_SAMPLE,
		COL_MAX_PCT,
		COL_PEAK_DB,
		COL_DC_BIAS,
		COL_BIAS_PCT,
		COLS
	};
	enum {	// goto targets
		GOTO_NONE,
		GOTO_MIN,
		GOTO_MAX,
	};
	static const CReportControl::RES_COL m_ColInfo[COLS];
	static const CControlResizer::CTRL_LIST	m_CtrlList[];

// Member data
	CSignalStudioView	*m_View;	// pointer to view
	CSignalProcess::CPeakStats&	m_Stats;	// reference to peak statistics
	CControlResizer	m_Resize;		// control resizer
	CPoint	m_ContextPt;		// context menu point

// Helpers
	int		GetGotoTarget(CPoint Point, int& ChannelIdx);
	static int CALLBACK SortCompare(LPARAM p1, LPARAM p2, LPARAM This);
	int		SortCompare(int p1, int p2) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodePeakStats_H__9F98DAD8_98F2_43BD_8C09_0C821BDFE7DB__INCLUDED_)
