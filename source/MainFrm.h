// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// MainFrm.h : interface of the CMainFrame class

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__7D2DA52E_FBA8_45CB_9C09_A4779D4F1975__INCLUDED_)
#define AFX_MAINFRM_H__7D2DA52E_FBA8_45CB_9C09_A4779D4F1975__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UISignalGen.h"
#include "CodeOptions.h"
#include "DSPlayer.h"
#include "NavBar.h"
#include "AudioBar.h"
#include "CodeSetPitch.h"
#include "SignalStudioDoc.h"
#include "SignalStudioView.h"
#include "CodeViewResults.h"
#include "HistoryTool.h"
#include "CodeMeterBar.h"
#include "CodeSpectrum.h"
#include "CodeRecord.h"
#include "PluginManager.h"

#define MAKEBARID(idx) (AFX_IDW_CONTROLBAR_FIRST + 32 + idx)

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Constants
	enum {	// control bar indices
		// APPEND ONLY: this list generates unique IDs for the bars
		CBI_TRANSPORT,
		CBI_NAV,
		CBI_VOLUME,
		CBI_PITCH,
		CBI_RESULTS,
		CBI_HISTORY,
		CBI_METER,
		CBI_SPECTRUM,
		CONTROL_BARS
	};

// Types
	class CPlay : public WObject {
	public:
		CPlay(CSignalStudioView *View = NULL, bool Enable = FALSE);
		~CPlay();
		static	int		GetInstanceCount();

	protected:
		CSignalStudioView *m_View;		// pointer to caller's view
		bool	m_WasPlaying;		// true if playing when created
		WAVEFORMATEXTENSIBLE	m_WaveFormat;	// previous audio format
		static	int		m_Instances;	// number of instances of this object
	};

// Attributes
public:
	CSignalStudioView	*GetView();
	CSignalProcess	*GetViewWave();
	CSignalStudioView	*GetPlayerView();
	const CCodeOptionsInfo&	GetOptions() const;
	void	SetOptions(const CCodeOptionsInfo& Options);
	void	SetRTSAParms(const RTSA_PARMS& Parms);
	void	SetRecordParms(const RECORD_PARMS& Parms);
	void	SetOptionsPage(int PageIdx);
	CStatusBar&	GetStatusBar();
	CNavBar& GetNavBar();
	CAudioBar&	GetAudioBar();
	CCodeSetPitch&	GetCodeSetPitch();
	CCodeViewResults&	GetCodeViewResults();
	CHistoryTool&	GetHistoryTool();
	CMeterBar&	GetMeterBar();
	CCodeSpectrum&	GetCodeSpectrum();
	CRetractManager	*GetRetractManager();
	CPluginManager&	GetPluginManager();	
	void	SetNow(double Now, bool Center = FALSE);
	void	SetSelection(const CDblRange& Sel);
	void	SetCursorWavePos(CString Pos);
	bool	IsChannelBarVisible() const;
	HACCEL	GetAccelTable() const;
	bool	IsOpen() const;
	bool	IsPlaying() const;
	bool	IsViewPlaying(const CSignalStudioView *View) const;
	bool	ActivePlayer();
	double	GetVolume() const;
	bool	SetVolume(double Volume);
	double	GetFrequency() const;
	bool	SetFrequency(double Frequency);
	bool	GetRepeat() const;
	bool	SetRepeat(bool Enable);
	bool	IsRecording() const;
	static	int		GetTimerFrequency();

// Handlers
	void	OnActivateView(CSignalStudioView *View);
	void	OnDestroyView(CSignalStudioView *View);
	void	OnUpdateUndoTitles();
	void	OnWaveFormatChange();

