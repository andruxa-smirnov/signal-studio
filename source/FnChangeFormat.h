// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_FnChangeFormat_H__ACF26E58_948A_4EA4_8F15_46694593E500__INCLUDED_)
#define AFX_FnChangeFormat_H__ACF26E58_948A_4EA4_8F15_46694593E500__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FnChangeFormat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFnChangeFormat dialog

class CFnChangeFormat : public CDialog
{
// Construction
public:
	CFnChangeFormat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFnChangeFormat)
	enum { IDD = IDD_CHANGE_FORMAT };
	UINT	m_SampleRate;
	UINT	m_SampleBits;
	UINT	m_Channels;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFnChangeFormat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFnChangeFormat)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FnChangeFormat_H__ACF26E58_948A_4EA4_8F15_46694593E500__INCLUDED_)
