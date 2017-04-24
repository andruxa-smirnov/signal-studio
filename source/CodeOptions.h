// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeOptions_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_)
#define AFX_CodeOptions_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeOptions dialog

#include "CodeOptionsInfo.h"
#include "OptViewDlg.h"
#include "OptAudioDlg.h"
#include "OptEditDlg.h"
#include "OptRTSADlg.h"
#include "OptCodeRecord.h"

class CCodeOptions : public CPropertySheet
{
	DECLARE_DYNAMIC(CCodeOptions)
// Construction
public:
	CCodeOptions(UINT nIDCaption, CCodeOptionsInfo& Options, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Constants
	#define OPTIONSPAGEDEF(name) PAGE_##name,
	enum {
		#include "OptPages.h"	// enumerate property pages
		OPTIONS_PAGES
	};

// Attributes
	int		GetCurPage() const;

// Operations
	void	RestoreDefaults();
	const CCodeOptionsInfo&	GetDefaults() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeOptions)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
// Generated message map functions
	//{{AFX_MSG(CCodeOptions)
	afx_msg void OnDestroy();
	afx_msg void OnResetAll();
	//}}AFX_MSG
	afx_msg LRESULT	OnKickIdle(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Constants
	static const int	m_PageOffset[OPTIONS_PAGES];	// page offsets

// Member data
	CCodeOptionsInfo&	m_oi;			// reference to current options
	#define OPTIONSPAGEDEF(name) COpts##name##Dlg m_##name##Dlg;
	#include "OptPages.h"		// allocate property pages
	CButton	m_ResetAll;				// reset all button
	int		m_CurPage;				// index of current page

// Helpers
	void	CreateResetAllButton();
};

inline int CCodeOptions::GetCurPage() const
{
	return(m_CurPage);
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeOptions_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_)
