// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CRetractManager_INCLUDED
#define CRetractManager_INCLUDED

#include "ArrayEx.h"
#include "StateReverse.h"

class CRetractable;

class CRetractManager : public WObject {
public:
// Construction
	CRetractManager(CRetractable *Root = NULL);
	virtual	~CRetractManager();

// Constants
	enum {	// undo actions
		UA_NONE,
		UA_UNDO,
		UA_REDO,
	};

// Attributes
	bool	CanUndo() const;
	bool	CanRedo() const;
	int		GetAction() const;
	bool	IsIdle() const;
	bool	IsUndoing() const;
	bool	IsRedoing() const;
	bool	IsModified() const;
	void	ResetModifiedFlag();
	LPCTSTR	GetUndoTitle();
	LPCTSTR	GetRedoTitle();
	int		GetLevels() const;
	void	SetLevels(int Levels);
	void	SetRoot(CRetractable *Root);
	int		GetSize() const;
	int		GetPos() const;
	void	SetPos(int Pos);
	const	CStateReverse& GetState(int Pos) const;

// Operations
	void	Undo();
	void	Redo();
	void	UndoNoRedo();
	void	NotifyEdit(WORD CtrlID, WORD Code, UINT Flags = 0);
	void	CancelEdit(WORD CtrlID, WORD Code);
	void	DiscardAllEdits();

protected:
// Overridables
	virtual	void	OnModify(bool Modified);
	virtual	void	OnUpdateTitles();

private:
// Types
	typedef	CArrayEx<CStateReverse, CStateReverse&> CStateReverseArray;

// Constants
	enum {
		BLOCK_SIZE = 100	// list grows in blocks of this many elements
	};

// Member data
	CRetractable	*m_Root;	// owner of this undo stack
	CStateReverseArray	m_List;	// undo stack; array of undo states
	bool	m_CanUndo;		// true if edit can be undone
	bool	m_CanRedo;		// true if edit can be redone
	int		m_Pos;			// current position in undo stack
	int		m_Levels;		// number of undo levels, or -1 for unlimited
	int		m_Edits;		// total number of edits made so far
	int		m_Action;		// undo action; see enum above
	CString	m_UndoTitle;	// current undo title for edit menu
	CString	m_RedoTitle;	// current redo title for edit menu

// Helpers
	void	SwapState(int Pos);
	void	DumpState(LPCTSTR Tag, int Pos);
	CString	GetTitle(int Pos);
	void	UpdateTitles();
	int		FindRetractable() const;
	int		FindRedoable() const;
};

inline bool CRetractManager::CanUndo() const
{
	return(m_CanUndo);
}

inline bool CRetractManager::CanRedo() const
{
	return(m_CanRedo);
}

inline int CRetractManager::GetAction() const
{
	return(m_Action);
}

inline bool CRetractManager::IsIdle() const
{
	return(m_Action == UA_NONE);
}

inline bool CRetractManager::IsUndoing() const
{
	return(m_Action == UA_UNDO);
}

inline bool CRetractManager::IsRedoing() const
{
	return(m_Action == UA_REDO);
}

inline bool CRetractManager::IsModified() const
{
	return(m_Edits > 0);
}

inline void CRetractManager::ResetModifiedFlag()
{
	m_Edits = 0;
}

inline int CRetractManager::GetLevels() const
{
	return(m_Levels);
}

inline LPCTSTR CRetractManager::GetUndoTitle()
{
	return(m_UndoTitle);
}

inline LPCTSTR CRetractManager::GetRedoTitle()
{
	return(m_RedoTitle);
}

inline void CRetractManager::SetRoot(CRetractable *Root)
{
	m_Root = Root;
}

inline int CRetractManager::GetSize() const
{
	return(m_List.GetSize());
}

inline int CRetractManager::GetPos() const
{
	return(m_Pos);
}

inline const CStateReverse& CRetractManager::GetState(int Pos) const
{
	return(m_List[Pos]);
}

#endif
