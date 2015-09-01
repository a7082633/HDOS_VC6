// Dll_Call_Dll_TESTDEMO.h : main header file for the DLL_CALL_DLL_TESTDEMO application
//

#if !defined(AFX_DLL_CALL_DLL_TESTDEMO_H__AF9DE3C2_8E3D_4FA9_9AFF_D84CE1E81262__INCLUDED_)
#define AFX_DLL_CALL_DLL_TESTDEMO_H__AF9DE3C2_8E3D_4FA9_9AFF_D84CE1E81262__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDll_Call_Dll_TESTDEMOApp:
// See Dll_Call_Dll_TESTDEMO.cpp for the implementation of this class
//

class CDll_Call_Dll_TESTDEMOApp : public CWinApp
{
public:
	CDll_Call_Dll_TESTDEMOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDll_Call_Dll_TESTDEMOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDll_Call_Dll_TESTDEMOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLL_CALL_DLL_TESTDEMO_H__AF9DE3C2_8E3D_4FA9_9AFF_D84CE1E81262__INCLUDED_)
