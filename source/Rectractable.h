// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CRetractable_INCLUDED
#define CRetractable_INCLUDED

#include "StateReverse.h"
#include "RetractManager.h"

class CRetractable : public WObject {
public:
// Constants
	enum UE_FLAGS {
		UE_COALESCE			= 0x01,
		UE_INSIGNIFICANT	= 0x02
	};

// Construction
	CRetractable();

// Attributes
	CRetractManager	*GetRetractManager() const;
	void	SetRetractManager(CRetractManager *Mgr);
	CRetractable	*GetUndoHandler() const;
	void	SetUndoHandler(CRetractable *Handler);
	int		GetUndoAction() const;
	bool	UndoMgrIsIdle() const;
	bool	IsUndoing() const;
	bool	IsRedoing() const;

// Operations
	void	NotifyRetractableEdit(WORD CtrlID, WORD Code, UINT Flags = 0);
	void	CancelRetractableEdit(WORD CtrlID, WORD Code);
	void	ClearUndoHistory();

// Overridables
	virtual	void	SaveStateReverse(CStateReverse& State) = 0;
	virtual	void	RestoreStateReverse(const CStateReverse& State) = 0;
	virtual	CString	GetUndoTitle(const CStateReverse& State) = 0;

private:
// Member data
	CRetractManager	*m_RetractManager;
};

inline CRetractable::CRetractable()
{
	m_RetractManager = NULL;
}

inline CRetractManager *CRetractable::GetRetractManager() const
{
	return(m_RetractManager);
}

inline void CRetractable::SetRetractManager(CRetractManager *Mgr)
{
	m_RetractManager = Mgr;
}

inline void CRetractable::NotifyRetractableEdit(WORD CtrlID, WORD Code, UINT Flags)
{
	m_RetractManager->NotifyEdit(CtrlID, Code, Flags);
}

inline void CRetractable::CancelRetractableEdit(WORD CtrlID, WORD Code)
{
	m_RetractManager->CancelEdit(CtrlID, Code);
}

inline int CRetractable::GetUndoAction() const
{
	return(m_RetractManager->GetAction());
}

inline bool CRetractable::UndoMgrIsIdle() const
{
	return(m_RetractManager->IsIdle());
}

inline bool CRetractable::IsUndoing() const
{
	return(m_RetractManager->IsUndoing());
}

inline bool CRetractable::IsRedoing() const
{
	return(m_RetractManager->IsRedoing());
}

inline void CRetractable::ClearUndoHistory()
{
	m_RetractManager->DiscardAllEdits();
}

#endif
