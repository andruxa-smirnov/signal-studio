// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

#pragma once

class CDocTemplateIter : public WObject {
public:
	CDocTemplateIter();
	CDocTemplate	*GetNextDocTemplate();

protected:
	POSITION	m_TplPos;	// template position
};

class CDclter : public WObject {
public:
	CDclter(CDocTemplate *pTpl);
	CDocument	*GetNextDoc();

protected:
	CDocTemplate	*m_pTpl;	// template pointer
	POSITION	m_DocPos;		// document position
};

class CViewIter : public WObject {
public:
	CViewIter(CDocument *pDoc);
	CView	*GetNextView();

protected:
	CDocument	*m_pDoc;		// document pointer
	POSITION	m_ViewPos;		// view position
};

class CAllDclter : public WObject {
public:
	CAllDclter();
	CDocument	*GetNextDoc();

protected:
	CDocTemplateIter	m_TplIter;	// template iterator
	CDocTemplate	*m_pTpl;		// template pointer
	POSITION	m_DocPos;			// document position
};

class CAllViewIter : public WObject {
public:
	CAllViewIter();
	CView	*GetNextView();

protected:
	CAllDclter	m_Dclter;		// document iterator
	CDocument	*m_pDoc;		// document pointer
	POSITION	m_ViewPos;		// view position
};

class CMDIChildIter : public WObject {
public:
	CMDIChildWnd	*GetNextChild();

protected:
	CAllDclter	m_Dclter;	// all document iterator
};
