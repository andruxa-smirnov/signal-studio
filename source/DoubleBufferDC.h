// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_DoubleBufferDC_H__8DA580FF_35B7_464A_BC56_4AF82D60B1FE__INCLUDED_)
#define AFX_DoubleBufferDC_H__8DA580FF_35B7_464A_BC56_4AF82D60B1FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoubleBufferDC.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoubleBufferDC window

class CDoubleBufferDC : public CDC
{
// Construction
public:
	CDoubleBufferDC();
	BOOL	Create(CWnd *pWnd);

// Operations
public:
	BOOL	CreateBackBuffer(int Width, int Height);
	void	DestroyBackBuffer();

// Implementation
public:
	virtual ~CDoubleBufferDC();

protected:
// Member data
	CBitmap	m_BackBuf;			// back buffer
	HGDIOBJ	m_PrevBmp;			// previously selected bitmap
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DoubleBufferDC_H__8DA580FF_35B7_464A_BC56_4AF82D60B1FE__INCLUDED_)
