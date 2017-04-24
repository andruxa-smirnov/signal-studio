// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_AudioBar_H__3952AAB6_552B_45CB_B970_07578B3A2C6F__INCLUDED_)
#define AFX_AudioBar_H__3952AAB6_552B_45CB_B970_07578B3A2C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AudioBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAudioBar dialog

#include "BaseDialog.h"
#include "ClickSliderController.h"
#include "BtnFlatIco.h"
#include "ControlResizer.h"

class CAudioBar : public CBaseDialog
{
	DECLARE_DYNAMIC(CAudioBar);
// Construction
public:
	CAudioBar(CWnd* pParent = NULL);   // standard constructor
	~CAudioBar();

// Attributes
	double	GetVolume() const;
	void	SetVolume(double Volume);

// Operations

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudioBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CAudioBar)
	enum { IDD = IDD_VOLUME_BAR };
	CBtnFlatIco	m_MuteBtn;
	CClickSliderController	m_VolumeSlider;
	//}}AFX_DATA

// Generated message map functions
	//{{AFX_MSG(CAudioBar)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVolumeMute();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateMute(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()

// Constants
	enum {
		VOLUME_STEPS = 100
	};
	static const CControlResizer::CTRL_LIST	m_CtrlList[];

// Member data
	double	m_Volume;			// current volume
	bool	m_Mute;				// true if muted
	CControlResizer	m_Resize;

// Helpers
	void	UpdatePlayer();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AudioBar_H__3952AAB6_552B_45CB_B970_07578B3A2C6F__INCLUDED_)
