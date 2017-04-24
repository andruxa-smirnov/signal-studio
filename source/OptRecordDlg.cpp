// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// OptCodeRecord.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "OptCodeRecord.h"
#include <afxpriv.h>	// for WM_KICKIDLE
#include "CodeRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptCodeRecord dialog


COptCodeRecord::COptCodeRecord(CCodeOptionsInfo& Info)
	: CPropertyPage(IDD),
	m_oi(Info)
{
	//{{AFX_DATA_INIT(COptCodeRecord)
	//}}AFX_DATA_INIT
	m_SelHotKeyFunc = 0;
}

int COptCodeRecord::GetActivationType()
{
	int	nID = GetCheckedRadioButton(IDC_OPT_REC_ACTIVATION, IDC_OPT_REC_ACTIVATION3);
	int	ActType = nID -= IDC_OPT_REC_ACTIVATION;
	ASSERT(ActType >= 0 && ActType < CCodeRecord::ACTIVATION_TYPES);
	return(ActType);
}

DWORD COptCodeRecord::GetSysHotKey(const CHotKeyCtrl& HotKeyCtrl)
{
	WORD	VKeyCode, HKModFlags;
	HotKeyCtrl.GetHotKey(VKeyCode, HKModFlags);
	WORD	SysModFlags = 0;
	if (HKModFlags & HOTKEYF_ALT)
		SysModFlags |= MOD_ALT;
	if (HKModFlags & HOTKEYF_CONTROL)
		SysModFlags |= MOD_CONTROL;
	if (HKModFlags & HOTKEYF_SHIFT)
		SysModFlags |= MOD_SHIFT;
	return(MAKELONG(VKeyCode, SysModFlags));
}

void COptCodeRecord::SetSysHotKey(CHotKeyCtrl& HotKeyCtrl, DWORD HotKeyDef)
{
	WORD	SysModFlags = HIWORD(HotKeyDef);
	ASSERT(!(SysModFlags & MOD_WIN));	// hot key control doesn't support Windows key
	WORD	HKModFlags = 0;
	if (SysModFlags & MOD_ALT)
		HKModFlags |= HOTKEYF_ALT;
	if (SysModFlags & MOD_CONTROL)
		HKModFlags |= HOTKEYF_CONTROL;
	if (SysModFlags & MOD_SHIFT)
		HKModFlags |= HOTKEYF_SHIFT;
	HotKeyCtrl.SetHotKey(LOWORD(HotKeyDef), HKModFlags);
}

void COptCodeRecord::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptCodeRecord)
	DDX_Control(pDX, IDC_OPT_REC_HOT_KEY_FUNCTION, m_HotKeyFunction);
	DDX_Control(pDX, IDC_OPT_REC_HOT_KEY, m_HotKey);
	DDX_Control(pDX, IDC_OPT_REC_SAMPLE_SIZE, m_SampleSizeCombo);
	DDX_Control(pDX, IDC_OPT_REC_SAMPLE_RATE, m_SampleRateCombo);
	//}}AFX_DATA_MAP
	DDX_Radio(pDX, IDC_OPT_REC_ACTIVATION, m_oi.m_Record.ActivationType);
	DDX_Text(pDX, IDC_OPT_REC_CHANNELS, m_oi.m_Record.Channels);
	DDV_MinMaxUInt(pDX, m_oi.m_Record.Channels, 1, 100);
	DDX_Text(pDX, IDC_OPT_REC_START_DURATION, m_oi.m_Record.StartDuration);
	DDV_MinMaxFloat(pDX, m_oi.m_Record.StartDuration, 0.f, 3600.f);
	DDX_Text(pDX, IDC_OPT_REC_START_LEVEL, m_oi.m_Record.StartLevel);
	DDV_MinMaxFloat(pDX, m_oi.m_Record.StartLevel, -100.f, 0.f);
	DDX_Text(pDX, IDC_OPT_REC_STOP_DURATION, m_oi.m_Record.StopDuration);
	DDV_MinMaxFloat(pDX, m_oi.m_Record.StopDuration, 0.f, 3600.f);
	DDX_Text(pDX, IDC_OPT_REC_STOP_LEVEL, m_oi.m_Record.StopLevel);
	DDV_MinMaxFloat(pDX, m_oi.m_Record.StopLevel, -100.f, 0.f);
	DDX_Text(pDX, IDC_OPT_REC_FOLDER_EDIT, m_oi.m_RecordFolderPath);
	if (m_oi.m_Record.ActivationType != CCodeRecord::ACT_PROMPT)
		COptEditDlg::ValidateFolder(pDX, IDC_OPT_REC_FOLDER_EDIT, m_oi.m_RecordFolderPath);
	CCodeRecord::ValidateSampleRate(pDX, IDC_OPT_REC_SAMPLE_RATE, 
		m_SampleRateCombo, m_oi.m_Record.SampleRate);
	if (pDX->m_bSaveAndValidate)
		m_oi.m_Record.SampleSize = CCodeRecord::GetSampleSize(m_SampleSizeCombo);
}

