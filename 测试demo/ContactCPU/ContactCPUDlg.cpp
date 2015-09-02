// ContactCPUDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ContactCPU.h"
#include "ContactCPUDlg.h"

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
// CContactCPUDlg dialog

CContactCPUDlg::CContactCPUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CContactCPUDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CContactCPUDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CContactCPUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContactCPUDlg)
	DDX_Control(pDX, IDC_COMBO_APDU, m_cb);
	DDX_Control(pDX, IDC_COMBO_SLOT, m_slot);
	DDX_Control(pDX, IDC_COMBO_CPUPARA, m_combobox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CContactCPUDlg, CDialog)
	//{{AFX_MSG_MAP(CContactCPUDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_POWERON, OnBtnPoweron)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_SETCPUPARA, OnBtnSetcpupara)
	ON_BN_CLICKED(IDC_BTN_EXC, OnBtnExc)
	ON_BN_CLICKED(IDC_BTN_POWEROFF, OnBtnPoweroff)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_BN_CLICKED(IDC_BTN_OPENPORT, OnBtnOpenport)
	ON_BN_CLICKED(IDC_BTN_CLOSEPORT, OnBtnCloseport)
	ON_BN_CLICKED(IDC_BTN_CPOWERON, OnBtnCpoweron)
	ON_BN_CLICKED(IDC_BTN_HPOWERON, OnBtnHpoweron)
	ON_BN_CLICKED(IDC_BTN_CLA, OnBtnCla)
	ON_CBN_SELCHANGE(IDC_COMBO_APDU, OnSelchangeComboApdu)
	ON_CBN_SELENDOK(IDC_COMBO_APDU, OnSelendokComboApdu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContactCPUDlg message handlers

BOOL CContactCPUDlg::OnInitDialog()
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
	m_combobox.AddString("9600");
	m_combobox.AddString("19200");
	m_combobox.AddString("38400");
	m_combobox.AddString("115200");

	m_slot.AddString("大卡座");
	m_slot.AddString("SAM1");
	m_slot.AddString("SAM2");
	m_slot.AddString("SAM3");
	m_slot.AddString("SAM4");

	m_combobox.SetCurSel(0);
	m_slot.SetCurSel(0);




	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CContactCPUDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CContactCPUDlg::OnPaint() 
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
HCURSOR CContactCPUDlg::OnQueryDragIcon()
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
typedef int(__stdcall *FXNC)(long ,unsigned char ,unsigned char ,unsigned char);
typedef int(__stdcall *FXND)(long ,unsigned char ,unsigned char *);
typedef int(__stdcall *FXNE)(long ,unsigned char ,long ,unsigned char* ,unsigned char*);
HMODULE hModule=::LoadLibrary("SSSE32.dll");
void CContactCPUDlg::OnBtnPoweron() 
{
	unsigned char Response[50]={0};
	FXND PowerOnHEX=(FXND)::GetProcAddress(hModule,"ICC_Reader_PowerOnHEX");
	int re=0;
	re=PowerOnHEX(hReader,nSlot,Response);
	if(re<=0)
	{
		this->MessageBox("上电失败");
		return;
	}
	CString sData;
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	CString temp;
	temp.Format("ATR:%s\n",Response);
	for(int i=4;i<temp.GetLength();)
	{
		temp.Insert(i," ");
		i=i+3;
	}
	sData+=temp+"\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CContactCPUDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	FXN2 ClosePort=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close");//关闭USB
	long hReader2=ClosePort(hReader);
	FreeLibrary(hModule);
}

void CContactCPUDlg::OnClose() 
{
	::PostQuitMessage(0);
	CDialog::OnClose();
}

void CContactCPUDlg::OnBtnSetcpupara() 
{
	nCpuPara = m_combobox.GetCurSel();
	nSlot = m_slot.GetCurSel();
	//FXNC SetCpupara=(FXNC)::GetProcAddress(hModule,"ICC_SetCpupara");//设置速率
	switch(nCpuPara)
	{
	case 0:
		nCpuPara=1;
		break;
	case 1:
		nCpuPara=2;
		break;
	case 2:
		nCpuPara=3;
		break;
	case 3:
		nCpuPara=4;
		break;
	}

	switch(nSlot)
	{
	case 0:
		nSlot=0x01;
		break;
	case 1:
		nSlot=0x11;
		break;
	case 2:
		nSlot=0x12;
		break;
	case 3:
		nSlot=0x13;
		break;
	case 4:
		nSlot=0x14;
		break;
	}

	//int re=0;
	//re=SetCpupara(hReader,nSlot,0,nCpuPara);
//	if(re)
	//	this->MessageBox("设置失败");
}

