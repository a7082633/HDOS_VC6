// HD_BHGXDLL_DEMO.h : main header file for the HD_BHGXDLL_DEMO application
//

#if !defined(AFX_HD_BHGXDLL_DEMO_H__23DA77B0_608F_43E9_9B49_93226B328239__INCLUDED_)
#define AFX_HD_BHGXDLL_DEMO_H__23DA77B0_608F_43E9_9B49_93226B328239__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_BHGXDLL_DEMOApp:
// See HD_BHGXDLL_DEMO.cpp for the implementation of this class
//

class CHD_BHGXDLL_DEMOApp : public CWinApp
{
public:
	CHD_BHGXDLL_DEMOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_BHGXDLL_DEMOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHD_BHGXDLL_DEMOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_BHGXDLL_DEMO_H__23DA77B0_608F_43E9_9B49_93226B328239__INCLUDED_)
