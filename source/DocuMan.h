// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_DocuMan_H__ED62E7B1_7F4E_4DC3_92D2_75B32CDFBBBB__INCLUDED_)
#define AFX_DocuMan_H__ED62E7B1_7F4E_4DC3_92D2_75B32CDFBBBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DocuMan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDocuMan

#include "SignalFileFormat.h"

class CDocuMan : public CDocManager {
	DECLARE_DYNAMIC(CDocuMan);
public:
// Construction
	CDocuMan();

// Types
	class CFileDialogEx : public CFileDialog {
	public:
		CFileDialogEx(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL);
		virtual void OnTypeChange();
		bool	SetFileName(CString FileName);
		CSignalFileFormatArray	*m_SignalFileFormat;
	};

// Attributes
	int		GetAudioFormat() const;
	void	SetAudioFormat(int Format);
	static	bool	GetFileFilter(CString& Filter, BOOL bOpenFileDialog, CSignalFileFormatArray *pSignalFileFormat = NULL);
	static	CString	GetAliasedExtension(int Format, CString Extension);
	static	CString	GetAllFilter();

// Overrides
	virtual	BOOL	DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);

protected:
// Types
	struct EXT_ALIAS {	// extension alias
		int		Format;			// sndfile major format
		int		Exts;			// number of extensions
		const LPCTSTR	*Ext;	// array of pointers to extensions
	};

// Constants
	static const EXT_ALIAS	m_ExtAlias[];	// array of extension aliases

// Data members
	int		m_AudioFormat;			// libsndfile audio format
};

inline int CDocuMan::GetAudioFormat() const
{
	return(m_AudioFormat);
}

inline void CDocuMan::SetAudioFormat(int Format)
{
	m_AudioFormat = Format;
}

inline CDocuMan::CFileDialogEx::CFileDialogEx(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName, DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd)
	: CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DocuMan_H__ED62E7B1_7F4E_4DC3_92D2_75B32CDFBBBB__INCLUDED_)
