// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "Oscillator.h"
#include <math.h>

const double COscillator::pi = 3.141592653589793;

COscillator::COscillator()
{
	Init();
}

COscillator::COscillator(double TimerFreq, int Waveform, double Freq)
{
	Init();
	m_TimerFreq = TimerFreq;
	m_Waveform = Waveform;
	m_Freq = Freq;
}

void COscillator::Init()
{
	m_TimerFreq = 0;
	m_Waveform = 0;
	m_Freq = 0;
	m_PulseWidth = .5;
	m_RandPrvPhase = 0;
	m_RandCurVal = 0;
	m_RandPrvVal = 0;
	m_Clock = 0;
}

inline double COscillator::CurPos() const
{
	return(m_Freq / m_TimerFreq * m_Clock);
}

inline double COscillator::CurPhase() const
{
	return(fmod(CurPos(), 1));
}

inline void COscillator::Resync(double Phase)
{
	m_Clock = m_Freq ? Phase * (m_TimerFreq / m_Freq) : 0;
}

double COscillator::GetPhase() const
{
	return(CurPhase());
}

void COscillator::SetPhase(double Phase)
{
	Resync(Phase);
}

void COscillator::SetFreq(double Freq)
{
	double	Phase = CurPhase();
	m_Freq = Freq;
	Resync(Phase);
}

void COscillator::SetPhaseFromVal(double Val)
{
	double	r;
	switch (m_Waveform) {
	case TRIANGLE:
		r = (Val + 1) / 2 + 1.5;
		break;
	case SINE:
		r = asin(Val) / pi;
		break;
	case RAMP_UP:
		r = Val + 1;
		break;
	case RAMP_DOWN:
		r = 1 - Val;
		break;
	case SQUARE:
	case PULSE:
		r = (Val + 1) / 2 + 1;
		break;
	default:
		r = 0;
	}
	SetPhase(r / 2);
}

double COscillator::GetVal()
{
	double	r;
	switch (m_Waveform) {
	case TRIANGLE:
		r = fmod(CurPos() * 2 + .5, 2);
		r = r < 1 ? r * 2 - 1 : 3 - r * 2;
		break;
	case SINE:
		r = sin(CurPos() * pi * 2);
		break;
	case RAMP_UP:
		r = CurPhase() * 2 - 1;
		break;
	case RAMP_DOWN:
		r = 1 - CurPhase() * 2;
		break;
	case SQUARE:
		r = CurPhase() < .5 ? 1 : -1;
		break;
	case PULSE:
		r = CurPhase() < m_PulseWidth ? 1 : -1;
		break;
	case RANDOM:
		r = CurPhase();
		if (r < .5 && m_RandPrvPhase > .5)
			m_RandCurVal = double(rand()) / RAND_MAX * 2 - 1;
		m_RandPrvPhase = r;
		r = m_RandCurVal;
		break;
	case RANDOM_RAMP:
		r = CurPhase();
		if (r < .5 && m_RandPrvPhase > .5) {
			m_RandPrvVal = m_RandCurVal;
			m_RandCurVal = double(rand()) / RAND_MAX * 2 - 1;
		}
		m_RandPrvPhase = r;
		r = m_RandPrvVal + (m_RandCurVal - m_RandPrvVal) * r;
		break;
	default:
		r = 0;
	}
	return(r);
}
