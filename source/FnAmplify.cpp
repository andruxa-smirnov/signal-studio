// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// FnAmplify.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "FnAmplify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFnAmplify dialog

#define RK_AMPLIFY_GAIN _T("AmplifyGain")

CFnAmplify::CFnAmplify(double Peak, CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CFnAmplify)
	//}}AFX_DATA_INIT
	m_Gain = theApp.RdRegDouble(RK_AMPLIFY_GAIN, 3);
	m_PrevGain = m_Gain;
	m_Peak = Peak;
}

CFnAmplify::~CFnAmplify()
{
	theApp.WrRegDouble(RK_AMPLIFY_GAIN, m_Gain);
}

void CFnAmplify::UpdateUI(double Gain)
{
	CString	s;
	s.Format(_T("%.2f"), m_Peak + Gain);
	m_PeakEdit.SetWindowText(s);
	int	ShowClip = m_Peak + Gain > 0 ? SW_SHOW : SW_HIDE;
	m_Clip.ShowWindow(ShowClip);
}

void CFnAmplify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFnAmplify)
	DDX_Control(pDX, IDC_AMPL_CLIP, m_Clip);
	DDX_Control(pDX, IDC_AMPL_PEAK, m_PeakEdit);
	DDX_Text(pDX, IDC_AMPL_GAIN, m_Gain);
	//}}AFX_DATA_MAP
	if (pDX->m_bSaveAndValidate) {	// if saving
		if (!m_Gain) {	// if no gain
			AfxMessageBox(IDS_AMPL_NO_GAIN);
			DDV_Fail(pDX, IDC_AMPL_GAIN);
		}
		if (m_Peak + m_Gain > 0) {	// if audio will be clipped
			if (AfxMessageBox(IDS_AMPL_CLIP_WARN, MB_OKCANCEL) != IDOK)	// warn user
				DDV_Fail(pDX, IDC_AMPL_GAIN);	// user chickened out
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFnAmplify message map

BEGIN_MESSAGE_MAP(CFnAmplify, CDialog)
	//{{AFX_MSG_MAP(CFnAmplify)
	ON_EN_KILLFOCUS(IDC_AMPL_GAIN, OnKillfocusGain)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFnAmplify message handlers

BOOL CFnAmplify::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateUI(m_Gain);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFnAmplify::OnCancel() 
{
	m_Gain = m_PrevGain;	// restore previous gain
	CDialog::OnCancel();
}

void CFnAmplify::OnKillfocusGain() 
{
	CString	s;
	GetDlgItem(IDC_AMPL_GAIN)->GetWindowText(s);
	UpdateUI(_tstof(s));
}

HBRUSH CFnAmplify::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd == &m_Clip) {
		const COLORREF	ClipColor = RGB(255, 192, 0);	// medium yellow
		hbr = (HBRUSH)GetStockObject(DC_BRUSH);
		SetDCBrushColor(pDC->m_hDC, ClipColor);
		pDC->SetBkColor(ClipColor);
	}
	
	return hbr;
}
