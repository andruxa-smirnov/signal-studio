// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "fcntl.h"
#include "io.h"
#include "wincon.h"
#include "Win32Console.h"

bool Win32Console::m_IsOpen;

BOOL WINAPI Win32Console::SignalHandler(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT) {
		AfxGetMainWnd()->PostMessage(WM_CLOSE);	// close main window
		return(TRUE);
	}
	return(FALSE);
}

bool Win32Console::Create()
{
	if (!m_IsOpen) {
		if (AllocConsole()) {
			if (Redirect(GetStdHandle(STD_OUTPUT_HANDLE), stdout, "w")
			&& Redirect(GetStdHandle(STD_INPUT_HANDLE), stdin, "r")
			&& Redirect(GetStdHandle(STD_ERROR_HANDLE), stderr, "w")) {
				m_IsOpen = TRUE;
				SetConsoleCtrlHandler(SignalHandler, TRUE);
			}
		}
	}
	return(m_IsOpen);
}

bool Win32Console::SetScreenBufferSize(WORD Cols, WORD Rows)
{
	HANDLE	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hCon != INVALID_HANDLE_VALUE) {
		COORD	dwSize;
		dwSize.X = Cols;
		dwSize.Y = Rows;
		if (SetConsoleScreenBufferSize(hCon, dwSize))
			return(TRUE);
	}
	return(FALSE);
}

bool Win32Console::Redirect(HANDLE Handle, FILE *File, LPCSTR Mode)
{
	if (Handle != INVALID_HANDLE_VALUE) {
		int hCrt = _open_osfhandle((long)Handle, _O_TEXT);
		if (hCrt >= 0) {
			FILE	*fp = _fdopen(hCrt, Mode);
			if (fp != NULL) {
				*File = *fp;
				return(TRUE);
			}
		}
	}
	return(FALSE);
}
