// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_FnAmplify_H__18F96C57_B828_4C06_BC61_15B82D362DBC__INCLUDED_)
#define AFX_FnAmplify_H__18F96C57_B828_4C06_BC61_15B82D362DBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FnAmplify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFnAmplify dialog

class CFnAmplify : public CDialog
{
// Construction
public:
	CFnAmplify(double Peak, CWnd* pParent = NULL);
	~CFnAmplify();

// Attributes
	double	GetGain() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFnAmplify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CFnAmplify)
	enum { IDD = IDD_AMPLIFY };
	CStatic	m_Clip;
	CEdit	m_PeakEdit;
	double	m_Gain;
	//}}AFX_DATA

// Generated message map functions
	//{{AFX_MSG(CFnAmplify)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusGain();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Member data
	double	m_Peak;		// initial peak loudness in decibels
	double	m_PrevGain;	// previous gain in case user cancels

// Helpers
	void	UpdateUI(double Gain);
};

inline double CFnAmplify::GetGain() const
{
	return(m_Gain);
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FnAmplify_H__18F96C57_B828_4C06_BC61_15B82D362DBC__INCLUDED_)
