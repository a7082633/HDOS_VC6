// HD_ZTHReadM1ActiveXPpg.cpp : Implementation of the CHD_ZTHReadM1ActiveXPropPage property page class.

#include "stdafx.h"
#include "HD_ZTHReadM1ActiveX.h"
#include "HD_ZTHReadM1ActiveXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_ZTHReadM1ActiveXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_ZTHReadM1ActiveXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CHD_ZTHReadM1ActiveXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_ZTHReadM1ActiveXPropPage, "HDZTHREADM1ACTIVEX.HDZTHReadM1ActiveXPropPage.1",
	0xef49b2d6, 0x75c3, 0x4271, 0x98, 0xa7, 0xa7, 0x1d, 0x23, 0xa0, 0xf9, 0x91)


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXPropPage::CHD_ZTHReadM1ActiveXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_ZTHReadM1ActiveXPropPage

BOOL CHD_ZTHReadM1ActiveXPropPage::CHD_ZTHReadM1ActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_HD_ZTHREADM1ACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXPropPage::CHD_ZTHReadM1ActiveXPropPage - Constructor

CHD_ZTHReadM1ActiveXPropPage::CHD_ZTHReadM1ActiveXPropPage() :
	COlePropertyPage(IDD, IDS_HD_ZTHREADM1ACTIVEX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CHD_ZTHReadM1ActiveXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXPropPage::DoDataExchange - Moves data between page and properties

void CHD_ZTHReadM1ActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CHD_ZTHReadM1ActiveXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHReadM1ActiveXPropPage message handlers
