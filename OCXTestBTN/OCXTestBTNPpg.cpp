// OCXTestBTNPpg.cpp : Implementation of the COCXTestBTNPropPage property page class.

#include "stdafx.h"
#include "OCXTestBTN.h"
#include "OCXTestBTNPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(COCXTestBTNPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(COCXTestBTNPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(COCXTestBTNPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(COCXTestBTNPropPage, "OCXTESTBTN.OCXTestBTNPropPage.1",
	0x4926d03, 0x691, 0x4ac9, 0xb3, 0x67, 0x90, 0xf9, 0x84, 0x23, 0xec, 0x84)


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNPropPage::COCXTestBTNPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for COCXTestBTNPropPage

BOOL COCXTestBTNPropPage::COCXTestBTNPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_OCXTESTBTN_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNPropPage::COCXTestBTNPropPage - Constructor

COCXTestBTNPropPage::COCXTestBTNPropPage() :
	COlePropertyPage(IDD, IDS_OCXTESTBTN_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(COCXTestBTNPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNPropPage::DoDataExchange - Moves data between page and properties

void COCXTestBTNPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(COCXTestBTNPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// COCXTestBTNPropPage message handlers
