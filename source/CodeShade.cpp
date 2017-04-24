// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// CodeShade.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "CodeShade.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeShade

IMPLEMENT_DYNAMIC(CCodeShade, CButton);

CCodeShade::CCodeShade()
{
	m_Color = 0;
}

CCodeShade::~CCodeShade()
{
}

void CCodeShade::SetColor(COLORREF Color)
{
	m_Color = Color;
	m_Swatch.Invalidate();
}

void CCodeShade::GetSwatchRect(CRect& Rect) const
{
	GetClientRect(Rect);
	Rect.DeflateRect(SWATCH_MARGIN, SWATCH_MARGIN);
}

bool CCodeShade::EditColor(COLORREF *CustomColors)
{
	ASSERT(CustomColors != NULL);	// caller must allocate custom colors
	CColorDialog	dlg;
	dlg.m_cc.Flags |= CC_RGBINIT;
	dlg.m_cc.lpCustColors = CustomColors;
	dlg.m_cc.rgbResult = m_Color;
	if (dlg.DoModal() != IDOK)
		return(FALSE);
	SetColor(dlg.m_cc.rgbResult);
	return(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CCodeShade message map

BEGIN_MESSAGE_MAP(CCodeShade, CButton)
	//{{AFX_MSG_MAP(CCodeShade)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(BM_SETSTATE, OnSetState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeShade message handlers

void CCodeShade::PreSubclassWindow() 
{
	CRect	rSwatch;
	GetSwatchRect(rSwatch);
	m_Swatch.Create(NULL, WS_CHILD | WS_VISIBLE, rSwatch, this);
	ModifyStyle(0, WS_CLIPCHILDREN);	// clip button around swatch
	CButton::PreSubclassWindow();
}

HBRUSH CCodeShade::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	SetDCBrushColor(pDC->m_hDC, m_Color);
	return (HBRUSH)GetStockObject(DC_BRUSH);
}

LRESULT CCodeShade::OnSetState(WPARAM wParam, LPARAM lParam)
{
	CRect	rSwatch;
	GetSwatchRect(rSwatch);
	if (wParam)	// if pushed
		rSwatch += CSize(PUSHED_OFFSET, PUSHED_OFFSET);	// offset swatch
	m_Swatch.MoveWindow(rSwatch);	// move swatch to updated position
	return Default();
}
