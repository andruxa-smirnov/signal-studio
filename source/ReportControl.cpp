// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// ReportControl.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "ReportControl.h"
#include "Persist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportControl

IMPLEMENT_DYNAMIC(CReportControl, CListCtrl);

CReportControl::CReportControl()
{
	m_Columns = 0;
	m_Column = NULL;
	m_SortCol = -1;
	m_SortDir = 0;
	m_SortCallback = NULL;
	m_SortWaitCursor = FALSE;
	m_Style = 0;
	m_ColHeap = NULL;
}

CReportControl::~CReportControl()
{
	if (m_ColHeap != NULL)
		delete [] m_ColHeap;
}

void	CReportControl::SetColumns(int Columns, const COLUMN *Column)
{
	m_Columns = Columns;
	m_Column = Column;
}

void	CReportControl::SetColumns(int Columns, const RES_COL *Column)
{
	m_Columns = Columns;
	m_ColHeap = new COLUMN[Columns];
	m_Title.SetSize(Columns);
	for (int i = 0; i < Columns; i++) {
		m_Title[i] = LDS(Column[i].TitleID);
		m_ColHeap[i].Title		= m_Title[i];
		m_ColHeap[i].Align		= Column[i].Align;
		m_ColHeap[i].Width		= Column[i].Width;
		m_ColHeap[i].InitSort	= Column[i].InitSort;
	}
	m_Column = m_ColHeap;
}

void	CReportControl::SetSortCallback(PFNLVCOMPARE Callback, PVOID Data)
{
	m_SortCallback = Callback;
	m_SortCallbackData = Data;
}

void	CReportControl::InitControl(int Rows, int Style)
{
	while (DeleteColumn(0));	// delete any existing columns
	for (int i = 0; i < m_Columns; i++) {
		InsertColumn(i, m_Column[i].Title, 
			m_Column[i].Align, m_Column[i].Width, i);
	}
#if _MFC_VER < 0x0700	// if MFC 6
	if (Style & SORT_ARROWS) {
		// create header image list containing sort arrows
		m_HdrImgList.Create(IDB_HEADER_SORT, 8, 0, RGB(0, 128, 128));
		GetHeaderCtrl()->SetImageList(&m_HdrImgList);
	}
#endif
	m_Style = Style;
	ModifyStyle(0, LVS_REPORT);	// force report view
	ResetControl(Rows);
}

void	CReportControl::ResetControl(int Rows)
{
	m_SortCol = -1;
	m_SortDir = 0;
	DeleteAllItems();
	SetItemCount(Rows);	// allocate memory in advance
}

int		CReportControl::InsertRow(int Idx, const CStringArray& Row, int SortKey)
{
	int	pos = InsertItem(Idx, Row[0]);
	for (int i = 1; i < m_Columns; i++)
		SetItemText(pos, i, Row[i]);
	SetItemData(pos, SortKey);
	return(pos);
}

int		CReportControl::InsertRow(int Idx, const LPCTSTR *Row, int SortKey)
{
	int	pos = InsertItem(Idx, Row[0]);
	for (int i = 1; i < m_Columns; i++)
		SetItemText(pos, i, Row[i]);
	SetItemData(pos, SortKey);
	return(pos);
}

int		CReportControl::InsertCallbackRow(int Idx, int SortKey)
{
	int	pos = InsertItem(Idx, LPSTR_TEXTCALLBACK);
	for (int i = 1; i < m_Columns; i++)
		SetItemText(pos, i, LPSTR_TEXTCALLBACK);
	SetItemData(pos, SortKey);
	return(pos);
}

int	CReportControl::FindRow(int SortKey)
{
	LVFINDINFO	fi;
	ZeroMemory(&fi, sizeof(fi));
	fi.flags = LVFI_PARAM;
	fi.lParam = SortKey;
	return(FindItem(&fi));
}

