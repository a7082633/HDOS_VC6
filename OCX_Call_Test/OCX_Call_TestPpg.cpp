// OCX_Call_TestPpg.cpp : Implementation of the COCX_Call_TestPropPage property page class.

#include "stdafx.h"
#include "OCX_Call_Test.h"
#include "OCX_Call_TestPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(COCX_Call_TestPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(COCX_Call_TestPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(COCX_Call_TestPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(COCX_Call_TestPropPage, "OCXCALLTEST.OCXCallTestPropPage.1",
	0x4f86bbaf, 0x8bbc, 0x41e3, 0xa4, 0x8c, 0x9a, 0x4d, 0x3, 0xe2, 0x31, 0x6b)


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestPropPage::COCX_Call_TestPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for COCX_Call_TestPropPage

BOOL COCX_Call_TestPropPage::COCX_Call_TestPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_OCX_CALL_TEST_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestPropPage::COCX_Call_TestPropPage - Constructor

COCX_Call_TestPropPage::COCX_Call_TestPropPage() :
	COlePropertyPage(IDD, IDS_OCX_CALL_TEST_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(COCX_Call_TestPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestPropPage::DoDataExchange - Moves data between page and properties

void COCX_Call_TestPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(COCX_Call_TestPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// COCX_Call_TestPropPage message handlers
