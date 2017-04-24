// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "StateReverse.h"

CStateReverse::CStateReverse(const CStateReverse& State) :
	CRefPtr<CRefObj>(State)	// call base class copy constructor
{
	Copy(State);
}

CStateReverse& CStateReverse::operator=(const CStateReverse& State)
{
	CRefPtr<CRefObj>::operator=(State);	// call base class assignment operator
    Copy(State);
	return(*this);
}

void CStateReverse::Copy(const CStateReverse& State)
{
	m_Val = State.m_Val;
	m_CtrlID = State.m_CtrlID;
	m_Code = State.m_Code;
}

CString CStateReverse::DumpState() const
{
	CString	s;
	s.Format(_T("CtrlID=%d Code=%d a=0x%x b=0x%x"), 
		m_CtrlID, m_Code, m_Val.p.x.i, m_Val.p.y.i);
	return(s);
}
