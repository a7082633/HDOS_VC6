// HD_HNOCX.cpp : Implementation of CHD_HNOCXApp and DLL registration.

#include "stdafx.h"
#include "HD_HNOCX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CHD_HNOCXApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x36a81db1, 0xe1a0, 0x47e7, { 0x82, 0xd1, 0x13, 0x27, 0xc8, 0x4c, 0x2b, 0xd7 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXApp::InitInstance - DLL initialization

BOOL CHD_HNOCXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
        // TODO: 在此添加您自己的模块初始化代码。
//        CString g_szOcxPath = this->m_pszHelpFilePath;
//        CString g_szOcxName = this->m_pszExeName;
// 
//        g_szOcxName += ".HLP";
//        int nTmp = g_szOcxName.GetLength();
//        nTmp = g_szOcxPath.GetLength() - nTmp;
//        g_szOcxPath = g_szOcxPath.Left(nTmp);
//
//		::MessageBox(NULL,g_szOcxPath,NULL,MB_OK);
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXApp::ExitInstance - DLL termination

int CHD_HNOCXApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
