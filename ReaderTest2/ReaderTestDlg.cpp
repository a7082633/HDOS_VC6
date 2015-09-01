// ReaderTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReaderTest.h"
#include "ReaderTestDlg.h"
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
// CReaderTestDlg dialog

CReaderTestDlg::CReaderTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReaderTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReaderTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReaderTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReaderTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReaderTestDlg, CDialog)
	//{{AFX_MSG_MAP(CReaderTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReaderTestDlg message handlers

BOOL CReaderTestDlg::OnInitDialog()
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

void CReaderTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CReaderTestDlg::OnPaint() 
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
HCURSOR CReaderTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
int test(int a=0)
{
	return 0;
}

void CReaderTestDlg::OnButton1() 
{
	HANDLE hDev;
	char ATR[100]={0};
	int re=IPowerOn(hDev,0x11,ATR,"test","111111",1,"1|2|3","S078987");
	int i=IDOpenPort("test","111111");
	i=IPowerOn(hDev,0x01,ATR,"test","111111",1,"1|2|3","S078987");
	memset(ATR,0x00,100);
	i=IPowerOn(hDev,0x11,ATR,"test","111111",1,"1|2|3","S078987");
	CString PIN="1234";
	i=IVerifyPIN(hDev,PIN.GetBuffer(0));
	CString sPara;
	this->GetDlgItemText(IDC_EDIT_ADDR,sPara);
	char dataOut[200]={0};
	i=IR_ReadCard(sPara.GetBuffer(0),dataOut);
//	CString dataIn;
//	this->GetDlgItemText(IDC_EDIT_ACCOUNT,dataIn);
//	i=IR_WriteCard(sPara.GetBuffer(0),dataIn.GetBuffer(0));
	i=IDClosePort();
//	int i=iDOpenPort();
//	///
//	long hReader=ICC_Reader_Open("USB1");
//	ICC_PosBeep(hReader,1000);
//	ICC_Reader_Close(hReader);
//	ICC_PosBeep(hReader,1000);
//	//
//	int re=0;
//	char info[100]={0};
//	re=iReader_SAM_Public(i,info);
//	CString PIN="1234";
//	HANDLE hDev;
//	char ATR[100]={0};
//	//re=PowerOn(hDev,0x11,ATR);
//	//re=iVerifyPIN(hDev,PIN.GetBuffer(0));
}

