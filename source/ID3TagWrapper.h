// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CID3TagWrapper_INCLUDED
#define CID3TagWrapper_INCLUDED

#include "DLLWrap.h"
#include "id3tag.h"
#include "id3tagFunctions.h"

struct id3_file;

class CID3TagWrapper : public WObject {
public:
// Construction
	CID3TagWrapper();
	~CID3TagWrapper();
	bool	Create();

// Operations
	bool	Read(LPCTSTR Path, CStringArray& Metadata);

protected:
// Constants
	#define METADATASTR(sndfile_str, id3v2_tag, wav_tag) STR_##sndfile_str,
	enum {
		#include "MetadataStrhead.h"	// generate metadata string enum
		STRINGS
	};
	static const LPCSTR m_StrTag[];

// Types
	struct IID3TAG {	// id3tag interface
		#define ID3TAG_DEF(name, ordinal) p##name name;
		#include "id3tagDefinitions.h"
	};
	static const int m_FuncOrd[];	// function ordinals

// Member data
	CDLLWrap	m_Lib;			// wrapped instance of library
	CPtrArray	m_FuncPtr;		// array of pointers to exported functions
	IID3TAG	*m_id3;				// pointer to id3tag interface struct
	struct id3_file	*m_File;	// id3tag file interface struct
};

#endif
