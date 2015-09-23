#if !defined(AFX_TESTOCX_H__A24C10E7_2E6F_455E_8815_4596B47E157E__INCLUDED_)
#define AFX_TESTOCX_H__A24C10E7_2E6F_455E_8815_4596B47E157E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// TestOcx.h : main header file for TESTOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestOcxApp : See TestOcx.cpp for implementation.

class CTestOcxApp : public COleControlModule
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

#endif // !defined(AFX_TESTOCX_H__A24C10E7_2E6F_455E_8815_4596B47E157E__INCLUDED)
