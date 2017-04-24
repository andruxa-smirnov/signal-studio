// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// SignalStudioDoc.cpp : implementation of the CSignalStudioDoc class

#include "stdafx.h"
#include "SignalStudio.h"

#include "SignalStudioDoc.h"
#include "Benchmark.h"
#include "sndfile.h"
#include "DocuMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSignalStudioDoc

IMPLEMENT_DYNCREATE(CSignalStudioDoc, CDocument)

/////////////////////////////////////////////////////////////////////////////
// CSignalStudioDoc construction/destruction

CSignalStudioDoc::CSignalStudioDoc() : m_UndoMgr(this)
{
	m_UndoMgr.SetLevels(theApp.GetMain()->GetOptions().m_UndoLevels);
	m_AudioFormat = 0;
}

CSignalStudioDoc::~CSignalStudioDoc()
{
}

inline CSignalStudioDoc::CMyRetractManager::CMyRetractManager(CDocument *Doc)
{
	m_Document = Doc;
}

void CSignalStudioDoc::CMyRetractManager::OnModify(bool Modified)
{
	m_Document->SetModifiedFlag(Modified);
}

void CSignalStudioDoc::CMyRetractManager::OnUpdateTitles()
{
	theApp.GetMain()->OnUpdateUndoTitles();
}

/////////////////////////////////////////////////////////////////////////////
// CSignalStudioDoc serialization

void CSignalStudioDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSignalStudioDoc diagnostics

#ifdef _DEBUG
void CSignalStudioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSignalStudioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSignalStudioDoc message map

BEGIN_MESSAGE_MAP(CSignalStudioDoc, CDocument)
	//{{AFX_MSG_MAP(CSignalStudioDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSignalStudioDoc commands

BOOL CSignalStudioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

BOOL CSignalStudioDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	int	AudioFormat;
	if (!m_Wave.Import(lpszPathName, AudioFormat, &m_Metadata))
		return(FALSE);
	// success; update our audio format
	m_AudioFormat = AudioFormat & SF_FORMAT_TYPEMASK;	// preserve format's type only

	return TRUE;
}

BOOL CSignalStudioDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnSaveDocument(lpszPathName))
		return FALSE;

	CDocuMan	*pDocMgr = STATIC_DOWNCAST(CDocuMan, theApp.m_pDocManager);
	int	AudioFormat = pDocMgr->GetAudioFormat();	// get selected audio format
	if (!m_Wave.Export(lpszPathName, AudioFormat, &m_Metadata))
		return(FALSE);
	// success, update our audio format
	m_AudioFormat = AudioFormat;

	return TRUE;
}

BOOL CSignalStudioDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
{
	CDocuMan	*pDocMgr = STATIC_DOWNCAST(CDocuMan, theApp.m_pDocManager);
	pDocMgr->SetAudioFormat(m_AudioFormat);	// pass audio format to doc manager

	CString	ext(PathFindExtension(lpszPathName));
	if (!ext.IsEmpty()) {
		ext.MakeLower();
		if (CString(MP4_FILTER).Find(ext) >= 0)	// if path has AAC/MP4 file extension
			lpszPathName = NULL;	// writing AAC/MP4 isn't supported; force Save As
	}

	return CDocument::DoSave(lpszPathName, bReplace);
}
