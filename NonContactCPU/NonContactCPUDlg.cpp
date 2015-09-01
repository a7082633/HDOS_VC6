// NonContactCPUDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NonContactCPU.h"
#include "NonContactCPUDlg.h"

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
// CNonContactCPUDlg dialog

CNonContactCPUDlg::CNonContactCPUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNonContactCPUDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNonContactCPUDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNonContactCPUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNonContactCPUDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNonContactCPUDlg, CDialog)
	//{{AFX_MSG_MAP(CNonContactCPUDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK_POWER_ON, OnPowerOn)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK_BTN_EXC, OnBtnExc)
	ON_BN_CLICKED(IDC_BTN_OPENPORT, OnBtnOpenport)
	ON_BN_CLICKED(IDC_BTN_CLOSEPORT, OnBtnCloseport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNonContactCPUDlg message handlers

BOOL CNonContactCPUDlg::OnInitDialog()
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

	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_A);
	radio->SetCheck(1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNonContactCPUDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNonContactCPUDlg::OnPaint() 
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
HCURSOR CNonContactCPUDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
#pragma comment(lib,"SSSE32.lib") 
typedef int(__stdcall *FXN)(char*);
typedef int(__stdcall *FXN2)(long);
typedef int(__stdcall *FXN3)(long,unsigned char);
typedef int(__stdcall *FXN4)(long,unsigned char*);
typedef int(__stdcall *FXN5)(long);
typedef int(__stdcall *FXN6)(long,int,int,unsigned char *);
typedef int(__stdcall *FXN7)(long,int,int,unsigned char *);
typedef int(__stdcall *FXN8)(long,unsigned char *);
typedef int(__stdcall *FXN9)(long);
typedef int(__stdcall *FXNA)(unsigned char *,int,unsigned char *);
typedef int(__stdcall *FXNB)(long ,long ,unsigned char* ,unsigned char* );
HMODULE hModule=::LoadLibrary("SSSE32.dll");
void CNonContactCPUDlg::OnPowerOn() 
{
	if(hModule==NULL) this->MessageBox("load failure!");
	FXN3 Beep=(FXN3)::GetProcAddress(hModule,"ICC_PosBeep");//蜂鸣
	FXN4 PowerOnA=(FXN4)::GetProcAddress(hModule,"PICC_Reader_PowerOnTypeA");//上电A
	FXN4 PowerOnB=(FXN4)::GetProcAddress(hModule,"PICC_Reader_PowerOnTypeB");//上电B
	FXN2 SetTypeA=(FXN2)::GetProcAddress(hModule,"PICC_Reader_SetTypeA");//上电A
	FXN2 SetTypeB=(FXN2)::GetProcAddress(hModule,"PICC_Reader_SetTypeB");//上电B

	unsigned char Respons[30]={0};
	int re=0;

	if(1==((CButton *)GetDlgItem(IDC_RADIO_A))->GetCheck())
	{
		SetTypeA(hReader);//设置读卡A

		FXN2 ReaderRequest=(FXN2)::GetProcAddress(hModule,"PICC_Reader_Request"); //请求卡片
		re=ReaderRequest(hReader);
		if(re)
		{
			this->MessageBox("请求卡片失败");
			return;
		}

		FXN4 ReaderAnticoll=(FXN4)::GetProcAddress(hModule,"PICC_Reader_anticoll"); //防碰撞
		unsigned char uid[10]={0};
		re =ReaderAnticoll(hReader,uid);
		if(re)
		{
			this->MessageBox("防碰撞失败");
			return;
		}

		FXN3 ReaderSelect=(FXN3)::GetProcAddress(hModule,"PICC_Reader_Select"); //选择卡片
		re=ReaderSelect(hReader,0x41);
		if(re)
		{
			this->MessageBox("选卡失败");
			return;
		}

		re=PowerOnA(hReader,Respons);
		if(re<=0)
		{
			this->MessageBox("上电失败!");
			return;
		}
	}else
	{
		SetTypeB(hReader);
		re=PowerOnB(hReader,Respons);
		if(re<=0)
		{
			this->MessageBox("上电失败!");
			return;
		}
		FXN3 ReaderSelect=(FXN3)::GetProcAddress(hModule,"PICC_Reader_Select"); //选择卡片
		re=ReaderSelect(hReader,0x41);
		if(re)
		{
			this->MessageBox("选卡失败");
			return;
		}
	}
	unsigned char StrOut[30]={0};
	CString sData;
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	CString temp;
	for(int i=0;Respons[i]!=0;i++)
	{
		CString temp;
		if(i==0)
			temp.Format("ATR:%02x",(int)Respons[i]);
		else
			temp.Format("%02x",(int)Respons[i]);
		sData=sData+temp+" ";
	}
	sData+="\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CNonContactCPUDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	FXN2 ClosePort=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close");//关闭USB
	long hReader2=ClosePort(hReader);
	FreeLibrary(hModule);	
}

