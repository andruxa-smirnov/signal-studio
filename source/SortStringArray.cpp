// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "SortStringArray.h"

void CSortStringArray::Sort(CStringArray& StrArray)
{
	qsort(StrArray.GetData(), StrArray.GetSize(), sizeof(CString *), compare);
}

int CSortStringArray::compare(const void *arg1, const void *arg2)
{
	return(_tcscmp(*(LPCTSTR *)arg1, *(LPCTSTR *)arg2));
}


