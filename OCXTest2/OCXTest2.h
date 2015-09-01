#if !defined(AFX_OCXTEST2_H__95B16181_A0C7_43E2_B1B2_206C6CCEADDC__INCLUDED_)
#define AFX_OCXTEST2_H__95B16181_A0C7_43E2_B1B2_206C6CCEADDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OCXTest2.h : main header file for OCXTEST2.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COCXTest2App : See OCXTest2.cpp for implementation.

class COCXTest2App : public COleControlModule
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

#endif // !defined(AFX_OCXTEST2_H__95B16181_A0C7_43E2_B1B2_206C6CCEADDC__INCLUDED)
