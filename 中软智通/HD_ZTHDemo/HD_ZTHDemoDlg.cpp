// HD_ZTHDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HD_ZTHDemo.h"
#include "HD_ZTHDemoDlg.h"

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
// CHD_ZTHDemoDlg dialog

CHD_ZTHDemoDlg::CHD_ZTHDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHD_ZTHDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHD_ZTHDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHD_ZTHDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHD_ZTHDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHD_ZTHDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CHD_ZTHDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENDEVICE, OnBtnOpendevice)
	ON_BN_CLICKED(IDC_BTN_CLOSEDEVICE, OnBtnClosedevice)
	ON_BN_CLICKED(IDC_BTN_READCARD, OnBtnReadcard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHDemoDlg message handlers

BOOL CHD_ZTHDemoDlg::OnInitDialog()
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
	this->SetDlgItemText(IDC_EDIT_KEY,"ffffffffffff");
	this->SetDlgItemText(IDC_EDIT_PIN,"1234");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHD_ZTHDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHD_ZTHDemoDlg::OnPaint() 
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
HCURSOR CHD_ZTHDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHD_ZTHDemoDlg::OnBtnOpendevice() 
{
	char pErr[100]={0};
	CString sPin;
	this->GetDlgItemText(IDC_EDIT_PIN,sPin);
	int ret=HD_OpenDevice(sPin.GetBuffer(0),pErr);
	if(ret!=0)
	{
		this->SetDlgItemText(IDC_STATIC_STATE,pErr);
	}else
		this->SetDlgItemText(IDC_STATIC_STATE,"打开设备成功");
	sPin.ReleaseBuffer();
}

void CHD_ZTHDemoDlg::OnBtnClosedevice() 
{
	HD_CloseDevice();
}

void CHD_ZTHDemoDlg::OnBtnReadcard() 
{
	char Key[50]="ffffffffffff";
	char CardType[100]={0};
	char CardNo[100]={0};
	char Name[100]={0};
	char Sex[100]={0};
	char Born[100]={0};
	char IDNo[100]={0};
	char MakeCDT[100]={0};
	char EffectD[100]={0};
	char Nation[100]={0};
	char pErr[100]={0};
	int ret=HD_ReadCardInfo(Key,CardType,CardNo,Name,Sex,Born,IDNo,MakeCDT,EffectD,Nation,pErr);
	if(ret!=0)
	{
		this->SetDlgItemText(IDC_STATIC_STATE,pErr);
		return;
	}else
		this->SetDlgItemText(IDC_STATIC_STATE,"读卡信息成功!");
	this->SetDlgItemText(IDC_EDIT_CARDTYPE,CardType);
	this->SetDlgItemText(IDC_EDIT_KH,CardNo);
	this->SetDlgItemText(IDC_EDIT_XM,Name);
	this->SetDlgItemText(IDC_EDIT_XB,Sex);
	this->SetDlgItemText(IDC_EDIT_CSRQ,Born);
	this->SetDlgItemText(IDC_EDIT_SFZH,IDNo);
	this->SetDlgItemText(IDC_EDIT_BKRQ,MakeCDT);
	this->SetDlgItemText(IDC_EDIT_KYXQ,EffectD);
	this->SetDlgItemText(IDC_EDIT_MZ,Nation);
}

void CHD_ZTHDemoDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
