// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_DragRulerController_H__490CA5D7_29D1_4381_9849_416A9904451A__INCLUDED_)
#define AFX_DragRulerController_H__490CA5D7_29D1_4381_9849_416A9904451A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DragRulerController.h : header file
//

#include "CodeRulerControl.h"

/////////////////////////////////////////////////////////////////////////////
// CDragRulerController window

class CDragRulerController : public CCodeRulerControl
{
	DECLARE_DYNAMIC(CDragRulerController)
// Construction
public:
	CDragRulerController();

// Attributes
public:

// Operations
public:
	virtual	void	EndDrag();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragRulerController)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDragRulerController();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDragRulerController)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Types

// Constants
	enum {	// drag states
		DRAG_NONE,			// default state
		DRAG_TRACK,			// tracking potential drag
		DRAG_ACTIVE,		// drag in progress
	};

// Data members
	int		m_DragState;		// drag state, see enum above
	CPoint	m_DragOrigin;		// drag initial point, in client coords

// Overridables
	virtual	void	OnDragBegin(UINT Flags, CPoint Point);
	virtual	void	OnDrop(UINT Flags, CPoint Point);

// Helpers
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DragRulerController_H__490CA5D7_29D1_4381_9849_416A9904451A__INCLUDED_)
