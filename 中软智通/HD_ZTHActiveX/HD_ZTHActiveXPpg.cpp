// HD_ZTHActiveXPpg.cpp : Implementation of the CHD_ZTHActiveXPropPage property page class.

#include "stdafx.h"
#include "HD_ZTHActiveX.h"
#include "HD_ZTHActiveXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_ZTHActiveXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_ZTHActiveXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CHD_ZTHActiveXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_ZTHActiveXPropPage, "HDZTHACTIVEX.HDZTHActiveXPropPage.1",
	0xe5783668, 0xb540, 0x4bcd, 0xa3, 0x5a, 0xcd, 0x4b, 0x75, 0xac, 0x88, 0xe0)


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXPropPage::CHD_ZTHActiveXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_ZTHActiveXPropPage

BOOL CHD_ZTHActiveXPropPage::CHD_ZTHActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_HD_ZTHACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXPropPage::CHD_ZTHActiveXPropPage - Constructor

CHD_ZTHActiveXPropPage::CHD_ZTHActiveXPropPage() :
	COlePropertyPage(IDD, IDS_HD_ZTHACTIVEX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CHD_ZTHActiveXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXPropPage::DoDataExchange - Moves data between page and properties

void CHD_ZTHActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CHD_ZTHActiveXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHActiveXPropPage message handlers
