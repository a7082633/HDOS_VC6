// HD_ZTHM1ActiveXCtl.cpp : Implementation of the CHD_ZTHM1ActiveXCtrl ActiveX Control class.

#include "stdafx.h"
#include "HD_ZTHM1ActiveX.h"
#include "HD_ZTHM1ActiveXCtl.h"
#include "HD_ZTHM1ActiveXPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_ZTHM1ActiveXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_ZTHM1ActiveXCtrl, COleControl)
	//{{AFX_MSG_MAP(CHD_ZTHM1ActiveXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CHD_ZTHM1ActiveXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CHD_ZTHM1ActiveXCtrl)
	DISP_FUNCTION(CHD_ZTHM1ActiveXCtrl, "HDWriteM1", HDWriteM1, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CHD_ZTHM1ActiveXCtrl, "HDReadM1", HDReadM1, VT_BSTR, VTS_BSTR VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CHD_ZTHM1ActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CHD_ZTHM1ActiveXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CHD_ZTHM1ActiveXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CHD_ZTHM1ActiveXCtrl, 1)
	PROPPAGEID(CHD_ZTHM1ActiveXPropPage::guid)
END_PROPPAGEIDS(CHD_ZTHM1ActiveXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_ZTHM1ActiveXCtrl, "HDZTHM1ACTIVEX.HDZTHM1ActiveXCtrl.1",
	0xb0acd71d, 0x6d, 0x428b, 0xb1, 0xb6, 0xa2, 0x11, 0x71, 0xe9, 0x35, 0x43)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CHD_ZTHM1ActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DHD_ZTHM1ActiveX =
		{ 0xeb7eb6e6, 0x9a3f, 0x4aec, { 0xb9, 0x50, 0xf1, 0x78, 0x4e, 0xd7, 0x68, 0xe0 } };
const IID BASED_CODE IID_DHD_ZTHM1ActiveXEvents =
		{ 0x925cf380, 0x7c05, 0x4174, { 0xa3, 0x20, 0x26, 0xb4, 0xd9, 0x64, 0xfe, 0x9e } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwHD_ZTHM1ActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CHD_ZTHM1ActiveXCtrl, IDS_HD_ZTHM1ACTIVEX, _dwHD_ZTHM1ActiveXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXCtrl::CHD_ZTHM1ActiveXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_ZTHM1ActiveXCtrl

BOOL CHD_ZTHM1ActiveXCtrl::CHD_ZTHM1ActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_HD_ZTHM1ACTIVEX,
			IDB_HD_ZTHM1ACTIVEX,
			afxRegApartmentThreading,
			_dwHD_ZTHM1ActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXCtrl::CHD_ZTHM1ActiveXCtrl - Constructor

CHD_ZTHM1ActiveXCtrl::CHD_ZTHM1ActiveXCtrl()
{
	InitializeIIDs(&IID_DHD_ZTHM1ActiveX, &IID_DHD_ZTHM1ActiveXEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXCtrl::~CHD_ZTHM1ActiveXCtrl - Destructor

CHD_ZTHM1ActiveXCtrl::~CHD_ZTHM1ActiveXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXCtrl::OnDraw - Drawing function

void CHD_ZTHM1ActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXCtrl::DoPropExchange - Persistence support

void CHD_ZTHM1ActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXCtrl::OnResetState - Reset control to default state

void CHD_ZTHM1ActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXCtrl::AboutBox - Display an "About" box to the user

void CHD_ZTHM1ActiveXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_HD_ZTHM1ACTIVEX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXCtrl message handlers

//DEL BSTR CHD_ZTHM1ActiveXCtrl::HDWriteM1(LPCTSTR Key, LPCTSTR DataIn, LPCTSTR Addr) 
//DEL {
//DEL 	CString strResult;
//DEL 	// TODO: Add your dispatch handler code here
//DEL 	char pErr[100]={0};
//DEL 	int iAddr=atoi(Addr);
//DEL 	int ret=HD_WriteM1((char *)Key,(char *)DataIn,iAddr,(char *)pErr);
//DEL 	if(ret!=0)
//DEL 	{
//DEL 		strResult.Format("<ERROR>%s</ERROR>",pErr);
//DEL 	}else
//DEL 	{
//DEL 		strResult.Format("<MSG>写数据成功!</MSG>");
//DEL 	}
//DEL 	return strResult.AllocSysString();
//DEL }

BSTR CHD_ZTHM1ActiveXCtrl::HDWriteM1(LPCTSTR Key, LPCTSTR Name, LPCTSTR Sex, LPCTSTR IDNo, LPCTSTR Born, LPCTSTR CardNo, LPCTSTR MakeCDT) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char pErr[100]={0};
	int ret=HD_WriteM1((char *)Key,(char *)Name,(char *)Sex,(char *)IDNo,(char *)Born,(char *)CardNo,(char *)MakeCDT,pErr);
	if(ret!=0)
	{
		strResult.Format("<ERROR>%s</ERROR>",pErr);
	}else
	{
		strResult.Format("<MSG>写数据成功!</MSG>");
	}
	return strResult.AllocSysString();
}

BSTR CHD_ZTHM1ActiveXCtrl::HDReadM1(LPCTSTR Key, LPCTSTR Addr) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char pErr[100]={0};
	char DataOut[100]={0};
	int ret=HD_ReadM1((char *)Key,(char *)Addr,DataOut,pErr);
	if(ret!=0)
	{
		strResult.Format("<ERROR>%s</ERROR>",pErr);
	}else
	{
		strResult.Format("<MSG>%s</MSG>",DataOut);
	}
	return strResult.AllocSysString();
}
