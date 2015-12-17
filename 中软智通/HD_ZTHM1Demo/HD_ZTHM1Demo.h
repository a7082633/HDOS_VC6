// HD_ZTHM1Demo.h : main header file for the HD_ZTHM1DEMO application
//

#if !defined(AFX_HD_ZTHM1DEMO_H__ADFD77C4_2CFF_44C6_9F3E_C40297752BC3__INCLUDED_)
#define AFX_HD_ZTHM1DEMO_H__ADFD77C4_2CFF_44C6_9F3E_C40297752BC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1DemoApp:
// See HD_ZTHM1Demo.cpp for the implementation of this class
//

class CHD_ZTHM1DemoApp : public CWinApp
{
public:
	CHD_ZTHM1DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_ZTHM1DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHD_ZTHM1DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHM1DEMO_H__ADFD77C4_2CFF_44C6_9F3E_C40297752BC3__INCLUDED_)
