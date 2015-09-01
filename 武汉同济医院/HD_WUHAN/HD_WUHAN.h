// HD_WUHAN.h : main header file for the HD_WUHAN application
//

#if !defined(AFX_HD_WUHAN_H__13910DE0_7CC5_4EE8_ADBA_F79E56A0CBE7__INCLUDED_)
#define AFX_HD_WUHAN_H__13910DE0_7CC5_4EE8_ADBA_F79E56A0CBE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_WUHANApp:
// See HD_WUHAN.cpp for the implementation of this class
//

class CHD_WUHANApp : public CWinApp
{
public:
	CHD_WUHANApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_WUHANApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHD_WUHANApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_WUHAN_H__13910DE0_7CC5_4EE8_ADBA_F79E56A0CBE7__INCLUDED_)
