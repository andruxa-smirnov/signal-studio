// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// ClickSliderController.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "ClickSliderController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClickSliderController

IMPLEMENT_DYNAMIC(CClickSliderController, CSliderCtrl);

CClickSliderController::CClickSliderController()
{
	m_DefPos = 0;
}

CClickSliderController::~CClickSliderController()
{
}

int CClickSliderController::PointToPos(CPoint point)
{
	int	rmin, rmax, rwid;
	GetRange(rmin, rmax);
	rwid = rmax - rmin;
	CRect	cr, tr;
	GetChannelRect(cr);
	GetThumbRect(tr);
	int pos = rmin + rwid * (point.x - cr.left - tr.Width() / 2)
		/ (cr.Width() - tr.Width());
	return(min(max(pos, rmin), rmax));	// clamp to range
}

void CClickSliderController::PostPos()
{
	GetParent()->PostMessage(WM_HSCROLL,
		MAKELONG(SB_THUMBTRACK, GetPos()), long(this->m_hWnd));
}

void CClickSliderController::PostNotification(int Code)
{
	GetParent()->PostMessage(WM_HSCROLL, Code, long(this->m_hWnd));
}

void CClickSliderController::SetTicCount(int Count)
{
	int	lo, hi;
	GetRange(lo, hi);
	SetTicFreq(Count > 0 ? ((hi - lo) / (Count - 1)) : 0);
}

BEGIN_MESSAGE_MAP(CClickSliderController, CSliderCtrl)
	//{{AFX_MSG_MAP(CClickSliderController)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClickSliderController message handlers

void CClickSliderController::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (nFlags & MKU_DEFAULT_POS) {	// restore default position
		SetPos(m_DefPos);
		PostPos();	// post HScroll to parent window
		SetFocus();	// must do this because we're not calling base class
		return;
	}
	CRect	tr;
	GetThumbRect(tr);
	if (!tr.PtInRect(point))	// if click was within thumb, don't jump
		SetPos(PointToPos(point));
	// We need to call the base class for capture and mouse move handling, but
	// the base class also sets the current position, potentially altering the
	// position we just set. The base class jumps to the nearest page boundary,
	// so its position could differ significantly from ours, particularly for
	// small ranges. We fix this by temporarily setting the page size to one.
	int PageSize = GetPageSize();	// save page size
	SetPageSize(1);	// disable paging so base class doesn't change position
	CSliderCtrl::OnLButtonDown(nFlags, point);	// do base class behavior
	SetPageSize(PageSize);	// restore page size
	// if click was outside channel, MFC doesn't post HScroll
	CRect	cr;
	GetChannelRect(cr);
	if (!cr.PtInRect(point))
		PostPos();
}

void CClickSliderController::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// un-reverse arrow up/down, page up/page down
	switch (nChar) {
	case VK_UP:
		SetPos(GetPos() + GetLineSize());
		PostNotification(TB_LINEUP);
		return;
	case VK_DOWN:
		SetPos(GetPos() - GetLineSize());
		PostNotification(TB_LINEDOWN);
		return;
	case VK_PRIOR:
		SetPos(GetPos() + GetPageSize());
		PostNotification(TB_PAGEUP);
		return;
	case VK_NEXT:
		SetPos(GetPos() - GetPageSize());
		PostNotification(TB_PAGEDOWN);
		return;
	}
	CSliderCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CClickSliderController::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// un-reverse wheel
	if (zDelta > 0)
		OnKeyDown(VK_UP, 0, 0);
	else
		OnKeyDown(VK_DOWN, 0, 0);
	return(TRUE);
}
