// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CCodeStrPath_INCLUDED
#define CCodeStrPath_INCLUDED

#include "shlwapi.h"

class CCodeStrPath : public CString {
public:
	CCodeStrPath();
	CCodeStrPath(const CString& stringSrc);
	CCodeStrPath(LPCTSTR lpsz);
	BOOL	Append(LPCTSTR More);
	void	RemoveExtension();
	BOOL	RemoveFileSpec();
	BOOL	RenameExtension(LPCTSTR Ext);
	void	QuoteSpaces();
};

inline CCodeStrPath::CCodeStrPath()
{
}

inline CCodeStrPath::CCodeStrPath(const CString& stringSrc) : CString(stringSrc)
{
}

inline CCodeStrPath::CCodeStrPath(LPCTSTR lpsz) : CString(lpsz)
{
}

#endif
