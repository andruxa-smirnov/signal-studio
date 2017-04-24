// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// DragRulerController.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "DragRulerController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragRulerController

IMPLEMENT_DYNAMIC(CDragRulerController, CCodeRulerControl)

CDragRulerController::CDragRulerController()
{
	m_DragState = DRAG_NONE;
	m_DragOrigin = CPoint(0, 0);
}

CDragRulerController::~CDragRulerController()
{
}

void CDragRulerController::EndDrag()
{
	ReleaseCapture();	// release mouse input
	m_DragState = DRAG_NONE;	// reset drag state
}

void CDragRulerController::OnDragBegin(UINT Flags, CPoint Point)
{
}

void CDragRulerController::OnDrop(UINT Flags, CPoint Point)
{
}

/////////////////////////////////////////////////////////////////////////////
// CDragRulerController message map

BEGIN_MESSAGE_MAP(CDragRulerController, CCodeRulerControl)
	//{{AFX_MSG_MAP(CDragRulerController)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragRulerController message handlers

void CDragRulerController::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_DragState = DRAG_TRACK;	// begin tracking possible drag
	m_DragOrigin = point;	// store drag origin
	SetCapture();	// capture mouse input
	CCodeRulerControl::OnLButtonDown(nFlags, point);
}

void CDragRulerController::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_DragState != DRAG_NONE) {
		if (m_DragState == DRAG_ACTIVE)
			OnDrop(nFlags, point);
		EndDrag();
	}
	CCodeRulerControl::OnLButtonUp(nFlags, point);
}

void CDragRulerController::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_DragState == DRAG_TRACK) {
		int	delta;
		if (IsVertical())
			delta = abs(point.y - m_DragOrigin.y);	// track vertical motion only
		else	// horizontal
			delta = abs(point.x - m_DragOrigin.x);	// track horizontal motion only
		int	DragThreshold = GetSystemMetrics(SM_CXDRAG);
		// if mouse motion relative to origin exceeds drag threshold
		if (delta >= DragThreshold) {
			m_DragState = DRAG_ACTIVE;	// set drag state to active
			OnDragBegin(nFlags, point);
			SetFocus();	// take focus so we receive keyboard input
			// recurse to update UI; safe due to changed drag state
			OnMouseMove(nFlags, point);
		}
	}
	CCodeRulerControl::OnMouseMove(nFlags, point);
}

void CDragRulerController::OnKillFocus(CWnd* pNewWnd) 
{
	CCodeRulerControl::OnKillFocus(pNewWnd);
	if (m_DragState != DRAG_NONE)
		EndDrag();
}

BOOL CDragRulerController::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) {
		if (m_DragState != DRAG_NONE)
			EndDrag();
		return TRUE;	// no further dispatching
	}
	return CCodeRulerControl::PreTranslateMessage(pMsg);
}
