// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_UISignalGen_H__1A4B9247_AFEE_4CBB_94FE_44885CDAEE1C__INCLUDED_)
#define AFX_UISignalGen_H__1A4B9247_AFEE_4CBB_94FE_44885CDAEE1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UISignalGen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUISignalGen dialog

#include "UISignalGenOsc.h"
#include "SignalGenParameters.h"

class CWave;
class CProgressDlg;
class CUISweepAction;

class CUISignalGen : public CDialog, public WAVEGEN_MAIN_PARMS
{
// Construction
public:
	CUISignalGen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUISignalGen)
	enum { IDD = IDD_WAVE_GEN };
	CTabCtrl	m_OscTab;
	//}}AFX_DATA

// Constants
	enum {	// modulation types
		MOD_NONE,
		MOD_FREQUENCY,
		MOD_AMPLITUDE,
		MOD_PULSE,
	};

// Attributes
	void	GetParms(WAVEGEN_PARMS& Parms) const;
	void	SetParms(const WAVEGEN_PARMS& Parms);

// Operations
	static	bool	MakeWave(const WAVEGEN_PARMS& Parms, CWave& Wave, CProgressDlg *ProgressDlg = NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUISignalGen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Generated message map functions
	//{{AFX_MSG(CUISignalGen)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchangeOscTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnReset();
	afx_msg void OnSweep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Constants
	static const int m_OscName[OSCILLATORS];	// oscillator name string IDs
	static const WAVEGEN_MAIN_PARMS m_Defaults;	// default parameters

// Member data
	CUISignalGenOsc	m_OscDlg[OSCILLATORS];	// oscillator dialogs

// Helpers
	void	ShowOscDlg(int TabIdx);
	void	ResizeOscDlgs();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UISignalGen_H__1A4B9247_AFEE_4CBB_94FE_44885CDAEE1C__INCLUDED_)
