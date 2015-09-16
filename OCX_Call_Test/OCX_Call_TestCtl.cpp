// OCX_Call_TestCtl.cpp : Implementation of the COCX_Call_TestCtrl ActiveX Control class.

#include "stdafx.h"
#include "OCX_Call_Test.h"
#include "OCX_Call_TestCtl.h"
#include "OCX_Call_TestPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(COCX_Call_TestCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(COCX_Call_TestCtrl, COleControl)
	//{{AFX_MSG_MAP(COCX_Call_TestCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(COCX_Call_TestCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(COCX_Call_TestCtrl)
	DISP_FUNCTION(COCX_Call_TestCtrl, "ReadSam", ReadSam, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(COCX_Call_TestCtrl, "ReadID", ReadID, VT_BSTR, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(COCX_Call_TestCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(COCX_Call_TestCtrl, COleControl)
	//{{AFX_EVENT_MAP(COCX_Call_TestCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(COCX_Call_TestCtrl, 1)
	PROPPAGEID(COCX_Call_TestPropPage::guid)
END_PROPPAGEIDS(COCX_Call_TestCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(COCX_Call_TestCtrl, "OCXCALLTEST.OCXCallTestCtrl.1",
	0xfb81f047, 0xbe05, 0x404c, 0x80, 0xe4, 0xe, 0x84, 0x3b, 0xde, 0x56, 0xfa)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(COCX_Call_TestCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DOCX_Call_Test =
		{ 0x3a80ba51, 0x3dc9, 0x454d, { 0xa3, 0x65, 0xdb, 0x6c, 0x9, 0xb7, 0xfa, 0xa6 } };
const IID BASED_CODE IID_DOCX_Call_TestEvents =
		{ 0xb1166dec, 0x3dbc, 0x4f4e, { 0xbc, 0x61, 0x7c, 0x3f, 0x20, 0x44, 0xf1, 0xe0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwOCX_Call_TestOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(COCX_Call_TestCtrl, IDS_OCX_CALL_TEST, _dwOCX_Call_TestOleMisc)


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestCtrl::COCX_Call_TestCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for COCX_Call_TestCtrl

BOOL COCX_Call_TestCtrl::COCX_Call_TestCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_OCX_CALL_TEST,
			IDB_OCX_CALL_TEST,
			afxRegApartmentThreading,
			_dwOCX_Call_TestOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestCtrl::COCX_Call_TestCtrl - Constructor

COCX_Call_TestCtrl::COCX_Call_TestCtrl()
{
	InitializeIIDs(&IID_DOCX_Call_Test, &IID_DOCX_Call_TestEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestCtrl::~COCX_Call_TestCtrl - Destructor

COCX_Call_TestCtrl::~COCX_Call_TestCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestCtrl::OnDraw - Drawing function

void COCX_Call_TestCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestCtrl::DoPropExchange - Persistence support

void COCX_Call_TestCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestCtrl::OnResetState - Reset control to default state

void COCX_Call_TestCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestCtrl::AboutBox - Display an "About" box to the user

void COCX_Call_TestCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_OCX_CALL_TEST);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestCtrl message handlers

BSTR COCX_Call_TestCtrl::ReadSam() 
{
	CString strResult;
//	//::MessageBox(NULL,"开始",NULL,MB_OK);
//	// TODO: Add your dispatch handler code here
//	int i=iDOpenPort();
//	//::MessageBox(NULL,"打开端口成功",NULL,MB_OK);
//	int hDev=0;
//	char info[5000]={0};
//	i=iReader_SAM_Public(hDev,info);
//	//::MessageBox(NULL,"读成功",NULL,MB_OK);
//	i=iDClosePort();
//	//::MessageBox(NULL,"关端口成功",NULL,MB_OK);
//	strResult.Format("%s",info);
//	//::MessageBox(NULL,info,NULL,MB_OK);
	return strResult.AllocSysString();
}

BSTR COCX_Call_TestCtrl::ReadID() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	int i=HD_InitComm(1001); //连接设备
	if(i)
	{
		strResult.Format("打开设备失败:%d",i);
		return strResult.AllocSysString();
	}
	i=HD_Authenticate();
	if(i)
	{
		strResult.Format("验证失败:%d",i);
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
	i=HD_Read_BaseMsg(NULL,name,sex,nation, born,address,cardNo,issuedat,effectedDate,expiredDate);
	if(i)
	{
		strResult.Format("读信息:%d",i);
		return strResult.AllocSysString();
	}
	strResult.Format("%s|%s|%s|%s|%s|%s|%s|%s|%s",name,sex,nation, born,address,cardNo,issuedat,effectedDate,expiredDate);
	HD_CloseComm(1001);
	return strResult.AllocSysString();
}
