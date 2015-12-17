// HD_ZTHDemo.h : main header file for the HD_ZTHDEMO application
//

#if !defined(AFX_HD_ZTHDEMO_H__D759DDCD_4CA9_4DC0_9EED_70D082E262E9__INCLUDED_)
#define AFX_HD_ZTHDEMO_H__D759DDCD_4CA9_4DC0_9EED_70D082E262E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHDemoApp:
// See HD_ZTHDemo.cpp for the implementation of this class
//

class CHD_ZTHDemoApp : public CWinApp
{
public:
	CHD_ZTHDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_ZTHDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHD_ZTHDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHDEMO_H__D759DDCD_4CA9_4DC0_9EED_70D082E262E9__INCLUDED_)
