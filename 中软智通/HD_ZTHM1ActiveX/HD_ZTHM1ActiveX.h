#if !defined(AFX_HD_ZTHM1ACTIVEX_H__F1AABC71_F219_465A_9226_F377A78516D8__INCLUDED_)
#define AFX_HD_ZTHM1ACTIVEX_H__F1AABC71_F219_465A_9226_F377A78516D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_ZTHM1ActiveX.h : main header file for HD_ZTHM1ACTIVEX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXApp : See HD_ZTHM1ActiveX.cpp for implementation.

class CHD_ZTHM1ActiveXApp : public COleControlModule
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

#endif // !defined(AFX_HD_ZTHM1ACTIVEX_H__F1AABC71_F219_465A_9226_F377A78516D8__INCLUDED)