// Operations
public:
	bool	UpdatePlayerState();
	bool	Open(CWave& Wave);
	bool	Close();
	bool	SetPlaying(bool Enable);
	bool	Stop();
	bool	Seek(double Frame);
	bool	SetLoopPoints(const CDblRange& Sel);
	bool	SetPosition(double Pos);
	bool	MakeWave(const WAVEGEN_PARMS& Parms);
	void	ApplyOptions(const CCodeOptionsInfo& PrevOpts);
	void	ShowChannelBar(bool Enable);
	bool	Find(CSignalProcess::FIND_SAMPLE_INFO& FindInfo, bool First);
	bool	CheckForUpdates(bool Explicit);
	bool	Record(bool Enable);
	void	RegisterHotKeys();
	void	UnregisterHotKeys();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnAppCheckForUpdates();
	afx_msg void OnAudioGenerate();
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnEditOptions();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(W64UINT nIDEvent);
	afx_msg void OnTransportLoop();
	afx_msg void OnTransportPlay();
	afx_msg void OnTransportRecord();
	afx_msg void OnTransportRewind();
	afx_msg void OnTransportStop();
	afx_msg void OnUpdateTransportLoop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransportPlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransportRecord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransportRewind(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransportStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewChannelBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewHistoryTool(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewMeterBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewNavigationBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewCodeSetPitch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewCodeViewResults(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewCodeSpectrum(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewTransportBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewAudioBar(CCmdUI* pCmdUI);
	afx_msg void OnViewChannelBar();
	afx_msg void OnViewHistoryTool();
	afx_msg void OnViewMeterBar();
	afx_msg void OnViewNavigationBar();
	afx_msg void OnViewCodeSetPitch();
	afx_msg void OnViewCodeViewResults();
	afx_msg void OnViewCodeSpectrum();
	afx_msg void OnViewTransportBar();
	afx_msg void OnViewAudioBar();
	//}}AFX_MSG
	afx_msg void OnUpdateIndicatorChannels(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorSampleRate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorSampleBits(CCmdUI *pCmdUI);
	afx_msg LRESULT	OnHandleDlgKey(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnModelessDestroy(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnInitialRecord(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnPluginsFound(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnHotKey(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

// Types
	struct BAR_INFO {
		int		Offset;		// offset of instance within this class
		int		BarID;		// control bar ID
		int		BarResID;	// control bar's resource ID
		int		CaptionID;	// string resource ID of bar's caption
		int		DockStyle;	// docking style flags
		int		LeftOf;		// offset of control bar to left, if any
		BOOL	InitShow;	// true if bar should show on initial run
		int		DockBarID;	// dock bar ID for initial docking
	};
	typedef UINT (CALLBACK *CKUPDATE_PTR)(HWND hWnd, LPCTSTR TargetAppName, UINT Flags);
	struct INDICATOR_CACHE {
		UINT	SampleBits;	// bits per sample
		UINT	Channels;	// channel count
		UINT	SampleRate;	// sampling frequency in Hz
	};

// Constants
	enum {	// status panes
		SBP_MESSAGE,
		SBP_SAMPLE_SIZE,
		SBP_CHANNEL_COUNT,
		SBP_SAMPLE_RATE,
		SBP_CURSOR_WAVE_POS,
		STATUS_BAR_PANES
	};
	enum {	// tool bars
		TB_TOOLBAR,
		TB_TRANSPORT,
		TOOLBARS
	};
	enum {	// dialog bars
		DB_NAVIGATION,
		DB_VOLUME,
		DB_PITCH,
		DIALOG_BARS
	};
	enum {	// sizing control bars
		SCB_RESULTS,
		SCB_HISTORY,
		SCB_METER,
		SCB_SPECTRUM,
		SIZING_BARS
	};
	enum {
		TIMER_ID = 100,			// timer identifier
		TIMER_FREQUENCY = 20,	// timer frequency, in Hz
	};
	static const BAR_INFO m_ToolbarInfo[TOOLBARS];
	static const BAR_INFO m_DlgBarInfo[DIALOG_BARS];
	static const BAR_INFO m_SizingBarInfo[SIZING_BARS];

// Data members
	bool	m_WasShown;			// true if window was shown
	bool	m_ShowChannelBar;	// true if showing channel bar
	CStatusBar  m_StatusBar;	// status bar
	CToolBar    m_ToolBar;		// tool bar
	CToolBar    m_TransportBar;	// transport bar
	CNavBar		m_NavBar;		// navigation bar
	CAudioBar	m_AudioBar;	// volume bar
	CCodeSetPitch	m_CodeSetPitch;		// pitch bar
	CCodeViewResults	m_CodeViewResults;	// results bar
	CHistoryTool	m_HistoryTool;	// history bar
	CMeterBar	m_MeterBar;		// meter bar
	CCodeSpectrum	m_CodeSpectrum;	// spectrum meter bar
	CSignalStudioView	*m_View;	// active view if any, else null
	CSignalStudioView	*m_PlayerView;	// view that owns the player if any, else null
	WAVEGEN_PARMS	m_SignalGenParameters;	// wave generation parameters
	CCodeOptionsInfo	m_Options;	// options
	int		m_OptionsPage;		// index of selected options page
	CDSPlayer	m_Player;		// DirectShow player
	CSignalProcess::FIND_SAMPLE_INFO	m_FindInfo;	// find sample info
	INDICATOR_CACHE	m_IndicatorCache;	// indicator cached values
	CCodeRecord	*m_CodeRecord;	// pointer to record dialog
	CPluginManager	m_PluginMgr;	// plugin manager

// Helpers
	CControlBar	*GetBarAtOffset(int Offset);
	BOOL	VerifyBarState(LPCTSTR lpszProfileName);
	static	BOOL	VerifyDockState(const CDockState& state, CFrameWnd *Frm);
	bool	CreateToolbars();
	bool	CreateDialogBars();
	bool	CreateSizingBars();
	static	void	ShowButton(CToolBar& ToolBar, int CmdID, bool Enable);
	static	UINT	CheckForUpdatesThreadFunc(LPVOID Param);
	static	UINT	IteratePluginsThread(LPVOID Param);
};

inline int CMainFrame::CPlay::GetInstanceCount()
{
	return(m_Instances);
}

inline CSignalStudioView *CMainFrame::GetView()
{
	return(m_View);
}

inline CSignalProcess *CMainFrame::GetViewWave()
{
	if (m_View != NULL)
		return(&m_View->GetWave());
	return(NULL);
}

inline CSignalStudioView *CMainFrame::GetPlayerView()
{
	return(m_PlayerView);
}

inline const CCodeOptionsInfo& CMainFrame::GetOptions() const
{
	return(m_Options);
}

inline void CMainFrame::SetRTSAParms(const RTSA_PARMS& Parms)
{
	m_Options.m_RTSA = Parms;
}

inline void CMainFrame::SetRecordParms(const RECORD_PARMS& Parms)
{
	m_Options.m_Record = Parms;
}

inline void CMainFrame::SetOptionsPage(int PageIdx)
{
	ASSERT(PageIdx >= 0 && PageIdx < CCodeOptions::OPTIONS_PAGES);
	m_OptionsPage = PageIdx;
}

inline CStatusBar& CMainFrame::GetStatusBar()
{
	return(m_StatusBar);
}

inline CNavBar& CMainFrame::GetNavBar()
{
	return(m_NavBar);
}

inline CAudioBar& CMainFrame::GetAudioBar()
{
	return(m_AudioBar);
}

inline CCodeSetPitch& CMainFrame::GetCodeSetPitch()
{
	return(m_CodeSetPitch);
}

inline CCodeViewResults& CMainFrame::GetCodeViewResults()
{
	return(m_CodeViewResults);
}

inline CHistoryTool& CMainFrame::GetHistoryTool()
{
	return(m_HistoryTool);
}

inline CMeterBar& CMainFrame::GetMeterBar()
{
	return(m_MeterBar);
}

inline CCodeSpectrum& CMainFrame::GetCodeSpectrum()
{
	return(m_CodeSpectrum);
}

inline bool CMainFrame::IsChannelBarVisible() const
{
	return(m_ShowChannelBar);
}

inline HACCEL CMainFrame::GetAccelTable() const
{
	return(m_hAccelTable);
}

inline bool CMainFrame::IsOpen() const
{
	return(m_Player.IsOpen());
}

inline bool CMainFrame::IsPlaying() const
{
	return(m_Player.IsPlaying());
}

inline bool CMainFrame::ActivePlayer()
{
	return(m_View == m_PlayerView);	// true if active view owns player
}

inline int CMainFrame::GetTimerFrequency()
{
	return(TIMER_FREQUENCY);
}

inline double CMainFrame::GetVolume() const
{
	return(m_AudioBar.GetVolume());
}

inline double CMainFrame::GetFrequency() const
{
	return(m_CodeSetPitch.GetPitch());
}

inline bool CMainFrame::GetRepeat() const
{
	return(m_Player.GetRepeat());
}

inline bool CMainFrame::IsRecording() const
{
	return(m_CodeRecord != NULL && m_CodeRecord->IsRecording());
}

inline CPluginManager& CMainFrame::GetPluginManager()
{
	return(m_PluginMgr);
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7D2DA52E_FBA8_45CB_9C09_A4779D4F1975__INCLUDED_)
