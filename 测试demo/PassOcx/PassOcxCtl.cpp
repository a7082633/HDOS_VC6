// PassOcxCtl.cpp : Implementation of the CPassOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "PassOcx.h"
#include "PassOcxCtl.h"
#include "PassOcxPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPassOcxCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPassOcxCtrl, COleControl)
	//{{AFX_MSG_MAP(CPassOcxCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CPassOcxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CPassOcxCtrl)
	DISP_FUNCTION(CPassOcxCtrl, "GetInputPass", GetInputPass, VT_BSTR, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CPassOcxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CPassOcxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CPassOcxCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CPassOcxCtrl, 1)
	PROPPAGEID(CPassOcxPropPage::guid)
END_PROPPAGEIDS(CPassOcxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPassOcxCtrl, "PASSOCX.PassOcxCtrl.1",
	0x9bcccb83, 0xd575, 0x4782, 0x93, 0x95, 0xec, 0x7c, 0xa2, 0x9a, 0xa9, 0x1a)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CPassOcxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DPassOcx =
		{ 0x4920eb5b, 0x4456, 0x4bd6, { 0xaf, 0x6, 0x9a, 0xee, 0x67, 0x34, 0xef, 0xd1 } };
const IID BASED_CODE IID_DPassOcxEvents =
		{ 0x862c0f89, 0x27f2, 0x48ea, { 0xb8, 0x20, 0x78, 0xcc, 0x47, 0xf7, 0, 0x51 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwPassOcxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CPassOcxCtrl, IDS_PASSOCX, _dwPassOcxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CPassOcxCtrl::CPassOcxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CPassOcxCtrl

BOOL CPassOcxCtrl::CPassOcxCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_PASSOCX,
			IDB_PASSOCX,
			afxRegApartmentThreading,
			_dwPassOcxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxCtrl::CPassOcxCtrl - Constructor

CPassOcxCtrl::CPassOcxCtrl()
{
	InitializeIIDs(&IID_DPassOcx, &IID_DPassOcxEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxCtrl::~CPassOcxCtrl - Destructor

CPassOcxCtrl::~CPassOcxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxCtrl::OnDraw - Drawing function

void CPassOcxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxCtrl::DoPropExchange - Persistence support

void CPassOcxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxCtrl::OnResetState - Reset control to default state

void CPassOcxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxCtrl::AboutBox - Display an "About" box to the user

void CPassOcxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_PASSOCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxCtrl message handlers

BSTR CPassOcxCtrl::GetInputPass() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	long ReaderHandle=ICC_Reader_Open("USB1");
	if(ReaderHandle<=0)
	{
		strResult="打开端口失败!";
		return strResult.AllocSysString();
	}
	unsigned char rlen=0;
	unsigned char cpass[100]={0};
	ICC_DispSound(ReaderHandle,4,0);
	::Sleep(1000);
	int rt=ICC_GetInputPass(ReaderHandle,20,&rlen,0,1,cpass);
	if(rt)
	{
		strResult="获取密码失败!";
		return strResult.AllocSysString();
	}
	strResult=cpass;
	ICC_Reader_Close(ReaderHandle);
	return strResult.AllocSysString();
}
