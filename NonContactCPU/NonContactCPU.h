// NonContactCPU.h : main header file for the NONCONTACTCPU application
//

#if !defined(AFX_NONCONTACTCPU_H__BA8E7422_547E_4411_9801_1917ECB09E2D__INCLUDED_)
#define AFX_NONCONTACTCPU_H__BA8E7422_547E_4411_9801_1917ECB09E2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNonContactCPUApp:
// See NonContactCPU.cpp for the implementation of this class
//

class CNonContactCPUApp : public CWinApp
{
public:
	CNonContactCPUApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNonContactCPUApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNonContactCPUApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NONCONTACTCPU_H__BA8E7422_547E_4411_9801_1917ECB09E2D__INCLUDED_)
