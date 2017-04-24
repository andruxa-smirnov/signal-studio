// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeViewResults_H__1E61CD05_C1F0_49C5_89EA_653327F7C1C7__INCLUDED_)
#define AFX_CodeViewResults_H__1E61CD05_C1F0_49C5_89EA_653327F7C1C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeViewResults.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeViewResults window

#include "SizingControllerBar.h"
#include "ResultsReportControl.h"

class CCodeViewResults : public CSizingControllerBar
{
	DECLARE_DYNAMIC(CCodeViewResults);
// Construction
public:
	CCodeViewResults();

// Attributes
public:
	bool	ReportClipping(CSignalProcess::CClipSpanArray& ClipSpan, CSignalStudioView *View);

// Operations
public:
	void	OnDestroyView(CSignalStudioView *View);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeViewResults)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCodeViewResults();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCodeViewResults)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Types
	typedef CRefPtr<CResultsReportControl> CResultsReportControlPtr;

// Member data
	CResultsReportControlPtr	m_Report;	// reference-counted pointer to report control
	CSignalStudioView	*m_View;	// pointer to owner view
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeViewResults_H__1E61CD05_C1F0_49C5_89EA_653327F7C1C7__INCLUDED_)
