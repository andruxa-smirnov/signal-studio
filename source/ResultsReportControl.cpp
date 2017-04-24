// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// ResultsReportControl.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "ResultsReportControl.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultsReportControl

IMPLEMENT_DYNAMIC(CResultsReportControl, CReportControl);

const CResultsReportControl::RES_COL	CResultsReportControl::m_ClipColInfo[CLIP_COLS] = {
	{IDS_CLIP_COL_START,	LVCFMT_RIGHT,	100,	DIR_ASC},
	{IDS_CLIP_COL_LENGTH,	LVCFMT_RIGHT,	60,		DIR_ASC},
	{IDS_CLIP_COL_CHANNEL,	LVCFMT_RIGHT,	60,		DIR_ASC},
};

CResultsReportControl	*CResultsReportControl::m_This;

CResultsReportControl::CResultsReportControl()
{
	m_View = NULL;
	m_SortWaitCursor = TRUE;
}

void CResultsReportControl::Update(CSignalProcess::CClipSpanArray& ClipSpan, CSignalStudioView *View)
{
	m_ClipSpan.Swap(ClipSpan);	// take ownership of clip spans via pointer swap
	m_View = View;	// set our owner view
	// defer updating report items until after bar layout is recalculated, 
	// to avoid calling view's EnsureVisible before view's size is updated;
	// also avoids report unexpectedly scrolling vertically by a few items
	PostMessage(UWM_UPDATEITEMS);
}

BOOL CResultsReportControl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle |= WS_EX_CLIENTEDGE;	// add 3D edge to blend with host bar
	if (!CReportControl::PreCreateWindow(cs))
		return FALSE;

	return TRUE;
}

void CResultsReportControl::OnItemSelection(int ItemIdx)
{
	if (m_View != NULL) {	// should always be true but check anyway
		CChildFrame	*Frame = STATIC_DOWNCAST(CChildFrame, m_View->GetParentFrame());
		Frame->MDIActivate();	// activate view
		int	iSortedItem = m_SortIdx[ItemIdx];
		const CSignalProcess::CLIP_SPAN&	span = m_ClipSpan[iSortedItem];
		double	fStart = double(span.Start);
		theApp.GetMain()->SetNow(fStart, TRUE);
	}
}

#define SORT_CMP(x) retc = SortCmp(srv1.x, srv2.x);

int CResultsReportControl::SortCompare(const int *p1, const int *p2) const
{
	const CSignalProcess::CLIP_SPAN&	srv1 = m_ClipSpan[*p1];
	const CSignalProcess::CLIP_SPAN&	srv2 = m_ClipSpan[*p2];
	int	retc;
	switch (SortCol()) {
	case CLIP_COL_START:
		SORT_CMP(Start);
		if (!retc)
			SORT_CMP(Channel);
		break;
	case CLIP_COL_LENGTH:
		SORT_CMP(Length);
		if (!retc)
			SORT_CMP(Start);
		break;
	case CLIP_COL_CHANNEL:
		SORT_CMP(Channel);
		if (!retc)
			SORT_CMP(Start);
		break;
	default:
		NODEFAULTCASE;	// logic error
		retc = 0;
	}
	return(retc);
}

int CResultsReportControl::SortCompare(const void *p1, const void *p2)
{
	return(m_This->SortCompare((const int *)p1, (const int *)p2));
}

void CResultsReportControl::SortRows()
{
	if (m_SortIdx.GetSize() <= 0)
		return;	// nothing to do
	CWaitCursor	wc;	// sort can be slow
	int	sel = GetSelectionMark();
	if (sel >= 0)	// if an item is selected
		sel = m_SortIdx[sel];	// save its sorted index
	m_This = this;	// pass our instance to SortCompare
	qsort(m_SortIdx.GetData(), m_SortIdx.GetSize(), sizeof(int), SortCompare);
	Invalidate();
	if (sel >= 0)	// if an item was selected
		sel = FindItem(sel);	// find its sorted index
	else
		sel = 0;
	SelectItem(sel);	// reselect item
}

