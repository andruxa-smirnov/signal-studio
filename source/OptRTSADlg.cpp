// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// OptRTSADlg.cpp : implementation file

#include "stdafx.h"
#include "SignalStudio.h"
#include "OptRTSADlg.h"
#include <afxpriv.h>	// for WM_KICKIDLE
#include "UISpectrum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptRTSADlg dialog

COptRTSADlg::COptRTSADlg(CCodeOptionsInfo& Info)
	: CPropertyPage(IDD),
	m_oi(Info)
{
	//{{AFX_DATA_INIT(COptRTSADlg)
	//}}AFX_DATA_INIT
}

void COptRTSADlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptRTSADlg)
	DDX_Control(pDX, IDC_RTSA_COLOR_PLOT_GRID, m_GridSwatch);
	DDX_Control(pDX, IDC_RTSA_COLOR_PLOT_BKGND, m_BkgndSwatch);
	DDX_Control(pDX, IDC_RTSA_AVERAGING_SPIN, m_AveragingSpin);
	DDX_Control(pDX, IDC_RTSA_WINDOW_SIZE, m_WindowSizeCombo);
	DDX_Control(pDX, IDC_RTSA_WINDOW_FUNC, m_WindowFuncCombo);
	//}}AFX_DATA_MAP
	DDX_CBIndex(pDX, IDC_RTSA_CHANNEL_MODE, m_oi.m_RTSA.ChannelMode);
	DDX_CBIndex(pDX, IDC_RTSA_FREQ_AXIS, m_oi.m_RTSA.FreqAxisType);
	DDX_CBIndex(pDX, IDC_RTSA_PLOT_STYLE, m_oi.m_RTSA.PlotStyle);
	DDX_Text(pDX, IDC_RTSA_AVERAGING_EDIT, m_oi.m_RTSA.Averaging);
	DDV_MinMaxInt(pDX, m_oi.m_RTSA.Averaging, CCodeSpectrum::MIN_AVERAGING, CCodeSpectrum::MAX_AVERAGING);
	DDX_CBIndex(pDX, IDC_RTSA_SHOW_PEAKS, m_oi.m_RTSA.ShowPeaks);
	DDX_Text(pDX, IDC_RTSA_PEAK_HOLD, m_oi.m_RTSA.PeakHoldTime);
	// peak hold counter is a byte, limiting hold time to around 13 seconds
	int	MaxPeakHoldTime = 255 * 1000 / CMainFrame::GetTimerFrequency();
	DDV_MinMaxInt(pDX, m_oi.m_RTSA.PeakHoldTime, 0, MaxPeakHoldTime);
	DDX_Text(pDX, IDC_RTSA_PEAK_DECAY, m_oi.m_RTSA.PeakDecay);
	DDV_MinMaxInt(pDX, m_oi.m_RTSA.PeakDecay, 0, 10000);
}

BEGIN_MESSAGE_MAP(COptRTSADlg, CPropertyPage)
	//{{AFX_MSG_MAP(COptRTSADlg)
	ON_BN_CLICKED(IDC_RTSA_COLOR_PLOT_BKGND, OnColorPlotBkgnd)
	ON_BN_CLICKED(IDC_RTSA_COLOR_PLOT_GRID, OnColorPlotGrid)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptRTSADlg message handlers

BOOL COptRTSADlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	CUISpectrum::InitWindowFunctionCombo(m_WindowFuncCombo, m_oi.m_RTSA.WindowFunction);
	CUISpectrum::InitWindowSizeCombo(m_WindowSizeCombo, m_oi.m_RTSA.WindowSize);
	GetDlgItem(IDC_RTSA_AVERAGING_SPIN)->SendMessage(	// set spin control range
		UDM_SETRANGE32, CCodeSpectrum::MIN_AVERAGING, CCodeSpectrum::MAX_AVERAGING);
	m_BkgndSwatch.SetColor(m_oi.m_RTSA.PlotBkgndColor);
	m_GridSwatch.SetColor(m_oi.m_RTSA.PlotGridColor);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptRTSADlg::OnOK() 
{
	int	sel = m_WindowFuncCombo.GetCurSel();
	ASSERT(sel >= 0);
	m_oi.m_RTSA.WindowFunction = INT64TO32(m_WindowFuncCombo.GetItemData(sel));
	sel = m_WindowSizeCombo.GetCurSel();
	ASSERT(sel >= 0);
	m_oi.m_RTSA.WindowSize = INT64TO32(m_WindowSizeCombo.GetItemData(sel));
	m_oi.m_RTSA.PlotBkgndColor = m_BkgndSwatch.GetColor();
	m_oi.m_RTSA.PlotGridColor = m_GridSwatch.GetColor();
	CPropertyPage::OnOK();
}

LRESULT COptRTSADlg::OnKickIdle(WPARAM wParam, LPARAM lParam)
{
    UpdateDialogControls(this, TRUE);
    return FALSE;
}

void COptRTSADlg::OnColorPlotBkgnd() 
{
	m_BkgndSwatch.EditColor(m_oi.m_CustomColors.Color);
}

void COptRTSADlg::OnColorPlotGrid() 
{
	m_GridSwatch.EditColor(m_oi.m_CustomColors.Color);
}
