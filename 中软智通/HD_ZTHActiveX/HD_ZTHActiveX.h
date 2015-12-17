#if !defined(AFX_HD_ZTHACTIVEX_H__15B756BA_7000_4E99_B0B5_5B500BB63984__INCLUDED_)
#define AFX_HD_ZTHACTIVEX_H__15B756BA_7000_4E99_B0B5_5B500BB63984__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// HD_ZTHActiveX.h : main header file for HD_ZTHACTIVEX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXApp : See HD_ZTHActiveX.cpp for implementation.

class CHD_ZTHActiveXApp : public COleControlModule
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

#endif // !defined(AFX_HD_ZTHACTIVEX_H__15B756BA_7000_4E99_B0B5_5B500BB63984__INCLUDED)
