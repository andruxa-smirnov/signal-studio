// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeMetadataDlg_H__207C23D0_78D6_4AAB_867C_1DFA5E4C7817__INCLUDED_)
#define AFX_CodeMetadataDlg_H__207C23D0_78D6_4AAB_867C_1DFA5E4C7817__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeMetadataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeMetadataDlg dialog

#include "CodePersist.h"
#include "ControlResizer.h"
#include "EditSubitemListController.h"

class CCodeMetadataDlg : public CCodePersist
{
// Construction
public:
	CCodeMetadataDlg(CStringArray& Metadata, CWnd* pParent = NULL);

// Constants
	#define METADATASTR(sndfile_str, id3v2_tag, wav_tag) STR_##sndfile_str,
	enum {
		#include "MetadataStrhead.h"	// generate metadata string enum
		STRINGS
	};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeMetadataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CCodeMetadataDlg)
	enum { IDD = IDD_METADATA };
	CEditSubitemListController	m_List;
	//}}AFX_DATA

// Generated message map functions
	//{{AFX_MSG(CCodeMetadataDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	virtual void OnOK();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Types
	struct COL_INFO {	// column info
		int		NameID;			// column's name as a string resource ID
		int		Width;			// column's default width
	};

// Constants
	enum {
		COL_NAME,
		COL_VALUE,
		COLUMNS
	};
	static const CControlResizer::CTRL_LIST	m_CtrlList[];
	static const COL_INFO	m_ColInfo[COLUMNS];
	static const int	m_StrNameID[STRINGS];

// Member data
	CSize	m_InitSize;			// dialog's initial size in window coords
	CControlResizer	m_Resize;		// control resizer
	CStringArray&	m_Metadata;	// array of metadata strings

// Helpers
	static	bool	StoreColumnWidths(CListCtrl& List, LPCTSTR Key);
	static	bool	LoadColumnWidths(CListCtrl& List, LPCTSTR Key);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeMetadataDlg_H__207C23D0_78D6_4AAB_867C_1DFA5E4C7817__INCLUDED_)
