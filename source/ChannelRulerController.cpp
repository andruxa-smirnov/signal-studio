// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// ChannelRulerController.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "ChannelRulerController.h"
#include "ChannelBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelRulerController

IMPLEMENT_DYNAMIC(CChannelRulerController, CZoomCodeRulerControl)

CChannelRulerController::CChannelRulerController()
{
	m_Origin = 0;
	m_Amplitude = 1;
}

CChannelRulerController::~CChannelRulerController()
{
}

void CChannelRulerController::GetTargetRect(CRect& Rect) const
{
	CSignalStudioView	*View = STATIC_DOWNCAST(CSignalStudioView, m_Target);
	CRect	rTarget;
	GetClientRect(rTarget);
	MapWindowPoints(View, rTarget);
	rTarget.left = 0;
	rTarget.right = View->GetPageSize().cx;
	Rect = rTarget;
}

int CChannelRulerController::GetRulerIndex() const
{
	CChannelBar	*Bar = STATIC_DOWNCAST(CChannelBar, GetParent());
	int	iChan = Bar->FindRuler(this);
	ASSERT(iChan >= 0);
	return(iChan);
}

void CChannelRulerController::OnDrop(UINT Flags, CPoint Point)
{
	int	iChan = GetRulerIndex();
	CSignalStudioView	*View = STATIC_DOWNCAST(CSignalStudioView, m_Target);
	CRect	rTarget;
	GetTargetRect(rTarget);
	int	height = rTarget.Height();
	Point.y = CLAMP(Point.y, 0, height);	// clamp point to target
	int	dy = Point.y - m_DragOrigin.y;
	double	DeltaZoom = double(abs(dy)) / height;
	double	zoom = View->GetAmplitude(iChan);
	double	newzoom;
	if (Flags & MK_SHIFT)	// if shift key pressed
		newzoom = zoom * DeltaZoom;	// zoom out
	else	// no modifier key
		newzoom = zoom / DeltaZoom;	// zoom in
	int	y = min(Point.y, m_DragOrigin.y);
	CPoint	pt(0, y);
	MapWindowPoints(View, &pt, 1);	// convert to view coords
	View->SetVerticalZoom(iChan, pt.y, newzoom);
	double	org = View->GetVerticalOrigin(iChan);
	View->SetVerticalOrigin(iChan, org - double(y) / height);
}

void CChannelRulerController::UpdateZoom(int Height)
{
	double	NominalZoom = CChannelBar::GetNominalZoom();
	// manipulate height to match view as precisely as possible
	SetScrollPosition((Height - 1) / NominalZoom - m_Origin * Height);
	SetZoom(NominalZoom / (Height - 1) / m_Amplitude);
}

void CChannelRulerController::StepZoom(CPoint Point, bool In)
{
	CRect	rc;
	GetClientRect(rc);
	if (rc.PtInRect(Point)) {	// if point within ruler
		int	iChan = GetRulerIndex();
		CSignalStudioView	*View = STATIC_DOWNCAST(CSignalStudioView, m_Target);
		CPoint	pt(Point);
		MapWindowPoints(View, &pt, 1);	// convert to view coords
		View->StepVerticalZoom(iChan, pt.y, In);	// step zoom
	}
}

/////////////////////////////////////////////////////////////////////////////
// CChannelRulerController message map

BEGIN_MESSAGE_MAP(CChannelRulerController, CZoomCodeRulerControl)
	//{{AFX_MSG_MAP(CChannelRulerController)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelRulerController message handlers

void CChannelRulerController::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_DragState == DRAG_TRACK)	// if tracking cursor for potential drag
		StepZoom(point, TRUE);	// drag threshold wasn't reached; step zoom in instead
	CZoomCodeRulerControl::OnLButtonUp(nFlags, point);
}

void CChannelRulerController::OnRButtonUp(UINT nFlags, CPoint point) 
{
	StepZoom(point, FALSE);	// step zoom out
	CZoomCodeRulerControl::OnRButtonUp(nFlags, point);
}
