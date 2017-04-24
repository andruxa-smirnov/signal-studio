// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeRuler_H__4BA66D6B_9B2D_4D4F_B604_F9B08D2CD5A9__INCLUDED_)
#define AFX_CodeRuler_H__4BA66D6B_9B2D_4D4F_B604_F9B08D2CD5A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CodeRuler.h : header file

/////////////////////////////////////////////////////////////////////////////
// CCodeRuler window

#include "CodeRulerControl.h"

class CCodeRuler : public CControlBar
{
	DECLARE_DYNAMIC(CCodeRuler)
// Construction
public:
	CCodeRuler();
	BOOL	Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID);

// Attributes
public:
	CCodeRulerControl	*GetRuler();
	const CCodeRulerControl	*GetRuler() const;
	int		GetHeight() const;
	void	SetHeight(int Height);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeRuler)
	//}}AFX_VIRTUAL
	virtual void	OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize	CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual bool	CreateRuler();

// Implementation
public:
	virtual ~CCodeRuler();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCodeRuler)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Data members
	CCodeRulerControl	*m_Ruler;		// pointer to child ruler window
	int		m_Height;			// bar height if horizontal, or width if vertical

// Helpers
};

inline CCodeRulerControl *CCodeRuler::GetRuler()
{
	return(m_Ruler);
}

inline const CCodeRulerControl *CCodeRuler::GetRuler() const
{
	return(m_Ruler);
}

inline int CCodeRuler::GetHeight() const
{
	return(m_Height);
}

inline void CCodeRuler::SetHeight(int Height)
{
	m_Height = Height;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeRuler_H__4BA66D6B_9B2D_4D4F_B604_F9B08D2CD5A9__INCLUDED_)
