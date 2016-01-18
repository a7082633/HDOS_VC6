#if !defined(AFX_HD_SHHEALTHYACX_H__6969E7AC_A22B_4B5C_B5F7_5FB131CF1CA5__INCLUDED_)
#define AFX_HD_SHHEALTHYACX_H__6969E7AC_A22B_4B5C_B5F7_5FB131CF1CA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_SHHealthyACX.h : main header file for HD_SHHEALTHYACX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXApp : See HD_SHHealthyACX.cpp for implementation.

class CHD_SHHealthyACXApp : public COleControlModule
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

#endif // !defined(AFX_HD_SHHEALTHYACX_H__6969E7AC_A22B_4B5C_B5F7_5FB131CF1CA5__INCLUDED)
