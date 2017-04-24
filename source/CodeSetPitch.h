// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeSetPitch_H__3952AAB6_552B_45CB_B970_07578B3A2C6F__INCLUDED_)
#define AFX_CodeSetPitch_H__3952AAB6_552B_45CB_B970_07578B3A2C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeSetPitch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeSetPitch dialog

#include "BaseDialog.h"
#include "EditSlider.h"
#include "ControlResizer.h"

class CCodeSetPitch : public CBaseDialog
{
	DECLARE_DYNAMIC(CCodeSetPitch);
// Construction
public:
	CCodeSetPitch(CWnd* pParent = NULL);   // standard constructor
	~CCodeSetPitch();

// Attributes
	double	GetPitch() const;
	void	CodeSetPitch(double Pitch);

// Operations

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeSetPitch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// Dialog Data
	//{{AFX_DATA(CCodeSetPitch)
	enum { IDD = IDD_PITCH_BAR };
	CEditSlider	m_PitchSlider;
	CNumEdit	m_PitchEdit;
	//}}AFX_DATA

// Generated message map functions
	//{{AFX_MSG(CCodeSetPitch)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChangedPitch(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateMute(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()

// Constants
	static const CControlResizer::CTRL_LIST	m_CtrlList[];
	static const CEditSlider::INFO	m_SliderInfo;

// Member data
	CControlResizer	m_Resize;

// Helpers
};

inline double CCodeSetPitch::GetPitch() const
{
	return(m_PitchEdit.GetVal());
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeSetPitch_H__3952AAB6_552B_45CB_B970_07578B3A2C6F__INCLUDED_)
