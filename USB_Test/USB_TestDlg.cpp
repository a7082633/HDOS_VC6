// USB_TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "USB_Test.h"
#include "USB_TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUSB_TestDlg dialog

CUSB_TestDlg::CUSB_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUSB_TestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUSB_TestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSB_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUSB_TestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUSB_TestDlg, CDialog)
	//{{AFX_MSG_MAP(CUSB_TestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_FINDDEV, OnBtnFinddev)
	ON_BN_CLICKED(IDC_BTN_CLOSEDEV, OnBtnClosedev)
	ON_BN_CLICKED(IDC_BTN_BEEP, OnBtnBeep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUSB_TestDlg message handlers

BOOL CUSB_TestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUSB_TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUSB_TestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUSB_TestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUSB_TestDlg::OnBtnFinddev() 
{
	GUID HidGuid;
	 /* Get GUID for all System HIDs */
	HidD_GetHidGuid(&HidGuid);//指针指向调用者分配的GUID的内存区域，通常返回HID设备的GUID
	 /* Get Device Information for all present devices */
	HDEVINFO DevInfo;
	DevInfo = SetupDiGetClassDevs(&HidGuid, NULL, NULL, (DIGCF_PRESENT | DIGCF_DEVICEINTERFACE));
	//An SP_DEVICE_INTERFACE_DATA structure defines a device interface in a device information set.
	SP_DEVICE_INTERFACE_DATA    DevData;
	DevData.cbSize=sizeof(DevData);
	int Index=0;  //the number of Dev;
	BOOL ok=TRUE;
	ULONG   Length;
	PSP_DEVICE_INTERFACE_DETAIL_DATA DevDetail;
	HIDD_ATTRIBUTES      DevAttributes;
//	PHIDP_PREPARSED_DATA          PreparsedData;
	do
	{
		 /* Device Interface Element of a Device Information set */
		ok = SetupDiEnumDeviceInterfaces(DevInfo,0,&HidGuid,Index++,&DevData);
		if(!ok)
		{
			this->MessageBox("SetupDiEnumDeviceInterfaces failure");
			break;
		}
		//------------------------------pair--------------------------
		 /* Get Device Interface Details - Get Length */
		//this place for get Buffer size
		ok = SetupDiGetDeviceInterfaceDetail(DevInfo,&DevData,NULL,0,&Length,NULL);
//		int i=::GetLastError();
		 /* Allocate memory for Device Detailed Data */
        DevDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);
		  /* Set cbSize in the DevDetail structure */
		DevDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
        /* Get Device Interface Details */
		ok = SetupDiGetDeviceInterfaceDetail(DevInfo, &DevData, DevDetail, Length, NULL, NULL);
		//------------------------------pair--------------------------
		if (!ok) 
		{
			free(DevDetail);
			DevDetail = NULL;
			continue;
		}
		  /* Create File for Device Read/Write */
        DevHandle = CreateFile(DevDetail->DevicePath, 
								GENERIC_READ | GENERIC_WRITE, 
								FILE_SHARE_READ | FILE_SHARE_WRITE, 
								(LPSECURITY_ATTRIBUTES)NULL,OPEN_EXISTING, 
								0, 
								NULL);
		int i=::GetLastError();
		if (DevHandle == INVALID_HANDLE_VALUE)
		{
			free(DevDetail);
			DevDetail = NULL;
			continue;
		}
		DevAttributes.Size = sizeof(DevAttributes);
		//Get factory and producer and version
		ok = HidD_GetAttributes(DevHandle,&DevAttributes);
		if(!ok) 
		{
			free(DevDetail);
			CloseHandle(DevHandle);
			DevDetail = NULL;
			continue;
		}
		//Judge if the VID AND PID match mine 
		if(DevAttributes.VendorID!=V_ID||DevAttributes.ProductID != P_ID)
		{
			free(DevDetail);
			CloseHandle(DevHandle);
			DevDetail = NULL;
			continue;
		}
		else
		{
			this->MessageBox("got it");
			break;
		}
		  /* Get Preparsed Data */
//		ok = HidD_GetPreparsedData(DevHandle, &PreparsedData);
//		if (!ok) 
//		{
//			free(DevDetail);
//			CloseHandle(DevHandle);
//			DevDetail = NULL;
//			continue;
//		}
//		CloseHandle(DevHandle);
	}while(Index<10);
	if (DevDetail) free(DevDetail);
	SetupDiDestroyDeviceInfoList(DevInfo);
}

void CUSB_TestDlg::OnBtnClosedev() 
{
	if(DevHandle==NULL)
	{
		this->MessageBox("no device");
	}
	else
	{
		if(CloseHandle((HANDLE)DevHandle))
		{
			this->MessageBox("Close success!");
		}
		else
		{
			this->MessageBox("Close failure!");
			return;
		}
	}
}

void CUSB_TestDlg::OnBtnBeep() 
{
		unsigned char temp[255]={0};
		unsigned char OutReport[255]={0};
		temp[0]=0x00;
		temp[1]=CardCommandT1;
		temp[2]=CardCommandT3;
		temp[3]=0x00;
		temp[4]=0x02;
		temp[5]=0x00;
		temp[6]=0xb2;
		temp[7]=0x30;

		temp[8]=temp[2]^temp[3]^temp[4]^temp[5]^temp[6]^temp[7];//0x3c
		//temp[8]=0x00;
		
	   BOOL flag=FALSE;
	   flag=HidD_SetFeature(DevHandle,temp,0x21);
	   flag=HidD_GetFeature(DevHandle,OutReport,0x21);
}
