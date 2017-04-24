// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_OptAudioDlg_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_)
#define AFX_OptAudioDlg_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptAudioDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptAudioDlg dialog

#include "CodeOptionsInfo.h"
#include "DSPlayer.h"
#include "EditSlider.h"

class COptAudioDlg : public CPropertyPage
{
// Construction
public:
	COptAudioDlg(CCodeOptionsInfo& Info);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptAudioDlg)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Generated message map functions
	//{{AFX_MSG(COptAudioDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT	OnKickIdle(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Dialog data
	//{{AFX_DATA(COptAudioDlg)
	enum { IDD = IDD_OPT_AUDIO };
	CEditSlider	m_VBRQualitySlider;
	CNumEdit	m_VBRQualityEdit;
	CComboBox	m_PlayDeviceCombo;
	CComboBox	m_RecordDeviceCombo;
	//}}AFX_DATA

// Types
	typedef CDSPlayer::CDSDeviceInfoArray CDSDeviceInfoArray;

// Member data
	CCodeOptionsInfo&	m_oi;		// reference to parent's options info 
	CDSDeviceInfoArray	m_PlayDevInfo;	// playback device info array
	CDSDeviceInfoArray	m_RecordDevInfo;	// record device info array

// Helpers
	bool	PopulatePlayDeviceCombo();
	bool	PopulateRecordDeviceCombo();
	static	void	PopulateDeviceCombo(CComboBox& Combo, const CDSDeviceInfoArray& DevInfo, const GUID& DeviceGuid);
	static	CString	GetSelectedDeviceName(CComboBox& Combo, const CDSDeviceInfoArray& DevInfo);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OptAudioDlg_H__84776AB1_689B_46EE_84E6_931C1542871D__INCLUDED_)
