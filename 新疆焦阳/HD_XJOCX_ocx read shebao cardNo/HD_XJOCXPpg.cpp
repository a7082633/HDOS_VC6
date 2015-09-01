// HD_XJOCXPpg.cpp : Implementation of the CHD_XJOCXPropPage property page class.

#include "stdafx.h"
#include "HD_XJOCX.h"
#include "HD_XJOCXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_XJOCXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_XJOCXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CHD_XJOCXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_XJOCXPropPage, "HDXJOCX.HDXJOCXPropPage.1",
	0xe5be5574, 0xe63b, 0x4f4a, 0x80, 0x21, 0x35, 0x4c, 0x3e, 0xd3, 0x74, 0x1d)


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXPropPage::CHD_XJOCXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_XJOCXPropPage

BOOL CHD_XJOCXPropPage::CHD_XJOCXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_HD_XJOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXPropPage::CHD_XJOCXPropPage - Constructor

CHD_XJOCXPropPage::CHD_XJOCXPropPage() :
	COlePropertyPage(IDD, IDS_HD_XJOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CHD_XJOCXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXPropPage::DoDataExchange - Moves data between page and properties

void CHD_XJOCXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CHD_XJOCXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_XJOCXPropPage message handlers
