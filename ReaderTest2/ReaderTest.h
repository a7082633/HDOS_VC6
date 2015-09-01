// ReaderTest.h : main header file for the READERTEST application
//

#if !defined(AFX_READERTEST_H__B3B801C9_0451_4DB1_A4F7_B855266636A3__INCLUDED_)
#define AFX_READERTEST_H__B3B801C9_0451_4DB1_A4F7_B855266636A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReaderTestApp:
// See ReaderTest.cpp for the implementation of this class
//

class CReaderTestApp : public CWinApp
{
public:
	CReaderTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReaderTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReaderTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READERTEST_H__B3B801C9_0451_4DB1_A4F7_B855266636A3__INCLUDED_)
