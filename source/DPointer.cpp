// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#include "stdafx.h"
#include "DPointer.h"
#include "math.h"

const double DPointer::Epsilon = 1e-10;

bool DPointer::Equal(double a, double b)
{
	return(fabs(a - b) < Epsilon);	// less than this and they're equal
}
