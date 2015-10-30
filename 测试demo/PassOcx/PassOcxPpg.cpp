// PassOcxPpg.cpp : Implementation of the CPassOcxPropPage property page class.

#include "stdafx.h"
#include "PassOcx.h"
#include "PassOcxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CPassOcxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CPassOcxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CPassOcxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CPassOcxPropPage, "PASSOCX.PassOcxPropPage.1",
	0xee0f7d6d, 0x87a6, 0x4171, 0xab, 0xeb, 0x86, 0x98, 0xcc, 0xe5, 0xff, 0x5b)


/////////////////////////////////////////////////////////////////////////////
// CPassOcxPropPage::CPassOcxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CPassOcxPropPage

BOOL CPassOcxPropPage::CPassOcxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_PASSOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxPropPage::CPassOcxPropPage - Constructor

CPassOcxPropPage::CPassOcxPropPage() :
	COlePropertyPage(IDD, IDS_PASSOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CPassOcxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxPropPage::DoDataExchange - Moves data between page and properties

void CPassOcxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CPassOcxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CPassOcxPropPage message handlers
