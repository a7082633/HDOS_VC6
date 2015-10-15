// PCSC Demo.h : main header file for the PCSC DEMO application
//

#if !defined(AFX_PCSCDEMO_H__CBC6AB1E_0B5E_46E5_BD59_33F3B8D26152__INCLUDED_)
#define AFX_PCSCDEMO_H__CBC6AB1E_0B5E_46E5_BD59_33F3B8D26152__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPCSCDemoApp:
// See PCSC Demo.cpp for the implementation of this class
//

class CPCSCDemoApp : public CWinApp
{
public:
	CPCSCDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCSCDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPCSCDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCSCDEMO_H__CBC6AB1E_0B5E_46E5_BD59_33F3B8D26152__INCLUDED_)
