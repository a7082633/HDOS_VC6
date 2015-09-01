// HD_XJOCXCtl.cpp : Implementation of the CHD_XJOCXCtrl ActiveX Control class.

#include "stdafx.h"
#include "HD_XJOCX.h"
#include "HD_XJOCXCtl.h"
#include "HD_XJOCXPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_XJOCXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_XJOCXCtrl, COleControl)
	//{{AFX_MSG_MAP(CHD_XJOCXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CHD_XJOCXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CHD_XJOCXCtrl)
	DISP_FUNCTION(CHD_XJOCXCtrl, "HDGetCardNo", HDGetCardNo, VT_BSTR, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CHD_XJOCXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CHD_XJOCXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CHD_XJOCXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CHD_XJOCXCtrl, 1)
	PROPPAGEID(CHD_XJOCXPropPage::guid)
END_PROPPAGEIDS(CHD_XJOCXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_XJOCXCtrl, "HDXJOCX.HDXJOCXCtrl.1",
	0x27300181, 0xd5bc, 0x4df7, 0xb9, 0xfc, 0x8e, 0xce, 0xf0, 0xff, 0x55, 0x68)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CHD_XJOCXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DHD_XJOCX =
		{ 0x727a9c62, 0xb12f, 0x478b, { 0x82, 0x22, 0x9b, 0x52, 0xa4, 0x7f, 0x27, 0x82 } };
const IID BASED_CODE IID_DHD_XJOCXEvents =
		{ 0xca6b5901, 0xa3b3, 0x42b9, { 0xb5, 0xfe, 0x5d, 0x80, 0x81, 0x5, 0xef, 0x48 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwHD_XJOCXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CHD_XJOCXCtrl, IDS_HD_XJOCX, _dwHD_XJOCXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXCtrl::CHD_XJOCXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_XJOCXCtrl

BOOL CHD_XJOCXCtrl::CHD_XJOCXCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_HD_XJOCX,
			IDB_HD_XJOCX,
			afxRegApartmentThreading,
			_dwHD_XJOCXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXCtrl::CHD_XJOCXCtrl - Constructor

CHD_XJOCXCtrl::CHD_XJOCXCtrl()
{
	InitializeIIDs(&IID_DHD_XJOCX, &IID_DHD_XJOCXEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXCtrl::~CHD_XJOCXCtrl - Destructor

CHD_XJOCXCtrl::~CHD_XJOCXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXCtrl::OnDraw - Drawing function

void CHD_XJOCXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXCtrl::DoPropExchange - Persistence support

void CHD_XJOCXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXCtrl::OnResetState - Reset control to default state

void CHD_XJOCXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXCtrl::AboutBox - Display an "About" box to the user

void CHD_XJOCXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_HD_XJOCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXCtrl message handlers

BSTR CHD_XJOCXCtrl::HDGetCardNo() 
{
	CString strResult;
	BSTR    BResult;
	long hReader=ICC_Reader_Open("USB1");
	if(hReader<=0)//设备打开失败返回
	{
		strResult="打开设备失败";
		BResult=strResult.AllocSysString();
		return BResult;
	}
	//上电
	unsigned char Response[50]={0};
	int rt=ICC_Reader_PowerOn(hReader,0x01,Response);
	if(rt<=0)
	{
		strResult.Format("卡上电失败,代码:%d",rt);
		BResult=strResult.AllocSysString();
		return BResult;
	}
	//发送选SSSE指令
	unsigned char cmd[100]=
		{0x00,0xA4,0x04,0x00,0x0F,
		0x73,0x78,0x31,0x2E,0x73,
		0x68,0x2E,0xC9,0xE7,0xBB,
		0xE1,0xB1,0xA3,0xD5,0xCF};
	unsigned char ResponseAPDU[200]={0};
    int len=ICC_Reader_Application(hReader,0x01,20,cmd,ResponseAPDU);
	if(len<=0)
	{
		strResult.Format("执行指令失败,代码:%d",len);
		BResult=strResult.AllocSysString();
		return BResult;
	}
	if( (ResponseAPDU[len-2]!=0x61) && (ResponseAPDU[len-2]!=0x90) )
	{
		strResult.Format("其他卡型-00A4");
		BResult=strResult.AllocSysString();
		return BResult;
	}
	//读卡面号
	memset(cmd,0,100);
	memset(ResponseAPDU,0,200);
	memcpy(cmd, "\x00\xB2\x07\x2C\x0B",5);
	len = ICC_Reader_Application(hReader,0x01,5,cmd,ResponseAPDU);
	if(len<=0 || ResponseAPDU[len-2]!=0x90)
	{
		strResult.Format("其他卡型-00B2072C00");
		BResult=strResult.AllocSysString();
		return BResult;
	}
	char UserNo[0x0a]={0};
	memcpy(UserNo,ResponseAPDU+2,0x09);//获个人编号
	strResult.Format("%s",UserNo);
	BResult=strResult.AllocSysString();
	return BResult;
}
