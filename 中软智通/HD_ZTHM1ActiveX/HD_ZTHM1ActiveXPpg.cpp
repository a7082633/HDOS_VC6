// HD_ZTHM1ActiveXPpg.cpp : Implementation of the CHD_ZTHM1ActiveXPropPage property page class.

#include "stdafx.h"
#include "HD_ZTHM1ActiveX.h"
#include "HD_ZTHM1ActiveXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_ZTHM1ActiveXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_ZTHM1ActiveXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CHD_ZTHM1ActiveXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_ZTHM1ActiveXPropPage, "HDZTHM1ACTIVEX.HDZTHM1ActiveXPropPage.1",
	0x3669a9a7, 0x17dd, 0x40d0, 0x8f, 0x81, 0x1d, 0xc7, 0x6d, 0x94, 0xb9, 0x61)


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXPropPage::CHD_ZTHM1ActiveXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_ZTHM1ActiveXPropPage

BOOL CHD_ZTHM1ActiveXPropPage::CHD_ZTHM1ActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_HD_ZTHM1ACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXPropPage::CHD_ZTHM1ActiveXPropPage - Constructor

CHD_ZTHM1ActiveXPropPage::CHD_ZTHM1ActiveXPropPage() :
	COlePropertyPage(IDD, IDS_HD_ZTHM1ACTIVEX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CHD_ZTHM1ActiveXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXPropPage::DoDataExchange - Moves data between page and properties

void CHD_ZTHM1ActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CHD_ZTHM1ActiveXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1ActiveXPropPage message handlers
