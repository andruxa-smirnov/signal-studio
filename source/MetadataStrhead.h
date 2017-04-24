// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// these symbols must match the string type enum in sndfile.h

//			sndfile_str		id3v2_tag	wav_tag
METADATASTR(TITLE,			"TIT2",		'INAM')
METADATASTR(COPYRIGHT,		"TCOP",		'ICOP')
METADATASTR(SOFTWARE,		"TSSE",		'ISFT')
METADATASTR(ARTIST,			"TPE1",		'IART')
METADATASTR(COMMENT,		"COMM",		'ICMT')
METADATASTR(DATE,			"TDRC",		'ICRD')
METADATASTR(ALBUM,			"TALB",		'IPRD')
METADATASTR(LICENSE,		"TOWN",		0)
METADATASTR(TRACKNUMBER,	"TRCK",		'itrk')	// non-standard WAV tag
METADATASTR(GENRE,			"TCON",		'IGNR')

#undef METADATASTR
