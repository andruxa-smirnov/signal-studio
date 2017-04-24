// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "CodeStrPath.h"

BOOL CCodeStrPath::Append(LPCTSTR More)
{
	LPTSTR	p = GetBuffer(MAX_PATH);
	BOOL	retc = PathAppend(p, More);
	ReleaseBuffer();
	return(retc);
}

void CCodeStrPath::RemoveExtension()
{
	LPTSTR	p = GetBuffer(MAX_PATH);
	PathRemoveExtension(p);
	ReleaseBuffer();
}

BOOL CCodeStrPath::RemoveFileSpec()
{
	LPTSTR	p = GetBuffer(MAX_PATH);
	BOOL	retc = PathRemoveFileSpec(p);
	ReleaseBuffer();
	return(retc);
}

BOOL CCodeStrPath::RenameExtension(LPCTSTR Ext)
{
	LPTSTR	p = GetBuffer(MAX_PATH);
	BOOL	retc = PathRenameExtension(p, Ext);
	ReleaseBuffer();
	return(retc);
}

void CCodeStrPath::QuoteSpaces()
{
	LPTSTR	p = GetBuffer(MAX_PATH);
	PathQuoteSpaces(p);
	ReleaseBuffer();
}
