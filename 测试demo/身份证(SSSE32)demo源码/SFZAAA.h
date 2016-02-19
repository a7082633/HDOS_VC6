// SFZAAA.h : main header file for the SFZAAA application
//

#if !defined(AFX_SFZAAA_H__88BF4999_289E_42C4_9995_75D8F56F53FB__INCLUDED_)
#define AFX_SFZAAA_H__88BF4999_289E_42C4_9995_75D8F56F53FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSFZAAAApp:
// See SFZAAA.cpp for the implementation of this class
//

class CSFZAAAApp : public CWinApp
{
public:
	CSFZAAAApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFZAAAApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSFZAAAApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFZAAA_H__88BF4999_289E_42C4_9995_75D8F56F53FB__INCLUDED_)
