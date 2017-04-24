// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CControlResizer_INCLUDED
#define CControlResizer_INCLUDED

#include <afxtempl.h>

enum {
	BIND_TOP		= 0x01,
	BIND_LEFT		= 0x02,
	BIND_RIGHT		= 0x04,
	BIND_BOTTOM		= 0x08,
	BIND_ALL		= 0x0F,
	BIND_UNKNOWN	= 0x00
};

class CControlResizer : public WObject {
public:
	typedef struct tagCTRL_LIST {
		int		CtrlID;
		int		BindType;
	} CTRL_LIST;
	CControlResizer();
	void	OnSize();
	void	SetParentWnd(CWnd *pWnd);
	bool	FixControls();
	void	AddControl(int CtrlID, int BindType, const CRect *Rect = NULL);
	void	AddControlList(CWnd *pWnd, const CTRL_LIST *List);
	void	SetOriginShift(SIZE Shift);

private:
	class CtrlInfo {
	public:
		int		m_CtrlID;
		int		m_BindType;
		CRect	m_RectInit;
		HWND	m_hCtrlWnd;
	};
	CWnd	*m_pWnd;
	CArray	<CtrlInfo, CtrlInfo&> m_Info;
	CRect	m_RectInit;
	CSize	m_OrgShift;
};

inline void CControlResizer::SetParentWnd(CWnd *pWnd)
{
	m_pWnd = pWnd;
}

inline void CControlResizer::SetOriginShift(SIZE Shift)
{
	m_OrgShift = Shift;
}

#endif
