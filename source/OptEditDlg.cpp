// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// OptEditDlg.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "OptEditDlg.h"
#include <afxpriv.h>	// for WM_KICKIDLE
#include <shlwapi.h>
#include "NumFormatter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptEditDlg dialog


COptEditDlg::COptEditDlg(CCodeOptionsInfo& Info)
	: CPropertyPage(IDD),
	m_oi(Info)
{
	//{{AFX_DATA_INIT(COptEditDlg)
	m_TempFolderType = 0;
	//}}AFX_DATA_INIT
	m_UndoUnlimited = 0;
}

void COptEditDlg::UpdateTempFolderFreeSpace()
{
	CString	FreeSpace;
	// if custom folder selected but empty path, leave free space blank
	if (!(m_oi.m_CustomTempFolder && m_oi.m_TempFolderPath.IsEmpty())) {
		CString	PrevTempPath(theApp.m_TempFolderPath);
		// set app's temp folder path so GetTempPath uses our current setting
		theApp.m_TempFolderPath = m_oi.GetTempFolderPath();
		CString	TempPath;
		bool	GotTempPath = theApp.GetTempPath(TempPath);
		theApp.m_TempFolderPath = PrevTempPath;	// restore app's temp folder path
		if (GotTempPath) {	// if temporary folder path was obtained
			ULARGE_INTEGER	UserFreeBytes;
			// get free bytes available to user associated with calling thread
			if (GetDiskFreeSpaceEx(TempPath, &UserFreeBytes, NULL, NULL)) {
				CNumFormatter	fmt;
				FreeSpace = fmt.FormatByteSize(UserFreeBytes.QuadPart);
			}
		}
	}
	GetDlgItem(IDC_OPT_EDIT_TEMP_FOLDER_FREE)->SetWindowText(FreeSpace);
}

void COptEditDlg::ValidateFolder(CDataExchange* pDX, int CtrlID, const CString& Path)
{
	if (pDX->m_bSaveAndValidate) {
		CString	msg;
		if (Path.IsEmpty())	// if path is empty
			msg.LoadString(IDS_APP_FOLDER_REQUIRED);
		else {
			CString	AbsPath(Path);
			theApp.MakeAbsolutePath(AbsPath);
			if (!PathFileExists(AbsPath))	// if path doesn't exist
				AfxFormatString1(msg, IDS_APP_FOLDER_NOT_FOUND, AbsPath);
		}
		if (!msg.IsEmpty()) {
			AfxMessageBox(msg);
			DDV_Fail(pDX, CtrlID);
		}
	}
}

void COptEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptEditDlg)
	DDX_Radio(pDX, IDC_OPT_EDIT_TEMP_FOLDER_TYPE, m_TempFolderType);
	//}}AFX_DATA_MAP
	if (!m_UndoUnlimited)
		DDX_Text(pDX, IDC_OPT_EDIT_UNDO_LEVELS, m_oi.m_UndoLevels);
	DDX_Check(pDX, IDC_OPT_EDIT_UNDO_UNLIMITED, m_UndoUnlimited);
	DDX_Text(pDX, IDC_OPT_EDIT_DISK_THRESHOLD, m_oi.m_DiskThreshold);
	DDV_MinMaxInt(pDX, m_oi.m_DiskThreshold, 0, SHRT_MAX);
	DDX_Text(pDX, IDC_OPT_EDIT_TEMP_FOLDER_PATH, m_oi.m_TempFolderPath);
	// if saving and custom folder selected, but folder path doesn't exist
	if (m_TempFolderType)
		ValidateFolder(pDX, IDC_OPT_EDIT_TEMP_FOLDER_PATH, m_oi.m_TempFolderPath);
}

