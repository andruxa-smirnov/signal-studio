// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CDLLWRAP_INCLUDED
#define CDLLWRAP_INCLUDED

class CDLLWrap : public WObject {
public:
// Construction
	CDLLWrap();
	~CDLLWrap();

// Attributes
	bool	IsLoaded() const;
	FARPROC	GetProcAddress(LPCTSTR lpProcName);

// Operations
	bool	LoadLibrary(LPCTSTR lpLibFileName);
	bool	LoadLibraryEx(LPCTSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
	bool	FreeLibrary();

protected:
// Data members
	HINSTANCE	m_hInst;	// handle to DLL instance
};

inline bool CDLLWrap::IsLoaded() const
{
	return(m_hInst != NULL);
}

#endif
