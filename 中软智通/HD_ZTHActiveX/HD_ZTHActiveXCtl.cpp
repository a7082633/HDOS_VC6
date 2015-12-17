// HD_ZTHActiveXCtl.cpp : Implementation of the CHD_ZTHActiveXCtrl ActiveX Control class.

#include "stdafx.h"
#include "HD_ZTHActiveX.h"
#include "HD_ZTHActiveXCtl.h"
#include "HD_ZTHActiveXPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_ZTHActiveXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_ZTHActiveXCtrl, COleControl)
	//{{AFX_MSG_MAP(CHD_ZTHActiveXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CHD_ZTHActiveXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CHD_ZTHActiveXCtrl)
	DISP_FUNCTION(CHD_ZTHActiveXCtrl, "HDCloseDevice", HDCloseDevice, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CHD_ZTHActiveXCtrl, "HDReadCardInfo", HDReadCardInfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CHD_ZTHActiveXCtrl, "HDOpenDevice", HDOpenDevice, VT_BSTR, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CHD_ZTHActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CHD_ZTHActiveXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CHD_ZTHActiveXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CHD_ZTHActiveXCtrl, 1)
	PROPPAGEID(CHD_ZTHActiveXPropPage::guid)
END_PROPPAGEIDS(CHD_ZTHActiveXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_ZTHActiveXCtrl, "HDZTHACTIVEX.HDZTHActiveXCtrl.1",
	0xc2c8a499, 0x2a17, 0x452a, 0x9d, 0xfd, 0xb3, 0xbc, 0x78, 0x1c, 0xaf, 0x9c)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CHD_ZTHActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DHD_ZTHActiveX =
		{ 0xdc54e445, 0x7c27, 0x4567, { 0x81, 0xa5, 0x55, 0x77, 0xd7, 0xdd, 0x9, 0x1d } };
const IID BASED_CODE IID_DHD_ZTHActiveXEvents =
		{ 0x7ad160a7, 0x3193, 0x479c, { 0x86, 0x1e, 0x7d, 0x2f, 0xd8, 0x37, 0x35, 0x1a } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwHD_ZTHActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CHD_ZTHActiveXCtrl, IDS_HD_ZTHACTIVEX, _dwHD_ZTHActiveXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXCtrl::CHD_ZTHActiveXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_ZTHActiveXCtrl

BOOL CHD_ZTHActiveXCtrl::CHD_ZTHActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_HD_ZTHACTIVEX,
			IDB_HD_ZTHACTIVEX,
			afxRegApartmentThreading,
			_dwHD_ZTHActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXCtrl::CHD_ZTHActiveXCtrl - Constructor

CHD_ZTHActiveXCtrl::CHD_ZTHActiveXCtrl()
{
	InitializeIIDs(&IID_DHD_ZTHActiveX, &IID_DHD_ZTHActiveXEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXCtrl::~CHD_ZTHActiveXCtrl - Destructor

CHD_ZTHActiveXCtrl::~CHD_ZTHActiveXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXCtrl::OnDraw - Drawing function

void CHD_ZTHActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXCtrl::DoPropExchange - Persistence support

void CHD_ZTHActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXCtrl::OnResetState - Reset control to default state

void CHD_ZTHActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXCtrl::AboutBox - Display an "About" box to the user

void CHD_ZTHActiveXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_HD_ZTHACTIVEX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXCtrl message handlers

//BSTR CHD_ZTHActiveXCtrl::HDOpenDevice(LPCTSTR PIN) 
//{
//	CString strResult;
//	// TODO: Add your dispatch handler code here
//	char pErr[100]={0};
//	int ret=HD_OpenDevice((char *)PIN,pErr);
//	if(ret!=0)
//	{
//		strResult.Format("%s",pErr);
//	}else
//	{
//		strResult.Format("打开设备成功!",pErr);
//	}
//	return strResult.AllocSysString();
//}

BSTR CHD_ZTHActiveXCtrl::HDCloseDevice() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	HD_CloseDevice();
	strResult.Format("关闭设备成功!");
	return strResult.AllocSysString();
}

BSTR CHD_ZTHActiveXCtrl::HDReadCardInfo(LPCTSTR Key) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	//char Key[50]="ffffffffffff";
	char CardType[100]={0};
	char CardNo[100]={0};
	char Name[100]={0};
	char Sex[100]={0};
	char Born[100]={0};
	char IDNo[100]={0};
	char MakeCDT[100]={0};
	char EffectD[100]={0};
	char Nation[100]={0};
	char pErr[100]={0};
	int ret=HD_ReadCardInfo((char *)Key,CardType,CardNo,Name,Sex,Born,IDNo,MakeCDT,EffectD,Nation,pErr);
	if(ret!=0)
	{
		strResult.Format("<ERROR>%s</ERROR>",pErr);
	}else
		strResult.Format("<DATA>%s|%s|%s|%s|%s|%s|%s|%s|%s</DATA>",CardType,CardNo,Name,Sex,Born,IDNo,MakeCDT,EffectD,Nation);
	return strResult.AllocSysString();
}

BSTR CHD_ZTHActiveXCtrl::HDOpenDevice(LPCTSTR PIN) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char pErr[100]={0};
	int ret=HD_OpenDevice((char *)PIN,pErr);
	if(ret!=0)
	{
		strResult.Format("%s",pErr);
	}else
	{
		strResult.Format("打开设备成功!",pErr);
	}
	return strResult.AllocSysString();
}
