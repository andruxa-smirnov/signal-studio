// Copyleft 2017 Akshay.C.S. Based on works by Chris Korda and others.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or any later version.

// FnChangeFormat.cpp : implementation file

#include "stdafx.h"
#include "Resource.h"
#include "FnChangeFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFnChangeFormat dialog

CFnChangeFormat::CFnChangeFormat(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CFnChangeFormat)
	m_SampleRate = 0;
	m_SampleBits = 0;
	m_Channels = 0;
	//}}AFX_DATA_INIT
}

void CFnChangeFormat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFnChangeFormat)
	DDX_Text(pDX, IDC_CFMT_SAMPLE_RATE, m_SampleRate);
	DDV_MinMaxUInt(pDX, m_SampleRate, 1, 4294967295);
	DDX_Text(pDX, IDC_CFMT_SAMPLE_BITS, m_SampleBits);
	DDV_MinMaxUInt(pDX, m_SampleBits, 1, 32);
	DDX_Text(pDX, IDC_CFMT_CHANNELS, m_Channels);
	DDV_MinMaxUInt(pDX, m_Channels, 1, 65535);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFnChangeFormat message map

BEGIN_MESSAGE_MAP(CFnChangeFormat, CDialog)
	//{{AFX_MSG_MAP(CFnChangeFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFnChangeFormat message handlers
