// HD_ReadDemo_HN.h : main header file for the HD_READDEMO_HN application
//

#if !defined(AFX_HD_READDEMO_HN_H__40D999AE_EE7D_42D8_8000_2168E7733C33__INCLUDED_)
#define AFX_HD_READDEMO_HN_H__40D999AE_EE7D_42D8_8000_2168E7733C33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHD_ReadDemo_HNApp:
// See HD_ReadDemo_HN.cpp for the implementation of this class
//

class CHD_ReadDemo_HNApp : public CWinApp
{
public:
	CHD_ReadDemo_HNApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_ReadDemo_HNApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHD_ReadDemo_HNApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_READDEMO_HN_H__40D999AE_EE7D_42D8_8000_2168E7733C33__INCLUDED_)
