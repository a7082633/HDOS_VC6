// RWHealthSpeedTest.h : main header file for the RWHEALTHSPEEDTEST application
//

#if !defined(AFX_RWHEALTHSPEEDTEST_H__8ACD8F3B_720F_4BF5_9CB4_831982DEE9EE__INCLUDED_)
#define AFX_RWHEALTHSPEEDTEST_H__8ACD8F3B_720F_4BF5_9CB4_831982DEE9EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRWHealthSpeedTestApp:
// See RWHealthSpeedTest.cpp for the implementation of this class
//

class CRWHealthSpeedTestApp : public CWinApp
{
public:
	CRWHealthSpeedTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRWHealthSpeedTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRWHealthSpeedTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RWHEALTHSPEEDTEST_H__8ACD8F3B_720F_4BF5_9CB4_831982DEE9EE__INCLUDED_)
