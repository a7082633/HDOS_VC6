#if !defined(AFX_HD_CPUANDID_H__FE97DC18_F7C6_4B41_941B_C6B0AEE697AF__INCLUDED_)
#define AFX_HD_CPUANDID_H__FE97DC18_F7C6_4B41_941B_C6B0AEE697AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_CPUAndID.h : main header file for HD_CPUANDID.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDApp : See HD_CPUAndID.cpp for implementation.

class CHD_CPUAndIDApp : public COleControlModule
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

#endif // !defined(AFX_HD_CPUANDID_H__FE97DC18_F7C6_4B41_941B_C6B0AEE697AF__INCLUDED)
