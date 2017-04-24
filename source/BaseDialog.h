// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_BaseDialog_H__9D725823_F782_4C58_BBB8_01B240B648CA__INCLUDED_)
#define AFX_BaseDialog_H__9D725823_F782_4C58_BBB8_01B240B648CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseDialog.h : header file
//

#include "ControlResizer.h"

/////////////////////////////////////////////////////////////////////////////
// CBaseDialog dialog

class CBaseDialog : public CDialogBar
{
	DECLARE_DYNAMIC(CBaseDialog);
public:
// Construction
	CBaseDialog(UINT nIDAccel = 0);
	virtual ~CBaseDialog();
	BOOL	Create(CWnd *pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	BOOL	Create(CFrameWnd *pFrameWnd, UINT nIDTemplate, UINT nStyle,
				   DWORD dwDockStyle, UINT nBarID, CControlBar *LeftOf);

// Constants
	enum {	// option flags
		OPT_HORZ_RESIZE = 0x01,
		OPT_VERT_RESIZE = 0x02
	};
	enum {
		GRIPPER_SIZE = 6
	};

// Attributes
	CSize	GetMargin() const;
	int		GetLeftMargin() const;
	int		GetTopMargin() const;
	void	SetBarCaption(LPCTSTR Text);
	void	SetWindowText(LPCTSTR lpszString);
	int		GetBarOptions() const;
	void	SetBarOptions(int Options);

// Operations
	virtual	BOOL	EnableToolTips(BOOL bEnable);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CBaseDialog)
	//}}AFX_DATA

// Generated message map functions
	//{{AFX_MSG(CBaseDialog)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnToolTipText(UINT id, NMHDR* pTTTStruct, LRESULT* pResult);
	afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Constants
	static const int	CAP_MARGIN;

// Member data
	CSize	m_DockedSize;
	CSize	m_FloatingSize;
	BOOL	m_bChangeDockedSize;
	HACCEL	m_Accel;
	CStatic	m_Caption;
	CRect	m_CapRect;
	CSize	m_CapSize;
	CSize	m_Margin;
	CControlResizer	m_Resize;
	int		m_PrevFloating;
	bool	m_GotMRUWidth;
	int		m_Options;
};

inline CSize CBaseDialog::GetMargin() const
{
	return(m_Margin);
}

inline int CBaseDialog::GetLeftMargin() const
{
	return(m_Margin.cx);
}

inline int CBaseDialog::GetTopMargin() const
{
	return(m_Margin.cy);
}

inline int CBaseDialog::GetBarOptions() const
{
	return(m_Options);
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BaseDialog_H__9D725823_F782_4C58_BBB8_01B240B648CA__INCLUDED_)
