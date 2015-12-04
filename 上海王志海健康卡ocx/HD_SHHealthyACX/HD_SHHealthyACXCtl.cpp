// HD_SHHealthyACXCtl.cpp : Implementation of the CHD_SHHealthyACXCtrl ActiveX Control class.

#include "stdafx.h"
#include "HD_SHHealthyACX.h"
#include "HD_SHHealthyACXCtl.h"
#include "HD_SHHealthyACXPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_SHHealthyACXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_SHHealthyACXCtrl, COleControl)
	//{{AFX_MSG_MAP(CHD_SHHealthyACXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CHD_SHHealthyACXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CHD_SHHealthyACXCtrl)
	DISP_FUNCTION(CHD_SHHealthyACXCtrl, "ReadCard", ReadCard, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CHD_SHHealthyACXCtrl, "ReadInfoOutPatient", ReadInfoOutPatient, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CHD_SHHealthyACXCtrl, "ReadInfoHospitalization", ReadInfoHospitalization, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CHD_SHHealthyACXCtrl, "WriteInfoOutPatient", WriteInfoOutPatient, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CHD_SHHealthyACXCtrl, "WriteInfoHospitalization", WriteInfoHospitalization, VT_BSTR, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CHD_SHHealthyACXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CHD_SHHealthyACXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CHD_SHHealthyACXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CHD_SHHealthyACXCtrl, 1)
	PROPPAGEID(CHD_SHHealthyACXPropPage::guid)
END_PROPPAGEIDS(CHD_SHHealthyACXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_SHHealthyACXCtrl, "HDSHHEALTHYACX.HDSHHealthyACXCtrl.1",
	0xd4c825db, 0x2abf, 0x4dcc, 0xb4, 0x4c, 0xbb, 0x66, 0xda, 0x69, 0xfb, 0x3)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CHD_SHHealthyACXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DHD_SHHealthyACX =
		{ 0x9abc16fa, 0xf7bc, 0x47c0, { 0xb0, 0x3a, 0xe8, 0x29, 0x18, 0xe2, 0xdb, 0x76 } };
