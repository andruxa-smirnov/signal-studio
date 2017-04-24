// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// UIShowColours.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "UIShowColours.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUIShowColours dialog

#define VIEW_COLOR_DEF(name, tag, R, G, B) IDC_VWCLR_##tag,
const int CUIShowColours::m_BtnResID[COLORS] = {	// button resource IDs
	#include "ShowColours.h"
};

CUIShowColours::CUIShowColours(CCodeOptionsInfo& Info, CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent), m_oi(Info)
{
	//{{AFX_DATA_INIT(CUIShowColours)
	//}}AFX_DATA_INIT
}

int CUIShowColours::FindColor(int ResID)
{
	for (int iColor = 0; iColor < COLORS; iColor++) {	// for each color
		// if button resource ID for this color matches caller's resource ID
		if (m_BtnResID[iColor] == ResID)
			return(iColor);
	}
	return(-1);	// resource ID not found
}

void CUIShowColours::EditColor(int ColorIdx)
{
	ASSERT(ColorIdx >= 0 && ColorIdx < COLORS);
	m_SwatchBtn[ColorIdx].EditColor(m_oi.m_CustomColors.Color);
}

void CUIShowColours::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUIShowColours)
	//}}AFX_DATA_MAP
	// update swatch buttons
	for (int iColor = 0; iColor < COLORS; iColor++)	// for each color
		DDX_Control(pDX, m_BtnResID[iColor], m_SwatchBtn[iColor]);
}

/////////////////////////////////////////////////////////////////////////////
// CUIShowColours message map

BEGIN_MESSAGE_MAP(CUIShowColours, CDialog)
	//{{AFX_MSG_MAP(CUIShowColours)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_VWCLR_EXCLUDED_CHAN_BK, IDC_VWCLR_WAVE_DATA, OnColorBtn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUIShowColours message handlers

BOOL CUIShowColours::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// initialize swatch buttons from palette
	for (int iColor = 0; iColor < COLORS; iColor++)
		m_SwatchBtn[iColor].SetColor(m_oi.m_ViewPalette.Color[iColor]);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUIShowColours::OnOK() 
{
	// retrieve palette from swatch buttons
	for (int iColor = 0; iColor < COLORS; iColor++)	// for each color
		m_oi.m_ViewPalette.Color[iColor] = m_SwatchBtn[iColor].GetColor();
	CDialog::OnOK();
}

void CUIShowColours::OnColorBtn(UINT nID)
{
	int	iColor = FindColor(nID);
	ASSERT(iColor >= 0);	// else logic error
	EditColor(iColor);
}
