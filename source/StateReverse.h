// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CStateReverse_INCLUDED
#define CStateReverse_INCLUDED

#pragma pack(push, 1)	// 1-byte packing alignment

#include "RefPtr.h"

class CRetractManager;

// create accessors for an undo state value member
#define CStateReverse_VAL(alias, type, member)						\
	inline static const type& alias(const CStateReverse& State)	\
		{ return(State.m_Val.member); }							\
	inline static type& alias(CStateReverse& State)				\
		{ return(State.m_Val.member); }

// reserved control ID for insignificant edits
#define UNDO_CTRL_ID_INSIGNIFICANT 0x8000

class CStateReverse : public CRefPtr<CRefObj> {
public:
// Types
	typedef union tagELEM {
		int		i;
		UINT	u;
		float	f;
		bool	b;
		struct {
			WORD	lo;
			WORD	hi;
		} w;
		struct {
			short	lo;
			short	hi;
		} s;
		struct {
			BYTE	al;
			BYTE	ah;
			BYTE	bl;
			BYTE	bh;
		} c;
	} ELEM;
	typedef struct tagPAIR {
		ELEM	x;
		ELEM	y;
	} PAIR;
	typedef union tagVALUE {
		PAIR	p;
		double	d;
		__int64	i64;
	} VALUE;

// Member data
	VALUE	m_Val;

// Attributes
	WORD	GetCtrlID() const;
	WORD	GetCode() const;
	bool	IsMatch(WORD CtrlID, WORD Code) const;
	bool	IsSignificant() const;

// Construction
	CStateReverse();
	CStateReverse(const CStateReverse& State);
	CStateReverse& operator=(const CStateReverse& State);

// Operations
	CString	DumpState() const;
	void	Empty();

private:
// Member data
	WORD	m_CtrlID;	// ID of notifying control; UNDO_ID_INSIGNIFICANT
						// is reserved for flagging insignificant edits
	WORD	m_Code;		// edit function code

// Helpers
	void	Copy(const CStateReverse& State);

	friend CRetractManager;
};

#pragma pack(pop)	// restore default packing

inline CStateReverse::CStateReverse()
{
}

inline WORD CStateReverse::GetCtrlID() const
{
	return(m_CtrlID);
}

inline WORD CStateReverse::GetCode() const
{
	return(m_Code);
}

inline bool CStateReverse::IsMatch(WORD CtrlID, WORD Code) const
{
	return(CtrlID == m_CtrlID && Code == m_Code);
}

inline bool CStateReverse::IsSignificant() const
{
	return(m_CtrlID != UNDO_CTRL_ID_INSIGNIFICANT);
}

inline void CStateReverse::Empty()
{
	CRefPtr<CRefObj>::SetEmpty();
	memset(&m_Val, 0, sizeof(VALUE));
}

#endif
