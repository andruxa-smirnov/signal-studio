// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CStubFileLocation_INCLUDED
#define CStubFileLocation_INCLUDED

class CStubFileLocation : public WObject {
public:
	CStubFileLocation();
	~CStubFileLocation();
	BOOL	FindFile(LPCTSTR path);
	BOOL	FindNextFile(CFileFind*& cffp);
	const	CFileFind& GetFind();
	CString	GetRoot() const;
	int		GetDepth() const;
	CString	GetRelativePath() const;
private:
	enum {
		MAXDEPTH = 100
	};
	CFileFind	*cff[MAXDEPTH];
	BOOL	more[MAXDEPTH];
	int		depth;
};

inline int CStubFileLocation::GetDepth() const
{
	return(depth);
}

#endif
