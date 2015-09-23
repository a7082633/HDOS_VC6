// TestOcxCtl.cpp : Implementation of the CTestOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "TestOcx.h"
#include "TestOcxCtl.h"
#include "TestOcxPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CTestOcxCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CTestOcxCtrl, COleControl)
	//{{AFX_MSG_MAP(CTestOcxCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CTestOcxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CTestOcxCtrl)
	DISP_FUNCTION(CTestOcxCtrl, "ReadID", ReadID, VT_BSTR, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CTestOcxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CTestOcxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CTestOcxCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CTestOcxCtrl, 1)
	PROPPAGEID(CTestOcxPropPage::guid)
END_PROPPAGEIDS(CTestOcxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CTestOcxCtrl, "TESTOCX.TestOcxCtrl.1",
	0xcff42020, 0x7ad5, 0x4851, 0xa6, 0x93, 0xdd, 0xb2, 0x81, 0x2e, 0xf0, 0xea)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CTestOcxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DTestOcx =
		{ 0x4e5a68fa, 0xc36b, 0x4802, { 0x9f, 0x3b, 0x22, 0xb3, 0x92, 0x5b, 0x73, 0xc4 } };
const IID BASED_CODE IID_DTestOcxEvents =
		{ 0x7e831e4e, 0x6ded, 0x41cd, { 0xb6, 0xb0, 0x40, 0x5, 0x79, 0x87, 0x57, 0xa5 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwTestOcxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CTestOcxCtrl, IDS_TESTOCX, _dwTestOcxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CTestOcxCtrl::CTestOcxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CTestOcxCtrl

BOOL CTestOcxCtrl::CTestOcxCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_TESTOCX,
			IDB_TESTOCX,
			afxRegApartmentThreading,
			_dwTestOcxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxCtrl::CTestOcxCtrl - Constructor

CTestOcxCtrl::CTestOcxCtrl()
{
	InitializeIIDs(&IID_DTestOcx, &IID_DTestOcxEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxCtrl::~CTestOcxCtrl - Destructor

CTestOcxCtrl::~CTestOcxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxCtrl::OnDraw - Drawing function

void CTestOcxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxCtrl::DoPropExchange - Persistence support

void CTestOcxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxCtrl::OnResetState - Reset control to default state

void CTestOcxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxCtrl::AboutBox - Display an "About" box to the user

void CTestOcxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_TESTOCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxCtrl message handlers

BSTR CTestOcxCtrl::ReadID() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	int i=HD_InitComm(1001); //连接设备
	if(i)
	{
		strResult.Format("连接设备失败,错误代码:%d",i);
		return strResult.AllocSysString();
	}
	i=HD_Authenticate();
	if(i)
	{
		strResult.Format("验证身份证失败,错误代码:%d",i);
		HD_CloseComm(1001); //关闭设备
		return strResult.AllocSysString();
	}
	char name[200]={0};
	char sex[200]={0};
	char nation[200]={0};
	char born[200]={0};
	char address[400]={0};
	char cardNo[400]={0};
	char issuedat[200]={0};
	char effectedDate[200]={0};
	char expiredDate[200]={0};
	i=HD_Read_BaseMsg("d:\\zp.jpg",name,sex,nation,born,address,cardNo,issuedat,effectedDate,expiredDate);
	if(i)
	{
		strResult.Format("读身份证失败,错误代码:%d",i);
		HD_CloseComm(1001); //关闭设备
		return strResult.AllocSysString();
	}
	HD_CloseComm(1001); //关闭设备
	strResult.Format("%s|%s|%s|%s|%s|%s|%s|%s|%s",name,sex,nation,born,address,cardNo,issuedat,effectedDate,expiredDate);
	return strResult.AllocSysString();
}
