// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CFOLDERDIALOG_INCLUDED
#define CFOLDERDIALOG_INCLUDED

#ifndef BIF_NEWDIALOGSTYLE
#define BIF_NEWDIALOGSTYLE	0x0040
#endif

class CFolderDialog {
public:
	static	bool	BrowseFolder(
		LPCTSTR	Title,			// Title to display in dialog box.
		CString&	Folder,		// Receives the selected folder's path.
		LPCTSTR	Root = NULL,	// Optional root path to browse from.
		UINT	Flags = 0,		// See SHBrowseForFolder for more info.
		LPCTSTR	InitialDir = NULL,	// Optional initial directory path.
		HWND	OwnerWnd = NULL	// Optional owner window.
	);

private:
	static	bool	GetItemIdListFromPath(
		LPCTSTR	lpszPath, 
		LPITEMIDLIST	*lpItemIdList
	);
	static	int	CALLBACK	BrowseCallbackProc(
		HWND hWnd,
		UINT uMsg,
		LPARAM lParam,
		LPARAM lpData
	);
};

#endif
