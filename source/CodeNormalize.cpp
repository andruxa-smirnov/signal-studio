// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// CodeNormalize.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeNormalize.h"
#include <afxpriv.h>	// for WM_KICKIDLE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeNormalize dialog

#define RK_NORM_UNBIAS		_T("NormUnbias")
#define RK_NORM_NORMALIZE	_T("NormNormalize")
#define RK_NORM_INDEPENDENT	_T("NormIndependent")
#define RK_NORM_PEAK_LEVEL	_T("NormPeakLevel")

CCodeNormalize::CCodeNormalize(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodeNormalize)
	//}}AFX_DATA_INIT
	m_Unbias = theApp.RdRegInt(RK_NORM_UNBIAS, TRUE);
	m_Normalize = theApp.RdRegInt(RK_NORM_NORMALIZE, TRUE);
	m_Independent = theApp.RdRegInt(RK_NORM_INDEPENDENT, FALSE);
	m_PeakLevel = theApp.RdRegDouble(RK_NORM_PEAK_LEVEL, -1);
}

CCodeNormalize::~CCodeNormalize()
{
	theApp.WrRegInt(RK_NORM_UNBIAS, m_Unbias);
	theApp.WrRegInt(RK_NORM_NORMALIZE, m_Normalize);
	theApp.WrRegInt(RK_NORM_INDEPENDENT, m_Independent);
	theApp.WrRegDouble(RK_NORM_PEAK_LEVEL, m_PeakLevel);
}

void CCodeNormalize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeNormalize)
	DDX_Check(pDX, IDC_NORM_INDEPENDENT, m_Independent);
	DDX_Check(pDX, IDC_NORM_NORMALIZE, m_Normalize);
	DDX_Check(pDX, IDC_NORM_UNBIAS, m_Unbias);
	DDX_Text(pDX, IDC_NORM_PEAK_LEVEL, m_PeakLevel);
	DDV_MinMaxDouble(pDX, m_PeakLevel, -100., 0.);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCodeNormalize message map

BEGIN_MESSAGE_MAP(CCodeNormalize, CDialog)
	//{{AFX_MSG_MAP(CCodeNormalize)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(IDC_NORM_PEAK_LEVEL, OnUpdatePeakLevel)
	ON_UPDATE_COMMAND_UI(IDC_NORM_INDEPENDENT, OnUpdatePeakLevel)
	ON_UPDATE_COMMAND_UI(IDC_NORM_PEAK_LEVEL_CAPTION, OnUpdatePeakLevel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeNormalize message handlers

LRESULT CCodeNormalize::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
    UpdateDialogControls(this, TRUE);
    return FALSE;
}

void CCodeNormalize::OnUpdatePeakLevel(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsDlgButtonChecked(IDC_NORM_NORMALIZE));
}

