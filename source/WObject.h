// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

class WObject {
public:
	WObject() {}	// default ctor required

private:
	WObject(const WObject&);	// prevent bitwise copy
	WObject& operator=(const WObject&);	// prevent bitwise assignment
};
