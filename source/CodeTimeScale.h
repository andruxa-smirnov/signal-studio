// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_TIMECodeRulerControl_H__490CA5D7_29D1_4381_9849_416A9904451A__INCLUDED_)
#define AFX_TIMECodeRulerControl_H__490CA5D7_29D1_4381_9849_416A9904451A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeCodeRulerControl.h : header file

#include "ZoomCodeRulerControl.h"

class CSignalStudioView;

/////////////////////////////////////////////////////////////////////////////
// CTimeCodeRulerControl window

class CTimeCodeRulerControl : public CZoomCodeRulerControl
{
	DECLARE_DYNAMIC(CTimeCodeRulerControl)
// Construction
public:
	CTimeCodeRulerControl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeCodeRulerControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTimeCodeRulerControl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTimeCodeRulerControl)
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Overrides
	virtual	void	GetTargetRect(CRect& Rect) const;
	virtual	void	OnDrop(UINT Flags, CPoint Point);

// Helpers
	CSignalStudioView	*GetView();
	const CSignalStudioView	*GetView() const;
	void	StepZoom(CPoint Point, bool In);
};

inline CSignalStudioView *CTimeCodeRulerControl::GetView()
{
	return(STATIC_DOWNCAST(CSignalStudioView, m_Target));
}

inline const CSignalStudioView *CTimeCodeRulerControl::GetView() const
{
	return(STATIC_DOWNCAST(CSignalStudioView, m_Target));
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMECodeRulerControl_H__490CA5D7_29D1_4381_9849_416A9904451A__INCLUDED_)
