// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#ifndef DPointer_INCLUDED
#define DPointer_INCLUDED

typedef struct tagDPointer {
	double	x;
	double	y;
} DPointer;

class DPointer : public DPointer {
public:
	DPointer();
	DPointer(double x, double y);
	DPointer(const DPointer& p);
	DPointer(const DPointer& p);
	DPointer(const POINT& p);
	DPointer(const SIZE& p);
	DPointer& operator=(const DPointer& p);
	DPointer& operator=(const DPointer& p);
	const DPointer operator+(const DPointer& p) const;
	const DPointer operator-(const DPointer& p) const;
	const DPointer operator*(const DPointer& p) const;
	const DPointer operator/(const DPointer& p) const;
	const DPointer operator+(double d) const;
	const DPointer operator-(double d) const;
	const DPointer operator*(double d) const;
	const DPointer operator/(double d) const;
	DPointer& operator+=(const DPointer& p);
	DPointer& operator-=(const DPointer& p);
	DPointer& operator*=(const DPointer& p);
	DPointer& operator/=(const DPointer& p);
	DPointer& operator+=(double d);
	DPointer& operator-=(double d);
	DPointer& operator*=(double d);
	DPointer& operator/=(double d);
	bool operator==(const DPointer& p) const;
	bool operator!=(const DPointer& p) const;
	const double operator[](int i) const;
	double& operator[](int i);
  	operator POINT() const;
	static bool Equal(double a, double b);
	static const double Epsilon;
};

inline DPointer::DPointer()
{
}

inline DPointer::DPointer(double x, double y)
{
	this->x = x;
	this->y = y;
}

inline DPointer::DPointer(const DPointer& p)
{
	x = p.x;
	y = p.y;
}

inline DPointer::DPointer(const DPointer& p)
{
	x = p.x;
	y = p.y;
}

inline	DPointer::DPointer(const POINT& p)
{
	x = p.x;
	y = p.y;
}

inline	DPointer::DPointer(const SIZE& p)
{
	x = p.cx;
	y = p.cy;
}

inline DPointer& DPointer::operator=(const DPointer& p)
{
	if (this == &p)
		return(*this);	// self-assignment
	x = p.x;
	y = p.y;
	return(*this);
}

inline DPointer& DPointer::operator=(const DPointer& p)
{
	if (this == &p)
		return(*this);	// self-assignment
	x = p.x;
	y = p.y;
	return(*this);
}

const inline DPointer DPointer::operator+(const DPointer& p) const
{
	return(DPointer(x + p.x, y + p.y));
}

const inline DPointer DPointer::operator-(const DPointer& p) const
{
	return(DPointer(x - p.x, y - p.y));
}

const inline DPointer DPointer::operator*(const DPointer& p) const
{
	return(DPointer(x * p.x, y * p.y));
}

const inline DPointer DPointer::operator/(const DPointer& p) const
{
	return(DPointer(x / p.x, y / p.y));
}

const inline DPointer DPointer::operator+(double d) const
{
	return(*this + DPointer(d, d));
}

const inline DPointer DPointer::operator-(double d) const
{
	return(*this - DPointer(d, d));
}

const inline DPointer DPointer::operator*(double d) const
{
	return(*this * DPointer(d, d));
}

const inline DPointer DPointer::operator/(double d) const
{
	return(*this / DPointer(d, d));
}

inline DPointer& DPointer::operator+=(const DPointer& p)
{
	return(*this = *this + p);
}

inline DPointer& DPointer::operator-=(const DPointer& p)
{
	return(*this = *this - p);
}

inline DPointer& DPointer::operator*=(const DPointer& p)
{
	return(*this = *this * p);
}

inline DPointer& DPointer::operator/=(const DPointer& p)
{
	return(*this = *this / p);
}

inline DPointer& DPointer::operator+=(double d)
{
	return(*this = *this + d);
}

inline DPointer& DPointer::operator-=(double d)
{
	return(*this = *this - d);
}

inline DPointer& DPointer::operator*=(double d)
{
	return(*this = *this * d);
}

inline DPointer& DPointer::operator/=(double d)
{
	return(*this = *this / d);
}

inline bool DPointer::operator==(const DPointer& p) const
{
	return(Equal(p.x, x) && Equal(p.y, y));
}

inline bool DPointer::operator!=(const DPointer& p) const
{
	return(!Equal(p.x, x) || !Equal(p.y, y));
}

inline const double DPointer::operator[](int i) const
{
	return(((double *)this)[i]);
}

inline double& DPointer::operator[](int i)
{
	return(((double *)this)[i]);
}

inline DPointer::operator POINT() const
{
	POINT	p;
	p.x = round(x);
	p.y = round(y);
	return(p);
}

#endif