int CResultsReportControl::FindItem(int ItemIdx) const
{
	int	items = m_ClipSpan.GetSize();
	for (int iItem = 0; iItem < items; iItem++) {
		if (m_SortIdx[iItem] == ItemIdx)
			return(iItem);
	}
	return(-1);
}

void CResultsReportControl::SelectItem(int ItemIdx)
{
	SetSelectionMark(ItemIdx);
	int	mask = LVIS_FOCUSED | LVIS_SELECTED;
	SetItemState(ItemIdx, mask, mask);
	EnsureVisible(ItemIdx, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CResultsReportControl message map

BEGIN_MESSAGE_MAP(CResultsReportControl, CReportControl)
	//{{AFX_MSG_MAP(CResultsReportControl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_SETFOCUS()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UWM_UPDATEITEMS, OnUpdateItems)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultsReportControl message handlers

int CResultsReportControl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CReportControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	ASSERT(GetStyle() & LVS_OWNERDATA);	// must be owner data
	// set columns and init control
	SetColumns(CLIP_COLS, m_ClipColInfo);
	InitControl(0, CReportControl::SORT_ARROWS);
	SetExtendedStyle(LVS_EX_FULLROWSELECT);
	CReportControl::SortRows(CLIP_COL_START);	// set initial sort column

	return 0;
}

LRESULT	CResultsReportControl::OnUpdateItems(WPARAM wParam, LPARAM lParam)
{
	CWaitCursor	wc;
	int	items = m_ClipSpan.GetSize();
	m_SortIdx.SetSize(items);
	for (int iItem = 0; iItem < items; iItem++)
		m_SortIdx[iItem] = iItem;
	SetItemCountEx(items, 0);	// set virtual item count
	SortRows();
	if (items)
		SelectItem(0);	// select first item
	return(0);
}

void CResultsReportControl::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVDISPINFO* pDispInfo = (NMLVDISPINFO*)pNMHDR;
	LVITEM&	item = pDispInfo->item;
	int	iSortedItem = m_SortIdx[item.iItem];
	const CSignalProcess::CLIP_SPAN&	span = m_ClipSpan[iSortedItem];
	if (item.mask & LVIF_TEXT) {
		switch (item.iSubItem) {
		case CLIP_COL_START:
			_tcsncpy(item.pszText, 
				theApp.GetMain()->GetNavBar().FrameToStr(double(span.Start)),
				item.cchTextMax);
			break;
		case CLIP_COL_LENGTH:
			_sntprintf(item.pszText, item.cchTextMax, _T("%I64d"), LONGLONG(span.Length));
			break;
		case CLIP_COL_CHANNEL:
			_sntprintf(item.pszText, item.cchTextMax, _T("%d"), span.Channel);
			break;
		default:
			NODEFAULTCASE;
		}
	}
	*pResult = 0;
}

void CResultsReportControl::OnItemchanged(NMHDR* pNMHDR, LRESULT* result)
{
	NMLISTVIEW	*lpnmlv = (LPNMLISTVIEW)pNMHDR;
	if (!lpnmlv->iSubItem && (lpnmlv->uChanged & LVIF_STATE) 
	&& (lpnmlv->uNewState & LVIS_SELECTED)) {
		OnItemSelection(lpnmlv->iItem);
	}
}

void CResultsReportControl::OnSetFocus(CWnd* pOldWnd) 
{
	CReportControl::OnSetFocus(pOldWnd);
	int	iItem = GetSelectionMark();
	if (iItem >= 0)
		OnItemSelection(iItem);
}

BOOL CResultsReportControl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if (nFlags & MK_CONTROL && m_View != NULL) {
		m_View->StepZoom(m_View->GetNowX(), zDelta > 0);	// delegate to view
		return 0;
	}
	return CReportControl::OnMouseWheel(nFlags, zDelta, pt);
}
