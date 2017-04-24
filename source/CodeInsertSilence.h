// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeInsertSilence_H__FB135965_AF25_4747_A712_B1F68A730437__INCLUDED_)
#define AFX_CodeInsertSilence_H__FB135965_AF25_4747_A712_B1F68A730437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeInsertSilence.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeInsertSilence dialog

class CCodeInsertSilence : public CDialog
{
// Construction
public:
	CCodeInsertSilence(UINT SampleRate, CWnd* pParent = NULL);
	~CCodeInsertSilence();

// Attributes
	W64INT	GetFrameCount() const;
	double	GetDuration() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeInsertSilence)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CCodeInsertSilence)
	enum { IDD = IDD_INSERT_SILENCE };
	CString	m_LengthEdit;
	CString	m_Unit;
	//}}AFX_DATA

// Generated message map functions
	//{{AFX_MSG(CCodeInsertSilence)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Member data
	UINT	m_SampleRate;	// sample rate in Hz
	double	m_Duration;		// duration in seconds
};

inline double CCodeInsertSilence::GetDuration() const
{
	return(m_Duration);
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeInsertSilence_H__FB135965_AF25_4747_A712_B1F68A730437__INCLUDED_)
