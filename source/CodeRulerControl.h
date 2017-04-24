// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#if !defined(AFX_CodeRulerControl_H__490CA5D7_29D1_4381_9849_416A9904451A__INCLUDED_)
#define AFX_CodeRulerControl_H__490CA5D7_29D1_4381_9849_416A9904451A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CodeRulerControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCodeRulerControl window

#include "ArrayEx.h"

class CCodeRulerControl : public CWnd
{
	DECLARE_DYNAMIC(CCodeRulerControl)
// Construction
public:
	CCodeRulerControl();
	BOOL	Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Types
	struct TICK {
		int		Pos;		// tick's x or y position in client coords
		bool	IsMinor;	// true if minor tick, otherwise major tick
	};
	typedef CArrayEx<TICK, TICK&> CTickArray;

// Constants
	enum {	// ruler styles
		HIDE_CLIPPED_VALS	= 0x0001,	// hide values that would otherwise be clipped
		ENFORCE_MARGINS		= 0x0002,	// hide ticks that would lie outside margins
		LOG_SCALE			= 0x0004,	// use logarithmic scale
		// all control bar alignment styles (CBRS_ALIGN_*) are also supported 
	};
	enum {	// define units
		UNIT_METRIC,
		UNIT_ENGLISH,
		UNIT_TIME,
		UNIT_LOG,
		UNITS
	};
	enum {	// define numeric formats
		NF_FIXED,
		NF_EXPONENT,
		NF_GENERIC,
		NUMERIC_FORMATS
	};

// Attributes
public:
	bool	IsVertical() const;
	int		GetUnit() const;
	void	SetUnit(int Unit);
	double	GetZoom() const;
	void	SetZoom(double Zoom);
	void	SetZoom(int Pos, double Zoom);
	void	SetScrollPosition(double ScrollPos);	// doesn't scroll
	double	GetScrollPosition() const;
	int		GetNumericFormat() const;
	int		GetPrecision() const;
	void	SetNumericFormat(int NumericFormat, int Precision);
	int		GetMinMajorTickGap() const;
	void	SetMinMajorTickGap(int Gap);
	int		GetMinMinorTickGap() const;
	void	SetMinMinorTickGap(int Gap);
	double	GetMajorTickGap() const;
	int		GetMinorTicks() const;
	void	GetTickLengths(int& Major, int& Minor) const;
	void	SetTickLengths(int Major, int Minor);
	void	GetMargins(int& Start, int& End) const;
	void	SetMargins(int Start, int End);

// Operations
public:
	void	ScrollToPosition(double ScrollPos);
	void	UpdateSpacing();
	CString FormatValue(double Val) const;
	CSize	CalcTextExtent(CTickArray *TickArray = NULL);
	CSize	CalcTextExtent(CRect& rc, CTickArray *TickArray = NULL);
	int		CalcMinHeight();
	double	PositionToValue(double Pos) const;
	static	CString	FormatTime(double TimeSecs);
	static	int		TrimTrailingZeros(CString& Str);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodeRulerControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCodeRulerControl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCodeRulerControl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Types
	struct DIV_INFO {	// division info
		int		Major;			// major tick divison
		int		Minor;			// minor tick divison
	};
	struct UNIT_INFO {	// unit info
		const DIV_INFO	*Div;	// pointer to divisions array
		int		NumDivs;		// number of divisions
		int		Base;			// base for nearest power
	};

// Constants
	static const DIV_INFO	m_DivMetric[];	// metric divisions
	static const DIV_INFO	m_DivEnglish[];	// english divisions
	static const DIV_INFO	m_DivTime[];	// time divisions
	static const UNIT_INFO	m_UnitInfo[UNITS];	// info about each unit
	static const TCHAR	m_NumFmtCode[NUMERIC_FORMATS];	// numeric format codes
	enum {
		TICK_TEXT_GAP = 2,		// gap between tick and text in pixels (vertical only)
		LOG_UNIT_BASE = 10,		// log unit supports base ten only
		LOG_UNIT_SCALE = 1,		// scaling factor from log space to pixels
	};
	enum {	// tick types
		MAJOR,					// major tick
		MINOR,					// minor tick
		TICK_TYPES
	};

// Data members
	double	m_ScrollPos;		// scroll position, in pixels
	double	m_Zoom;				// scaling in units per pixel
	double	m_MajorTickStep;	// distance between major ticks, in current unit
	double	m_MajorTickGap;		// distance between major ticks, in pixels
	HFONT	m_Font;				// font handle, or NULL for system font
	int		m_Unit;				// unit of measurement, enumerated above
	int		m_MinorTicks;		// number of minor ticks between major ticks
	int		m_MinMajorTickGap;	// minimum clearance between major ticks, in pixels
								// (for log unit, minimum clearance between labels)
	int		m_MinMinorTickGap;	// minimum clearance between minor ticks, in pixels
	int		m_TickLen[TICK_TYPES];	// length of a tick, in pixels
	int		m_MarginStart;		// starting margin, in pixels
	int		m_MarginEnd;		// ending margin, in pixels
	int		m_NumericFormat;	// numeric format, 
	int		m_Precision;		// number of digits after decimal
	CString	m_NumFormatterStr;		// numeric format string

// Overridables
	virtual	void	OnDraw(CDC& dc);

// Helpers
	CSize	Draw(CDC& dc, const CRect& cb, const CRect& rc, bool MeasureText, CTickArray *TickArray);
	static	double	Wrap(double Val, double Limit);
	static	CSize	SizeMax(CSize a, CSize b);
	static	void	AddTick(CTickArray *TickArray, int Pos, bool IsMinor);
};

