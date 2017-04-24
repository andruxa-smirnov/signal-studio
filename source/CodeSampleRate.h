// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CCodeSampleRate_INCLUDED
#define CCodeSampleRate_INCLUDED

#include "samplerate.h"
#include "DllWrap.h"
#include "samplerateFunctions.h"

class CWave;

class CCodeSampleRate : public WObject {
public:
// Construction
	CCodeSampleRate();
	~CCodeSampleRate();

// Attributes
	bool	IsCreated() const;
	CString	GetError() const;

// Operations
	bool	Create(int Quality, int Channels);
	void	Destroy();
	bool	Resample(const CWave& SrcWave, CWave& DstWave, int NewSampleRate);

protected:
// Types
	struct ISampleRate {	// sample rate converter interface
		#define SAMPLERATE_DEF(name, ordinal) p##name name;
		#include "samplerateDefinitions.h"
	};

// Constants
	enum {
		BUF_SIZE = 0x100000,	// buffer size in bytes
	};
	static const int m_FuncOrd[];	// function ordinals

// Data members
	CDLLWrap	m_Lib;			// DLL wrapper
	ISampleRate	*m_src;			// pointer to sample rate converter interface
	CPtrArray	m_FuncPtr;		// array of pointers to exported functions
	SRC_STATE	*m_State;		// pointer to converter state
	int		m_LastError;		// most recent error code
};

#endif
