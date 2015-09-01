// HD_HNOCXCtl.cpp : Implementation of the CHD_HNOCXCtrl ActiveX Control class.

#include "stdafx.h"
#include "HD_HNOCX.h"
#include "HD_HNOCXCtl.h"
#include "HD_HNOCXPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_HNOCXCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_HNOCXCtrl, COleControl)
	//{{AFX_MSG_MAP(CHD_HNOCXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CHD_HNOCXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CHD_HNOCXCtrl)
	DISP_PROPERTY_NOTIFY(CHD_HNOCXCtrl, "zp", m_zp, OnZpChanged, VT_BSTR)
	DISP_FUNCTION(CHD_HNOCXCtrl, "ReadCard", ReadCard, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CHD_HNOCXCtrl, "WriteCard", WriteCard, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CHD_HNOCXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CHD_HNOCXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CHD_HNOCXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CHD_HNOCXCtrl, 1)
	PROPPAGEID(CHD_HNOCXPropPage::guid)
END_PROPPAGEIDS(CHD_HNOCXCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_HNOCXCtrl, "HDHNOCX.HDHNOCXCtrl.1",
	0xc16c150f, 0x5a24, 0x4615, 0x83, 0x7a, 0x18, 0x98, 0xbe, 0x46, 0x43, 0x49)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CHD_HNOCXCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DHD_HNOCX =
		{ 0xd9bcfe44, 0xabd4, 0x485c, { 0x98, 0xe7, 0xc2, 0x4d, 0xc1, 0x5d, 0xe8, 0x25 } };
const IID BASED_CODE IID_DHD_HNOCXEvents =
		{ 0xbe2560c8, 0xa2b6, 0x42d4, { 0x90, 0xd0, 0xe9, 0x1a, 0x5f, 0xd4, 0x3, 0x15 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwHD_HNOCXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CHD_HNOCXCtrl, IDS_HD_HNOCX, _dwHD_HNOCXOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXCtrl::CHD_HNOCXCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_HNOCXCtrl

BOOL CHD_HNOCXCtrl::CHD_HNOCXCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_HD_HNOCX,
			IDB_HD_HNOCX,
			afxRegApartmentThreading,
			_dwHD_HNOCXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXCtrl::CHD_HNOCXCtrl - Constructor

CHD_HNOCXCtrl::CHD_HNOCXCtrl()
{
	InitializeIIDs(&IID_DHD_HNOCX, &IID_DHD_HNOCXEvents);

	// TODO: Initialize your control's instance data here.
	memset(pDest,0,10000);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXCtrl::~CHD_HNOCXCtrl - Destructor

CHD_HNOCXCtrl::~CHD_HNOCXCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXCtrl::OnDraw - Drawing function

void CHD_HNOCXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXCtrl::DoPropExchange - Persistence support

void CHD_HNOCXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXCtrl::OnResetState - Reset control to default state

void CHD_HNOCXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXCtrl::AboutBox - Display an "About" box to the user

void CHD_HNOCXCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_HD_HNOCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXCtrl message handlers

char Encode_GetChar(BYTE num)
{
    return 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "+/="[num];
}

//±àÂë
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

BSTR CHD_HNOCXCtrl::ReadCard(LPCTSTR para, LPCTSTR account, LPCTSTR password, LPCTSTR doctype, LPCTSTR userid, LPCTSTR pin) 
{
 	CString strResult;
 	// TODO: Add your dispatch handler code here
 	char dataOut[12000]={0};
 	int idoctype=atoi(doctype);
 	int i=IR_ReadCard((char *)para,dataOut,(char *)account,(char *)password,idoctype,(char *)userid,(char *)pin);

	if(0==strcmp(para,"102"))
	{
		unsigned char strOut[4000]={0};
		StrToHex((unsigned char *)dataOut,strlen(dataOut),strOut);

		char temp[10]={0};
		sprintf(temp,"%02x%02x",strOut[0],strOut[1]);
		long len=strtol(temp,NULL,16);

		Base64_Encode(pDest,(const char *)strOut+2,len);
		m_zp.Format("%s",pDest);
	}


 	if(i==0) 
 		strResult.Format("%s",dataOut);
 	else
 		strResult.Format("¶Á¿¨Ê§°Ü£¬´íÎó´úÂë:%d",i);
 	return strResult.AllocSysString();
}

long CHD_HNOCXCtrl::WriteCard(LPCTSTR para, LPCTSTR dataIn, LPCTSTR account, LPCTSTR password, LPCTSTR doctype, LPCTSTR userid, LPCTSTR pin) 
{
	int idoctype=atoi(doctype);
	long i=IR_WriteCard((char *)para,(char *)dataIn,(char *)account,(char *)password,idoctype,(char *)userid,(char *)pin);
	return i;
}

void CHD_HNOCXCtrl::OnZpChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}
