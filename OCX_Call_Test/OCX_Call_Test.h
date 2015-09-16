#if !defined(AFX_OCX_CALL_TEST_H__02CCD7E6_0579_4910_8C1B_D19DA82E34B8__INCLUDED_)
#define AFX_OCX_CALL_TEST_H__02CCD7E6_0579_4910_8C1B_D19DA82E34B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OCX_Call_Test.h : main header file for OCX_CALL_TEST.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestApp : See OCX_Call_Test.cpp for implementation.

class COCX_Call_TestApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCX_CALL_TEST_H__02CCD7E6_0579_4910_8C1B_D19DA82E34B8__INCLUDED)
