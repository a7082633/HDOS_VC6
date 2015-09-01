// TestDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDemo.h"
#include "TestDemoDlg.h"

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
// CTestDemoDlg dialog

CTestDemoDlg::CTestDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ELECTR, OnBtnElectr)
	ON_BN_CLICKED(IDC_BTN_PF, OnBtnPf)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_RD, OnBtnRd)
	ON_BN_CLICKED(IDC_BTN_WR, OnBtnWr)
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_TRIALT, OnBtnTrialt)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_BN_CLICKED(IDC_BTN_CT, OnBtnCt)
	ON_BN_CLICKED(IDC_BTN_RDPROTECTED, OnBtnRdprotected)
	ON_BN_CLICKED(IDC_BTN_OPENPORT, OnBtnOpenport)
	ON_BN_CLICKED(IDC_BTN_CLOSEPORT, OnBtnCloseport)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDemoDlg message handlers

BOOL CTestDemoDlg::OnInitDialog()
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

void CTestDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDemoDlg::OnPaint() 
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
HCURSOR CTestDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//typedef char (*FXN)(char*);

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
HMODULE hModule=::LoadLibrary("SSSE32.dll");
void CTestDemoDlg::OnBtnElectr() 
{
	if(hModule==NULL) this->MessageBox("load failure!");
	
	FXN3 Beep=(FXN3)::GetProcAddress(hModule,"ICC_PosBeep");//蜂鸣
	FXN4 PowerOn=(FXN4)::GetProcAddress(hModule,"ICC_Reader_4428_PowerOn");//上电

	unsigned  char data[256]={0};
	long iPon=PowerOn(hReader,data);
	if(iPon)
		this->MessageBox("上电失败");
	else
		this->MessageBox("上电成功");
	//Beep(hReader,100);
}

void CTestDemoDlg::OnBtnPf() 
{
	FXN5 PowerOff=(FXN5)::GetProcAddress(hModule,"ICC_Reader_4428_PowerOff");//下电
	long iPfn=PowerOff(hReader);
	if(iPfn)
		this->MessageBox("下电失败");
	else
		this->MessageBox("下电成功");
}

void CTestDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	FXN2 ClosePort=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close");//关闭USB
	long hReader2=ClosePort(hReader);
	FreeLibrary(hModule);
}

