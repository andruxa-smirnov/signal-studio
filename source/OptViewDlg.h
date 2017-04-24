// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_OptViewDlg_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_)
#define AFX_OptViewDlg_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptViewDlg dialog

#include "CodeOptionsInfo.h"

class COptViewDlg : public CPropertyPage
{
// Construction
public:
	COptViewDlg(CCodeOptionsInfo& Info);

// Attributes

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptViewDlg)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Generated message map functions
	//{{AFX_MSG(COptViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnColors();
	//}}AFX_MSG
	afx_msg LRESULT	OnKickIdle(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Dialog data
	//{{AFX_DATA(COptViewDlg)
	enum { IDD = IDD_OPT_VIEW };
	//}}AFX_DATA

// Constants

// Member data
	CCodeOptionsInfo&	m_oi;		// reference to parent's options info 

// Helpers
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OptViewDlg_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_)
