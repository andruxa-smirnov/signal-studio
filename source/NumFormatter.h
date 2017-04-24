// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#pragma once

class CNumFormatter : public WObject {
public:
	CNumFormatter();
	CString	Format(LONGLONG Val) const;
	CString	Format(double Val, int Decimals) const;
	static	CString	FormatByteSize(LONGLONG Val);

protected:
	enum {
		MAX_BUF = 5
	};
	NUMBERFMT	m_DefFmt;
	TCHAR	m_DecimalSep[MAX_BUF];
	TCHAR	m_ThousandSep[MAX_BUF];
};
