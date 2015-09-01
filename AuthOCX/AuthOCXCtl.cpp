// AuthOCXCtl.cpp : Implementation of the CAuthOCXCtrl ActiveX Control class.

#include "stdafx.h"
#include "AuthOCX.h"
#include "AuthOCXCtl.h"
#include "AuthOCXPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CAuthOCXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CAuthOCXCtrl, COleControl)
	//{{AFX_MSG_MAP(CAuthOCXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CAuthOCXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CAuthOCXCtrl)
	DISP_FUNCTION(CAuthOCXCtrl, "TestAu", TestAu, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_I2)
	DISP_FUNCTION(CAuthOCXCtrl, "TestAu2", TestAu2, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CAuthOCXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CAuthOCXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CAuthOCXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CAuthOCXCtrl, 1)
	PROPPAGEID(CAuthOCXPropPage::guid)
END_PROPPAGEIDS(CAuthOCXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CAuthOCXCtrl, "AUTHOCX.AuthOCXCtrl.1",
	0x13821e15, 0xd909, 0x42d1, 0x89, 0xcd, 0x73, 0x63, 0x3b, 0xa7, 0x33, 0xfc)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CAuthOCXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DAuthOCX =
		{ 0xa611c2b3, 0x45a9, 0x454e, { 0xad, 0xc3, 0xde, 0x4c, 0x9c, 0x88, 0xa, 0x48 } };
const IID BASED_CODE IID_DAuthOCXEvents =
		{ 0x7b28a277, 0x8da2, 0x4313, { 0x87, 0xbc, 0x6f, 0xab, 0x9c, 0xdf, 0xeb, 0x2a } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwAuthOCXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CAuthOCXCtrl, IDS_AUTHOCX, _dwAuthOCXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXCtrl::CAuthOCXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CAuthOCXCtrl

BOOL CAuthOCXCtrl::CAuthOCXCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_AUTHOCX,
			IDB_AUTHOCX,
			afxRegApartmentThreading,
			_dwAuthOCXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXCtrl::CAuthOCXCtrl - Constructor

CAuthOCXCtrl::CAuthOCXCtrl()
{
	InitializeIIDs(&IID_DAuthOCX, &IID_DAuthOCXEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXCtrl::~CAuthOCXCtrl - Destructor

CAuthOCXCtrl::~CAuthOCXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXCtrl::OnDraw - Drawing function

void CAuthOCXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXCtrl::DoPropExchange - Persistence support

void CAuthOCXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXCtrl::OnResetState - Reset control to default state

void CAuthOCXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXCtrl::AboutBox - Display an "About" box to the user

void CAuthOCXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_AUTHOCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXCtrl message handlers

BSTR CAuthOCXCtrl::TestAu(LPCTSTR addr, LPCTSTR account, LPCTSTR password, short doctype, short action) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	char *s=Authentication((char *)addr,(char *)account,(char *)password,doctype,action);
	Test1((char *)addr);
	Test2(doctype);
	return strResult.AllocSysString();
}
void test(char *addr,int a)
{

}
BSTR CAuthOCXCtrl::TestAu2(LPCTSTR addr, LPCTSTR account, LPCTSTR password) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	//test((char *)addr,doctype);
//	BSTR s=Authentication((char *)addr,(char *)account,(char *)password
//		,1,1);

	return strResult.AllocSysString();
}
