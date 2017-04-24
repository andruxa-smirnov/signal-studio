// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CFocusEditor_INCLUDED
#define CFocusEditor_INCLUDED

class CFocusEditor {
public:
	static	bool	Undo();
	static	bool	Cut();
	static	bool	Copy();
	static	bool	Paste();
	static	bool	Insert();
	static	bool	Delete();
	static	bool	SelectAll();
	static	bool	UpdateUndo(CCmdUI* pCmdUI);
	static	bool	UpdateCut(CCmdUI* pCmdUI);
	static	bool	UpdateCopy(CCmdUI* pCmdUI);
	static	bool	UpdatePaste(CCmdUI* pCmdUI);
	static	bool	UpdateInsert(CCmdUI* pCmdUI);
	static	bool	UpdateDelete(CCmdUI* pCmdUI);
	static	bool	UpdateSelectAll(CCmdUI* pCmdUI);

// protected
	static	CEdit	*GetEdit();
	static	bool	IsReadOnly(CEdit *ep);
	static	bool	HasSelection(CEdit *ep);
};

inline bool CFocusEditor::IsReadOnly(CEdit *ep)
{
	return((ep->GetStyle() & ES_READONLY) != 0);
}

inline bool CFocusEditor::HasSelection(CEdit *ep)
{
	int	nBeg, nEnd;
	ep->GetSel(nBeg, nEnd);
	return(nBeg != nEnd);
}

#endif