const IID BASED_CODE IID_DHD_SHHealthyACXEvents =
		{ 0x51ddead8, 0x68c1, 0x48fa, { 0x94, 0x94, 0xed, 0xa5, 0x1, 0xd7, 0x88, 0xd3 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwHD_SHHealthyACXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CHD_SHHealthyACXCtrl, IDS_HD_SHHEALTHYACX, _dwHD_SHHealthyACXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXCtrl::CHD_SHHealthyACXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_SHHealthyACXCtrl

BOOL CHD_SHHealthyACXCtrl::CHD_SHHealthyACXCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_HD_SHHEALTHYACX,
			IDB_HD_SHHEALTHYACX,
			afxRegApartmentThreading,
			_dwHD_SHHealthyACXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXCtrl::CHD_SHHealthyACXCtrl - Constructor

CHD_SHHealthyACXCtrl::CHD_SHHealthyACXCtrl()
{
	InitializeIIDs(&IID_DHD_SHHealthyACX, &IID_DHD_SHHealthyACXEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXCtrl::~CHD_SHHealthyACXCtrl - Destructor

CHD_SHHealthyACXCtrl::~CHD_SHHealthyACXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXCtrl::OnDraw - Drawing function

void CHD_SHHealthyACXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXCtrl::DoPropExchange - Persistence support

void CHD_SHHealthyACXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXCtrl::OnResetState - Reset control to default state

void CHD_SHHealthyACXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXCtrl::AboutBox - Display an "About" box to the user

void CHD_SHHealthyACXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_HD_SHHEALTHYACX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXCtrl message handlers
char Encode_GetChar(BYTE num)
{
    return 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "+/="[num];
}
//编码
size_t Base64_Encode(char *pDest, const char *pSrc, size_t srclen)
{
    BYTE input[3], output[4];
    size_t i, index_src = 0, index_dest = 0;
    for(i = 0; i < srclen; i += 3)
    {
        //char [0]
        input[0] = pSrc[index_src++];
        output[0] = (BYTE)(input[0] >> 2);
        pDest[index_dest++] = Encode_GetChar(output[0]);

        //char [1]
        if(index_src < srclen)
        {
            input[1] = pSrc[index_src++];
            output[1] = (BYTE)(((input[0] & 0x03) << 4) + (input[1] >> 4));
            pDest[index_dest++] = Encode_GetChar(output[1]);
        }
        else
        {
            output[1] = (BYTE)((input[0] & 0x03) << 4);
            pDest[index_dest++] = Encode_GetChar(output[1]);
            pDest[index_dest++] = '=';
            pDest[index_dest++] = '=';
            break;
        }
        
        //char [2]
        if(index_src < srclen)
        {
            input[2] = pSrc[index_src++];
            output[2] = (BYTE)(((input[1] & 0x0f) << 2) + (input[2] >> 6));
            pDest[index_dest++] = Encode_GetChar(output[2]);
        }
        else
        {
            output[2] = (BYTE)((input[1] & 0x0f) << 2);
            pDest[index_dest++] = Encode_GetChar(output[2]);
            pDest[index_dest++] = '=';
            break;
        }

        //char [3]
        output[3] = (BYTE)(input[2] & 0x3f);
        pDest[index_dest++] = Encode_GetChar(output[3]);
    }
    //null-terminator
    pDest[index_dest] = 0;
    return index_dest;
}
BSTR CHD_SHHealthyACXCtrl::ReadCard() 
{
	CString strResult,temp;
	// TODO: Add your dispatch handler code here
	HANDLE hDev=NULL;
	int rt=iDOpenPort();
	if(rt!=0)
	{
		strResult.Format("<ERROR>打开端口失败,错误代码%d</ERROR>",rt);
		return strResult.AllocSysString();
	}
	char ATR[50]={0};
	rt=PowerOn(hDev,0x11,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>PSAM卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=PowerOn(hDev,0x01,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>用户卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=iVerifyPIN(hDev,"123456");
	if(rt!=0)
	{
		strResult.Format("<ERROR>校验PSAM卡PIN失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	//读持卡人基本信息
	char XM[50]={0};             //姓名
	char XB[50]={0};               //性别代码
	char MZ[50]={0};               //民族代码
	char CSRQ[50]={0};             //出生日期，YYYYMMDD格式
	char SFZH[50]={0};            //居民身份证号
	rt=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读持卡人基本信息失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	//读照片信息
	unsigned char picData[3075]={0};
	char picDataBase64[6000]={0};
	rt=iR_DDF1EF07Info(hDev,picData);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读照片信息失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	char piclen[10]={0};
	sprintf(piclen,"%02x%02x",picData[0],picData[1]);
	long len=strtol(piclen,NULL,16);
	Base64_Encode(picDataBase64,(const char *)picData+2,len);
	//读持卡人支付信息
	char KYXQ[21]={0};			//卡有效期
	char BRDH1[21]={0};         //本人电话1
	char BRDH2[21]={0};           //本人电话2
	char YLFYZFFS1[21]={0};		  //医疗费用支付方式1
	char YLFYZFFS2[21]={0};		  //医疗费用支付方式2
	char YLFYZFFS3[21]={0};		  //医疗费用支付方式3
	rt=iR_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读持卡人支付信息失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	//读地址信息
	char DZLB1[21]={0};		
	char DZ1[120]={0};       
	char DZLB2[21]={0};     
	char DZ2[120]={0};		  
	rt=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读地址信息失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	//读联系人信息
	char LXRXM1[40]={0};		
	char LXRGX1[2]={0};       
	char LXRDH1[30]={0};
	char LXRXM2[40]={0};		
	char LXRGX2[2]={0};       
	char LXRDH2[30]={0}; 
	char LXRXM3[40]={0};		
	char LXRGX3[2]={0};       
	char LXRDH3[30]={0}; 
	rt=iR_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读联系人信息失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	//读职业婚姻信息
	char WHCD[10]={0};		
	char HYZK[10]={0};       
	char ZY[10]={0};
	rt=iR_DF01EF07Info(hDev,WHCD,HYZK,ZY);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读职业婚姻信息失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	//读证件信息
	char ZJLB[20]={0};		
	char ZJHM[20]={0};       
	char JKDAH[20]={0};
	char XNHZH[20]={0};
	rt=iR_DF01EF08Info(hDev,ZJLB,ZJHM,JKDAH,XNHZH);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读证件信息失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	strResult.Format("<DDF1EF06><XM>%s</XM><XB>%s</XB><MZ>%s</MZ><CSRQ>%s</CSRQ><JMSFZHM>%s</JMSFZHM></DDF1EF06>\r\n<DDF1EF07><ZPSJ>%s</ZPSJ></DDF1EF07>\r\n<DDF1EF08><KYXQ>%s</KYXQ><BRDH1>%s</BRDH1><BRDH2>%s</BRDH2><YLFYZFFS1>%s</YLFYZFFS1><YLFYZFFS2>%s</YLFYZFFS2><YLFYZFFS3>%s</YLFYZFFS3></DDF1EF08>\r\n<DF01EF05><DZLB1>%s</DZLB1><DZ1>%s</DZ1><DZLB2>%s</DZLB2><DZ2>%s</DZ2></DF01EF05>\r\n<DF01EF06><LXRXM1>%s</LXRXM1><LXRGX1>%s</LXRGX1><LXRDH1>%s</LXRDH1><LXRXM2>%s</LXRXM2><LXRGX2>%s</LXRGX2><LXRDH2>%s</LXRDH2><LXRXM3>%s</LXRXM3><LXRGX3>%s</LXRGX3><LXRDH3>%s</LXRDH3></DF01EF06>\r\n<DF01EF07><WHCD>%s</WHCD><HYZK>%s</HYZK><ZY>%s</ZY></DF01EF07>\r\n<DF01EF08><ZJLB>%s</ZJLB><ZJHM>%s</ZJHM><JKDAH>%s</JKDAH><XNHZH>%s</XNHZH></DF01EF08>",XM,XB,MZ,CSRQ,SFZH,picDataBase64,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3,DZLB1,DZ1,DZLB2,DZ2,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3,WHCD,HYZK,ZY,ZJLB,ZJHM,JKDAH,XNHZH);
	iDClosePort();
	return strResult.AllocSysString();
}

BSTR CHD_SHHealthyACXCtrl::ReadInfoOutPatient() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	HANDLE hDev=NULL;
	int rt=iDOpenPort();
	if(rt!=0)
	{
		strResult.Format("<ERROR>打开端口失败,错误代码%d</ERROR>",rt);
		return strResult.AllocSysString();
	}
	char ATR[50]={0};
	rt=PowerOn(hDev,0x11,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>PSAM卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=PowerOn(hDev,0x01,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>用户卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=iVerifyPIN(hDev,"123456");
	if(rt!=0)
	{
		strResult.Format("<ERROR>校验PSAM卡PIN失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	//读门诊信息
	char szData1[3100]={0};
	char szData2[3100]={0};
	char szData3[3100]={0};
	struct TimeRecdMap
	{
		char DataTime[20];
		int RecdId;
	};
	TimeRecdMap TMap[5]={0};
	int i,j;
	for(i=0;i<5;i++)
	{
		rt=iR_DF03EDInfo (hDev,i+1,TMap[i].DataTime,80,4,0x0F);
		if(rt!=0)
		{
			strResult.Format("<ERROR>读门诊日期%d失败,错误代码%d</ERROR>",i+1,rt);
			iDClosePort();
			return strResult.AllocSysString();
		}
		TMap[i].RecdId=i+1;
	}
	for(i=0;i<4;i++)
	{
		for(j=i+1;j<5;j++)
		{
			char   *stopstring;
			long time1=strtol(TMap[i].DataTime,&stopstring,10);
			long time2=strtol(TMap[j].DataTime,&stopstring,10);
			if(time1<=time2)
			{
				TimeRecdMap temp;
				temp=TMap[i];
				TMap[i]=TMap[j];
				TMap[j]=temp;
			}
		}
	}
	rt=iR_DF03ED_ALLInfo(hDev,TMap[0].RecdId,szData1);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读门诊信息1失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=iR_DF03ED_ALLInfo(hDev,TMap[1].RecdId,szData2);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读门诊信息2失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=iR_DF03ED_ALLInfo(hDev,TMap[2].RecdId,szData3);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读门诊信息3失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	strResult.Format("<MZXX1>%s</MZXX1>\r\n<MZXX2>%s</MZXX2>\r\n<MZXX3>%s</MZXX3>",szData1,szData2,szData3);
	iDClosePort();
	return strResult.AllocSysString();
}

BSTR CHD_SHHealthyACXCtrl::ReadInfoHospitalization() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	HANDLE hDev=NULL;
	int rt=iDOpenPort();
	if(rt!=0)
	{
		strResult.Format("<ERROR>打开端口失败,错误代码%d</ERROR>",rt);
		return strResult.AllocSysString();
	}
	char ATR[50]={0};
	rt=PowerOn(hDev,0x11,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>PSAM卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=PowerOn(hDev,0x01,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>用户卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=iVerifyPIN(hDev,"123456");
	if(rt!=0)
	{
		strResult.Format("<ERROR>校验PSAM卡PIN失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	//读取住院信息
	char szData1[4000]={0};
	char szData2[4000]={0};
	char szData3[4000]={0};
	rt=iR_DF03EE_ALLInfo(hDev,1,szData1);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读住院信息1失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=iR_DF03EE_ALLInfo(hDev,2,szData2);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读住院信息2失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=iR_DF03EE_ALLInfo(hDev,3,szData3);
	if(rt!=0)
	{
		strResult.Format("<ERROR>读住院信息3失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	strResult.Format("<ZYXX1>%s</ZYXX1>\r\n<ZYXX2>%s</ZYXX2>\r\n<ZYXX3>%s</ZYXX3>",szData1,szData2,szData3);
	iDClosePort();
	return strResult.AllocSysString();
}

BSTR CHD_SHHealthyACXCtrl::WriteInfoOutPatient(LPCTSTR DataIn) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	HANDLE hDev=NULL;
	int rt=iDOpenPort();
	if(rt!=0)
	{
		strResult.Format("<ERROR>打开端口失败,错误代码%d</ERROR>",rt);
		return strResult.AllocSysString();
	}
	char ATR[50]={0};
	rt=PowerOn(hDev,0x11,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>PSAM卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=PowerOn(hDev,0x01,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>用户卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=iVerifyPIN(hDev,"123456");
	if(rt!=0)
	{
		strResult.Format("<ERROR>校验PSAM卡PIN失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	string sDataIn=DataIn;
	string temp;
	if(sDataIn.find("<ED01>",0)==-1&&sDataIn.find("<ed01>",0)==-1&&sDataIn.find("<ED02>",0)==-1&&sDataIn.find("<ed02>",0)==-1&&sDataIn.find("<ED03>",0)==-1&&sDataIn.find("<ed03>",0)==-1&&sDataIn.find("<ED04>",0)==-1&&sDataIn.find("<ed04>",0)==-1&&sDataIn.find("<ED05>",0)==-1&&sDataIn.find("<ed05>",0)==-1)
	{
		strResult.Format("<ERROR>传入参数格式有误!</ERROR>");
		iDClosePort();
		return strResult.AllocSysString();
	}
	long EndLen = sDataIn.find("<",2);
	long StartLen = sDataIn.find(">",0); 
	temp=sDataIn.substr(StartLen+1,EndLen-StartLen-1);
	if(sDataIn.find("<ED01>",0)!=-1||sDataIn.find("<ed01>",0)!=-1)
	{
		rt=iW_DF03ED_ALLInfo(hDev,1,(char *)temp.c_str());
		if(rt!=0)
		{
			strResult.Format("<ERROR>写门诊信息1失败,错误代码%d</ERROR>",rt);
			iDClosePort();
			return strResult.AllocSysString();
		}
	}else if(sDataIn.find("<ED02>",0)!=-1||sDataIn.find("<ed02>",0)!=-1)
	{
		rt=iW_DF03ED_ALLInfo(hDev,2,(char *)temp.c_str());
		if(rt!=0)
		{
			strResult.Format("<ERROR>写门诊信息2失败,错误代码%d</ERROR>",rt);
			iDClosePort();
			return strResult.AllocSysString();
		}
	}else if(sDataIn.find("<ED03>",0)!=-1||sDataIn.find("<ed03>",0)!=-1)
	{
		rt=iW_DF03ED_ALLInfo(hDev,3,(char *)temp.c_str());
		if(rt!=0)
		{
			strResult.Format("<ERROR>写门诊信息3失败,错误代码%d</ERROR>",rt);
			iDClosePort();
			return strResult.AllocSysString();
		}
	}else if(sDataIn.find("<ED04>",0)!=-1||sDataIn.find("<ed04>",0)!=-1)
	{
		rt=iW_DF03ED_ALLInfo(hDev,4,(char *)temp.c_str());
		if(rt!=0)
		{
			strResult.Format("<ERROR>写门诊信息4失败,错误代码%d</ERROR>",rt);
			iDClosePort();
			return strResult.AllocSysString();
		}
	}else if(sDataIn.find("<ED05>",0)!=-1||sDataIn.find("<ed05>",0)!=-1)
	{
		rt=iW_DF03ED_ALLInfo(hDev,5,(char *)temp.c_str());
		if(rt!=0)
		{
			strResult.Format("<ERROR>写门诊信息5失败,错误代码%d</ERROR>",rt);
			iDClosePort();
			return strResult.AllocSysString();
		}
	}else
	{
		strResult.Format("<ERROR>传入参数格式有误!</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	strResult.Format("<MSG>写门诊信息成功!</MSG>");
	iDClosePort();
	return strResult.AllocSysString();
}

BSTR CHD_SHHealthyACXCtrl::WriteInfoHospitalization(LPCTSTR DataIn) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	HANDLE hDev=NULL;
	int rt=iDOpenPort();
	if(rt!=0)
	{
		strResult.Format("<ERROR>打开端口失败,错误代码%d</ERROR>",rt);
		return strResult.AllocSysString();
	}
	char ATR[50]={0};
	rt=PowerOn(hDev,0x11,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>PSAM卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=PowerOn(hDev,0x01,ATR);
	if(rt!=0)
	{
		strResult.Format("<ERROR>用户卡上电失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	rt=iVerifyPIN(hDev,"123456");
	if(rt!=0)
	{
		strResult.Format("<ERROR>校验PSAM卡PIN失败,错误代码%d</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	string sDataIn=DataIn;
	string temp;
	if(sDataIn.find("<EE01>",0)==-1&&sDataIn.find("<ee01>",0)==-1&&sDataIn.find("<EE02>",0)==-1&&sDataIn.find("<ee02>",0)==-1&&sDataIn.find("<EE03>",0)==-1&&sDataIn.find("<ee03>",0)==-1)
	{
		strResult.Format("<ERROR>传入参数格式有误!</ERROR>");
		iDClosePort();
		return strResult.AllocSysString();
	}
	long EndLen = sDataIn.find("<",2);
	long StartLen = sDataIn.find(">",0); 
	temp=sDataIn.substr(StartLen+1,EndLen-StartLen-1);
	if(sDataIn.find("<EE01>",0)!=-1||sDataIn.find("<ee01>",0)!=-1)
	{
		rt=iW_DF03EE_ALLInfo(hDev,1,(char *)temp.c_str());
		if(rt!=0)
		{
			strResult.Format("<ERROR>写住院信息1失败,错误代码%d</ERROR>",rt);
			iDClosePort();
			return strResult.AllocSysString();
		}
	}else if(sDataIn.find("<EE02>",0)!=-1||sDataIn.find("<ee02>",0)!=-1)
	{
		rt=iW_DF03EE_ALLInfo(hDev,2,(char *)temp.c_str());
		if(rt!=0)
		{
			strResult.Format("<ERROR>写住院信息2失败,错误代码%d</ERROR>",rt);
			iDClosePort();
			return strResult.AllocSysString();
		}
	}else if(sDataIn.find("<EE03>",0)!=-1||sDataIn.find("<ee03>",0)!=-1)
	{
		rt=iW_DF03EE_ALLInfo(hDev,3,(char *)temp.c_str());
		if(rt!=0)
		{
			strResult.Format("<ERROR>写住院信息3失败,错误代码%d</ERROR>",rt);
			iDClosePort();
			return strResult.AllocSysString();
		}
	}else
	{
		strResult.Format("<ERROR>传入参数格式有误!</ERROR>",rt);
		iDClosePort();
		return strResult.AllocSysString();
	}
	strResult.Format("<MSG>写住院信息成功!</MSG>");
	iDClosePort();
	return strResult.AllocSysString();
}
