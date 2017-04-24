// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "StdAfx.h"
#include "Event.h"

WEvent::WEvent()
{
	m_hEvent = NULL;
}

WEvent::~WEvent()
{
	Close();
}

bool WEvent::Create(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset, 
							BOOL bInitialState, LPCTSTR lpName, LPCSTR DebugName)
{
//
// Force the event name to be NULL.  This prevents crazy stuff from happening 
// if two events accidentally get created with the same name.
//
	Close();
	m_hEvent = CreateEvent(lpEventAttributes, bManualReset, bInitialState, NULL);
#ifdef EMBKERN_H_INCLUDED	// if we're running under PharLap ETS
	if (m_hEvent != NULL && DebugName != NULL)
		EtsSetDebugName(m_hEvent, const_cast<char *>(DebugName));
#endif
	return(m_hEvent != NULL);
}

void WEvent::Close()
{
	if (m_hEvent != NULL) {
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}
}
