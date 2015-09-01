// OCXTest2Ctl.cpp : Implementation of the COCXTest2Ctrl ActiveX Control class.

#include "stdafx.h"
#include "OCXTest2.h"
#include "OCXTest2Ctl.h"
#include "OCXTest2Ppg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(COCXTest2Ctrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(COCXTest2Ctrl, COleControl)
	//{{AFX_MSG_MAP(COCXTest2Ctrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(COCXTest2Ctrl, COleControl)
	//{{AFX_DISPATCH_MAP(COCXTest2Ctrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(COCXTest2Ctrl, COleControl)
	//{{AFX_EVENT_MAP(COCXTest2Ctrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(COCXTest2Ctrl, 1)
	PROPPAGEID(COCXTest2PropPage::guid)
END_PROPPAGEIDS(COCXTest2Ctrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(COCXTest2Ctrl, "OCXTEST2.OCXTest2Ctrl.1",
	0x1776a217, 0xfab8, 0x48bf, 0x94, 0x63, 0x5c, 0x86, 0x66, 0x5, 0x1d, 0x90)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(COCXTest2Ctrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DOCXTest2 =
		{ 0xc2e380bf, 0xad6a, 0x4004, { 0x9b, 0x39, 0xf6, 0xb9, 0xc0, 0x59, 0xc7, 0xb8 } };
const IID BASED_CODE IID_DOCXTest2Events =
		{ 0x2c108fc, 0x5ab0, 0x4c94, { 0xb5, 0x61, 0xf8, 0xd2, 0x7f, 0xe6, 0x2, 0xf } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwOCXTest2OleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(COCXTest2Ctrl, IDS_OCXTEST2, _dwOCXTest2OleMisc)


/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl::COCXTest2CtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for COCXTest2Ctrl

BOOL COCXTest2Ctrl::COCXTest2CtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_OCXTEST2,
			IDB_OCXTEST2,
			afxRegApartmentThreading,
			_dwOCXTest2OleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("OCXTest2.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 2015 ";


/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl::COCXTest2CtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL COCXTest2Ctrl::COCXTest2CtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl::COCXTest2CtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL COCXTest2Ctrl::COCXTest2CtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl::COCXTest2Ctrl - Constructor

COCXTest2Ctrl::COCXTest2Ctrl()
{
	InitializeIIDs(&IID_DOCXTest2, &IID_DOCXTest2Events);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl::~COCXTest2Ctrl - Destructor

COCXTest2Ctrl::~COCXTest2Ctrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl::OnDraw - Drawing function

void COCXTest2Ctrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl::DoPropExchange - Persistence support

void COCXTest2Ctrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl::OnResetState - Reset control to default state

void COCXTest2Ctrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2Ctrl message handlers

void COCXTest2Ctrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	::MessageBox(NULL,"fuck you ypyo check now !","OKOK",MB_OK);
	COleControl::OnLButtonDown(nFlags, point);
}
