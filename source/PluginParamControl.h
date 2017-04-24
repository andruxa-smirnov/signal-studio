// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_PluginParamControl_H__BDEF99F6_639B_4E98_936E_C8CCD3D8CAC9__INCLUDED_)
#define AFX_PluginParamControl_H__BDEF99F6_639B_4E98_936E_C8CCD3D8CAC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PluginParamControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPluginParamControl dialog

#include "CodePersist.h"
#include "ControlResizer.h"
#include "Plugin.h"

class CPluginParamsViewer;

class CPluginParamControl : public CCodePersist
{
public:
// Construction
	CPluginParamControl(LPCTSTR Path, UINT SampleRate, CPlugin::CParamArray& Param, CWnd* pParent = NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPluginParamControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CPluginParamControl)
	enum { IDD = IDD_PLUGIN_PARAM };
	//}}AFX_DATA

// Generated message map functions
	//{{AFX_MSG(CPluginParamControl)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	virtual void OnOK();
	afx_msg void OnReset();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Constants
	static const CControlResizer::CTRL_LIST	m_CtrlList[];

// Data members
	CSize	m_InitSize;			// dialog's initial size in window coords
	CControlResizer	m_Resize;		// control resizer
	CString	m_PluginPath;		// plugin path
	UINT	m_SampleRate;		// audio sample rate in Hertz
	CPlugin::CParamArray&	m_Param;	// reference to caller's parameter array
	CPluginParamsViewer	*m_View;	// pointer to parameter view

// Helpers
	bool	CreateView();
	void	GetViewHolderRect(CRect& Rect) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PluginParamControl_H__BDEF99F6_639B_4E98_936E_C8CCD3D8CAC9__INCLUDED_)