void	CReportControl::AddRow(int SortKey)
{
	int	row = GetItemCount();
	InsertCallbackRow(row, SortKey);
	SortRows();
}

bool	CReportControl::RemoveRow(int SortKey)
{
	int	row = FindRow(SortKey);
	if (row < 0)
		return(FALSE);
	DeleteItem(row);
	int	items = GetItemCount();
	// items with sort keys >= the deleted item's need updating
	for (int i = 0; i < items; i++) { // for each item
		int	sk = INT64TO32(GetItemData(i));	// get item's sort key
		if (sk >= SortKey)	// if sort key is invalid
			SetItemData(i, sk - 1);	// update it
	}
	return(TRUE);
}

bool	CReportControl::RedrawRow(int SortKey)
{
	int	row = FindRow(SortKey);
	if (row < 0)
		return(FALSE);
	RedrawItems(row, row);
	return(TRUE);
}

int	CReportControl::TextSort(int p1, int p2)
{
	LVFINDINFO info;
	info.flags = LVFI_PARAM;
	info.lParam = p1;
	int nItem1 = FindItem(&info);
	info.lParam = p2;
	int nItem2 = FindItem(&info);
	return(SortCmp(GetItemText(nItem1, m_SortCol), GetItemText(nItem2, m_SortCol)));
}

int CALLBACK CReportControl::TextSort(LPARAM p1, LPARAM p2, LPARAM This)
{
	return(((CReportControl *)This)->TextSort(INT64TO32(p1), INT64TO32(p2)));
}

void	CReportControl::DrawSortArrow(int Col, int Desc)
{
	if (Col < 0)
		return;
#if _MFC_VER < 0x0700	// if MFC 6
	HDITEM	hdi;
	hdi.mask = HDI_IMAGE | HDI_FORMAT;
	GetHeaderCtrl()->GetItem(Col, &hdi);
	if (Desc < 0) {	// erase
		hdi.mask = HDI_FORMAT;
		hdi.fmt &= ~HDF_IMAGE;
	} else {
		hdi.mask = HDI_FORMAT | HDI_IMAGE;
		hdi.fmt |= HDF_IMAGE | HDF_BITMAP_ON_RIGHT;
		hdi.iImage = Desc;
	}
#else	// .NET; use sort header format flags instead of image list
	HDITEM	hdi;
	hdi.mask = HDI_FORMAT;
	GetHeaderCtrl()->GetItem(Col, &hdi);
	hdi.mask = HDI_FORMAT;
	if (Desc < 0)	// erase
		hdi.fmt &= ~(HDF_SORTUP | HDF_SORTDOWN);
	else {
		if (Desc)
			hdi.fmt |= HDF_SORTDOWN;
		else
			hdi.fmt |= HDF_SORTUP;
	}
#endif
	GetHeaderCtrl()->SetItem(Col, &hdi);
}

void	CReportControl::SortRows()
{
	if (m_SortWaitCursor)
		CCmdTarget::BeginWaitCursor();
	if (m_SortCallback != NULL)		// is there a sort callback?
		SortItems(m_SortCallback, (DWORD)m_SortCallbackData);	// y, use it
	else
		SortItems(TextSort, (DWORD)this);	// n, use text sort
	if (m_SortWaitCursor)
		CCmdTarget::EndWaitCursor();
	// if there's a selection, keep it visible, otherwise go to top
	EnsureVisible(GetSelectedCount() ? GetSelectionMark() : 0, FALSE);
}

void	CReportControl::SortRows(int SortCol, int SortDir)
{
	if (m_Style & SORT_ARROWS)
		DrawSortArrow(m_SortCol, -1);	// erase previous column's arrow
	if (m_Style & SORT_ARROWS)
		DrawSortArrow(SortCol, SortDir < 0);	// draw new arrow
	m_SortDir = SortDir;
	m_SortCol = SortCol;
	SortRows();
}

