// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// DoubleBufferDC.cpp : implementation file

#include "stdafx.h"
#include "DoubleBufferDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoubleBufferDC

CDoubleBufferDC::CDoubleBufferDC()
{
	m_PrevBmp = NULL;
}

CDoubleBufferDC::~CDoubleBufferDC()
{
	DestroyBackBuffer();
}

BOOL CDoubleBufferDC::Create(CWnd *pWnd)
{
	CClientDC	dc(pWnd);
	return(CreateCompatibleDC(&dc));
}

BOOL CDoubleBufferDC::CreateBackBuffer(int Width, int Height)
{
	DestroyBackBuffer();
	CClientDC	dc(GetWindow());
	if (!m_BackBuf.CreateCompatibleBitmap(&dc, Width, Height))
		return(FALSE);	// can't create back buffer
	m_PrevBmp = SelectObject(m_BackBuf);
	return(TRUE);
}

void CDoubleBufferDC::DestroyBackBuffer()
{
	if (m_PrevBmp != NULL) {	// if previous back buffer exists
		SelectObject(m_PrevBmp);
		m_BackBuf.DeleteObject();	// delete previous back buffer
		m_PrevBmp = NULL;
	}
}
