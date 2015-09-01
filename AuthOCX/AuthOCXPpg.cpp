// AuthOCXPpg.cpp : Implementation of the CAuthOCXPropPage property page class.

#include "stdafx.h"
#include "AuthOCX.h"
#include "AuthOCXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CAuthOCXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CAuthOCXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CAuthOCXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CAuthOCXPropPage, "AUTHOCX.AuthOCXPropPage.1",
	0xb0acd9c5, 0x4f24, 0x49b2, 0x87, 0x97, 0x50, 0x8f, 0x53, 0xae, 0x29, 0xa2)


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXPropPage::CAuthOCXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CAuthOCXPropPage

BOOL CAuthOCXPropPage::CAuthOCXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_AUTHOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXPropPage::CAuthOCXPropPage - Constructor

CAuthOCXPropPage::CAuthOCXPropPage() :
	COlePropertyPage(IDD, IDS_AUTHOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CAuthOCXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXPropPage::DoDataExchange - Moves data between page and properties

void CAuthOCXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CAuthOCXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CAuthOCXPropPage message handlers
