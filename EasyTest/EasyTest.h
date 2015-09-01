// EasyTest.h : main header file for the EASYTEST application
//

#if !defined(AFX_EASYTEST_H__1F9203A0_2B45_4F73_ADDE_86F36169E52B__INCLUDED_)
#define AFX_EASYTEST_H__1F9203A0_2B45_4F73_ADDE_86F36169E52B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEasyTestApp:
// See EasyTest.cpp for the implementation of this class
//

class CEasyTestApp : public CWinApp
{
public:
	CEasyTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEasyTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYTEST_H__1F9203A0_2B45_4F73_ADDE_86F36169E52B__INCLUDED_)
