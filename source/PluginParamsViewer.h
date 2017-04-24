// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_PluginParamsViewer_H__41F0C35F_CE2D_4B55_94C4_93D4A13D8E8F__INCLUDED_)
#define AFX_PluginParamsViewer_H__41F0C35F_CE2D_4B55_94C4_93D4A13D8E8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PluginParamsViewer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPluginParamsViewer form view

#include "ControlResizer.h"
#include "Plugin.h"
#include "PluginParameters.h"

class CPluginParamsViewer : public CScrollView
{
public:
	CPluginParamsViewer();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPluginParamsViewer)

// Attributes
public:
	int		GetRowCount() const;
	const _LADSPA_Descriptor	*GetDescriptor() const;
	void	GetParams(CPlugin::CParamArray& Param) const;
	bool	SetParams(const CPlugin::CParamArray& Param);

// Operations
public:
	bool	InitRows(LPCTSTR Path, UINT SampleRate);
	void	RestoreDefaults();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPluginParamsViewer)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPluginParamsViewer();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
	//{{AFX_MSG(CPluginParamsViewer)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	afx_msg void OnEditKillFocus(UINT nID);
	DECLARE_MESSAGE_MAP()

// Types
	typedef CArrayEx<CPluginParameters, CPluginParameters&> CParamRowArray;

// Data members
	CControlResizer	m_Resize;		// control resizer
	CParamRowArray	m_Row;		// array of plugin parameter rows
	CDLLWrap	m_Dll;			// plugin DLL instance
	const _LADSPA_Descriptor	*m_Desc;	// LADSPA plugin descriptor
};

inline int CPluginParamsViewer::GetRowCount() const
{
	return(m_Row.GetSize());
}

inline const _LADSPA_Descriptor *CPluginParamsViewer::GetDescriptor() const
{
	return(m_Desc);
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PluginParamsViewer_H__41F0C35F_CE2D_4B55_94C4_93D4A13D8E8F__INCLUDED_)
