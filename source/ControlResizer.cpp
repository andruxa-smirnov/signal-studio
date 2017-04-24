// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "ControlResizer.h"

CControlResizer::CControlResizer() 
{
	m_pWnd = NULL;
	m_OrgShift = CSize(0, 0);
}

void CControlResizer::AddControl(int CtrlID, int BindType, const CRect *RectInit)
{
	CtrlInfo	info;
	info.m_CtrlID = CtrlID;
	info.m_BindType = BindType;
	info.m_RectInit = RectInit;
	info.m_hCtrlWnd = NULL;
	m_Info.Add(info);
}

void CControlResizer::AddControlList(CWnd *pWnd, const CTRL_LIST *List)
{
	SetParentWnd(pWnd);
	for (int i = 0; List[i].CtrlID; i++)
		AddControl(List[i].CtrlID, List[i].BindType);
	FixControls();
}

bool CControlResizer::FixControls()
{
	if (!m_pWnd)
		return FALSE;
	m_pWnd->GetClientRect(&m_RectInit);
	HWND	hWnd = m_pWnd->m_hWnd;
	for (int i = 0; i < m_Info.GetSize(); i++) {
		CtrlInfo&	info = m_Info[i];
		info.m_hCtrlWnd = GetDlgItem(hWnd, info.m_CtrlID);
		if (info.m_hCtrlWnd) {
			GetWindowRect(info.m_hCtrlWnd, &info.m_RectInit);
			m_pWnd->ScreenToClient(&info.m_RectInit);
		}
	}
	return TRUE;
}

void CControlResizer::OnSize()
{
	if (!m_pWnd)
		return;
	CRect rr, rectWnd;
	m_pWnd->GetClientRect(&rectWnd);
	HDWP	dwp = BeginDeferWindowPos(INT64TO32(m_Info.GetSize()));
	for (int i = 0; i < m_Info.GetSize(); i++) {
		const CtrlInfo&	info = m_Info[i];
		rr = info.m_RectInit;
		rr.OffsetRect(m_OrgShift);
		if (info.m_BindType & BIND_RIGHT) 
			rr.right = rectWnd.right - (m_RectInit.Width() - info.m_RectInit.right);
		if (info.m_BindType & BIND_BOTTOM) 
			rr.bottom = rectWnd.bottom - (m_RectInit.Height() - info.m_RectInit.bottom);
		if (info.m_BindType & BIND_TOP)
			;
		else
			rr.top = rr.bottom - info.m_RectInit.Height();
		if (info.m_BindType & BIND_LEFT)
			;
		else
			rr.left = rr.right - info.m_RectInit.Width();
		DeferWindowPos(dwp, info.m_hCtrlWnd, NULL,
			rr.left, rr.top, rr.Width(), rr.Height(), SWP_NOZORDER);
	}
	EndDeferWindowPos(dwp);
}
