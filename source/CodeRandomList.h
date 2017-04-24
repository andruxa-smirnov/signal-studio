// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef CCodeRandomList_DEFINED
#define CCodeRandomList_DEFINED

class CCodeRandomList : public WObject {
public:
	CCodeRandomList();
	CCodeRandomList(int Size);
	static	int		Rand(int Vals);
	void	Init(int Size);
	int		GetNext();
	int		GetSize() const;
	int		GetAvail() const;

private:
	CDWordArray	m_List;	// array of randomly generated elements
	int		m_Avail;	// number of elements that haven't been used
};

inline int CCodeRandomList::GetSize() const
{
	return(static_cast<int>(m_List.GetSize()));	// cast to 32-bit
}

inline int CCodeRandomList::GetAvail() const
{
	return(m_Avail);
}

#endif
