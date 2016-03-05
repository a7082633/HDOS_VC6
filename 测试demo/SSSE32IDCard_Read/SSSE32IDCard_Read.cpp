// SSSE32IDCard_Read.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SSSE32IDCard_Read.h"
#include "SSSE32IDCard_ReadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSSE32IDCard_ReadApp

BEGIN_MESSAGE_MAP(CSSSE32IDCard_ReadApp, CWinApp)
	//{{AFX_MSG_MAP(CSSSE32IDCard_ReadApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSSE32IDCard_ReadApp construction

CSSSE32IDCard_ReadApp::CSSSE32IDCard_ReadApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSSSE32IDCard_ReadApp object

CSSSE32IDCard_ReadApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSSSE32IDCard_ReadApp initialization

BOOL CSSSE32IDCard_ReadApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CSSSE32IDCard_ReadDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
