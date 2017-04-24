// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#pragma once

#include <afxtempl.h>
#include "DSPlayer.h"

struct VIEW_PALETTE {
	#define VIEW_COLOR_DEF(name, tag, R, G, B) tag,
	enum {	// palette as enum
		#include "ShowColours.h"
		COLORS
	};
	union {
		#define VIEW_COLOR_DEF(name, tag, R, G, B) COLORREF name;
		struct {	// palette as struct
			#include "ShowColours.h"
		};
		COLORREF	Color[COLORS];	// palette as color array
	};
};

struct RTSA_PARMS {	// real-time spectrum analyzer parameters
	int		WindowFunction;		// index of window function
	int		WindowSize;			// window size, in frames; must be a power of two
	int		Averaging;			// number of additional windows to analyze per clock
	int		PlotStyle;			// plot style; see enum in CodeSpectrum.h
	int		FreqAxisType;		// if non-zero, frequency axis is logarithmic
	int		ChannelMode;		// if non-zero, separate channels, else combine them
	int		ShowPeaks;			// show peaks style; see enum in CodeSpectrum.h
	int		PeakHoldTime;		// peak hold duration, in milliseconds
	int		PeakDecay;			// peak decay, in decibels per second
	COLORREF	PlotBkgndColor;	// plot background color
	COLORREF	PlotGridColor;	// plot grid color
};

struct RECORD_PARMS {	// record parameters
	enum {	// hot key functions; append only, don't reorder
		HK_START,				// start recording
		HK_STOP,				// stop recording
		HOT_KEYS
	};
	struct HOT_KEY_DEFS {
		DWORD	Def[HOT_KEYS];	// array of system-wide hot key definitions
	};
	int		ActivationType;		// activation type; see enum in CodeRecord.h
	UINT	Channels;			// number of channels
	UINT	SampleRate;			// sample rate, in Hertz
	UINT	SampleSize;			// sample size, in bits
	float	StartLevel;			// level at which recording starts, in decibels
	float	StartDuration;		// minimum duration of start level, in seconds
	float	StopLevel;			// level at which recording stops, in decibels
	float	StopDuration;		// minimum duration of stop level, in seconds
	HOT_KEY_DEFS	HotKeys;	// hot key definitions
};

struct CUSTOM_COLORS {
	COLORREF	Color[16];	// for color dialog
};

struct OPTIONS_INFO {
	int		m_ZoomStepHorz;		// horizontal zoom step as a percentage
	int		m_ZoomStepVert;		// vertical zoom step as a percentage
	bool	m_TimeInFrames;		// if true, show time in sample frames
	bool	m_VertSyncChans;	// if true, vertically synchronize channels
	bool	m_VertZoomCursor;	// if true, vertical zoom origin is cursor
	bool	m_ShowInterpolation;	// if true, highlight interpolation
	bool	m_CheckForUpdates;	// if true, automatically check for updates
	bool	m_ShowChannelNames;	// if true, display channel names in view
	bool	m_CustomTempFolder;	// if true, use custom temporary files folder
	bool	m_MP4Downmix;		// if true, mix MP4 surround down to stereo
	int		m_UndoLevels;		// undo levels, or -1 for unlimited
	UINT	m_PlayBufferSize;	// size of playback buffer, in milliseconds
	UINT	m_RecordBufferSize;	// size of recording buffer, in milliseconds
	int		m_DiskThreshold;	// size above which to use disk storage, in MB
	int		m_MaxDensity;		// view maximum density, in samples per pixel
	int		m_MP3ImportQuality;	// MP3 import quality: 0 == 16-bit, 1 == 24-bit
	int		m_VBREncodingQuality;	// VBR encoding quality, from 0 to 100
	int		m_MP4ImportQuality;	// MP4 import quality: 0 == 16-bit, 1 == 24-bit
	int		m_MeterClipThreshold;	// number of consecutive samples on the rails
	VIEW_PALETTE	m_ViewPalette;	// view palette
	CUSTOM_COLORS	m_CustomColors;	// custom colors for color dialog
	RTSA_PARMS	m_RTSA;			// real-time spectrum analyzer parameters
	RECORD_PARMS	m_Record;	// record parameters
};

class CCodeOptionsInfo : public CObject, public OPTIONS_INFO {
public:
	DECLARE_SERIAL(CCodeOptionsInfo);

// Construction
	CCodeOptionsInfo();
	CCodeOptionsInfo(const CCodeOptionsInfo& Info);
	CCodeOptionsInfo(const OPTIONS_INFO& CodeOptionsInfo);
	CCodeOptionsInfo& operator=(const CCodeOptionsInfo& Info);

// Attributes
	void	SetCodeOptionsInfo(const OPTIONS_INFO& CodeOptionsInfo);
	CString	GetTempFolderPath() const;

// Operations
	void	Load();
	void	Store();

// Constants
	enum {
		ARCHIVE_VERSION = 1			// archive version number
	};
	static const OPTIONS_INFO	m_DefaultCodeOptionsInfo;	// default scalar options
	static const CCodeOptionsInfo	m_Defaults;				// default options

// Public data; members MUST be included in Copy
	GUID	m_PlayDeviceGuid;	// identifier of selected playback device
	GUID	m_RecordDeviceGuid;	// identifier of selected recording device
	CString	m_TempFolderPath;	// path to temporary files folder
	CString	m_RecordFolderPath;	// path to folder for recordings

// Operations
	OPTIONS_INFO&	GetBaseInfo();

protected:
// Helpers
	void	Copy(const CCodeOptionsInfo& Info);
};

inline CCodeOptionsInfo::CCodeOptionsInfo(const CCodeOptionsInfo& Info)
{
	Copy(Info);
}

inline CCodeOptionsInfo& CCodeOptionsInfo::operator=(const CCodeOptionsInfo& Info)
{
	Copy(Info);
	return(*this);
}

inline void CCodeOptionsInfo::SetCodeOptionsInfo(const OPTIONS_INFO& CodeOptionsInfo)
{
	OPTIONS_INFO::operator=(CodeOptionsInfo);
}

inline CCodeOptionsInfo::CCodeOptionsInfo(const OPTIONS_INFO& CodeOptionsInfo)
{
	SetCodeOptionsInfo(CodeOptionsInfo);
}

inline OPTIONS_INFO& CCodeOptionsInfo::GetBaseInfo()
{
	return(*this);	// automatic upcast to base struct
}
