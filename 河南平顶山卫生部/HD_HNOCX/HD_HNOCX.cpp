// HD_HNOCX.cpp : Implementation of CHD_HNOCXApp and DLL registration.

#include "stdafx.h"
#include "HD_HNOCX.h"
#include "ComCat.h"  
#include "ObjSafe.h"  
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CHD_HNOCXApp NEAR theApp;
const GUID CDECL CLSID_SafeItem =  
        { 0xc16c150f, 0x5a24, 0x4615, { 0x83, 0x7a, 0x18, 0x98, 0xbe, 0x46, 0x43, 0x49 } };  
const GUID CDECL BASED_CODE _tlid =
		{ 0x36a81db1, 0xe1a0, 0x47e7, { 0x82, 0xd1, 0x13, 0x27, 0xc8, 0x4c, 0x2b, 0xd7 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXApp::InitInstance - DLL initialization
HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription)  
{  
    ICatRegister *pcr = NULL ;  
    HRESULT hr = S_OK ;  
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,   
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);  
    if (FAILED(hr))  
        return hr;  
  
    // 确认HKCR\Component Categories\{..catid...}键值被注册  
    CATEGORYINFO catinfo;  
    catinfo.catid = catid;  
    catinfo.lcid = 0x0409; // english  
    //size_t len;  
    // 确认描述不是太长。  
    // 只复制开始的127个字符。  
    // StringCchLength的第二个参数表示被读入catDescription的最大字符数。  
    // 第三个参数表示字符串的长度  
    //hr = StringCchLength(catDescription, STRSAFE_MAX_CCH, &len);  
    int len = wcslen(catDescription);  
    if (SUCCEEDED(hr))  
    {  
        if (len>127)  
        {  
            len = 127;  
        }  
    }     
    else  
    {  
        // TODO: Write an error handler;  
    }  
  
    wcsncpy(catinfo.szDescription, catDescription, len);  
    //hr = StringCchCopy(catinfo.szDescription, len + 1, catDescription);  
    // 添加字符串结束符.  
    //catinfo.szDescription[len + 1] = '\0';  
    catinfo.szDescription[len] = '/0';  
  
    hr = pcr->RegisterCategories(1, &catinfo);  
    pcr->Release();  
    return hr;  
} 
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)  
{  
    // 注册组件分类信息  
    ICatRegister *pcr = NULL ;  
    HRESULT hr = S_OK ;  
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,   
                NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);  
  
    if (SUCCEEDED(hr))  
    {  
       CATID rgcatid[1] ;  
       rgcatid[0] = catid;  
       hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);  
    }  
  
    if (pcr != NULL)  
        pcr->Release();  
              
    return hr;  
  
} 
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)  
{  
    ICatRegister *pcr = NULL ;  
    HRESULT hr = S_OK ;  
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,   
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);  
  
    if (SUCCEEDED(hr))  
    {  
       CATID rgcatid[1] ;  
       rgcatid[0] = catid;  
       hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);  
    }  
  
    if (pcr != NULL)  
        pcr->Release();  
    return hr;  
} 
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
    //创建脚本安全“补充”项，非CLSID中  
    HRESULT hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");  
    if (FAILED(hr))  
        return hr;  
  
    //创建初始化安全“补充”项，非CLSID中  
    hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");  
    if (FAILED(hr))  
        return hr;  
  
    //设置控件CLSID中补充项的脚本安全项，与“补充”项中的脚本安全项对应  
    hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);  
    if (FAILED(hr))  
        return hr;  
  
    //设置控件CLSID中补充项的初始化安全项，与“补充”项中的初始化安全项对应  
    hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);  
    if (FAILED(hr))  
        return hr;  
	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);
    // 删除控件初始化安全入口.  
    HRESULT hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);  
    if (FAILED(hr))  
        return hr;  
    // 删除控件脚本安全入口  
    hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);  
    if (FAILED(hr))  
        return hr; 
	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
 