// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_TIMECodeRuler_H__4BA66D6B_9B2D_4D4F_B604_F9B08D2CD5A9__INCLUDED_)
#define AFX_TIMECodeRuler_H__4BA66D6B_9B2D_4D4F_B604_F9B08D2CD5A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeCodeRuler.h : header file

/////////////////////////////////////////////////////////////////////////////
// CTimeCodeRuler window

#include "CodeRuler.h"
#include "TimeCodeRulerControl.h"

class CTimeCodeRuler : public CCodeRuler
{
	DECLARE_DYNAMIC(CTimeCodeRuler);
// Construction
public:
	CTimeCodeRuler();

// Attributes
public:
	CTimeCodeRulerControl	*GetRuler();
	const CTimeCodeRulerControl	*GetRuler() const;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeCodeRuler)
	//}}AFX_VIRTUAL
	virtual bool	CreateRuler();

// Implementation
public:
	virtual ~CTimeCodeRuler();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTimeCodeRuler)
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Data members

// Helpers
};

inline CTimeCodeRulerControl *CTimeCodeRuler::GetRuler()
{
	return((CTimeCodeRulerControl *)m_Ruler);
}

inline const CTimeCodeRulerControl *CTimeCodeRuler::GetRuler() const
{
	return((const CTimeCodeRulerControl *)m_Ruler);
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMECodeRuler_H__4BA66D6B_9B2D_4D4F_B604_F9B08D2CD5A9__INCLUDED_)
