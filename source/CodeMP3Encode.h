// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeMP3Encode_H__5B0BA7CC_5869_4247_B498_7B32EDAC8F75__INCLUDED_)
#define AFX_CodeMP3Encode_H__5B0BA7CC_5869_4247_B498_7B32EDAC8F75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeMP3Encode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeMP3Encode dialog

#include "LameWrapper.h"

class CCodeMP3Encode : public CDialog
{
// Construction
public:
	CCodeMP3Encode(CWnd* pParent = NULL);   // standard constructor
	~CCodeMP3Encode();

// Attributes
	void	GetParams(CLameWrapper::ENCODING_PARAMS& Params) const;

// Operations
	static	bool	Encode(LPCTSTR Path, const CWave& Wave, const CStringArray *Metadata = NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeMP3Encode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CCodeMP3Encode)
	enum { IDD = IDD_MP3_ENCODER };
	CClickSliderController	m_TargetQualitySlider;
	CComboBox	m_TargetBitRateCombo;
	int		m_BitRateMode;
	int		m_AlgorithmQualityPresetIdx;
	//}}AFX_DATA

// Generated message map functions
	//{{AFX_MSG(CCodeMP3Encode)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg	LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	afx_msg	void OnUpdateTargetBitRate(CCmdUI* pCmdUI);
	afx_msg	void OnUpdateTargetQuality(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

// Constants
	enum {	// algorithm quality presets
		AQP_FAST,
		AQP_STANDARD,
		AQP_HIGH_QUALITY,
		ALG_QUALITY_PRESETS
	};
	enum {
		MAX_VBR_QUALITY = 9
	};
	static const int	m_AlgorithmQualityPreset[ALG_QUALITY_PRESETS];
	static const int	m_BitRatePreset[];

// Member data
	int		m_AlgorithmQuality;	// encoder algorithm quality [0..9]
								// 0=slowest/best, 9=fastest/worst
	int		m_TargetBitRate;	// target bitrate in kbits/s; applicable
								// in constant and average modes only
	int		m_TargetQuality;	// target quality [0..9] 0=slowest/best, 
								// 9=fastest/worst; for variable mode only
// Helpers
	bool	LimitQuality();
	int		FindAlgorithmQuality(int Quality) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeMP3Encode_H__5B0BA7CC_5869_4247_B498_7B32EDAC8F75__INCLUDED_)
