// HD_ZTHReadM1ActiveXCtl.cpp : Implementation of the CHD_ZTHReadM1ActiveXCtrl ActiveX Control class.

#include "stdafx.h"
#include "HD_ZTHReadM1ActiveX.h"
#include "HD_ZTHReadM1ActiveXCtl.h"
#include "HD_ZTHReadM1ActiveXPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_ZTHReadM1ActiveXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_ZTHReadM1ActiveXCtrl, COleControl)
	//{{AFX_MSG_MAP(CHD_ZTHReadM1ActiveXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CHD_ZTHReadM1ActiveXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CHD_ZTHReadM1ActiveXCtrl)
	DISP_FUNCTION(CHD_ZTHReadM1ActiveXCtrl, "HDReadM1", HDReadM1, VT_BSTR, VTS_BSTR VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CHD_ZTHReadM1ActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CHD_ZTHReadM1ActiveXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CHD_ZTHReadM1ActiveXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CHD_ZTHReadM1ActiveXCtrl, 1)
	PROPPAGEID(CHD_ZTHReadM1ActiveXPropPage::guid)
END_PROPPAGEIDS(CHD_ZTHReadM1ActiveXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_ZTHReadM1ActiveXCtrl, "HDZTHREADM1ACTIVEX.HDZTHReadM1ActiveXCtrl.1",
	0x22a9d2e4, 0xc4a, 0x4590, 0x85, 0xc5, 0x5b, 0xe4, 0x63, 0x49, 0x78, 0xc3)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CHD_ZTHReadM1ActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DHD_ZTHReadM1ActiveX =
		{ 0x648c0b83, 0xcc34, 0x49ad, { 0xa1, 0x6f, 0x2f, 0x27, 0xa7, 0xa1, 0xf4, 0x37 } };
const IID BASED_CODE IID_DHD_ZTHReadM1ActiveXEvents =
		{ 0x46e5769d, 0x3feb, 0x4d7f, { 0xad, 0x6d, 0x7c, 0x26, 0x30, 0x6f, 0x2f, 0x21 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwHD_ZTHReadM1ActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CHD_ZTHReadM1ActiveXCtrl, IDS_HD_ZTHREADM1ACTIVEX, _dwHD_ZTHReadM1ActiveXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXCtrl::CHD_ZTHReadM1ActiveXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_ZTHReadM1ActiveXCtrl

BOOL CHD_ZTHReadM1ActiveXCtrl::CHD_ZTHReadM1ActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_HD_ZTHREADM1ACTIVEX,
			IDB_HD_ZTHREADM1ACTIVEX,
			afxRegApartmentThreading,
			_dwHD_ZTHReadM1ActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXCtrl::CHD_ZTHReadM1ActiveXCtrl - Constructor

CHD_ZTHReadM1ActiveXCtrl::CHD_ZTHReadM1ActiveXCtrl()
{
	InitializeIIDs(&IID_DHD_ZTHReadM1ActiveX, &IID_DHD_ZTHReadM1ActiveXEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXCtrl::~CHD_ZTHReadM1ActiveXCtrl - Destructor

CHD_ZTHReadM1ActiveXCtrl::~CHD_ZTHReadM1ActiveXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXCtrl::OnDraw - Drawing function

void CHD_ZTHReadM1ActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXCtrl::DoPropExchange - Persistence support

void CHD_ZTHReadM1ActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXCtrl::OnResetState - Reset control to default state

void CHD_ZTHReadM1ActiveXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXCtrl::AboutBox - Display an "About" box to the user

void CHD_ZTHReadM1ActiveXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_HD_ZTHREADM1ACTIVEX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXCtrl message handlers

BSTR CHD_ZTHReadM1ActiveXCtrl::HDReadM1(LPCTSTR Key, LPCTSTR Addr) 
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
