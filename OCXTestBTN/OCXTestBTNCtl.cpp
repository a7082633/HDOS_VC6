// OCXTestBTNCtl.cpp : Implementation of the COCXTestBTNCtrl ActiveX Control class.

#include "stdafx.h"
#include "OCXTestBTN.h"
#include "OCXTestBTNCtl.h"
#include "OCXTestBTNPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(COCXTestBTNCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(COCXTestBTNCtrl, COleControl)
	//{{AFX_MSG_MAP(COCXTestBTNCtrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(COCXTestBTNCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(COCXTestBTNCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(COCXTestBTNCtrl, COleControl)
	//{{AFX_EVENT_MAP(COCXTestBTNCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(COCXTestBTNCtrl, 1)
	PROPPAGEID(COCXTestBTNPropPage::guid)
END_PROPPAGEIDS(COCXTestBTNCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(COCXTestBTNCtrl, "OCXTESTBTN.OCXTestBTNCtrl.1",
	0x8ce65e8b, 0x5b7a, 0x4640, 0xa0, 0xac, 0xab, 0xa9, 0x32, 0x5d, 0x9f, 0x3)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(COCXTestBTNCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DOCXTestBTN =
		{ 0xab599221, 0x2ce4, 0x4ac3, { 0x82, 0x69, 0xf2, 0x2b, 0xcc, 0x8a, 0x59, 0xa3 } };
const IID BASED_CODE IID_DOCXTestBTNEvents =
		{ 0x1f959ce5, 0xf52c, 0x4250, { 0xad, 0x1a, 0x7d, 0xac, 0, 0x20, 0x87, 0x21 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwOCXTestBTNOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(COCXTestBTNCtrl, IDS_OCXTESTBTN, _dwOCXTestBTNOleMisc)


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl::COCXTestBTNCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for COCXTestBTNCtrl

BOOL COCXTestBTNCtrl::COCXTestBTNCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_OCXTESTBTN,
			IDB_OCXTESTBTN,
			afxRegApartmentThreading,
			_dwOCXTestBTNOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl::COCXTestBTNCtrl - Constructor

COCXTestBTNCtrl::COCXTestBTNCtrl()
{
	InitializeIIDs(&IID_DOCXTestBTN, &IID_DOCXTestBTNEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl::~COCXTestBTNCtrl - Destructor

COCXTestBTNCtrl::~COCXTestBTNCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl::OnDraw - Drawing function

void COCXTestBTNCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DoSuperclassPaint(pdc, rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl::DoPropExchange - Persistence support

void COCXTestBTNCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl::OnResetState - Reset control to default state

void COCXTestBTNCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL COCXTestBTNCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("BUTTON");
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl::IsSubclassedControl - This is a subclassed control

BOOL COCXTestBTNCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl::OnOcmCommand - Handle command messages

LRESULT COCXTestBTNCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNCtrl message handlers

void COCXTestBTNCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	::MessageBox(NULL,"HAHA",NULL,MB_OK);
	COleControl::OnLButtonDown(nFlags, point);
}
