// SendCmd_Health.h : main header file for the SENDCMD_HEALTH application
//

#if !defined(AFX_SENDCMD_HEALTH_H__3D652CBC_4AD2_4792_AD9C_23A6EE7E3D35__INCLUDED_)
#define AFX_SENDCMD_HEALTH_H__3D652CBC_4AD2_4792_AD9C_23A6EE7E3D35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSendCmd_HealthApp:
// See SendCmd_Health.cpp for the implementation of this class
//

class CSendCmd_HealthApp : public CWinApp
{
public:
	CSendCmd_HealthApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendCmd_HealthApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSendCmd_HealthApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDCMD_HEALTH_H__3D652CBC_4AD2_4792_AD9C_23A6EE7E3D35__INCLUDED_)
