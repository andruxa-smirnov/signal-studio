// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_SizingControllerBar_H__53C410DA_1109_40AF_B567_7D7918C63980__INCLUDED_)
#define AFX_SizingControllerBar_H__53C410DA_1109_40AF_B567_7D7918C63980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SizingControllerBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSizingControllerBar dialog

class CSizingControllerBar : public CSizingControlBarG
{
	DECLARE_DYNAMIC(CSizingControllerBar);
// Construction
public:
	CSizingControllerBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSizingControllerBar)
	//}}AFX_VIRTUAL

// Implementation
protected:
// Generated message map functions
	//{{AFX_MSG(CSizingControllerBar)
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	//}}AFX_MSG
	afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Member data
	bool	m_IsSizeValid;		// if true, OnSize arguments are valid
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SizingControllerBar_H__53C410DA_1109_40AF_B567_7D7918C63980__INCLUDED_)
