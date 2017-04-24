// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// BaseDialog.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "BaseDialog.h"
#include "WinAppEx.h"	// for DockControlBarLeftOf

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseDialog dialog

IMPLEMENT_DYNAMIC(CBaseDialog, CDialogBar);

const int CBaseDialog::CAP_MARGIN = 12;	// space between bar edge and caption

CBaseDialog::CBaseDialog(UINT nIDAccel)
{
	//{{AFX_DATA_INIT(CBaseDialog)
	//}}AFX_DATA_INIT
	m_DockedSize = 0;
	m_FloatingSize = 0;
	m_bChangeDockedSize = FALSE;
	m_Accel = LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(nIDAccel));
	m_CapRect = CRect(0, 0, 0, 0);
	m_CapSize = CSize(0, 0);
	m_Margin = CSize(0, 0);
	m_PrevFloating = -1;	// so first OnSize will invalidate regardless
	m_GotMRUWidth = FALSE;	// true if we've loaded CControlBar's MRU width
	m_Options = OPT_HORZ_RESIZE;	// prev versions had horz resizing, stay compatible
}

CBaseDialog::~CBaseDialog()
{
}

BOOL CBaseDialog::Create(CWnd *pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
{
	if (!CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID))
		return FALSE;

	m_bChangeDockedSize = FALSE;
	m_FloatingSize = m_DockedSize = m_sizeDefault;

	return TRUE;
}

BOOL CBaseDialog::Create(CFrameWnd *pFrameWnd, UINT nIDTemplate, UINT nStyle,
						  DWORD dwDockStyle, UINT nBarID, CControlBar *LeftOf)
{
	if (!nStyle) {	// if style is zero, use default style
		nStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER |
			CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	}
	if (!Create(pFrameWnd, nIDTemplate, nStyle, nBarID))
		return(FALSE);
	EnableDocking(dwDockStyle);
	CWinAppEx::DockControlBarLeftOf(pFrameWnd, this, LeftOf);
	return(TRUE);
}

CSize CBaseDialog::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	CSize	size;
	m_Margin = CSize(0, 0);
	m_CapRect = CRect(0, 0, 0, 0);
	if (dwMode & (LM_MRUWIDTH | LM_STRETCH)) {
		// if CControlBar has a valid MRU width and we haven't copied it yet
		if (m_nMRUWidth != 32767 && !m_GotMRUWidth) {
			m_FloatingSize.cx = m_nMRUWidth;	// copy width from CControlBar
			m_GotMRUWidth = TRUE;				// from now on we maintain width
		}
		size = m_FloatingSize;
	} else if (dwMode & (LM_VERTDOCK | LM_HORZDOCK)) {
		m_Margin = (dwMode & LM_HORZDOCK) ? 
			CSize(CAP_MARGIN / 2, 0) : CSize(0, CAP_MARGIN / 2);
		if (m_CapSize != CSize(0, 0)) {
			CRect	cr;
			GetClientRect(cr);
			if (dwMode & LM_HORZDOCK) {	// center caption horizontally
				int	y = (cr.Height() - m_CapSize.cy) / 2;
				m_CapRect = CRect(CAP_MARGIN, y,
					CAP_MARGIN + m_CapSize.cx, y + m_CapSize.cy);
				m_Margin.cx += m_CapRect.right;
			} else {	// center caption vertically
				int	x = (cr.Width() - m_CapSize.cx) / 2;
				m_CapRect = CRect(x, CAP_MARGIN,
					x + m_CapSize.cx, CAP_MARGIN + m_CapSize.cy);
				m_Margin.cy += m_CapRect.bottom;
			}
		}
		m_Caption.MoveWindow(m_CapRect, FALSE);
		size = m_FloatingSize + m_Margin;
	} else {
		if (dwMode & LM_LENGTHY) {	// if nLength is a height instead of a width
			if (m_Options & OPT_VERT_RESIZE)
				m_FloatingSize.cy = max(nLength, m_DockedSize.cy);
		} else {
			if (m_Options & OPT_HORZ_RESIZE)
				m_FloatingSize.cx = max(nLength, m_DockedSize.cx);
		}
		size = CSize(m_FloatingSize.cx, m_FloatingSize.cy);
		m_nMRUWidth = m_FloatingSize.cx;	// so SaveBarState captures our width
		// our height isn't persistent because CControlBarInfo doesn't support it
	}
	PostMessage(WM_SIZE, 0, MAKELONG(size.cx, size.cy));
	return(size);
}

