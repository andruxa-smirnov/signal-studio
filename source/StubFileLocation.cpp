// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "StdAfx.h"
#include "StubFileLocation.h"

CStubFileLocation::CStubFileLocation()
{
	depth = 0;
	cff[0] = new CFileFind;
	more[0] = 1;
}

CStubFileLocation::~CStubFileLocation()
{
	for (int i = 0; i <= depth; i++)
		delete cff[i];
}

BOOL CStubFileLocation::FindNextFile(CFileFind*& cffp)
{
	if (more[depth]) {
		while (1) {
			more[depth] = cff[depth]->FindNextFile();
			if (cff[depth]->IsDirectory() && !cff[depth]->IsDots()) {
				if (depth >= MAXDEPTH)
					return(FALSE);
				cff[++depth] = new CFileFind;
				if (!cff[depth]->FindFile(cff[depth - 1]->GetFilePath() += "\\*.*")) {
					delete cff[depth--];
					break;
				}
			} else
				break;
		}
	} else {
		if (depth)
			delete cff[depth--];
	}
	cffp = cff[depth];
	return(depth || more[depth]);
}

BOOL CStubFileLocation::FindFile(LPCTSTR path)
{
	return(cff[0]->FindFile(path));
}

CString	CStubFileLocation::GetRoot() const
{
	return(cff[0]->GetRoot());
}

CString	CStubFileLocation::GetRelativePath() const
{
	return(cff[depth]->GetFilePath().Mid(cff[0]->GetRoot().GetLength() + 1));
}
