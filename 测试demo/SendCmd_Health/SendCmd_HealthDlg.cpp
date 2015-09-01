// SendCmd_HealthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SendCmd_Health.h"
#include "SendCmd_HealthDlg.h"

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
// CSendCmd_HealthDlg dialog

CSendCmd_HealthDlg::CSendCmd_HealthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendCmd_HealthDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendCmd_HealthDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSendCmd_HealthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendCmd_HealthDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSendCmd_HealthDlg, CDialog)
	//{{AFX_MSG_MAP(CSendCmd_HealthDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_BN_CLICKED(IDC_BTN_USERPOWERON, OnBtnUserpoweron)
	ON_BN_CLICKED(IDC_BTN_SENDAPDU, OnBtnSendapdu)
	ON_BN_CLICKED(IDC_BTN_SAMPOWERON, OnBtnSampoweron)
	ON_BN_CLICKED(IDC_RADIO_USER, OnRadioUser)
	ON_BN_CLICKED(IDC_RADIO_SAM, OnRadioSam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendCmd_HealthDlg message handlers

BOOL CSendCmd_HealthDlg::OnInitDialog()
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
	radio=1;
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_USER);
	radio->SetCheck(1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSendCmd_HealthDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSendCmd_HealthDlg::OnPaint() 
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
HCURSOR CSendCmd_HealthDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSendCmd_HealthDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CSendCmd_HealthDlg::OnBtnOpen() 
{
	int i=iDOpenPort();
	if(i)
		this->SetDlgItemText(IDC_EDIT_DATA,"打开设备失败!\r\n");
	else
		this->SetDlgItemText(IDC_EDIT_DATA,"打开设备成功!\r\n");
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CSendCmd_HealthDlg::OnBtnClose() 
{
	int i=iDClosePort();
	if(i)
		this->SetDlgItemText(IDC_EDIT_DATA,"关闭设备失败!\r\n");
	else
		this->SetDlgItemText(IDC_EDIT_DATA,"关闭设备成功!\r\n");
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CSendCmd_HealthDlg::OnBtnUserpoweron() 
{
	HANDLE hDev;
	char ATR[50]={0};
	int i=PowerOn(hDev,0x01,ATR) ; //slot 1  User; slot 0x11 SAM1
	CString temp;
	temp.Format("%s\r\n",ATR);
	if(i==0)
	{
		CString sData;
		this->GetDlgItemText(IDC_EDIT_DATA,sData);
		sData+=temp;
		this->SetDlgItemText(IDC_EDIT_DATA,sData);
	}
	else
	{
		CString sData;
		this->GetDlgItemText(IDC_EDIT_DATA,sData);
		sData+="健康卡上电失败!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sData);
	}
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CSendCmd_HealthDlg::OnBtnSendapdu() 
{
	// TODO: Add your control notification handler code here
	HANDLE hDev;
	CString temp,sData;
	this->GetDlgItemText(IDC_EDIT_APDU,temp);
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	sData+="发送指令:"+temp+"\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	int n=0;
	while(-1!=(n=temp.FindOneOf(" ")))
	{
		temp.Delete(n);
	}
	if(temp.GetLength()%2!=0)
	{
		CString sData;
		this->GetDlgItemText(IDC_EDIT_DATA,sData);
		sData+="指令长度有误!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sData);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return ;
	}
	unsigned char cmd[100]={0};
	StrToHex((unsigned char *)temp.GetBuffer(0),temp.GetLength(),cmd);//将字符命令流转为16进制流
	temp.ReleaseBuffer();
	unsigned char Response[300]={0};
	int pnRes=0;

	int slot;
	if(radio==0)
	{
		this->MessageBox("未选择卡片!");
		return;
	}
	if(radio==1) slot=0x01;
	else slot=0x11;
	DWORD  len=SendAPDU (hDev,slot,cmd,temp.GetLength()/2,Response,	&pnRes);
	if(len)
	{	
		CString sData;
		this->GetDlgItemText(IDC_EDIT_DATA,sData);
		sData+="发送指令失败\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sData);
	}
	unsigned char strOut[300]={0};
	CString s;
	CString s2;
	for(int i=0;i<pnRes+2;i++)
	{
		s2.Format("%02x",Response[i]);
		s+=s2+" ";
	}
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	sData+=s+"\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CSendCmd_HealthDlg::OnBtnSampoweron() 
{
	HANDLE hDev;
	char ATR[50]={0};
	int i=PowerOn(hDev,0x11,ATR) ; //slot 1  User; slot 0x11 SAM1
	CString temp;
	temp.Format("%s",ATR);
	if(i==0)
	{
		CString sData;
		this->GetDlgItemText(IDC_EDIT_DATA,sData);
		sData+=temp+"\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sData);
	}
	else
	{
		CString sData;
		this->GetDlgItemText(IDC_EDIT_DATA,sData);
		sData+="SAM卡上电失败!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sData);
	}
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CSendCmd_HealthDlg::OnRadioUser() 
{	
	radio=1;
}

void CSendCmd_HealthDlg::OnRadioSam() 
{
	radio=2;
}
