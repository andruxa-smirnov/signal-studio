// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "SignalStudio.h"
#include "CodeSndFile.h"
#include "CodeStrPath.h"
#include "atlconv.h"

#define SNDFILE_DEF(name, ordinal) ordinal,
const int CCodeSndFile::m_FuncOrd[] = {
	#include "CodeSndfileDefinitions.h"
};

#define METADATASTR(sndfile_str, id3v2_tag, wav_tag) SF_STR_##sndfile_str,
const int CCodeSndFile::m_MetadataID[] = {
	#include "MetadataStrhead.h"	// generate sndfile metadata string identifiers
};

// foreign formats in alphabetical order by extension
const SF_FORMAT_INFO CCodeSndFile::m_ForeignFormat[] = {
//	format			name				extension
	{FORMAT_MP3,	"MP3 (MPEG)",		"mp3"},
};

CCodeSndFile::CCodeSndFile()
{
	m_File = NULL;
	m_sf = NULL;
}

CCodeSndFile::~CCodeSndFile()
{
	Close();
}

CString	CCodeSndFile::GetError() const
{
	ASSERT(IsCreated());
	return(CString(m_sf->sf_strerror(m_File)));
}

void CCodeSndFile::HandleError()
{
	AfxMessageBox(GetError());
}

bool CCodeSndFile::Open(LPCTSTR Path, int Mode, SF_INFO& Info)
{
	USES_CONVERSION;
	Close();
	m_File = m_sf->sf_open(T2CA(Path), Mode, &Info);
	return(IsOpen());
}

bool CCodeSndFile::Close()
{
	if (!IsOpen())
		return(TRUE);
	ASSERT(IsCreated());
	return(!m_sf->sf_close(m_File));
}

CString CCodeSndFile::GetLibPath()
{
	LPCTSTR	LibName = _T("libsndfile-1.dll");
	CCodeStrPath	LibPath(theApp.GetAppFolder());
	LibPath.Append(LibName);
	return(LibPath);
}

bool CCodeSndFile::Create()
{
	ASSERT(!IsCreated());
	CString	LibPath(GetLibPath());
	int	funcs = _countof(m_FuncOrd);
	if (!CSignalStudioApp::GetDLLFunctions(m_Lib, LibPath, m_FuncOrd, funcs, m_FuncPtr))
		return(FALSE);
	m_sf = (ISndFile *)m_FuncPtr.GetData();	// cast function pointer array to interface
	return(TRUE);
}

void CCodeSndFile::Convert(const CWave& Src, CWave& Dst, W64INT SrcOffset, W64INT DstOffset, LONGLONG Frames)
{
	ASSERT(Src.IsValid());
	ASSERT(Dst.IsValid());
	ASSERT(Src.GetChannels() == Dst.GetChannels());
	UINT	chans = Src.GetChannels();
	int	SrcStep = Src.GetSampleSize();
	int	DstStep = Dst.GetSampleSize();
	int	SampleSizeDelta = Dst.GetSampleSize() - Src.GetSampleSize();
	bool	ShiftRight = SampleSizeDelta < 0;	// if negative change, shift right
	int	SampleShift = abs(SampleSizeDelta) << 3;	// convert bytes to shift in bits
	for (LONGLONG iFrame = 0; iFrame < Frames; iFrame++) {	// for each frame
		for (UINT iChan = 0; iChan < chans; iChan++) {	// for each channel
			CWave::SAMPLE	samp = Src.GetSampleAt(SrcOffset);
			if (ShiftRight)
				samp >>= SampleShift;	// shift right
			else
				samp <<= SampleShift;	// shift left
			Dst.SetSampleAt(DstOffset, samp);
			SrcOffset += SrcStep;
			DstOffset += DstStep;
		}
	}
}

void CCodeSndFile::InitTempBuffer(const SF_INFO& info, const CWave& Wave, CWave& Temp, W64INT& BlockBytes)
{
	UINT	SampleSize = Wave.GetSampleSize();
	if (SampleSize == 1 || SampleSize == 3) {	// if wave is 8 or 24 bit PCM
		// libsndfile doesn't support reading/writing 8 or 24 bit PCM;
		// must read shorts or ints to a temporary buffer and convert
		UINT	TmpSampleBits;
		if (SampleSize == 1)	// if 8-bit
			TmpSampleBits = 16;	// read shorts
		else	// 24-bit
			TmpSampleBits = 32;	// read ints
		Temp.SetFormat(info.channels, info.samplerate, TmpSampleBits);
		BlockBytes = CONVERSION_BLOCK_SIZE;
		Temp.SetFrameCount(BlockBytes / Wave.GetFrameSize());
	}
}

