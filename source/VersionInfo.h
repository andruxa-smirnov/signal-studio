// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CVERSIONINFO_INCLUDED
#define CVERSIONINFO_INCLUDED

class CVersionInfo {
public:
	static	bool	GetFileInfo(VS_FIXEDFILEINFO& Info, LPCTSTR Path);
	static	bool	GetModuleInfo(VS_FIXEDFILEINFO& Info, LPCTSTR ModuleName);
};

#endif
