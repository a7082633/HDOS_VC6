// HD_EEDSInterfaceDemo.h : main header file for the HD_EEDSINTERFACEDEMO application
//

#if !defined(AFX_HD_EEDSINTERFACEDEMO_H__09E1AEEA_EE87_46E0_8F15_37C7F0CF26DE__INCLUDED_)
#define AFX_HD_EEDSINTERFACEDEMO_H__09E1AEEA_EE87_46E0_8F15_37C7F0CF26DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_EEDSInterfaceDemoApp:
// See HD_EEDSInterfaceDemo.cpp for the implementation of this class
//

class CHD_EEDSInterfaceDemoApp : public CWinApp
{
public:
	CHD_EEDSInterfaceDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_EEDSInterfaceDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHD_EEDSInterfaceDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_EEDSINTERFACEDEMO_H__09E1AEEA_EE87_46E0_8F15_37C7F0CF26DE__INCLUDED_)