void CBaseDialog::SetBarCaption(LPCTSTR Text)
{
	m_CapSize = CSize(0, 0);	// assume failure
	if (Text != NULL) {
		CDC	*pDC = GetDC();
		ASSERT(pDC != NULL);
		pDC->SelectObject(GetFont());	// use our font to calculate caption text size
		CRect	r;
		if (pDC->DrawText(Text, r, DT_CALCRECT | DT_NOPREFIX))
			m_CapSize = r.Size();
		ReleaseDC(pDC);
	}
	m_Caption.SetWindowText(Text);
	if (!IsFloating())
		GetDockingFrame()->RecalcLayout();		// force bar to be resized
}

void CBaseDialog::SetWindowText(LPCTSTR lpszString)
{
	CDialogBar::SetWindowText(lpszString);
	// SetWindowText doesn't work while a control bar is floating; it's because
	// in this case, the caption is owned by the parent frame (CMiniDockFrame)
	if (IsFloating()) {
		CFrameWnd	*Frame = GetParentFrame();
		if (Frame != NULL)		// call SetWindowText on the parent frame too
			Frame->SetWindowText(lpszString);
	}
}

BOOL CBaseDialog::EnableToolTips(BOOL bEnable)
{
	return(CDialogBar::EnableToolTips(bEnable));
}

void CBaseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseDialog)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBaseDialog, CDialogBar)
	//{{AFX_MSG_MAP(CBaseDialog)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseDialog message handlers

LRESULT CBaseDialog::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	// in MFC versions > 6.0, return value is always FALSE; see article 839297
	HandleInitDialog(wParam, lParam);	// ignore unreliable return value

	if (!UpdateData(FALSE))
	   TRACE0("Warning: UpdateData failed during dialog init.\n");

	// create caption window
	m_Caption.Create(_T(""), WS_CHILD | SS_NOPREFIX, CRect(0, 0, 0, 0), this);
	m_Caption.SetFont(GetFont());	// give it our font
	m_Resize.SetParentWnd(this);

	return 0;
}

BOOL CBaseDialog::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST) {
		if (m_Accel && TranslateAccelerator(m_hWnd, m_Accel, pMsg))
			return(TRUE);
		// route keys to main so menu key works when floating
		if (AfxGetMainWnd()->SendMessage(UWM_HANDLEDLGKEY, (WPARAM)pMsg))
			return(TRUE);
	}
	return CDialogBar::PreTranslateMessage(pMsg);
}

BOOL CBaseDialog::OnToolTipText(UINT id, NMHDR* pTTTStruct, LRESULT* pResult)
{
	LPNMTTDISPINFO	ttp = LPNMTTDISPINFO(pTTTStruct);
	// NMHDR idFrom changed from UINT to UINT_PTR in later versions of API
	UINT nID = UINT(ttp->hdr.idFrom);	// we only support 32-bit IDs
	if (ttp->uFlags & TTF_IDISHWND)		// idFrom can be HWND or ID
		nID = ::GetDlgCtrlID((HWND)nID);
	if (!nID)
		return(FALSE);
	CString	s;
	s.LoadString(nID);
	int	Line2 = s.Find('\n');	// find newline
	if (Line2 < 0)
		return(FALSE);
	_tcscpy(ttp->szText, s.Mid(Line2 + 1));	// show text after newline
	return(TRUE);
}

void CBaseDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialogBar::OnSize(nType, cx, cy);
	if (IsWindowVisible()) {
		if (m_CapSize != CSize(0, 0))
			m_Caption.ShowWindow(IsFloating() ? SW_HIDE : SW_SHOW);
		// trick resizer into making room for margin
		m_Resize.SetOriginShift(m_Margin);
		m_Resize.OnSize();
		// If dock state changed, we must invalidate bar; otherwise if app is
		// run via shell open, and document is initially maximized, and there's
		// a docked bar visible, bar's controls may not paint correctly.  Only
		// invalidate on dock state change, to avoid needless resizing flicker.
		if (m_PrevFloating != IsFloating()) {	// if dock state changed
			Invalidate();
			m_PrevFloating = IsFloating();
		}
	}
}

LRESULT CBaseDialog::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
	AfxGetApp()->WinHelp(GetDlgCtrlID());
	return TRUE;
}