bool CCodeSndFile::Read(LPCTSTR Path, CWave& Wave, int& Format, const CWave::IO_HOOK& Hook, CStringArray *Metadata)
{
	ASSERT(IsCreated());
	SF_INFO	info;
	info.format = 0;	// required according to doc
	if (!Open(Path, SFM_READ, info)) {	// open source file
		HandleError();
		return(FALSE);
	}
	Format = info.format;	// return format to caller
#ifndef _WIN64	// if x86
	if (info.frames > INT_MAX)	// if too many frames for x86
		CWave::ThrowError(IDS_SFEX_TOO_MANY_FRAMES);
#endif
	int	SampleBits;
	UINT	subtype = (info.format & SF_FORMAT_SUBMASK);
	if (subtype <= SF_FORMAT_PCM_U8) {	// if format is integer PCM
		if (subtype == SF_FORMAT_PCM_U8)	// if unsigned 8-bit PCM
			SampleBits = 8;	// sample size is 8-bit
		else	// signed integer PCM
			SampleBits = subtype << 3;	// use format enum as sample size
	} else {	// not integer PCM format; floating point, compressed, etc.
		SampleBits = 32;	// convert to 32-bit integer PCM
		// enable scale factor for reading integer data from floating point file
		m_sf->sf_command(m_File, SFC_SET_SCALE_FLOAT_INT_READ, NULL, SF_TRUE);
	}
	Wave.SetFrameCount(0);	// delete any existing audio before setting format
	Wave.SetFormat(info.channels, info.samplerate, SampleBits);	// set format
	Wave.SetFrameCount(W64INT(info.frames));	// set frame count
	CWave	tmp;	// temporary buffer for conversion
	W64INT	BlockBytes = Hook.BlockSize;	// InitTempBuffer can override block size
	InitTempBuffer(info, Wave, tmp, BlockBytes);	// init temporary buffer
	LONGLONG	BlockFrames = BlockBytes / Wave.GetFrameSize();	// frames per block
	LONGLONG	RemainFrames = Wave.GetFrameCount();	// remaining frames to read
	BYTE	*pData = Wave.GetData();
	UINT	SampleSize = Wave.GetSampleSize();
	if (RemainFrames) {	// if at least one block
		LONGLONG	blocks = (RemainFrames - 1) / BlockFrames + 1;
		for (LONGLONG iBlock = 0; iBlock < blocks; iBlock++) {
			if (!Hook.Callback(UINT(iBlock), UINT(blocks), Hook.wParam, Hook.lParam))
				AfxThrowUserException();
			LONGLONG	frames = min(RemainFrames, BlockFrames);
			LONGLONG	reads;
			switch (SampleSize) {
			case 1:	// 8-bit: read shorts and then convert to 8-bit
				reads = m_sf->sf_readf_short(m_File, (short *)tmp.GetData(), frames);
				Convert(tmp, Wave, 0, pData - Wave.GetData(), frames);
				break;
			case 2:	// 16-bit: read shorts
				reads = m_sf->sf_readf_short(m_File, (short *)pData, frames);
				break;
			case 3:	// 24-bit: read ints and then convert to 24-bit
				reads = m_sf->sf_readf_int(m_File, (int *)tmp.GetData(), frames);
				Convert(tmp, Wave, 0, pData - Wave.GetData(), frames);
				break;
			case 4:	// 32-bit: read ints
				reads = m_sf->sf_readf_int(m_File, (int *)pData, frames);
				break;
			default:
				NODEFAULTCASE;
				reads = 0;
			}
			if (reads != frames) {	// if all frames weren't read
				HandleError();
				return(FALSE);
			}
			pData += frames * Wave.GetFrameSize();
			RemainFrames -= frames;
		}
	}
	if (Metadata != NULL) {	// if caller wants metadata
		int	nStrs = _countof(m_MetadataID);
		Metadata->SetSize(nStrs);
		int	nValidStrs = 0;
		for (int iStr = 0; iStr < nStrs; iStr++) {	// for each metadata string
			LPCSTR	pStr = m_sf->sf_get_string(m_File, m_MetadataID[iStr]);
			if (pStr != NULL) {	// if metadata string was retrieved
				(*Metadata)[iStr] = pStr;	// copy into metadata array
				nValidStrs++;
			}
		}
		if (!nValidStrs)	// if no strings were found
			Metadata->RemoveAll();	// delete metadata array
	}
	return(TRUE);
}

