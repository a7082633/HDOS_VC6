// M1.h : main header file for the M1 application
//

#if !defined(AFX_M1_H__3A280A29_0886_448C_853E_F5A23032A03A__INCLUDED_)
#define AFX_M1_H__3A280A29_0886_448C_853E_F5A23032A03A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CM1App:
// See M1.cpp for the implementation of this class
//

class CM1App : public CWinApp
{
public:
	CM1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CM1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CM1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_M1_H__3A280A29_0886_448C_853E_F5A23032A03A__INCLUDED_)
