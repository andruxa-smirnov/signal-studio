// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeFindClipping_H__FBA0CA0B_6D57_4371_BEF3_AF14C3BBC59B__INCLUDED_)
#define AFX_CodeFindClipping_H__FBA0CA0B_6D57_4371_BEF3_AF14C3BBC59B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeFindClipping.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeFindClipping dialog

class CCodeFindClipping : public CDialog
{
// Construction
public:
	CCodeFindClipping(CWnd* pParent = NULL);   // standard constructor
	~CCodeFindClipping();

// Dialog Data
	//{{AFX_DATA(CCodeFindClipping)
	enum { IDD = IDD_FIND_CLIPPING };
	UINT	m_StopThreshold;
	UINT	m_StartThreshold;
	double	m_ClippingLevel;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeFindClipping)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Generated message map functions
	//{{AFX_MSG(CCodeFindClipping)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeFindClipping_H__FBA0CA0B_6D57_4371_BEF3_AF14C3BBC59B__INCLUDED_)
