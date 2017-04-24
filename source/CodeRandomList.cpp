// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "CodeRandomList.h"

CCodeRandomList::CCodeRandomList()
{
	m_Avail = 0;
}

CCodeRandomList::CCodeRandomList(int Size)
{
	Init(Size);
}

void CCodeRandomList::Init(int Size)
{
	m_List.SetSize(Size);
	for (int i = 0; i < Size; i++)
		m_List[i] = i;
	m_Avail = 0;
}

int CCodeRandomList::Rand(int Vals)
{
	if (Vals <= 0)
		return(-1);
	int	i = trunc(rand() / double(RAND_MAX) * Vals);
	return(min(i, Vals - 1));
}

int CCodeRandomList::GetNext()
{
	if (!m_Avail)
		m_Avail = GetSize();
	ASSERT(m_Avail > 0);
	int	idx = Rand(m_Avail);
	m_Avail--;
	int	tmp = m_List[idx];
	m_List[idx] = m_List[m_Avail];
	m_List[m_Avail] = tmp;
	return(tmp);
}
