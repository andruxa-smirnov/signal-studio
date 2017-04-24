// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeShade_H__E2FC8C22_2FF5_4CD2_B5E4_A912A9EAB77F__INCLUDED_)
#define AFX_CodeShade_H__E2FC8C22_2FF5_4CD2_B5E4_A912A9EAB77F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeShade.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeShade window

class CCodeShade : public CButton
{
	DECLARE_DYNAMIC(CCodeShade)
// Construction
public:
	CCodeShade();

// Attributes
public:
	COLORREF	GetColor() const;
	void	SetColor(COLORREF Color);

// Operations
public:
	bool	EditColor(COLORREF *CustomColors);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeShade)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCodeShade();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCodeShade)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnSetState(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Constants
	enum {
		SWATCH_MARGIN = 5,		// swatch margin in pixels
		PUSHED_OFFSET = 1,		// pushed offset in pixels
	};

// Member data
	CStatic	m_Swatch;			// swatch overlay
	COLORREF	m_Color;		// swatch color

// Helpers
	void	GetSwatchRect(CRect& Rect) const;
};

inline COLORREF CCodeShade::GetColor() const
{
	return(m_Color);
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeShade_H__E2FC8C22_2FF5_4CD2_B5E4_A912A9EAB77F__INCLUDED_)