BEGIN_MESSAGE_MAP(COptCodeRecord, CPropertyPage)
	//{{AFX_MSG_MAP(COptCodeRecord)
	ON_BN_CLICKED(IDC_OPT_REC_FOLDER_BROWSE, OnFolderBrowse)
	ON_CBN_SELCHANGE(IDC_OPT_REC_HOT_KEY_FUNCTION, OnSelchangeHotKeyFunction)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(IDC_OPT_REC_FOLDER_EDIT, OnUpdateFolderPath)
	ON_UPDATE_COMMAND_UI(IDC_OPT_REC_FOLDER_BROWSE, OnUpdateFolderPath)
	ON_UPDATE_COMMAND_UI(IDC_OPT_REC_START_LEVEL, OnUpdateTriggers)
	ON_UPDATE_COMMAND_UI(IDC_OPT_REC_START_DURATION, OnUpdateTriggers)
	ON_UPDATE_COMMAND_UI(IDC_OPT_REC_STOP_LEVEL, OnUpdateTriggers)
	ON_UPDATE_COMMAND_UI(IDC_OPT_REC_STOP_DURATION, OnUpdateTriggers)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptCodeRecord message handlers

BOOL COptCodeRecord::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	CCodeRecord::InitSampleRateCombo(m_SampleRateCombo, m_oi.m_Record.SampleRate);
	CCodeRecord::InitSampleSizeCombo(m_SampleSizeCombo, m_oi.m_Record.SampleSize);
	m_HotKeyFunction.SetCurSel(0);
	// disallow unmodified keys and keys only modified by Alt, to reduce conflict
	m_HotKey.SetRules(HKCOMB_NONE | HKCOMB_A, HOTKEYF_SHIFT);
	SetSysHotKey(m_HotKey, m_oi.m_Record.HotKeys.Def[0]);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptCodeRecord::OnOK() 
{
	m_oi.m_Record.HotKeys.Def[m_SelHotKeyFunc] = GetSysHotKey(m_HotKey);

	CPropertyPage::OnOK();
}

LRESULT COptCodeRecord::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
    UpdateDialogControls(this, TRUE);
    return FALSE;
}

void COptCodeRecord::OnFolderBrowse() 
{
	bool	retc = theApp.BrowseFolder(IDS_OPT_SELECT_RECORD_FOLDER, 
		m_oi.m_RecordFolderPath, m_hWnd);
	if (retc) {	// if user didn't cancel folder dialog
		GetDlgItem(IDC_OPT_REC_FOLDER_EDIT)->SetWindowText(m_oi.m_RecordFolderPath);
	}
}

void COptCodeRecord::OnUpdateFolderPath(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetActivationType() != CCodeRecord::ACT_PROMPT);
}

void COptCodeRecord::OnUpdateTriggers(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetActivationType() == CCodeRecord::ACT_SOUND);
}

void COptCodeRecord::OnSelchangeHotKeyFunction() 
{
	m_oi.m_Record.HotKeys.Def[m_SelHotKeyFunc] = GetSysHotKey(m_HotKey);
	int	sel = m_HotKeyFunction.GetCurSel();
	ASSERT(sel >= 0 && sel < RECORD_PARMS::HOT_KEYS);
	SetSysHotKey(m_HotKey, m_oi.m_Record.HotKeys.Def[sel]);
	m_SelHotKeyFunc = sel;
}
