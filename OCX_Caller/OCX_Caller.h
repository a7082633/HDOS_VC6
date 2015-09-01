// OCX_Caller.h : main header file for the OCX_CALLER application
//

#if !defined(AFX_OCX_CALLER_H__C443FBD3_0906_4803_B1D9_CF891CD4D987__INCLUDED_)
#define AFX_OCX_CALLER_H__C443FBD3_0906_4803_B1D9_CF891CD4D987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COCX_CallerApp:
// See OCX_Caller.cpp for the implementation of this class
//

class COCX_CallerApp : public CWinApp
{
public:
	COCX_CallerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCX_CallerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COCX_CallerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCX_CALLER_H__C443FBD3_0906_4803_B1D9_CF891CD4D987__INCLUDED_)
