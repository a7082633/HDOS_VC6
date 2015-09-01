// HD_HNOCXPpg.cpp : Implementation of the CHD_HNOCXPropPage property page class.

#include "stdafx.h"
#include "HD_HNOCX.h"
#include "HD_HNOCXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_HNOCXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_HNOCXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CHD_HNOCXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_HNOCXPropPage, "HDHNOCX.HDHNOCXPropPage.1",
	0x5014b7db, 0xc961, 0x44c9, 0xae, 0xd8, 0x95, 0xb3, 0x42, 0x69, 0xd6, 0xf9)


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXPropPage::CHD_HNOCXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_HNOCXPropPage

BOOL CHD_HNOCXPropPage::CHD_HNOCXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_HD_HNOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXPropPage::CHD_HNOCXPropPage - Constructor

CHD_HNOCXPropPage::CHD_HNOCXPropPage() :
	COlePropertyPage(IDD, IDS_HD_HNOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CHD_HNOCXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXPropPage::DoDataExchange - Moves data between page and properties

void CHD_HNOCXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CHD_HNOCXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_HNOCXPropPage message handlers