void CNonContactCPUDlg::OnClose() 
{	
	::PostQuitMessage(0);
	CDialog::OnClose();
}

void CNonContactCPUDlg::InitialA()
{
		FXN2 SetTypeA=(FXN2)::GetProcAddress(hModule,"PICC_Reader_SetTypeA");//上电A
		FXN4 PowerOnA=(FXN4)::GetProcAddress(hModule,"PICC_Reader_PowerOnTypeA");//上电A
		SetTypeA(hReader);//设置读卡A
		int re=0;
		FXN2 ReaderRequest=(FXN2)::GetProcAddress(hModule,"PICC_Reader_Request"); //请求卡片
		re=ReaderRequest(hReader);
		if(re)
		{
			this->MessageBox("请求卡片失败");
			return;
		}

		FXN4 ReaderAnticoll=(FXN4)::GetProcAddress(hModule,"PICC_Reader_anticoll"); //防碰撞
		unsigned char uid[10]={0};
		re =ReaderAnticoll(hReader,uid);
		if(re)
		{
			this->MessageBox("防碰撞失败");
			return;
		}

		FXN3 ReaderSelect=(FXN3)::GetProcAddress(hModule,"PICC_Reader_Select"); //选择卡片
		re=ReaderSelect(hReader,0x41);
		if(re)
		{
			this->MessageBox("选卡失败");
			return;
		}

		unsigned char Respons[30]={0};
		re=PowerOnA(hReader,Respons);
		if(re<=0)
		{
			this->MessageBox("上电失败!");
			return;
		}
}

void CNonContactCPUDlg::OnBtnExc() 
{
	//long WINAPI PICC_Reader_Application(long ReaderHandle,long Lenth_of_Command_APDU,unsigned char* Command_APDU,unsigned char* Response_APDU);
	int re=0;
	FXNB SendAPDU=(FXNB)::GetProcAddress(hModule,"PICC_Reader_Application");//执行APDU
	CString sAPDU;
	long Lenth_of_Command_APDU=0;
	unsigned char Command_APDU[100]={0};
	unsigned char StrOut[100]={0};
	unsigned char Response_APDU[100]={0};
	this->GetDlgItemText(IDC_EDIT_APDU,sAPDU);
	Lenth_of_Command_APDU=sAPDU.GetLength()/2;
	FXNA StrToHex=(FXNA)::GetProcAddress(hModule,"StrToHex");//转换
	StrToHex((unsigned char*)sAPDU.GetBuffer(sAPDU.GetLength()) , sAPDU.GetLength() , StrOut);//将字符命令流转为16进制流
	re=SendAPDU(hReader,Lenth_of_Command_APDU,StrOut,Response_APDU);//0084000004
	if(re<=0)
	{
		this->MessageBox("指令执行失败!");
		return;
	}

	CString sData;
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	CString temp;
	for(int i=0;i<re;i++)
	{
		CString temp;
		if(i==0)
			temp.Format("返回信息:%02x",(int)Response_APDU[i]);
		else
			temp.Format("%02x",(int)Response_APDU[i]);
		sData=sData+temp+" ";
	}
	sData+="\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CNonContactCPUDlg::InitialB()
{
	FXN2 SetTypeB=(FXN2)::GetProcAddress(hModule,"PICC_Reader_SetTypeB");//上电B
	FXN4 PowerOnB=(FXN4)::GetProcAddress(hModule,"PICC_Reader_PowerOnTypeB");//上电B
	SetTypeB(hReader);
	unsigned char Respons[30]={0};
	int re=PowerOnB(hReader,Respons);
	if(re<=0)
	{
		this->MessageBox("上电失败!");
		return;
	}
	FXN3 ReaderSelect=(FXN3)::GetProcAddress(hModule,"PICC_Reader_Select"); //选择卡片
	re=ReaderSelect(hReader,0x41);
	if(re)
	{
		this->MessageBox("选卡失败");
		return;
	}
}

void CNonContactCPUDlg::OnBtnOpenport() 
{
	FXN OpenPort=(FXN)::GetProcAddress(hModule,"ICC_Reader_Open"); //打开USB
	hReader=OpenPort("USB1");	//打开 USB1 口
	if(hReader<=0)
		this->MessageBox("打开端口失败");
}

void CNonContactCPUDlg::OnBtnCloseport() 
{
	FXN2 ClosePort=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close");//关闭USB
	long hReader2=ClosePort(hReader);
	if(hReader2)
		this->MessageBox("关闭端口失败");
}
