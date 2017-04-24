// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_OptCodeRecord_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_)
#define AFX_OptCodeRecord_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptCodeRecord.h : header file

/////////////////////////////////////////////////////////////////////////////
// COptCodeRecord dialog

#include "CodeOptionsInfo.h"

class COptCodeRecord : public CPropertyPage
{
// Construction
public:
	COptCodeRecord(CCodeOptionsInfo& Info);

// Attributes

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptCodeRecord)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Generated message map functions
	//{{AFX_MSG(COptCodeRecord)
	virtual BOOL OnInitDialog();
	afx_msg void OnFolderBrowse();
	afx_msg void OnSelchangeHotKeyFunction();
	//}}AFX_MSG
	afx_msg LRESULT	OnKickIdle(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateFolderPath(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTriggers(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

// Dialog data
	//{{AFX_DATA(COptCodeRecord)
	enum { IDD = IDD_OPT_RECORD };
	CComboBox	m_HotKeyFunction;
	CHotKeyCtrl	m_HotKey;
	CComboBox	m_SampleSizeCombo;
	CComboBox	m_SampleRateCombo;
	int		m_Activation;
	CString	m_Folder;
	//}}AFX_DATA

// Constants

// Member data
	CCodeOptionsInfo&	m_oi;		// reference to parent's options info 
	int		m_SelHotKeyFunc;	// index of selected hot key function

// Helpers
	int		GetActivationType();
	static	DWORD	GetSysHotKey(const CHotKeyCtrl& HotKeyCtrl);
	static	void	SetSysHotKey(CHotKeyCtrl& HotKeyCtrl, DWORD HotKeyDef);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OptCodeRecord_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_)
