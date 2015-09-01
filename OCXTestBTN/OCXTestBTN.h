#if !defined(AFX_OCXTESTBTN_H__AE1C75DA_84F2_4862_8BA1_EBB2988E7748__INCLUDED_)
#define AFX_OCXTESTBTN_H__AE1C75DA_84F2_4862_8BA1_EBB2988E7748__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// OCXTestBTN.h : main header file for OCXTESTBTN.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNApp : See OCXTestBTN.cpp for implementation.

class COCXTestBTNApp : public COleControlModule
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

#endif // !defined(AFX_OCXTESTBTN_H__AE1C75DA_84F2_4862_8BA1_EBB2988E7748__INCLUDED)
