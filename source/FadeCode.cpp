// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// CodeFade.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeFade.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeFade dialog

#define RK_FADE_TYPE	_T("FadeType")
#define RK_FADE_START	_T("FadeStart")
#define RK_FADE_END		_T("FadeEnd")
#define RK_FADE_LOG		_T("FadeLog")

CCodeFade::CCodeFade(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodeFade)
	//}}AFX_DATA_INIT
	m_FadeType = theApp.RdRegInt(RK_FADE_TYPE, FT_IN);
	m_Start = theApp.RdRegDouble(RK_FADE_START, 0);
	m_End = theApp.RdRegDouble(RK_FADE_END, 0);
	m_Log = theApp.RdRegBool(RK_FADE_LOG, FALSE);
}

CCodeFade::~CCodeFade()
{
	theApp.WrRegInt(RK_FADE_TYPE, m_FadeType);
	theApp.WrRegDouble(RK_FADE_START, m_Start);
	theApp.WrRegDouble(RK_FADE_END, m_End);
	theApp.WrRegBool(RK_FADE_LOG, m_Log != 0);
}

void CCodeFade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeFade)
	DDX_Radio(pDX, IDC_FADE_TYPE, m_FadeType);
	DDX_Text(pDX, IDC_FADE_START, m_Start);
	DDX_Text(pDX, IDC_FADE_END, m_End);
	DDX_Check(pDX, IDC_FADE_LOG, m_Log);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCodeFade message map

BEGIN_MESSAGE_MAP(CCodeFade, CDialog)
	//{{AFX_MSG_MAP(CCodeFade)
	ON_BN_CLICKED(IDC_FADE_TYPE, OnFadeType)
	ON_BN_CLICKED(IDC_FADE_TYPE2, OnFadeType)
	ON_BN_CLICKED(IDC_FADE_TYPE3, OnFadeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeFade message handlers

BOOL CCodeFade::OnInitDialog() 
{
	CDialog::OnInitDialog();

	OnFadeType();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCodeFade::OnFadeType() 
{
	int	FadeType = GetCheckedRadioButton(IDC_FADE_TYPE, IDC_FADE_TYPE3);
	ASSERT(FadeType);
	bool	IsCustom = FadeType == IDC_FADE_TYPE3;
	GetDlgItem(IDC_FADE_START)->EnableWindow(IsCustom);
	GetDlgItem(IDC_FADE_END)->EnableWindow(IsCustom);
	int	start, end;
	if (!IsCustom) {	// if not custom fade
		if (FadeType == IDC_FADE_TYPE) {	// if fade in
			start = IDC_FADE_START;
			end = IDC_FADE_END;
		} else {	// fade out
			start = IDC_FADE_END;
			end = IDC_FADE_START;
		}
		GetDlgItem(start)->SetWindowText(_T("-100"));
		GetDlgItem(end)->SetWindowText(_T("0"));
	}
}
