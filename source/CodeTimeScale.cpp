// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// TimeCodeRulerControl.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "TimeCodeRulerControl.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeCodeRulerControl

IMPLEMENT_DYNAMIC(CTimeCodeRulerControl, CZoomCodeRulerControl)

CTimeCodeRulerControl::CTimeCodeRulerControl()
{
}

CTimeCodeRulerControl::~CTimeCodeRulerControl()
{
}

void CTimeCodeRulerControl::GetTargetRect(CRect& Rect) const
{
	Rect = CRect(CPoint(0, 0), GetView()->GetPageSize());
}

void CTimeCodeRulerControl::OnDrop(UINT Flags, CPoint Point) 
{
	CSignalStudioView	*View = GetView();
	int	offset = View->GetTimeRulerOffset();
	Point.x += offset;	// correct for ruler's offset relative to view
	m_DragOrigin.x += offset;
	Point.x = CLAMP(Point.x, 0, View->GetWndSize().cx);	// clamp point to target
	int	dx = Point.x - m_DragOrigin.x;
	double	DeltaZoom = double(abs(dx)) / View->GetWndSize().cx;
	double	zoom = View->GetZoom();
	if (Flags & MK_SHIFT)	// if shift key pressed
		zoom /= DeltaZoom;	// zoom out
	else	// no modifier key
		zoom *= DeltaZoom;	// zoom in
	int	x = min(Point.x, m_DragOrigin.x);
	View->SetZoom(x, zoom);
	View->ScrollToPosition(View->GetScrollPosition() + x);
}

void CTimeCodeRulerControl::StepZoom(CPoint Point, bool In)
{
	CRect	rc;
	GetClientRect(rc);
	if (rc.PtInRect(Point)) {	// if cursor within ruler
		CSignalStudioView	*View = GetView();
		if (!View->GetWave().IsEmpty()) {	// if non-empty wave
			int	x = Point.x + View->GetTimeRulerOffset();
			View->StepZoom(x, In);	// step zoom
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTimeCodeRulerControl message map

BEGIN_MESSAGE_MAP(CTimeCodeRulerControl, CZoomCodeRulerControl)
	//{{AFX_MSG_MAP(CTimeCodeRulerControl)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeCodeRulerControl message handlers

void CTimeCodeRulerControl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_DragState == DRAG_TRACK)	// if tracking cursor for potential drag
		StepZoom(point, TRUE);	// drag threshold wasn't reached; step zoom in instead
	CZoomCodeRulerControl::OnLButtonUp(nFlags, point);
}

void CTimeCodeRulerControl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	StepZoom(point, FALSE);	// step zoom out
	CZoomCodeRulerControl::OnRButtonUp(nFlags, point);
}
