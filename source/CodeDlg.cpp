// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// CodeDlg.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCodeDlg dialog

#define RK_FIND_START	_T("FindStart")
#define RK_FIND_END		_T("FindEnd")
#define RK_FIND_UNIT	_T("FindUnit")
#define RK_FIND_MATCH	_T("FindMatch")
#define RK_FIND_DIR		_T("FindDir")
#define RK_FIND_WRAP	_T("FindWrap")
#define RK_FIND_CHANNEL	_T("FindChannel")

CCodeDlg::CCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CCodeDlg)
	m_TargetStart = 0.0;
	m_TargetEnd = 0.0;
	m_Unit = 0;
	m_Match = 0;
	m_Dir = 0;
	m_Wrap = TRUE;
	//}}AFX_DATA_INIT
	theApp.RdReg2Double(RK_FIND_START, m_TargetStart);
	theApp.RdReg2Double(RK_FIND_END, m_TargetEnd);
	theApp.RdReg2Int(RK_FIND_UNIT, m_Unit);
	theApp.RdReg2Int(RK_FIND_MATCH, m_Match);
	theApp.RdReg2Int(RK_FIND_DIR, m_Dir);
	theApp.RdReg2Int(RK_FIND_WRAP, m_Wrap);
	m_Channel = theApp.RdRegInt(RK_FIND_CHANNEL, -1);	// not in AFX data init
}

CCodeDlg::~CCodeDlg()
{
	theApp.WrRegDouble(RK_FIND_START, m_TargetStart);
	theApp.WrRegDouble(RK_FIND_END, m_TargetEnd);
	theApp.WrRegInt(RK_FIND_UNIT, m_Unit);
	theApp.WrRegInt(RK_FIND_MATCH, m_Match);
	theApp.WrRegInt(RK_FIND_DIR, m_Dir);
	theApp.WrRegInt(RK_FIND_WRAP, m_Wrap);
	theApp.WrRegInt(RK_FIND_CHANNEL, m_Channel);
}

CCodeDlg::CSampleRange CCodeDlg::GetTargetRange() const
{
	CDblRange	target(GetTargetRange(m_Unit));
	return(CSampleRange(round(target.Start), round(target.End)));
}

CDblRange CCodeDlg::GetTargetRange(int Unit) const
{
	CSignalStudioView	*view = theApp.GetMain()->GetView();
	ASSERT(view != NULL);
	CSignalProcess::CConvert	norm(view->GetWave());
	return(CDblRange(
		norm.UnitToSample(m_TargetStart, Unit),
		norm.UnitToSample(m_TargetEnd, Unit)));
}

void CCodeDlg::SetTargetRange(CDblRange Target, int Unit)
{
	CSignalStudioView	*view = theApp.GetMain()->GetView();
	ASSERT(view != NULL);
	CSignalProcess::CConvert	norm(view->GetWave());
	m_TargetStart = norm.SampleToUnit(Target.Start, Unit),
	m_TargetEnd = norm.SampleToUnit(Target.End, Unit);
}

void CCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCodeDlg)
	DDX_Text(pDX, IDC_FIND_TARGET_START, m_TargetStart);
	DDX_Text(pDX, IDC_FIND_TARGET_END, m_TargetEnd);
	DDX_Radio(pDX, IDC_FIND_UNIT, m_Unit);
	DDX_Radio(pDX, IDC_FIND_MATCH, m_Match);
	DDX_Radio(pDX, IDC_FIND_DIR, m_Dir);
	DDX_Check(pDX, IDC_FIND_WRAP, m_Wrap);
	DDX_Control(pDX, IDC_FIND_CHANNEL, m_ChannelCombo);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCodeDlg message map

BEGIN_MESSAGE_MAP(CCodeDlg, CDialog)
	//{{AFX_MSG_MAP(CCodeDlg)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_FIND_UNIT, IDC_FIND_UNIT3, OnUnit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCodeDlg message handlers

BOOL CCodeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CSignalStudioView	*view = theApp.GetMain()->GetView();
	CSignalProcess&	wave = view->GetWave();
	CStringArray	ChanName;
	wave.GetChannelNames(ChanName);
	int	chans = wave.GetChannels();
	m_ChannelCombo.AddString(LDS(IDS_FIND_ALL_CHANNELS));
	for (int iChan = 0; iChan < chans; iChan++)
		m_ChannelCombo.AddString(ChanName[iChan]);
	m_ChannelCombo.SetCurSel(m_Channel + 1);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCodeDlg::OnOK() 
{
	m_Channel = m_ChannelCombo.GetCurSel() - 1;
	CDialog::OnOK();
}

void CCodeDlg::OnUnit(UINT nID) 
{
	int	PrevUnit = m_Unit;	// copy unit before retrieving data
	UpdateData();	// retrieve data
	// convert target from previous unit to new unit
	SetTargetRange(GetTargetRange(PrevUnit), m_Unit);
	UpdateData(FALSE);	// store data
}
