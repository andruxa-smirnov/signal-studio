// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CFnAnalyze_INCLUDED
#define CFnAnalyze_INCLUDED

#include "SignalProcess.h"
#include "KissFFT.h"

class CFnAnalyze : public WObject {
public:
// Construction
	CFnAnalyze();

// Constants
	#define WINDOWFUNCTIONDEF(name) WF_##name,
	enum {	// window functions
		#include "WindowFuncData.h"
		WINDOW_FUNCTIONS
	};

// Types
	typedef CSignalProcess::CDblArray CDblArray;

// Attributes
	const CWave	*GetWave() const;
	void	SetJob(CAsyncJob *Job);
	void	SetParms(int Windows, int WindowSize, int WindowFunction, bool SeparateChannels);
	void	SetSelection(const CW64IntRange& Selection);
	void	SetRange(const CW64IntRange& Range);
	void	SetRepeat(bool Repeat);
	void	GetOutput(CDblArray& Bin) const;
	const double	*GetOutput() const;
	bool	IsValidBinPtr(const double *Ptr) const;
	static	bool	IsValidBinPtr(const CDblArray& Bin, const double *Ptr);

// Operations
	void	ResetOutput();
	void	Setup(const CWave *Wave);
	bool	Analyze(W64INT Frame);
	static	void	GetWindowFunction(int FuncIdx, double *Buf, int Elems);
	static	CString	GetWindowFuncName(int FuncIdx);
	static	bool	IsPowerOfTwo(int x);

protected:
// Types
	class CComplex : public kiss_fft_cpx {
	public:
		double	Magnitude() const;
	};
	typedef CArrayEx<CComplex, CComplex&> CComplexArray;

// Constants
	static const int m_WindowFuncName[];	// resource IDs of function names

// Member data
	CKissFFT	m_FFT;			// FFT instance
	CDblArray	m_TimeIn;		// FFT input: array of scalar time data
	CComplexArray	m_FreqOut;	// FFT output: array of complex frequency data
	CDblArray m_WinFuncVal;		// array of precomputed window function values
	CSignalProcess::CConvert	m_Cvt;	// converter for normalizing samples
	const CWave	*m_Wave;		// pointer to audio container
	CAsyncJob	*m_Job;			// pointer to asynchronous job state
	int		m_Windows;			// number of windows to process
	int		m_WindowSize;		// size of window, in frames
	int		m_WindowFunction;	// index of window function
	bool	m_SeparateChannels;	// if true, separate channels, else combine
	bool	m_Repeat;			// if true, loop within selection
	CW64IntRange	m_Selection;	// selection to analyze, as byte offsets
	CDblArray	m_Bin;			// array of output magnitude bins, one for each
								// frequency band; if separating channels, array 
								// is 2-D (rows are channels, columns are bands)
	double	m_Scale;			// output scaling factor
};

inline double CFnAnalyze::CComplex::Magnitude() const
{
	return(r * r + i * i);
}

inline CString CFnAnalyze::GetWindowFuncName(int FuncIdx)
{
	ASSERT(FuncIdx >= 0 && FuncIdx < WINDOW_FUNCTIONS);
	return(LDS(m_WindowFuncName[FuncIdx]));
}

inline bool CFnAnalyze::IsPowerOfTwo(int x)
{
	return(x && !(x & (x - 1)));
}

inline const CWave *CFnAnalyze::GetWave() const
{
	return(m_Wave);
}

inline void CFnAnalyze::GetOutput(CDblArray& Bin) const
{
	Bin = m_Bin;
}

inline const double *CFnAnalyze::GetOutput() const
{
	return(m_Bin.GetData());
}

inline void CFnAnalyze::ResetOutput()
{
	ZeroMemory(m_Bin.GetData(), m_Bin.GetSize() * sizeof(double));
}

inline bool CFnAnalyze::IsValidBinPtr(const double *Ptr) const
{
	return(IsValidBinPtr(m_Bin, Ptr));
}

inline bool CFnAnalyze::IsValidBinPtr(const CDblArray& Bin, const double *Ptr)
{
	return(Ptr >= Bin.GetData() && Ptr < Bin.GetData() + Bin.GetSize());
}

inline void CFnAnalyze::SetJob(CAsyncJob *Job)
{
	m_Job = Job;
}

inline void CFnAnalyze::SetSelection(const CW64IntRange& Selection)
{
	m_Selection = Selection;
}

inline void CFnAnalyze::SetRepeat(bool Repeat)
{
	m_Repeat = Repeat;
}

#endif
