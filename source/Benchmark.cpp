// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// Compute benchmarks using performance counter

#include "stdafx.h"
#include "Benchmark.h"

__int64 CBenchmark::m_Freq = InitFreq();

__int64 CBenchmark::InitFreq()
{
	__int64	Freq;
	QueryPerformanceFrequency((LARGE_INTEGER *)&Freq);
	return(Freq);
}

CBenchmark::CBenchmark()
{
	Reset();
}
