// HD_ZTHM1DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HD_ZTHM1Demo.h"
#include "HD_ZTHM1DemoDlg.h"

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
// CHD_ZTHM1DemoDlg dialog

CHD_ZTHM1DemoDlg::CHD_ZTHM1DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHD_ZTHM1DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHD_ZTHM1DemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHD_ZTHM1DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHD_ZTHM1DemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHD_ZTHM1DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CHD_ZTHM1DemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHM1DemoDlg message handlers

BOOL CHD_ZTHM1DemoDlg::OnInitDialog()
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
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHD_ZTHM1DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHD_ZTHM1DemoDlg::OnPaint() 
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
HCURSOR CHD_ZTHM1DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHD_ZTHM1DemoDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CHD_ZTHM1DemoDlg::OnBtnWrite() 
{
	CString sKey,sName,sSex,sIDNo,sBornDate,sCardNo,sMakeCardDT;
	char pErr[100]={0};
	this->GetDlgItemText(IDC_EDIT_KEY,sKey);
	this->GetDlgItemText(IDC_EDIT_NAME,sName);
	this->GetDlgItemText(IDC_EDIT_SEX,sSex);
	this->GetDlgItemText(IDC_EDIT_SFZH,sIDNo);
	this->GetDlgItemText(IDC_EDIT_CSRQ,sBornDate);
	this->GetDlgItemText(IDC_EDIT_KH,sCardNo);
	this->GetDlgItemText(IDC_EDIT_BKRQ,sMakeCardDT);
	int ret=HD_WriteM1(sKey.GetBuffer(0),sName.GetBuffer(0),sSex.GetBuffer(0),sIDNo.GetBuffer(0),sBornDate.GetBuffer(0),sCardNo.GetBuffer(0),sMakeCardDT.GetBuffer(0),pErr);
	if(ret==0)
	{
		this->SetDlgItemText(IDC_STATIC_STATE,"写卡成功!");
	}else
	{
		this->SetDlgItemText(IDC_STATIC_STATE,pErr);
	}
	sKey.ReleaseBuffer();
	sName.ReleaseBuffer();
	sSex.ReleaseBuffer();
	sIDNo.ReleaseBuffer();
	sBornDate.ReleaseBuffer();
	sCardNo.ReleaseBuffer();
	sMakeCardDT.ReleaseBuffer();
}

void CHD_ZTHM1DemoDlg::OnBtnRead() 
{
	CString sKey,sAddr,sSex,sIDNo,sBornDate,sCardNo,sMakeCardDT;
	char pErr[100]={0};
	char DataOut[100]={0};
	this->GetDlgItemText(IDC_EDIT_KEY,sKey);
	this->GetDlgItemText(IDC_EDIT_BLOCKNO,sAddr);
	int ret=HD_ReadM1(sKey.GetBuffer(0),sAddr.GetBuffer(0),DataOut,pErr);
	if(ret==0)
	{
		this->SetDlgItemText(IDC_STATIC_STATE,"读卡成功!");
		this->SetDlgItemText(IDC_EDIT_SHOWDATA,DataOut);
	}else
	{
		this->SetDlgItemText(IDC_STATIC_STATE,pErr);
	}
}
