// HD_SHHealthyACXPpg.cpp : Implementation of the CHD_SHHealthyACXPropPage property page class.

#include "stdafx.h"
#include "HD_SHHealthyACX.h"
#include "HD_SHHealthyACXPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_SHHealthyACXPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_SHHealthyACXPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CHD_SHHealthyACXPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_SHHealthyACXPropPage, "HDSHHEALTHYACX.HDSHHealthyACXPropPage.1",
	0x9125d92f, 0xf163, 0x4603, 0x83, 0x69, 0x2b, 0xc7, 0x2, 0x2c, 0x1b, 0x71)


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXPropPage::CHD_SHHealthyACXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_SHHealthyACXPropPage

BOOL CHD_SHHealthyACXPropPage::CHD_SHHealthyACXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_HD_SHHEALTHYACX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXPropPage::CHD_SHHealthyACXPropPage - Constructor

CHD_SHHealthyACXPropPage::CHD_SHHealthyACXPropPage() :
	COlePropertyPage(IDD, IDS_HD_SHHEALTHYACX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CHD_SHHealthyACXPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXPropPage::DoDataExchange - Moves data between page and properties

void CHD_SHHealthyACXPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CHD_SHHealthyACXPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_SHHealthyACXPropPage message handlers
