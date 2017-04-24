// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeDlg_H__1C442729_89BB_414E_A7EA_9FE11945D043__INCLUDED_)
#define AFX_CodeDlg_H__1C442729_89BB_414E_A7EA_9FE11945D043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeDlg dialog

#include "SignalProcess.h"

class CCodeDlg : public CDialog
{
// Construction
public:
	CCodeDlg(CWnd* pParent = NULL);   // standard constructor
	~CCodeDlg();

// Dialog Data
	//{{AFX_DATA(CCodeDlg)
	enum { IDD = IDD_FIND };
	double	m_TargetStart;
	double	m_TargetEnd;
	int		m_Unit;
	int		m_Match;
	int		m_Dir;
	BOOL	m_Wrap;
	CComboBox	m_ChannelCombo;
	//}}AFX_DATA
	int		m_Channel;	// index of channel to search, or -1 for all channels

// Types
	typedef CSignalProcess::CSampleRange CSampleRange;

// Attributes
	CSampleRange	GetTargetRange() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Generated message map functions
	//{{AFX_MSG(CCodeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg void OnUnit(UINT nID);
	DECLARE_MESSAGE_MAP()

// Helpers
	CDblRange	GetTargetRange(int Unit) const;
	void	SetTargetRange(CDblRange Target, int Unit);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeDlg_H__1C442729_89BB_414E_A7EA_9FE11945D043__INCLUDED_)
