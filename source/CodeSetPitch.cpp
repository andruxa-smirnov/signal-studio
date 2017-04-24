// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// CodeSetPitch.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeSetPitch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeSetPitch dialog

IMPLEMENT_DYNAMIC(CCodeSetPitch, CBaseDialog);

const CControlResizer::CTRL_LIST CCodeSetPitch::m_CtrlList[] = {
	{IDC_PITCH_SLIDER,	BIND_LEFT | BIND_RIGHT},
	{IDC_PITCH_EDIT,	BIND_RIGHT},
	{0}
};

const CEditSlider::INFO CCodeSetPitch::m_SliderInfo = {
//	Range	Range	Log		Slider	Default	Tic		Edit	Edit
//	Min		Max		Base	Scale	Pos		Count	Scale	Precision
	-200,	200,	0,		100,	0,		0,		1,		2
};

CCodeSetPitch::CCodeSetPitch(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CCodeSetPitch)
	//}}AFX_DATA_INIT
}

CCodeSetPitch::~CCodeSetPitch()
{
}

void CCodeSetPitch::CodeSetPitch(double Pitch)
{
	m_PitchEdit.SetVal(Pitch);
}

void CCodeSetPitch::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeSetPitch)
	DDX_Control(pDX, IDC_PITCH_SLIDER, m_PitchSlider);
	DDX_Control(pDX, IDC_PITCH_EDIT, m_PitchEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCodeSetPitch, CBaseDialog)
	//{{AFX_MSG_MAP(CCodeSetPitch)
	ON_WM_SIZE()
	ON_NOTIFY(NEN_CHANGED, IDC_PITCH_EDIT, OnChangedPitch)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeSetPitch message handlers

LRESULT CCodeSetPitch::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	CBaseDialog::OnInitDialog(wParam, lParam);
	m_PitchSlider.SetInfo(m_SliderInfo, &m_PitchEdit);
	m_Resize.AddControlList(this, m_CtrlList);
	return 0;
}

void CCodeSetPitch::OnSize(UINT nType, int cx, int cy) 
{
	CBaseDialog::OnSize(nType, cx, cy);
	int	xshift = IsFloating() ? 0 : GRIPPER_SIZE;
	m_Resize.SetOriginShift(CSize(xshift, 0));
	m_Resize.OnSize();
}

void CCodeSetPitch::OnChangedPitch(NMHDR* pNMHDR, LRESULT* pResult)
{
	theApp.GetMain()->SetFrequency(m_PitchEdit.GetVal());
	*pResult = 0;
}
