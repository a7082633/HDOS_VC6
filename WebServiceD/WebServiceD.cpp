// WebServiceD.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "WebServiceD.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE WebServiceDDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("WEBSERVICED.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(WebServiceDDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(WebServiceDDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("WEBSERVICED.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(WebServiceDDLL);
	}
	return 1;   // ok
}

int __stdcall Auth()
{
	CInternetSession m_session("haha");
	CString strData;
	char *requestUrl="http://221.176.197.13:8011/Api!CardIdentify.do?account=123&&password=123";
	CHttpFile *pFile = (CHttpFile *) m_session.OpenURL(requestUrl, 1, 
	INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_RELOAD);
	char ch;
	while (pFile->Read(&ch, sizeof(TCHAR)))
	{
		strData += ch;
	}
	pFile->Close();
	m_session.Close();
	return 0;
}