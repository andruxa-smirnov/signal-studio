// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// SignalStudioDoc.h : interface of the CSignalStudioDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVVIEWDOC_H__19BD38C6_0E43_4888_A08A_636088ADA052__INCLUDED_)
#define AFX_WAVVIEWDOC_H__19BD38C6_0E43_4888_A08A_636088ADA052__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SignalProcess.h"
#include "RetractManager.h"

class CSignalStudioDoc : public CDocument
{
protected: // create from serialization only
	CSignalStudioDoc();
	DECLARE_DYNCREATE(CSignalStudioDoc)

// Types
	class CMyRetractManager : public CRetractManager {
	public:
		CMyRetractManager(CDocument *Doc);

	protected:
		virtual	void	OnModify(bool Modified);
		virtual	void	OnUpdateTitles();
		CDocument	*m_Document;
	};

// Attributes
public:
	CSignalProcess	m_Wave;			// wave
	CMyRetractManager	m_UndoMgr;		// undo manager
	int				m_AudioFormat;	// libsndfile audio format
	CStringArray	m_Metadata;		// audio file metadata strings

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSignalStudioDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSignalStudioDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSignalStudioDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVVIEWDOC_H__19BD38C6_0E43_4888_A08A_636088ADA052__INCLUDED_)
