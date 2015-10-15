// HD_CPUAndIDPpg.cpp : Implementation of the CHD_CPUAndIDPropPage property page class.

#include "stdafx.h"
#include "HD_CPUAndID.h"
#include "HD_CPUAndIDPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CHD_CPUAndIDPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CHD_CPUAndIDPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CHD_CPUAndIDPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CHD_CPUAndIDPropPage, "HDCPUANDID.HDCPUAndIDPropPage.1",
	0x31b30408, 0x372f, 0x4978, 0xb6, 0x23, 0xdb, 0x6a, 0x7, 0x73, 0xef, 0xda)


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDPropPage::CHD_CPUAndIDPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CHD_CPUAndIDPropPage

BOOL CHD_CPUAndIDPropPage::CHD_CPUAndIDPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_HD_CPUANDID_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDPropPage::CHD_CPUAndIDPropPage - Constructor

CHD_CPUAndIDPropPage::CHD_CPUAndIDPropPage() :
	COlePropertyPage(IDD, IDS_HD_CPUANDID_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CHD_CPUAndIDPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDPropPage::DoDataExchange - Moves data between page and properties

void CHD_CPUAndIDPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CHD_CPUAndIDPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CHD_CPUAndIDPropPage message handlers
