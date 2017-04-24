// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeStrPath.h"
#include "ID3TagWrapper.h"
#include "atlconv.h"	// for ATL string conversion macros

#define ID3TAG_DEF(name, ordinal) ordinal,
const int CID3TagWrapper::m_FuncOrd[] = {
	#include "id3tagDefinitions.h"
};

#define METADATASTR(sndfile_str, id3v2_tag, wav_tag) id3v2_tag,
const LPCSTR CID3TagWrapper::m_StrTag[] = {
	#include "MetadataStrhead.h"	// generate metadata string info
};

CID3TagWrapper::CID3TagWrapper()
{
	m_id3 = NULL;
}

CID3TagWrapper::~CID3TagWrapper()
{
	if (m_id3 != NULL && m_File != NULL)	// if file is open
		m_id3->id3_file_close(m_File);	// close file and deallocate memory
}

bool CID3TagWrapper::Create()
{
	ASSERT(m_id3 == NULL);	// reuse of instance not supported
	LPCTSTR	LibName = _T("libid3tag.dll");
	CCodeStrPath	LibPath(theApp.GetAppFolder());
	LibPath.Append(LibName);
	int	funcs = _countof(m_FuncOrd);
	if (!CSignalStudioApp::GetDLLFunctions(m_Lib, LibPath, m_FuncOrd, funcs, m_FuncPtr))
		return(FALSE);
	m_id3 = (IID3TAG *)m_FuncPtr.GetData();	// cast function pointer array to interface
	return(TRUE);
}

bool CID3TagWrapper::Read(LPCTSTR Path, CStringArray& Metadata)
{
	USES_CONVERSION;	// for ATL string conversion macros
	m_File = m_id3->id3_file_open(T2CA(Path), ID3_FILE_MODE_READONLY);
	if (m_File == NULL)	// if can't open file
		return(FALSE);
	id3_tag	*tag = m_id3->id3_file_tag(m_File);
	if (tag == NULL)	// if can't obtain tag pointer
		return(FALSE);
	int	nStrs = _countof(m_StrTag);
	Metadata.SetSize(nStrs);
	for (int iStr = 0; iStr < nStrs; iStr++) {	// for each metadata string
		if (m_StrTag[iStr] != NULL) {	// if string has an associated ID3V2 tag
			id3_frame	*frame = m_id3->id3_tag_findframe(tag, m_StrTag[iStr], 0);
			if (frame != NULL) {	// if frame was retrieved from audio file
				const id3_ucs4_t	*pUCS4;
				if (iStr == STR_COMMENT && frame->nfields >= 4)	// if comment
					pUCS4 = m_id3->id3_field_getfullstring(&frame->fields[3]);
				else if (frame->nfields >= 2)
					pUCS4 = m_id3->id3_field_getstrings(&frame->fields[1], 0);
				else
					pUCS4 = NULL;
				if (pUCS4 != NULL) {	// if UCS-4 string was retrieved
#ifdef UNICODE
					PWSTR	pStr = (PWSTR)m_id3->id3_ucs4_utf16duplicate(pUCS4);
#else	// MBCS
					PSTR	pStr = (PSTR)m_id3->id3_ucs4_latin1duplicate(pUCS4);
#endif
					CString	str(pStr);	// copy string allocated by id3tag DLL
					//
					// Some id3tag functions allocate an object on the heap,
					// and rely on the caller to free the object; examples
					// include id3_ucs4_latin1duplicate and similar functions.
					// In the DLL version of id3tag, such objects MUST be freed
					// using id3_free instead of free, otherwise the heap may 
					// be corrupted, crashing the application. The id3_free
					// function is a custom extension of id3tag, to facilitate
					// porting it to a DLL. DLLs should free any memory they
					// allocate, and if these allocations are exposed to the 
					// user, the DLL should provide a method for freeing them,
					// so that the freeing is done by the DLL's heap manager.
					//
					m_id3->id3_free(pStr);	// let DLL free its own memory
					Metadata[iStr] = str;	// copy string into array
				}
			}
		}
	}
	return(TRUE);
}
