// HD_HDRWInterfaceDemo.h : main header file for the HD_HDRWINTERFACEDEMO application
//

#if !defined(AFX_HD_HDRWINTERFACEDEMO_H__8E8B354F_254F_4945_8A80_664ADE10E2F7__INCLUDED_)
#define AFX_HD_HDRWINTERFACEDEMO_H__8E8B354F_254F_4945_8A80_664ADE10E2F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_HDRWInterfaceDemoApp:
// See HD_HDRWInterfaceDemo.cpp for the implementation of this class
//

class CHD_HDRWInterfaceDemoApp : public CWinApp
{
public:
	CHD_HDRWInterfaceDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_HDRWInterfaceDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHD_HDRWInterfaceDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_HDRWINTERFACEDEMO_H__8E8B354F_254F_4945_8A80_664ADE10E2F7__INCLUDED_)
