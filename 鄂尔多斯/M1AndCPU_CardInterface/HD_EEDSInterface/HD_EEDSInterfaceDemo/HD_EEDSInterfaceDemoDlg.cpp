// HD_EEDSInterfaceDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HD_EEDSInterfaceDemo.h"
#include "HD_EEDSInterfaceDemoDlg.h"

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
// CHD_EEDSInterfaceDemoDlg dialog

CHD_EEDSInterfaceDemoDlg::CHD_EEDSInterfaceDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHD_EEDSInterfaceDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHD_EEDSInterfaceDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHD_EEDSInterfaceDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHD_EEDSInterfaceDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHD_EEDSInterfaceDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CHD_EEDSInterfaceDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_READCARD, OnBtnReadcard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHD_EEDSInterfaceDemoDlg message handlers

BOOL CHD_EEDSInterfaceDemoDlg::OnInitDialog()
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
	this->SetDlgItemText(IDC_EDIT_M1PASS,"FFFFFFFFFFFF");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHD_EEDSInterfaceDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHD_EEDSInterfaceDemoDlg::OnPaint() 
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
HCURSOR CHD_EEDSInterfaceDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHD_EEDSInterfaceDemoDlg::OnBtnRead() 
{
//	this->SetDlgItemText(IDC_STATIC_STATE,"");
//	CString sPass;
//	this->GetDlgItemText(IDC_EDIT_M1PASS,sPass);
//	unsigned char GECHH[50]={0};
//	unsigned char XM[50]={0}; 
//	unsigned char SFZH[50]={0};
//	unsigned char CSRQ[50]={0};
//	unsigned char XB[50]={0};
//	unsigned char MZ[50]={0};
//	char pErr[50]={0};
//	int re=ReadInfo((unsigned char *)sPass.GetBuffer(0),GECHH,XM,SFZH,CSRQ,XB,MZ,pErr);
//	if(re)
//	{
//		this->SetDlgItemText(IDC_STATIC_STATE,pErr);
//		return ;
//	}else
//		this->SetDlgItemText(IDC_STATIC_STATE,"¶Á¿¨³É¹¦!");
//	this->SetDlgItemText(IDC_STATIC_GZCHH,(const char *)GECHH);
//	this->SetDlgItemText(IDC_STATIC_XM,(const char *)XM);
//	this->SetDlgItemText(IDC_STATIC_SFZH,(const char *)SFZH);
//	this->SetDlgItemText(IDC_STATIC_CSRQ,(const char *)CSRQ);
//	this->SetDlgItemText(IDC_STATIC_XB,(const char *)XB);
//	this->SetDlgItemText(IDC_STATIC_MZ,(const char *)MZ);
}

void CHD_EEDSInterfaceDemoDlg::OnBtnReadcard() 
{
	unsigned char OutXml[5000]={0};
	char pErr[500]={0};
	int ret=iReadCard(OutXml,pErr);
	if(ret==0)
	{
		this->SetDlgItemText(IDC_EDIT_DATA,(const char *)OutXml);
	}else
	{
		this->SetDlgItemText(IDC_STATIC_STATE,pErr);
	}
}
