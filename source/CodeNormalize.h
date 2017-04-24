// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeNormalize_H__B0184709_EAAB_49D7_9328_60274750D1D2__INCLUDED_)
#define AFX_CodeNormalize_H__B0184709_EAAB_49D7_9328_60274750D1D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeNormalize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeNormalize dialog

class CCodeNormalize : public CDialog
{
// Construction
public:
	CCodeNormalize(CWnd* pParent = NULL);   // standard constructor
	~CCodeNormalize();

// Dialog Data
	//{{AFX_DATA(CCodeNormalize)
	enum { IDD = IDD_NORMALIZE };
	BOOL	m_Independent;
	BOOL	m_Normalize;
	BOOL	m_Unbias;
	double	m_PeakLevel;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeNormalize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCodeNormalize)
	//}}AFX_MSG
	afx_msg	LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	afx_msg	void OnUpdatePeakLevel(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeNormalize_H__B0184709_EAAB_49D7_9328_60274750D1D2__INCLUDED_)
