// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// UISignalGenOsc.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "UISignalGenOsc.h"
#include "UISignalGen.h"
#include "Oscillator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUISignalGenOsc dialog

// order of resource IDs must match waveform enum in COscillator
const int CUISignalGenOsc::m_WaveformName[COscillator::WAVEFORMS] = {
	IDS_OSC_TRIANGLE,
	IDS_OSC_SINE,
	IDS_OSC_RAMP_UP,
	IDS_OSC_RAMP_DOWN,
	IDS_OSC_SQUARE,
	IDS_OSC_PULSE,
	IDS_OSC_RANDOM,
	IDS_OSC_RANDOM_RAMP,
};

const WAVEGEN_OSC_PARMS CUISignalGenOsc::m_Defaults = {
	COscillator::SINE,	// m_Waveform
	60.0,		// m_Frequency
	50.0,		// m_PulseWidth
	0.0,		// m_Phase
	0.0,		// m_DCBias
};

CUISignalGenOsc::CUISignalGenOsc(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CUISignalGenOsc)
	//}}AFX_DATA_INIT
	WAVEGEN_OSC_PARMS::operator=(m_Defaults);
}

void CUISignalGenOsc::InitWaveformCombo(CComboBox& Combo, int SelIdx)
{
	for (int iWave = 0; iWave < COscillator::WAVEFORMS; iWave++)
		Combo.AddString(LDS(m_WaveformName[iWave]));
	Combo.SetCurSel(SelIdx);
}

void CUISignalGenOsc::DDX_Combo(CDataExchange *pDX, CComboBox& Combo, int& SelIdx)
{
	if (pDX->m_bSaveAndValidate) {
		int	sel = Combo.GetCurSel();
		ASSERT(sel >= 0 && sel < COscillator::WAVEFORMS);
		SelIdx = sel;
	} else
		Combo.SetCurSel(SelIdx);
}

void CUISignalGenOsc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUISignalGenOsc)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_WGEN_WAVEFORM, m_WaveformCombo);
	DDX_Text(pDX, IDC_WGEN_FREQUENCY, m_Frequency);
	DDX_Text(pDX, IDC_WGEN_PULSE_WIDTH, m_PulseWidth);
	DDX_Text(pDX, IDC_WGEN_PHASE, m_Phase);
	DDX_Text(pDX, IDC_WGEN_DC_BIAS, m_DCBias);
	DDX_Combo(pDX, m_WaveformCombo, m_Waveform);
}

/////////////////////////////////////////////////////////////////////////////
// CUISignalGenOsc message map

BEGIN_MESSAGE_MAP(CUISignalGenOsc, CDialog)
	//{{AFX_MSG_MAP(CUISignalGenOsc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUISignalGenOsc message handlers

BOOL CUISignalGenOsc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitWaveformCombo(m_WaveformCombo, m_Waveform);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
