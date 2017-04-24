// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CCodeSndFile_INCLUDED
#define CCodeSndFile_INCLUDED

#include "sndfile.h"
#include "sndfileFunctions.h"
#include "SignalFileFormat.h"
#include "DllWrap.h"
#include "Wave.h"

class CCodeSndFile : public WObject {
public:
// Construction
	CCodeSndFile();
	~CCodeSndFile();

// Constants
	enum {	// get major format flags
		GMF_NATIVE_WAVE		= 0x01,		// handling wave format natively
		GMF_INCLUDE_FOREIGN	= 0x02,		// include non-sndfile formats
	};
	// foreign format types; start at maximum value (SF_FORMAT_TYPEMASK)
	// and count down, hopefully avoiding collision with sndfile formats
	enum {
		FORMAT_MP3			= 0x0FFF0000,
	};

// Attributes
	static	CString GetLibPath();
	bool	IsCreated() const;
	bool	IsOpen() const;
	CString	GetError() const;
	bool	GetMajorFormats(CSignalFileFormatArray& Format, UINT Flags = 0) const;
	bool	GetSubtypes(CSignalFileFormatArray& Format) const;

// Operations
	bool	Create();
	bool	Open(LPCTSTR Path, int Mode, SF_INFO& Info);
	bool	Close();
	bool	Read(LPCTSTR Path, CWave& Wave, int& Format, const CWave::IO_HOOK& Hook, CStringArray *Metadata = NULL);
	bool	Write(LPCTSTR Path, const CWave& Wave, int Format, const CWave::IO_HOOK& Hook, const CStringArray *Metadata = NULL);
	bool	FormatCheck(const SF_INFO& Info) const;
	static	void	Convert(const CWave& Src, CWave& Dst, W64INT SrcOffset, W64INT DstOffset, LONGLONG Frames);

protected:
	struct ISndFile {	// sndfile interface
		#define SNDFILE_DEF(name, ordinal) p##name name;
		#include "CodeSndfileDefinitions.h"
	};
	static const int m_FuncOrd[];	// function ordinals
	static const int m_MetadataID[];	// sndfile metadata string identifiers

// Constants
	enum {
		CONVERSION_BLOCK_SIZE	= 0x100000,	// block size for conversion, in bytes;
											// keeps temporary buffer size reasonable
		OGG_WRITE_BLOCK_SIZE	= 0x10000,	// block size for writing ogg, in bytes;
											// libsndfile crashes if this is too big
	};
	static const SF_FORMAT_INFO	m_ForeignFormat[];	// non-sndfile formats

// Member data
	CDLLWrap	m_Lib;			// wrapped instance of sndfile library
	CPtrArray	m_FuncPtr;		// array of pointers to exported functions
	ISndFile	*m_sf;			// pointer to sndfile interface struct
	SNDFILE		*m_File;		// pointer to sndfile instance

// Helpers
	void	HandleError();
	static	void	InitTempBuffer(const SF_INFO& info, const CWave& Wave, CWave& Temp, W64INT& BlockBytes);
	static	void	SetFormat(CSignalFileFormat& Format, const SF_FORMAT_INFO& Info);
};

inline bool	CCodeSndFile::IsCreated() const
{
	return(m_sf != NULL);
}

inline bool CCodeSndFile::IsOpen() const
{
	return(m_File != NULL);
}

#endif
