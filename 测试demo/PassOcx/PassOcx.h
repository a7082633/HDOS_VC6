#if !defined(AFX_PASSOCX_H__D9F0D6BA_92DB_4E1F_BAC5_87AE4A0D60F3__INCLUDED_)
#define AFX_PASSOCX_H__D9F0D6BA_92DB_4E1F_BAC5_87AE4A0D60F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PassOcx.h : main header file for PASSOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPassOcxApp : See PassOcx.cpp for implementation.

class CPassOcxApp : public COleControlModule
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

#endif // !defined(AFX_PASSOCX_H__D9F0D6BA_92DB_4E1F_BAC5_87AE4A0D60F3__INCLUDED)
