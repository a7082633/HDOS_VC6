// ID_CARD.h : main header file for the ID_CARD application
//

#if !defined(AFX_ID_CARD_H__62FD275C_62E8_4589_A0C5_EF8930072BC3__INCLUDED_)
#define AFX_ID_CARD_H__62FD275C_62E8_4589_A0C5_EF8930072BC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CID_CARDApp:
// See ID_CARD.cpp for the implementation of this class
//

class CID_CARDApp : public CWinApp
{
public:
//	_ConnectionPtr m_pConnection;
	CID_CARDApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CID_CARDApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CID_CARDApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ID_CARD_H__62FD275C_62E8_4589_A0C5_EF8930072BC3__INCLUDED_)