void CTestDemoDlg::OnBtnRd() 
{
	FXN6 Read=(FXN6)::GetProcAddress(hModule,"ICC_Reader_4428_Read");//读数据
	//FXN6 Read=(FXN6)::GetProcAddress(hModule,"ICC_Reader_4428_ReadHEX");//读数据
	unsigned  char data[1024]={0};
	CString start;
	CString size;
	this->GetDlgItemText(IDC_EDIT_RDS,start);
	this->GetDlgItemText(IDC_EDIT_RDSIZE,size);
	long lstart=_ttoi(start);
	long lsize=_ttoi(size);
	long lrn=Read(hReader,lstart,lsize,data);
	if(lrn)
	{
		this->MessageBox("读取失败");
		return;
	}
	CString sData;
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	for(int i=0;i<lsize;i++)
	{
		if(i%12==0&&i!=0) sData=sData+"\r\n";
		CString temp;
		temp.Format("%02x",int(data[i]));
		sData=sData+" "+temp;
	}
	sData=sData+"\r\n";
	sData=sData+"------------------------------";
	sData=sData+"\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CTestDemoDlg::OnBtnWr() 
{
	//FXN7 Write=(FXN7)::GetProcAddress(hModule,"ICC_Reader_4428_WriteHEX");//写数据
	//long WINAPI  StrToHex(unsigned char *strIn,int inLen,unsigned char *strOut);//将字符命令流转为16进制流
	FXN7 Write=(FXN7)::GetProcAddress(hModule,"ICC_Reader_4428_Write");//写数据
	FXNA StrToHex=(FXNA)::GetProcAddress(hModule,"StrToHex");//写数据
	// ICC_Reader_4428_ Write
	unsigned  char data[1024]={0};
	//data[0]=0xCC;
	CString start;
	CString size;
	CString sData;
	this->GetDlgItemText(IDC_EDIT_WRS,start);
	this->GetDlgItemText(IDC_EDIT_WRSIZE,size);
	this->GetDlgItemText(IDC_EDIT_WRDATA,sData);
	long lstart=_ttoi(start);
	long lsize=_ttoi(size);
	//strtoul(sData,char **endptr,16);
	//memcpy(data,sData,sData.GetLength());
	int n=StrToHex((unsigned char *)sData.GetBuffer(lsize) , sData.GetLength() , data);
	long lwn=Write(hReader,lstart,lsize,data);
	if(lwn)
		this->MessageBox("写入失败");
	else
		this->MessageBox("写入成功");

	//long WINAPI ICC_Reader_4442_WriteHEX(long ReaderHandle,int offset,int len,unsigned char *dataHex);
}

void CTestDemoDlg::OnBtnLogin() 
{
	FXN8 Login=(FXN8)::GetProcAddress(hModule,"ICC_Reader_4428_VerifyHEX");//登录
	CString sPass;
	this->GetDlgItemText(IDC_EDIT_PASS,sPass);
	unsigned  char data[256]={0};
	memcpy(data,sPass,sPass.GetLength()); 
	long ln=Login(hReader,data);
	if(ln)
		this->MessageBox("登录失败");
	else
		this->MessageBox("登录成功");
}
void CTestDemoDlg::OnBtnTrialt() 
{
	FXN9 ReadCount=(FXN9)::GetProcAddress(hModule,"ICC_Reader_4428_ReadCount");//获取剩余次数
	int n=ReadCount(hReader);
	if(n==0)
		this->MessageBox("获取失败");
	else
	{
		CString temp;
		temp.Format("%d",n);
		this->MessageBox(temp);
	}
}

void CTestDemoDlg::OnBtnModify() 
{	
}

void CTestDemoDlg::OnBtnCt() 
{
	FXN2 ReadCardType=(FXN9)::GetProcAddress(hModule,"ICC_Reader_DisCardType");//获取剩余次数
	int n=ReadCardType(hReader);
	CString s;
	s.Format("%d",n);
	this->MessageBox(s);
	//long WINAPI ICC_Reader_DisCardType(long ReaderHandle)
}

void CTestDemoDlg::OnBtnRdprotected() 
{
	FXN6 ReadProtected=(FXN6)::GetProcAddress(hModule,"ICC_Reader_4428_ReadProtect");//读数据
	//FXN6 Read=(FXN6)::GetProcAddress(hModule,"ICC_Reader_4428_ReadHEX");//读数据
	unsigned  char data[1024]={0};
	CString start;
	CString size;
	this->GetDlgItemText(IDC_EDIT_RDS,start);
	this->GetDlgItemText(IDC_EDIT_RDSIZE,size);
	long lstart=_ttoi(start);
	long lsize=_ttoi(size);
	long lrn=ReadProtected(hReader,lstart,lsize,data);
	if(lrn)
	{
		this->MessageBox("读取失败");
		return;
	}
	CString sData;
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	for(int i=0;i<lsize;i++)
	{
		if(i%12==0&&i!=0) sData=sData+"\r\n";
		CString temp;
		temp.Format("%02x",int(data[i]));
		sData=sData+" "+temp;
	}
	sData=sData+"\r\n";
	sData=sData+"------------------------------";
	sData=sData+"\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
	//long WINAPI ICC_Reader_4428_ReadProtect(long ReaderHandle,int offset,int len,unsigned char *data); //4428卡读保护数据
}

void CTestDemoDlg::OnBtnOpenport() 
{
	FXN OpenPort=(FXN)::GetProcAddress(hModule,"ICC_Reader_Open"); //打开USB
	hReader=OpenPort("USB1");	//打开 USB1 口
	if(hReader<=0)
		this->MessageBox("打开端口失败");
}

void CTestDemoDlg::OnBtnCloseport() 
{
	FXN2 ClosePort=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close");//关闭USB
	long hReader2=ClosePort(hReader);
	if(hReader2)
		this->MessageBox("关闭端口失败");
}

void CTestDemoDlg::OnBtnClear() 
{
	this->SetDlgItemText(IDC_EDIT_DATA,"");
}
