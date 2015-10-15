// HD_CPUAndIDCtl.cpp : Implementation of the CHD_CPUAndIDCtrl ActiveX Control class.

#include "stdafx.h"
#include "HD_CPUAndID.h"
#include "HD_CPUAndIDCtl.h"
#include "HD_CPUAndIDPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_CPUAndIDCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_CPUAndIDCtrl, COleControl)
	//{{AFX_MSG_MAP(CHD_CPUAndIDCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CHD_CPUAndIDCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CHD_CPUAndIDCtrl)
	DISP_FUNCTION(CHD_CPUAndIDCtrl, "ReaderOpen", ReaderOpen, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CHD_CPUAndIDCtrl, "ReaderClose", ReaderClose, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CHD_CPUAndIDCtrl, "ICCPowerOn", ICCPowerOn, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CHD_CPUAndIDCtrl, "ICCPowerOff", ICCPowerOff, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CHD_CPUAndIDCtrl, "ICCReaderApplicationHEX", ICCReaderApplicationHEX, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CHD_CPUAndIDCtrl, "ReadIDCard", ReadIDCard, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CHD_CPUAndIDCtrl, "GetInputPass", GetInputPass, VT_BSTR, VTS_I4)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CHD_CPUAndIDCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CHD_CPUAndIDCtrl, COleControl)
	//{{AFX_EVENT_MAP(CHD_CPUAndIDCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CHD_CPUAndIDCtrl, 1)
	PROPPAGEID(CHD_CPUAndIDPropPage::guid)
END_PROPPAGEIDS(CHD_CPUAndIDCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_CPUAndIDCtrl, "HDCPUANDID.HDCPUAndIDCtrl.1",
	0xa2224632, 0xaac9, 0x4715, 0x84, 0x76, 0xe3, 0x37, 0xf8, 0xc6, 0xe8, 0xaf)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CHD_CPUAndIDCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DHD_CPUAndID =
		{ 0x34ec79ff, 0xd75c, 0x4eaf, { 0xbb, 0xb4, 0x6b, 0x49, 0x93, 0xf8, 0x7, 0x82 } };
const IID BASED_CODE IID_DHD_CPUAndIDEvents =
		{ 0xe69f0c36, 0x3cfa, 0x448b, { 0x97, 0xa, 0x63, 0xc0, 0xd4, 0x4c, 0x5, 0x84 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwHD_CPUAndIDOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CHD_CPUAndIDCtrl, IDS_HD_CPUANDID, _dwHD_CPUAndIDOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDCtrl::CHD_CPUAndIDCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_CPUAndIDCtrl

BOOL CHD_CPUAndIDCtrl::CHD_CPUAndIDCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_HD_CPUANDID,
			IDB_HD_CPUANDID,
			afxRegApartmentThreading,
			_dwHD_CPUAndIDOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDCtrl::CHD_CPUAndIDCtrl - Constructor

CHD_CPUAndIDCtrl::CHD_CPUAndIDCtrl()
{
	InitializeIIDs(&IID_DHD_CPUAndID, &IID_DHD_CPUAndIDEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDCtrl::~CHD_CPUAndIDCtrl - Destructor

CHD_CPUAndIDCtrl::~CHD_CPUAndIDCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDCtrl::OnDraw - Drawing function

void CHD_CPUAndIDCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDCtrl::DoPropExchange - Persistence support

void CHD_CPUAndIDCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDCtrl::OnResetState - Reset control to default state

void CHD_CPUAndIDCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDCtrl::AboutBox - Display an "About" box to the user

void CHD_CPUAndIDCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_HD_CPUANDID);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDCtrl message handlers

BSTR CHD_CPUAndIDCtrl::ReaderOpen() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	ReaderHandle=ICC_Reader_Open("USB1");
	if(ReaderHandle>0)
		strResult="打开端口成功";
	else
		strResult.Format("打开端口失败,错误代码%d",strResult);
	return strResult.AllocSysString();
}

void CHD_CPUAndIDCtrl::ReaderClose() 
{
	ICC_Reader_Close(ReaderHandle);
}

BSTR CHD_CPUAndIDCtrl::ICCPowerOn() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	unsigned  char  Response[100]={0};
	int i=ICC_Reader_PowerOnHEX(ReaderHandle,0x01,Response);
	if(i>=0)
		strResult.Format("%s",Response);
	else
		strResult.Format("上电失败,错误代码%d",i);
	return strResult.AllocSysString();
}

BSTR CHD_CPUAndIDCtrl::ICCPowerOff() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	ICC_Reader_PowerOff(ReaderHandle,0x01);
	strResult="下电成功!";
	return strResult.AllocSysString();
}

BSTR CHD_CPUAndIDCtrl::ICCReaderApplicationHEX(LPCTSTR Command_APDU) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	unsigned  char  Response_APDU[200]={0};
	int i=ICC_Reader_ApplicationHEX(ReaderHandle,0x01,(char *)Command_APDU,(char *)Response_APDU);
	if(i>0)
		strResult.Format("%s",Response_APDU);
	else
		strResult.Format("指令执行失败,错误代码%d",i);
	return strResult.AllocSysString();
}


BSTR CHD_CPUAndIDCtrl::ReadIDCard(LPCTSTR PicPath) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	int i=PICC_Reader_ID_Request(ReaderHandle);//身份证寻卡
	if(i!=0)
	{
		strResult.Format("身份证寻卡失败,错误代码%d",i);
		return strResult.AllocSysString();
	}
	i=PICC_Reader_ID_Select(ReaderHandle);//身份证选卡
	if(i!=0)
	{
		strResult.Format("身份证选卡失败,错误代码%d",i);
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
	char pErrMsg[200]={0};
	i=PICC_Reader_ReadIDMsg(ReaderHandle,PicPath,name,sex,nation,born,address,cardNo,issuedat,effectedDate,expiredDate,pErrMsg);
	if(i!=0)
	{
		strResult.Format("读身份证失败(%s),错误代码%d",pErrMsg,i);
		return strResult.AllocSysString();
	}
	strResult.Format("%s|%s|%s|%s|%s|%s|%s|%s|%s",name,sex,nation,born,address,cardNo,issuedat,effectedDate,expiredDate);
	return strResult.AllocSysString();
}

BSTR CHD_CPUAndIDCtrl::GetInputPass(long ctime) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	unsigned char rlen;
	unsigned char cpass[100]={0};
	int i=ICC_GetInputPass(ReaderHandle,ctime,&rlen,0,1,cpass);
	if(i!=0)
	{
		strResult.Format("获取密码失败,错误代码%d",i);
		return strResult.AllocSysString();
	}
	strResult.Format("%s",cpass);
	return strResult.AllocSysString();
}
