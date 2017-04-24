// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CSignalFileFormat_INCLUDED
#define CSignalFileFormat_INCLUDED

#include "ArrayEx.h"

class CSignalFileFormat : public WObject {
public:
// Construction
	CSignalFileFormat();
	CSignalFileFormat& operator=(const CSignalFileFormat& Info);

// Data members
	int		m_Format;		// identifier
	CString	m_Name;			// descriptive title
	CString	m_Extension;	// file extension
};

class CSignalFileFormatArray : public CArrayEx<CSignalFileFormat, CSignalFileFormat&> {
public:
	int		FindFormat(int Format) const;
};

#endif
