// USB_Test.h : main header file for the USB_TEST application
//

#if !defined(AFX_USB_TEST_H__687B874A_8095_4455_BB75_8616223B5C7B__INCLUDED_)
#define AFX_USB_TEST_H__687B874A_8095_4455_BB75_8616223B5C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUSB_TestApp:
// See USB_Test.cpp for the implementation of this class
//

class CUSB_TestApp : public CWinApp
{
public:
	CUSB_TestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUSB_TestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUSB_TestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USB_TEST_H__687B874A_8095_4455_BB75_8616223B5C7B__INCLUDED_)
