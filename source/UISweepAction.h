// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_UISweepAction_H__5C95AFC3_EA1D_4DED_BEF6_599047F85189__INCLUDED_)
#define AFX_UISweepAction_H__5C95AFC3_EA1D_4DED_BEF6_599047F85189__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UISweepAction.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUISweepAction dialog

class CUISweepAction : public CDialog
{
// Construction
public:
	CUISweepAction(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUISweepAction)
	enum { IDD = IDD_SWEEP };
	CComboBox	m_WaveformCombo;
	double	m_Duration;
	double	m_EndFreq;
	double	m_StartFreq;
	//}}AFX_DATA
	int		m_Waveform;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUISweepAction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Generated message map functions
	//{{AFX_MSG(CUISweepAction)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Helpers
	static	void	DDV_GTZeroDouble(CDataExchange *pDX, int nIDC, double& value);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UISweepAction_H__5C95AFC3_EA1D_4DED_BEF6_599047F85189__INCLUDED_)
