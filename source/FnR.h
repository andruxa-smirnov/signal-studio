// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#pragma once

// define macro to enumerate undo codes
#define UCODE_DEF(name) UCODE_##name,
enum {	// enumerate undo codes
	#include "RDefinitions.h"
	UNDO_CODES,
};

