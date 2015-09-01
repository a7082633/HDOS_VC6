#if !defined(AFX_HD_HNOCX_H__8790455B_5073_48FD_9961_3F891B370885__INCLUDED_)
#define AFX_HD_HNOCX_H__8790455B_5073_48FD_9961_3F891B370885__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_HNOCX.h : main header file for HD_HNOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXApp : See HD_HNOCX.cpp for implementation.

class CHD_HNOCXApp : public COleControlModule
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

#endif // !defined(AFX_HD_HNOCX_H__8790455B_5073_48FD_9961_3F891B370885__INCLUDED)
