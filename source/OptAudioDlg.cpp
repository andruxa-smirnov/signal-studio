// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// OptAudioDlg.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "OptAudioDlg.h"
#include <afxpriv.h>	// for WM_KICKIDLE
#include "DSCap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptAudioDlg dialog

COptAudioDlg::COptAudioDlg(CCodeOptionsInfo& Info)
	: CPropertyPage(IDD),
	m_oi(Info)
{
	//{{AFX_DATA_INIT(COptAudioDlg)
	//}}AFX_DATA_INIT
}

void COptAudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptAudioDlg)
	DDX_Control(pDX, IDC_OPT_VBR_QUALITY_SLIDER, m_VBRQualitySlider);
	DDX_Control(pDX, IDC_OPT_VBR_QUALITY_EDIT, m_VBRQualityEdit);
	DDX_Control(pDX, IDC_OPT_AUDIO_PLAY_DEVICE, m_PlayDeviceCombo);
	DDX_Control(pDX, IDC_OPT_AUDIO_RECORD_DEVICE, m_RecordDeviceCombo);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_OPT_AUDIO_PLAY_BUF_SIZE, m_oi.m_PlayBufferSize);
	DDV_MinMaxInt(pDX, m_oi.m_PlayBufferSize, 1, SHRT_MAX);
	DDX_Text(pDX, IDC_OPT_AUDIO_RECORD_BUF_SIZE, m_oi.m_RecordBufferSize);
	DDV_MinMaxInt(pDX, m_oi.m_RecordBufferSize, 1, SHRT_MAX);
	DDX_CBIndex(pDX, IDC_OPT_MP3_IMPORT_QUALITY, m_oi.m_MP3ImportQuality);
	DDX_CBIndex(pDX, IDC_OPT_MP4_IMPORT_QUALITY, m_oi.m_MP4ImportQuality);
	DDX_Check(pDX, IDC_OPT_MP4_DOWNMIX, m_oi.m_MP4Downmix);
	DDX_Text(pDX, IDC_OPT_METER_CLIP_THRESHOLD, m_oi.m_MeterClipThreshold);
	DDV_MinMaxInt(pDX, m_oi.m_MeterClipThreshold, 1, INT_MAX);
}

bool COptAudioDlg::PopulatePlayDeviceCombo()
{
	m_PlayDeviceCombo.ResetContent();
	if (!CDSPlayer::EnumDevices(m_PlayDevInfo))	// enumerate playback devices
		return(FALSE);
	PopulateDeviceCombo(m_PlayDeviceCombo, m_PlayDevInfo, m_oi.m_PlayDeviceGuid);
	return(TRUE);
}

bool COptAudioDlg::PopulateRecordDeviceCombo()
{
	m_RecordDeviceCombo.ResetContent();
	if (!CDSCap::EnumDevices(m_RecordDevInfo))	// enumerate capture devices
		return(FALSE);
	PopulateDeviceCombo(m_RecordDeviceCombo, m_RecordDevInfo, m_oi.m_RecordDeviceGuid);
	return(TRUE);
}

void COptAudioDlg::PopulateDeviceCombo(CComboBox& Combo, const CDSDeviceInfoArray& DevInfo, const GUID& DeviceGuid)
{
	int	iSelDev = -1;
	int	iDefaultDev = -1;
	int	devs = DevInfo.GetSize();
	for (int iDev = 0; iDev < devs; iDev++) {	// for each device
		const CDSPlayer::CDSDeviceInfo&	info = DevInfo[iDev];
		Combo.AddString(info.m_Description);
		if (IsEqualGUID(info.m_Guid, DeviceGuid))	// if selected device
			iSelDev = iDev;
		if (IsEqualGUID(info.m_Guid, GUID_NULL))	// if default device
			iDefaultDev = iDev;
	}
	if (iSelDev < 0) {	// if selected device not found
		if (iDefaultDev >= 0)	// if default device was found
			iSelDev = iDefaultDev;	// select default device
		else {	// no default device; shouldn't happen
			Combo.InsertString(0, _T("<default>"));
			iSelDev = 0;
		}
	}
	Combo.SetCurSel(iSelDev);
}

CString COptAudioDlg::GetSelectedDeviceName(CComboBox& Combo, const CDSDeviceInfoArray& DevInfo)
{
	CString	name;
	int	iSelDev = Combo.GetCurSel();
	if (iSelDev >= 0 && iSelDev < DevInfo.GetSize())	// if valid selection
		name = DevInfo[iSelDev].m_Description;
	return(name);
}

BEGIN_MESSAGE_MAP(COptAudioDlg, CPropertyPage)
	//{{AFX_MSG_MAP(COptAudioDlg)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptAudioDlg message handlers

BOOL COptAudioDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	PopulatePlayDeviceCombo();
	PopulateRecordDeviceCombo();
	m_VBRQualitySlider.SetEditCtrl(&m_VBRQualityEdit);
	m_VBRQualityEdit.SetVal(m_oi.m_VBREncodingQuality);
	m_VBRQualityEdit.SetFormat(CNumEdit::DF_INT);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptAudioDlg::OnOK() 
{
	int	sel = m_PlayDeviceCombo.GetCurSel();
	if (sel >= 0)
		m_oi.m_PlayDeviceGuid = m_PlayDevInfo[sel].m_Guid;
	sel = m_RecordDeviceCombo.GetCurSel();
	if (sel >= 0)
		m_oi.m_RecordDeviceGuid = m_RecordDevInfo[sel].m_Guid;
	m_oi.m_VBREncodingQuality = m_VBRQualityEdit.GetIntVal();

	CPropertyPage::OnOK();
}

LRESULT COptAudioDlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
    UpdateDialogControls(this, TRUE);
    return FALSE;
}
