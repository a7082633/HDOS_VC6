#if !defined(AFX_AUTHOCX_H__36CF98BE_0D4E_42BD_AC2C_EBD77A030F99__INCLUDED_)
#define AFX_AUTHOCX_H__36CF98BE_0D4E_42BD_AC2C_EBD77A030F99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// AuthOCX.h : main header file for AUTHOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAuthOCXApp : See AuthOCX.cpp for implementation.

class CAuthOCXApp : public COleControlModule
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

#endif // !defined(AFX_AUTHOCX_H__36CF98BE_0D4E_42BD_AC2C_EBD77A030F99__INCLUDED)
