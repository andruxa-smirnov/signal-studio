// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// UISpeakers.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "UISpeakers.h"
#include "SignalProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUISpeakers dialog


CUISpeakers::CUISpeakers(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CUISpeakers)
	//}}AFX_DATA_INIT
	m_ChannelCount = 0;
	m_ChannelMask = 0;
}

void CUISpeakers::SetChannelMask(UINT Channels, UINT Mask)
{
	m_ChannelCount = Channels;
	m_ChannelMask = Mask;
}

void CUISpeakers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUISpeakers)
	DDX_Control(pDX, IDC_SPKR_LIST, m_List);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CUISpeakers message map

BEGIN_MESSAGE_MAP(CUISpeakers, CDialog)
	//{{AFX_MSG_MAP(CUISpeakers)
	ON_BN_CLICKED(IDC_SPKR_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUISpeakers message handlers

BOOL CUISpeakers::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for (int iSpkr = 0; iSpkr < CSignalProcess::SPEAKERS; iSpkr++) {
		m_List.AddString(CSignalProcess::GetSpeakerName(iSpkr));
		if ((1 << iSpkr) & m_ChannelMask)
			m_List.SetCheck(iSpkr, TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUISpeakers::OnOK() 
{
	m_ChannelMask = 0;
	UINT	spkrs = 0;
	for (int iSpkr = 0; iSpkr < CSignalProcess::SPEAKERS; iSpkr++) {
		if (m_List.GetCheck(iSpkr)) {
			m_ChannelMask |= (1 << iSpkr);
			spkrs++;
		}
	}
	// if speakers are specified and speaker count doesn't match channel count
	if (spkrs && spkrs != m_ChannelCount) {
		CString	s;
		s.Format(IDS_SPKR_CHANNEL_MISMATCH, spkrs, m_ChannelCount);
		if (AfxMessageBox(s, MB_YESNO | MB_DEFBUTTON2) != IDYES)
			return;
	}
	
	CDialog::OnOK();
}

void CUISpeakers::OnReset() 
{
	for (int iSpkr = 0; iSpkr < CSignalProcess::SPEAKERS; iSpkr++)
		m_List.SetCheck(iSpkr, FALSE);
}
