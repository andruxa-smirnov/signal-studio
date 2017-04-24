// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// AudioBar.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "AudioBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudioBar dialog

IMPLEMENT_DYNAMIC(CAudioBar, CBaseDialog);

#define RK_VOLUME	_T("Volume")
#define RK_MUTE		_T("Mute")

const CControlResizer::CTRL_LIST CAudioBar::m_CtrlList[] = {
	{IDC_VOLUME_MUTE,	BIND_LEFT},
	{IDC_VOLUME_SLIDER,	BIND_LEFT | BIND_RIGHT},
	{0}
};

CAudioBar::CAudioBar(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CAudioBar)
	//}}AFX_DATA_INIT
	m_Volume = theApp.RdRegDouble(RK_VOLUME, 1.0);
	m_Mute = theApp.RdRegBool(RK_MUTE, FALSE);
}

CAudioBar::~CAudioBar()
{
	theApp.WrRegDouble(RK_VOLUME, m_Volume);
	theApp.WrRegBool(RK_MUTE, m_Mute);
}

void CAudioBar::SetVolume(double Volume)
{
	m_VolumeSlider.SetPos(round(Volume * double(VOLUME_STEPS)));
	m_Volume = Volume;
}

double CAudioBar::GetVolume() const
{
	if (m_Mute)
		return(0);
	return(m_Volume);
}

void CAudioBar::UpdatePlayer()
{
	theApp.GetMain()->SetVolume(GetVolume());
}

void CAudioBar::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAudioBar)
	DDX_Control(pDX, IDC_VOLUME_MUTE, m_MuteBtn);
	DDX_Control(pDX, IDC_VOLUME_SLIDER, m_VolumeSlider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAudioBar, CBaseDialog)
	//{{AFX_MSG_MAP(CAudioBar)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_VOLUME_MUTE, OnVolumeMute)
	ON_BN_DOUBLECLICKED(IDC_VOLUME_MUTE, OnVolumeMute)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_UPDATE_COMMAND_UI(IDC_VOLUME_MUTE, OnUpdateMute)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioBar message handlers

LRESULT CAudioBar::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	CBaseDialog::OnInitDialog(wParam, lParam);
	m_VolumeSlider.SetRange(0, VOLUME_STEPS);
	SetVolume(m_Volume);
	m_MuteBtn.SetIcons(IDI_MUTE_UP, IDI_MUTE_DOWN);
	m_MuteBtn.SetCheck(m_Mute);
	m_Resize.AddControlList(this, m_CtrlList);
	return 0;
}

void CAudioBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_Volume = 	m_VolumeSlider.GetPos() / double(VOLUME_STEPS);
	UpdatePlayer();
	CBaseDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAudioBar::OnVolumeMute() 
{
	m_Mute ^= 1;
	UpdatePlayer();
}

void CAudioBar::OnUpdateMute(CCmdUI *pCmdUI)
{
	// this handler is mandatory, else button is automatically disabled
	pCmdUI->SetCheck(m_Mute);
}

void CAudioBar::OnSize(UINT nType, int cx, int cy) 
{
	CBaseDialog::OnSize(nType, cx, cy);
	int	xshift = IsFloating() ? 0 : GRIPPER_SIZE;
	m_Resize.SetOriginShift(CSize(xshift, 0));
	m_Resize.OnSize();
}