bool CCodeSndFile::Write(LPCTSTR Path, const CWave& Wave, int Format, const CWave::IO_HOOK& Hook, const CStringArray *Metadata)
{
	ASSERT(IsCreated());
	UINT	subtype = Format & SF_FORMAT_SUBMASK;
	if (!subtype) {	// if caller's format doesn't specify subtype
		switch (Format & SF_FORMAT_TYPEMASK) {
		case SF_FORMAT_OGG:	// if ogg format
			subtype = SF_FORMAT_VORBIS;	// only one subtype allowed
			break;
		case SF_FORMAT_MAT5:
		case SF_FORMAT_RF64:
		case SF_FORMAT_VOC:
		case SF_FORMAT_W64:
		case SF_FORMAT_WAV:
		case SF_FORMAT_WAVEX:
			if (Wave.GetSampleSize() == 1)	// if 8-bit samples
				subtype = SF_FORMAT_PCM_U8;	// format only supports unsigned 8-bit
			else	// not 8-bit samples
				subtype = Wave.GetSampleSize();	// use sample size as format enum
			break;
		default:
			subtype = Wave.GetSampleSize();	// use sample size as format enum
		}
		Format |= subtype;	// add subtype to format
	}
	SF_INFO	info;
	info.samplerate = Wave.GetSampleRate();
	info.channels = Wave.GetChannels();
	info.format = Format;
	if (!Open(Path, SFM_WRITE, info)) {	// create destination file
		HandleError();
		return(FALSE);
	}
	// metadata must always be written before audio, per Erik de Castro Lopo
	if (Metadata != NULL && Metadata->GetSize()) {	// if caller has metadata
		USES_CONVERSION;
		int	nStrs = _countof(m_MetadataID);
		for (int iStr = 0; iStr < nStrs; iStr++) {	// for each metadata string
			m_sf->sf_set_string(m_File, m_MetadataID[iStr], T2CA((*Metadata)[iStr]));
		}
	}
	if (subtype >= SF_FORMAT_FLOAT) {	// if format could be floating point
		// enable scale factor for writing floating point file from integer data
		m_sf->sf_command(m_File, SFC_SET_SCALE_INT_FLOAT_WRITE, NULL, SF_TRUE);
	}
	if (subtype == SF_FORMAT_VORBIS) {
		double	quality = theApp.GetMain()->GetOptions().m_VBREncodingQuality / 100.0;
		m_sf->sf_command(m_File, SFC_SET_VBR_ENCODING_QUALITY, &quality, sizeof(double));
	}
	CWave	tmp;	// temporary buffer for conversion
	W64INT	BlockBytes = Hook.BlockSize;	// InitTempBuffer can override block size
	InitTempBuffer(info, Wave, tmp, BlockBytes);	// init temporary buffer
	if ((info.format & SF_FORMAT_TYPEMASK) == SF_FORMAT_OGG) {	// if ogg format
		// sndfile's ogg write crashes if it receives too many frames at once
		ASSERT(OGG_WRITE_BLOCK_SIZE <= BlockBytes);	// must fit within temp buffer
		BlockBytes = OGG_WRITE_BLOCK_SIZE;	// override block size with smaller one
	}
	LONGLONG	BlockFrames = BlockBytes / Wave.GetFrameSize();	// frames per block
	LONGLONG	RemainFrames = Wave.GetFrameCount();	// remaining frames to write
	const BYTE	*pData = Wave.GetData();
	UINT	SampleSize = Wave.GetSampleSize();
	if (RemainFrames) {	// if at least one block
		LONGLONG	blocks = (RemainFrames - 1) / BlockFrames + 1;
		for (LONGLONG iBlock = 0; iBlock < blocks; iBlock++) {
			if (!Hook.Callback(UINT(iBlock), UINT(blocks), Hook.wParam, Hook.lParam))
				AfxThrowUserException();
			LONGLONG	frames = min(RemainFrames, BlockFrames);
			LONGLONG	writes;
			switch (SampleSize) {
			case 1:	// 8-bit: convert to 16-bit and then write shorts
				Convert(Wave, tmp, pData - Wave.GetData(), 0, frames);
				writes = m_sf->sf_writef_short(m_File, (short *)tmp.GetData(), frames);
				break;
			case 2:	// 16-bit: write shorts
				writes = m_sf->sf_writef_short(m_File, (short *)pData, frames);
				break;
			case 3:	// 24-bit: convert to 32-bit and then write ints
				Convert(Wave, tmp, pData - Wave.GetData(), 0, frames);
				writes = m_sf->sf_writef_int(m_File, (int *)tmp.GetData(), frames);
				break;
			case 4:	// 32-bit: write ints
				writes = m_sf->sf_writef_int(m_File, (int *)pData, frames);
				break;
			default:
				NODEFAULTCASE;
				writes = 0;
			}
			if (writes != frames) {	// if all frames weren't written
				HandleError();
				return(FALSE);
			}
			pData += frames * Wave.GetFrameSize();
			RemainFrames -= frames;
		}
	}
	return(TRUE);
}

