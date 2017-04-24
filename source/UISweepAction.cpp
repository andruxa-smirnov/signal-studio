// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// UISweepAction.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "UISweepAction.h"
#include "UISignalGenOsc.h"
#include "Oscillator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUISweepAction dialog

CUISweepAction::CUISweepAction(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CUISweepAction)
	m_Duration = 0.0;
	m_EndFreq = 0.0;
	m_StartFreq = 0.0;
	//}}AFX_DATA_INIT
	m_Waveform = 0;
}

void CUISweepAction::DDV_GTZeroDouble(CDataExchange *pDX, int nIDC, double& value)
{
	if (pDX->m_bSaveAndValidate && value <= 0) {
		AfxMessageBox(IDS_DDV_VALUE_GT_ZERO);
		DDV_Fail(pDX, nIDC);
	}
}

void CUISweepAction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUISweepAction)
	DDX_Control(pDX, IDC_SWEEP_WAVEFORM, m_WaveformCombo);
	DDX_Text(pDX, IDC_SWEEP_DURATION, m_Duration);
	DDX_Text(pDX, IDC_SWEEP_END_FREQUENCY, m_EndFreq);
	DDX_Text(pDX, IDC_SWEEP_START_FREQUENCY, m_StartFreq);
	//}}AFX_DATA_MAP
	DDV_GTZeroDouble(pDX, IDC_SWEEP_DURATION, m_Duration);
	DDV_GTZeroDouble(pDX, IDC_SWEEP_START_FREQUENCY, m_StartFreq);
	DDV_GTZeroDouble(pDX, IDC_SWEEP_END_FREQUENCY, m_EndFreq);
	CUISignalGenOsc::DDX_Combo(pDX, m_WaveformCombo, m_Waveform);
}

BEGIN_MESSAGE_MAP(CUISweepAction, CDialog)
	//{{AFX_MSG_MAP(CUISweepAction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUISweepAction message handlers

BOOL CUISweepAction::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CUISignalGenOsc::InitWaveformCombo(m_WaveformCombo, m_Waveform);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