void	CReportControl::SortRows(int SortCol)
{
	if (SortCol == m_SortCol)		// same column as last time?
		m_SortDir = -m_SortDir;					// y, reverse sort order
	else
		m_SortDir = m_Column[SortCol].InitSort;	// n, set default sort order
	SortRows(SortCol, m_SortDir);
}

void	CReportControl::EnsureSelectionVisible()
{
	if (GetSelectedCount())
		EnsureVisible(GetSelectionMark(), FALSE);
}

inline int CReportControl::CalcHeaderStateSize(int Columns)
{
	return(sizeof(HEADER_STATE) + ((Columns * 2) - 1) * sizeof(int));
}

bool CReportControl::StoreHeaderState(LPCTSTR Key, LPCTSTR SubKey)
{
	DWORD	hsz = CalcHeaderStateSize(m_Columns);
	HEADER_STATE	*ph = (HEADER_STATE *)new BYTE[hsz];
	ph->Columns = m_Columns;
	ph->SortCol = SortCol();
	ph->SortDir = SortDir();
	int	cols = m_Columns;
	int	*pColWidth = &ph->ColInfo[cols];
	for (int i = 0; i < cols; i++)
		pColWidth[i] = GetColumnWidth(i);
	GetColumnOrderArray(ph->ColInfo, cols);
	bool	retc = CPersist::WriteBinary(Key, SubKey, ph, hsz) != 0;
	delete ph;
	return(retc);
}

bool CReportControl::LoadHeaderState(LPCTSTR Key, LPCTSTR SubKey)
{
	DWORD	hsz = CalcHeaderStateSize(m_Columns);
	HEADER_STATE	*ph = (HEADER_STATE *)new BYTE[hsz];
	ZeroMemory(ph, hsz);
	bool	retc = CPersist::GetBinary(Key, SubKey, ph, &hsz) != 0;
	if (retc) {
		SortRows(ph->SortCol, ph->SortDir);
		int	cols = ph->Columns;
		int	*pColWidth = &ph->ColInfo[cols];
		for (int i = 0; i < cols; i++)
			SetColumnWidth(i, pColWidth[i]);
		SetColumnOrderArray(cols, ph->ColInfo);
	}
	delete ph;
	return(retc);
}

void CReportControl::ResetHeaderState()
{
	int	cols = m_Columns;
	int	*pColOrder = new int[cols];
	for (int i = 0; i < cols; i++) {
		SetColumnWidth(i, m_Column[i].Width);
		pColOrder[i] = i;
	}
	SetColumnOrderArray(cols, pColOrder);
	delete pColOrder;
	Invalidate();
}

CString CReportControl::GetReport() const
{
	int	nRows = GetItemCount();
	int	nCols = m_Columns;
	CString	report;
	for (int iRow = 0; iRow < nRows; iRow++) {
		for (int iCol = 0; iCol < nCols; iCol++) {
			if (iCol)
				report += '\t';
			report += GetItemText(iRow, iCol);
		}
		report += '\n';
	}
	return(report);
}

BEGIN_MESSAGE_MAP(CReportControl, CListCtrl)
	//{{AFX_MSG_MAP(CReportControl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportControl message handlers

void CReportControl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int	Col = pNMListView->iSubItem;
	SortRows(Col);
	*pResult = 0;
}

void CReportControl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch (nSBCode) {
	case SB_PAGEDOWN:
	case SB_PAGEUP:
	case SB_LINEDOWN:
	case SB_LINEUP:
		// Don't update window if paging up or down. It looks terrible!
		LockWindowUpdate();
		CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
		UnlockWindowUpdate();
		break;
	default:
		CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
		break;
	}
}

void CReportControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar) {
	case VK_NEXT:
	case VK_PRIOR:
		// Don't update window if paging up or down. It looks terrible!
		LockWindowUpdate();
		CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
		UnlockWindowUpdate();
		break;
	default:
		CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
		break;
	}
}
