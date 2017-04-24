// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.


#if !defined(AFX_CodeFade_H__7D9CE819_5400_475B_BBC0_4440492DD2BC__INCLUDED_)
#define AFX_CodeFade_H__7D9CE819_5400_475B_BBC0_4440492DD2BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeFade.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeFade dialog

class CCodeFade : public CDialog
{
// Construction
public:
	CCodeFade(CWnd* pParent = NULL);   // standard constructor
	~CCodeFade();

// Attributes
	CDblRange	GetRange() const;
	bool	IsLog() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeFade)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CCodeFade)
	enum { IDD = IDD_FADE };
	int		m_FadeType;
	double	m_Start;
	double	m_End;
	BOOL	m_Log;
	//}}AFX_DATA

// Constants
	enum {	// fade types
		FT_IN,
		FT_OUT,
		FT_CUSTOM,
		FADE_TYPES
	};

// Generated message map functions
	//{{AFX_MSG(CCodeFade)
	virtual BOOL OnInitDialog();
	afx_msg void OnFadeType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline CDblRange CCodeFade::GetRange() const
{
	return(CDblRange(m_Start, m_End));
}

inline bool CCodeFade::IsLog() const
{
	return(m_Log != 0);
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeFade_H__7D9CE819_5400_475B_BBC0_4440492DD2BC__INCLUDED_)
