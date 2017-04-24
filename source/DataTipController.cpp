// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// DataTipController.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "DataTipController.h"
#include "DPointer.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataTipController

IMPLEMENT_DYNAMIC(CDataTipController, CToolTipCtrl)

CDataTipController::CDataTipController()
{
	m_Pos = CPoint(0, 0);
	m_DataPos = CPoint(0, 0);
	m_Epsilon = GetSystemMetrics(SM_CXDRAG);
}

CDataTipController::~CDataTipController()
{
}

double CDataTipController::DistancePointToLine(const DPointer& Pt, const DPointer& P1, const DPointer& P2)
{
	double	p = (P2.y - Pt.y) * (P2.y - P1.y) - (P2.x - Pt.x) * (P1.x - P2.x);
	DPointer	d(P1 - P2);
	p = p / (d.x * d.x + d.y * d.y);
	DPointer	c(P1 * p + P2 * (1 - p));
	d = c - Pt;
	double	dist = sqrt(d.x * d.x + d.y * d.y);
	return(dist);
}

void CDataTipController::OnMouseMove(MSG *pMsg)
{
	CPoint	point;
	POINTSTOPOINT(point, MAKEPOINTS(pMsg->lParam));
	CPoint	DataPos;
	bool	found = FinDPointer(point, DataPos);
	if (IsWindowVisible()) {	// if tip active
		// if cursor not near tip position
		if (!PointsNear(point, m_Pos)) {
			if (found) {	// if cursor near data point
				// if cursor's data point differs from tip's
				if (DataPos != m_DataPos) {
					m_Pos = point;
					m_DataPos = DataPos;
					Update();	// update tip
				}
			} else	// cursor not near data point
				Activate(FALSE);	// deactivate tip
		}
	} else {	// tip inactive
		if (found) {	// if cursor near data point
			m_Pos = point;
			m_DataPos = DataPos;
			Activate(TRUE);	// activate tip
		}
	}
	RelayEvent(pMsg);	// relay mouse events to tip
}

/////////////////////////////////////////////////////////////////////////////
// CDataTipController message map

BEGIN_MESSAGE_MAP(CDataTipController, CToolTipCtrl)
	//{{AFX_MSG_MAP(CDataTipController)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataTipController message handlers

void CDataTipController::OnTimer(W64UINT nIDEvent) 
{
	enum {
		AUTOPOP_TIMER_ID = 4,	// depending on a private detail here
	};
	// if autopop delay time has maximum allowed value (limited to 16-bit)
	if (nIDEvent == AUTOPOP_TIMER_ID && GetDelayTime(TTDT_AUTOPOP) == SHRT_MAX)
		return;	// disable autopop completely by eating timer event
	CToolTipCtrl::OnTimer(nIDEvent);
}
