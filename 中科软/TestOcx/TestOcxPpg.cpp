// TestOcxPpg.cpp : Implementation of the CTestOcxPropPage property page class.

#include "stdafx.h"
#include "TestOcx.h"
#include "TestOcxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CTestOcxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CTestOcxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CTestOcxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CTestOcxPropPage, "TESTOCX.TestOcxPropPage.1",
	0x8c290d68, 0x2423, 0x4144, 0xb3, 0x36, 0x39, 0xd4, 0xf8, 0xd3, 0x3a, 0x54)


/////////////////////////////////////////////////////////////////////////////
// CTestOcxPropPage::CTestOcxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CTestOcxPropPage

BOOL CTestOcxPropPage::CTestOcxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_TESTOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxPropPage::CTestOcxPropPage - Constructor

CTestOcxPropPage::CTestOcxPropPage() :
	COlePropertyPage(IDD, IDS_TESTOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CTestOcxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxPropPage::DoDataExchange - Moves data between page and properties

void CTestOcxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CTestOcxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CTestOcxPropPage message handlers
