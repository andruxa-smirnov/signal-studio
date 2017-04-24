// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "SignalFileFormat.h"

CSignalFileFormat::CSignalFileFormat()
{
	m_Format = 0;
}

CSignalFileFormat& CSignalFileFormat::operator=(const CSignalFileFormat& Info)
{
	if (this == &Info)
		return(*this);	// self-assignment
	m_Format	= Info.m_Format;
	m_Name		= Info.m_Name;
	m_Extension	= Info.m_Extension;
	return(*this);
}

int	CSignalFileFormatArray::FindFormat(int Format) const
{
	int	formats = GetSize();
	for (int iFormat = 0; iFormat < formats; iFormat++) {	// for each format
		if (ElementAt(iFormat).m_Format == Format)	// if format matches caller's
			return(iFormat);
	}
	return(-1);	// format not found
}
