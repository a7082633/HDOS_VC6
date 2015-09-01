#if !defined(AFX_HD_XJOCX_H__C3E9727E_B093_4076_A41D_D70374CDA603__INCLUDED_)
#define AFX_HD_XJOCX_H__C3E9727E_B093_4076_A41D_D70374CDA603__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_XJOCX.h : main header file for HD_XJOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXApp : See HD_XJOCX.cpp for implementation.

class CHD_XJOCXApp : public COleControlModule
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

#endif // !defined(AFX_HD_XJOCX_H__C3E9727E_B093_4076_A41D_D70374CDA603__INCLUDED)