inline bool CCodeRulerControl::IsVertical() const
{
	return((GetStyle() & CBRS_ORIENT_VERT) != 0);
}

inline int CCodeRulerControl::GetUnit() const
{
	return(m_Unit);
}

inline double CCodeRulerControl::GetZoom() const
{
	return(m_Zoom);
}

inline void CCodeRulerControl::SetScrollPosition(double ScrollPos)
{
	m_ScrollPos = ScrollPos;
}

inline double CCodeRulerControl::GetScrollPosition() const
{
	return(m_ScrollPos);
}

inline int CCodeRulerControl::GetNumericFormat() const
{
	return(m_NumericFormat);
}

inline int CCodeRulerControl::GetPrecision() const
{
	return(m_Precision);
}

inline int CCodeRulerControl::GetMinMajorTickGap() const
{
	return(m_MinMajorTickGap);
}

inline void CCodeRulerControl::SetMinMajorTickGap(int Gap)
{
	m_MinMajorTickGap = Gap;
}

inline int CCodeRulerControl::GetMinMinorTickGap() const
{
	return(m_MinMinorTickGap);
}

inline void CCodeRulerControl::SetMinMinorTickGap(int Gap)
{
	m_MinMinorTickGap = Gap;
}

inline double CCodeRulerControl::GetMajorTickGap() const
{
	return(m_MajorTickGap);
}

inline int CCodeRulerControl::GetMinorTicks() const
{
	return(m_MinorTicks);
}

inline void CCodeRulerControl::GetTickLengths(int& Major, int& Minor) const
{
	Major = m_TickLen[MAJOR];
	Minor = m_TickLen[MINOR];
}

inline void CCodeRulerControl::SetTickLengths(int Major, int Minor)
{
	m_TickLen[MAJOR] = Major;
	m_TickLen[MINOR] = Minor;
}

inline void CCodeRulerControl::GetMargins(int& Start, int& End) const
{
	End = m_MarginEnd;
	Start = m_MarginStart;
}

inline void CCodeRulerControl::SetMargins(int Start, int End)
{
	m_MarginEnd = End;
	m_MarginStart = Start;
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CodeRulerControl_H__490CA5D7_29D1_4381_9849_416A9904451A__INCLUDED_)
