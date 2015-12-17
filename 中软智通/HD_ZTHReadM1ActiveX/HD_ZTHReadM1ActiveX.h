#if !defined(AFX_HD_ZTHREADM1ACTIVEX_H__8864A96A_F9E4_4F03_84D1_084043161EEB__INCLUDED_)
#define AFX_HD_ZTHREADM1ACTIVEX_H__8864A96A_F9E4_4F03_84D1_084043161EEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_ZTHReadM1ActiveX.h : main header file for HD_ZTHREADM1ACTIVEX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXApp : See HD_ZTHReadM1ActiveX.cpp for implementation.

class CHD_ZTHReadM1ActiveXApp : public COleControlModule
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

#endif // !defined(AFX_HD_ZTHREADM1ACTIVEX_H__8864A96A_F9E4_4F03_84D1_084043161EEB__INCLUDED)