BEGIN_MESSAGE_MAP(COptEditDlg, CPropertyPage)
	//{{AFX_MSG_MAP(COptEditDlg)
	ON_BN_CLICKED(IDC_OPT_EDIT_UNDO_UNLIMITED, OnUndoUnlimited)
	ON_BN_CLICKED(IDC_OPT_EDIT_TEMP_FOLDER_BROWSE, OnTempFolderBrowse)
	ON_BN_CLICKED(IDC_OPT_EDIT_TEMP_FOLDER_TYPE, OnTempFolderType)
	ON_BN_CLICKED(IDC_OPT_EDIT_TEMP_FOLDER_TYPE2, OnTempFolderType)
	ON_EN_KILLFOCUS(IDC_OPT_EDIT_TEMP_FOLDER_PATH, OnKillFocusEditorTempFolderPath)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(IDC_OPT_EDIT_UNDO_LEVELS, OnUpdateUndoLevels)
	ON_UPDATE_COMMAND_UI(IDC_OPT_EDIT_TEMP_FOLDER_PATH, OnUpdateTempFolderPath)
	ON_UPDATE_COMMAND_UI(IDC_OPT_EDIT_TEMP_FOLDER_BROWSE, OnUpdateTempFolderPath)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptEditDlg message handlers

BOOL COptEditDlg::OnInitDialog() 
{
	m_UndoUnlimited = m_oi.m_UndoLevels < 0;
	m_TempFolderType = m_oi.m_CustomTempFolder;

	CPropertyPage::OnInitDialog();
	UpdateTempFolderFreeSpace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptEditDlg::OnOK() 
{
	CPropertyPage::OnOK();
	m_oi.m_CustomTempFolder = m_TempFolderType != 0;
}

LRESULT COptEditDlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
    UpdateDialogControls(this, TRUE);
    return FALSE;
}

void COptEditDlg::OnUndoUnlimited() 
{
	m_UndoUnlimited ^= 1;
	if (m_UndoUnlimited)
		m_oi.m_UndoLevels = -1;
	else {	// limited undo levels
		m_oi.m_UndoLevels = DEFAULT_UNDO_LEVELS;
		CString	sLevels;
		sLevels.Format(_T("%d"), m_oi.m_UndoLevels);
		GetDlgItem(IDC_OPT_EDIT_UNDO_LEVELS)->SetWindowText(sLevels);
	}
}

void COptEditDlg::OnUpdateUndoLevels(CCmdUI* pCmdUI)
{
	BOOL	unlimited = IsDlgButtonChecked(IDC_OPT_EDIT_UNDO_UNLIMITED);
	pCmdUI->Enable(!unlimited);
	if (unlimited)
		pCmdUI->SetText(_T(""));
}

void COptEditDlg::OnTempFolderType() 
{
	int BtnID = GetCheckedRadioButton(
		IDC_OPT_EDIT_TEMP_FOLDER_TYPE, IDC_OPT_EDIT_TEMP_FOLDER_TYPE2);
	m_oi.m_CustomTempFolder = (BtnID == IDC_OPT_EDIT_TEMP_FOLDER_TYPE2);
	UpdateTempFolderFreeSpace();
}

void COptEditDlg::OnKillFocusEditorTempFolderPath() 
{
	GetDlgItem(IDC_OPT_EDIT_TEMP_FOLDER_PATH)->GetWindowText(m_oi.m_TempFolderPath);
	UpdateTempFolderFreeSpace();
}

void COptEditDlg::OnTempFolderBrowse() 
{
	bool	retc = theApp.BrowseFolder(IDS_OPT_SELECT_TEMP_FOLDER, 
		m_oi.m_TempFolderPath, m_hWnd);
	if (retc) {	// if user didn't cancel folder dialog
		GetDlgItem(IDC_OPT_EDIT_TEMP_FOLDER_PATH)->SetWindowText(m_oi.m_TempFolderPath);
		UpdateTempFolderFreeSpace();
	}
}

void COptEditDlg::OnUpdateTempFolderPath(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_oi.m_CustomTempFolder);
}