bool CCodeSndFile::FormatCheck(const SF_INFO& Info) const
{
	return(m_sf->sf_format_check(&Info) != 0);
}

void CCodeSndFile::SetFormat(CSignalFileFormat& Format, const SF_FORMAT_INFO& Info)
{
	Format.m_Format = Info.format;
	Format.m_Name = CString(Info.name);
	Format.m_Extension = CString(Info.extension);
}

bool CCodeSndFile::GetMajorFormats(CSignalFileFormatArray& Format, UINT Flags) const
{
	int	ForeignFormats = _countof(m_ForeignFormat);
	ASSERT(IsCreated());
	int	MajorFormats;
	m_sf->sf_command(NULL, SFC_GET_FORMAT_MAJOR_COUNT, &MajorFormats, sizeof(int));
	int	TotalFormats = MajorFormats;
	if (Flags & GMF_INCLUDE_FOREIGN)
		TotalFormats += ForeignFormats;
	Format.SetSize(TotalFormats);
	int	ValidFmts = 0;
	LPCSTR	SkipExt;
	if (Flags & GMF_NATIVE_WAVE) {	// if handling wave as native format
		CSignalFileFormat	fmt;
		fmt.m_Name.LoadString(IDS_FILT_WAVE_FILES);
		fmt.m_Extension = _T("wav");
		Format[0] = fmt;	// wave format comes first
		ValidFmts++;
		SkipExt = "wav";	// skip sndfile wave formats
	} else	// no special handling for wave
		SkipExt = "";	// retrieve all sndfile formats
	SF_FORMAT_INFO	info;
	int	iForeignFmt = 0;
	for (int iFmt = 0; iFmt < MajorFormats; iFmt++) {	// for each major format
		info.format = iFmt;
        if (m_sf->sf_command(NULL, SFC_GET_FORMAT_MAJOR, &info, sizeof(info)))
			return(FALSE);
		if (Flags & GMF_INCLUDE_FOREIGN) {	// if including foreign formats
			while (iForeignFmt < ForeignFormats) {	// for remaining foreigners
				const SF_FORMAT_INFO&	FFInfo = m_ForeignFormat[iForeignFmt];
				if (strcmp(FFInfo.extension, info.extension) > 0)
					break;	// haven't reached alpha position yet
				CSignalFileFormat	fmt;
				SetFormat(fmt, FFInfo);
				Format[ValidFmts] = fmt;	// copy into array
				ValidFmts++;
				iForeignFmt++;
			}
		}
		if (strcmp(info.extension, SkipExt)) {	// if not skipping this extension
			CSignalFileFormat	fmt;
			SetFormat(fmt, info);
			Format[ValidFmts] = fmt;	// copy into array
			ValidFmts++;
		}
	}
	Format.SetSize(ValidFmts);
	return(TRUE);
}

bool CCodeSndFile::GetSubtypes(CSignalFileFormatArray& Format) const
{
	ASSERT(IsCreated());
	int	Subtypes;
	m_sf->sf_command(NULL, SFC_GET_FORMAT_SUBTYPE_COUNT, &Subtypes, sizeof(int));
	Format.SetSize(Subtypes);
	SF_FORMAT_INFO	info;
	for (int iFmt = 0; iFmt < Subtypes; iFmt++) {	// for each subtype
		info.format = iFmt;
        if (m_sf->sf_command(NULL, SFC_GET_FORMAT_SUBTYPE, &info, sizeof(info)))
			return(FALSE);
		CSignalFileFormat	fmt;
		SetFormat(fmt, info);
		Format[iFmt] = fmt;	// copy into array
	}
	return(TRUE);
}
