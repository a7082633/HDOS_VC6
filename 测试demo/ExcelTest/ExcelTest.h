// ExcelTest.h : main header file for the EXCELTEST application
//

#if !defined(AFX_EXCELTEST_H__F744D543_5F28_4DBE_B784_84985618FC3D__INCLUDED_)
#define AFX_EXCELTEST_H__F744D543_5F28_4DBE_B784_84985618FC3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExcelTestApp:
// See ExcelTest.cpp for the implementation of this class
//

class CExcelTestApp : public CWinApp
{
public:
	CExcelTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExcelTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELTEST_H__F744D543_5F28_4DBE_B784_84985618FC3D__INCLUDED_)
