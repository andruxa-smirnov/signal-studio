// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// CodeResample.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeResample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeResample dialog

#define RK_RESAMPLE_QUALITY	_T("ResampleQuality")

CCodeResample::CCodeResample(UINT SampleRate, CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodeResample)
	m_Quality = 0;
	m_SampleRate = 0;
	//}}AFX_DATA_INIT
	theApp.RdReg2Int(RK_RESAMPLE_QUALITY, m_Quality);
	m_SampleRate = SampleRate;
	m_PrevSampleRate = SampleRate;
}

CCodeResample::~CCodeResample()
{
	theApp.WrRegInt(RK_RESAMPLE_QUALITY, m_Quality);
}

void CCodeResample::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeResample)
	DDX_CBIndex(pDX, IDC_RESAMP_QUALITY, m_Quality);
	DDX_Text(pDX, IDC_RESAMP_SAMPLE_RATE, m_SampleRate);
	DDV_MinMaxUInt(pDX, m_SampleRate, 1, 4294967295);
	//}}AFX_DATA_MAP
	if (pDX->m_bSaveAndValidate) {
		if (m_SampleRate == m_PrevSampleRate) {
			AfxMessageBox(IDS_RESAMP_CHANGE_RATE);
			DDV_Fail(pDX, IDC_RESAMP_SAMPLE_RATE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCodeResample message map

BEGIN_MESSAGE_MAP(CCodeResample, CDialog)
	//{{AFX_MSG_MAP(CCodeResample)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeResample message handlers
