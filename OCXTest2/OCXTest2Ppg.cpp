// OCXTest2Ppg.cpp : Implementation of the COCXTest2PropPage property page class.

#include "stdafx.h"
#include "OCXTest2.h"
#include "OCXTest2Ppg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(COCXTest2PropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(COCXTest2PropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(COCXTest2PropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(COCXTest2PropPage, "OCXTEST2.OCXTest2PropPage.1",
	0x32891a74, 0x6aa4, 0x43c1, 0xaf, 0x24, 0xba, 0x22, 0xe4, 0xe1, 0xc1, 0x23)


/////////////////////////////////////////////////////////////////////////////
// COCXTest2PropPage::COCXTest2PropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for COCXTest2PropPage

BOOL COCXTest2PropPage::COCXTest2PropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_OCXTEST2_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2PropPage::COCXTest2PropPage - Constructor

COCXTest2PropPage::COCXTest2PropPage() :
	COlePropertyPage(IDD, IDS_OCXTEST2_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(COCXTest2PropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2PropPage::DoDataExchange - Moves data between page and properties

void COCXTest2PropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(COCXTest2PropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTest2PropPage message handlers