void CContactCPUDlg::OnBtnExc() 
{
	FXNE SendAPDU=(FXNE)::GetProcAddress(hModule,"ICC_Reader_Application");//执行指令
	CString sAPDU;
	CString sData;
	long Lenth_of_Command_APDU=0;
	unsigned char Command_APDU[300]={0};
	unsigned char StrOut[300]={0};
	unsigned char Response_APDU[100]={0};
	this->GetDlgItemText(IDC_EDIT_APDU,sAPDU);
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	sData+="执行命令:"+sAPDU+"\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	//sAPDU.Replace(' ', NULL);
	int n=0;
	while(-1!=(n=sAPDU.FindOneOf(" ")))
	{
		sAPDU.Delete(n);
	}
	Lenth_of_Command_APDU=sAPDU.GetLength()/2;
	FXNA StrToHex=(FXNA)::GetProcAddress(hModule,"StrToHex");//转换
	StrToHex((unsigned char*)sAPDU.GetBuffer(sAPDU.GetLength()) , sAPDU.GetLength() , StrOut);//将字符命令流转为16进制流
	int re=SendAPDU(hReader,nSlot,Lenth_of_Command_APDU,StrOut,Response_APDU);//0084000004
	if(re<=0)
	{
		this->GetDlgItemText(IDC_EDIT_DATA,sData);
		sData+="指令执行失败!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sData);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
		return;
	}
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
	this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
}

void CContactCPUDlg::OnBtnPoweroff() 
{
	FXN3 PowerOff=(FXN3)::GetProcAddress(hModule,"ICC_Reader_PowerOff");//执行指令
	int re=PowerOff(hReader,nSlot);
	if(re)
		this->MessageBox("下电失败");
}

void CContactCPUDlg::OnBtnClear() 
{
	this->SetDlgItemText(IDC_EDIT_DATA,"");
}

void CContactCPUDlg::OnBtnOpenport() 
{
	FXN OpenPort=(FXN)::GetProcAddress(hModule,"ICC_Reader_Open"); //打开USB
	hReader=OpenPort("USB1");	//打开 USB1 口
	if(hReader<=0)
		this->MessageBox("打开端口失败");
}

void CContactCPUDlg::OnBtnCloseport() 
{
	FXN2 ClosePort=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close");//关闭USB
	long hReader2=ClosePort(hReader);
	if(hReader2)
		this->MessageBox("关闭端口失败");
}

void CContactCPUDlg::OnBtnCpoweron() 
{
	unsigned char Response[50]={0};
	FXND PowerOnHEX=(FXND)::GetProcAddress(hModule,"ICC_Reader_pre_PowerOn");
	int re=0;
	re=PowerOnHEX(hReader,nSlot,Response);
	if(re<=0)
	{
		this->MessageBox("上电失败");
		return;
	}
	CString sData;
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	sData+="ATR:";
	CString temp;
	for(int i=0;i<17;i++)
	{
		temp.Format("%02x ",Response[i]);
		sData+=temp;
	}
	sData+="\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CContactCPUDlg::OnBtnHpoweron() 
{
	unsigned char Response[50]={0};
	FXND PowerOnHEX=(FXND)::GetProcAddress(hModule,"ICC_Reader_hot_PowerOn");
	int re=0;
	re=PowerOnHEX(hReader,nSlot,Response);
	if(re<=0)
	{
		this->MessageBox("上电失败");
		return;
	}
	CString sData;
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	sData+="ATR:";
	CString temp;
	for(int i=0;i<17;i++)
	{
		temp.Format("%02x ",Response[i]);
		sData+=temp;
	}
	sData+="\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CContactCPUDlg::OnBtnCla() 
{
	this->SetDlgItemText(IDC_EDIT_APDU,"");
	this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
}


void CContactCPUDlg::OnSelchangeComboApdu() 
{
	CString sApdu;
	this->m_cb.GetLBText(m_cb.GetCurSel(),sApdu);
	this->SetDlgItemText(IDC_EDIT_APDU,sApdu);
	this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
}

void CContactCPUDlg::OnSelendokComboApdu() 
{
//	CString sApdu;
//	this->GetDlgItemText(IDC_COMBO_APDU,sApdu);
//	this->SetDlgItemText(IDC_EDIT_APDU,sApdu);
//	this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
}
