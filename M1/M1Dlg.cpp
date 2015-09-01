// M1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "M1.h"
#include "M1Dlg.h"
#include "DialogLoadKey.h"
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
// CM1Dlg dialog

CM1Dlg::CM1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CM1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CM1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CM1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CM1Dlg, CDialog)
	//{{AFX_MSG_MAP(CM1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RQE, OnBtnRqe)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_RA, OnBtnRa)
	ON_BN_CLICKED(IDC_BTN_RA2, OnBtnRa2)
	ON_BN_CLICKED(IDC_BTN_RA3, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_WRITEHEX, OnBtnWritehex)
	ON_BN_CLICKED(IDC_BTN_INITIAL, OnBtnInitial)
	ON_BN_CLICKED(IDC_BTN_INCREMENT, OnBtnIncrement)
	ON_BN_CLICKED(IDC_BTN_DESCMENT, OnBtnDescment)
	ON_BN_CLICKED(IDC_BTN_READVAL, OnBtnReadval)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_BN_CLICKED(IDC_BTN_RASTR, OnBtnRastr)
	ON_BN_CLICKED(IDC_BTN_WRITESTR, OnBtnWritestr)
	ON_BN_CLICKED(IDC_BTN_RAALL, OnBtnRaall)
	ON_BN_CLICKED(IDC_BTN_LOADKEY, OnBtnLoadkey)
	ON_BN_CLICKED(IDC_BTN_OPENPORT, OnBtnOpenport)
	ON_BN_CLICKED(IDC_BTN_CLOSEPORT, OnBtnCloseport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CM1Dlg message handlers

BOOL CM1Dlg::OnInitDialog()
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
	this->SetDlgItemText(IDC_EDIT_SN,"0");
	this->SetDlgItemText(IDC_EDIT_PASS,"FFFFFFFFFFFF");
	this->SetDlgItemText(IDC_EDIT_WRITEDATA,"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFAA");
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_KEYA);
	radio->SetCheck(1);
	CEdit *edit=(CEdit *)GetDlgItem(IDC_EDIT_PASS);
	edit->SetLimitText(12);
	hModule=::LoadLibrary("SSSE32.dll");
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CM1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CM1Dlg::OnPaint() 
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
HCURSOR CM1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
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
typedef int(__stdcall *FXNB)(long , unsigned char , unsigned char);
typedef int(__stdcall *FXNC)(long , unsigned char , unsigned char,unsigned char *);
typedef int(__stdcall *FXND)(long , unsigned char , unsigned char *);
typedef int(__stdcall *FXNE)(long , unsigned char , unsigned long);
typedef int(__stdcall *FXNF)(long , unsigned char ,unsigned long *);
void CM1Dlg::OnBtnRqe() 
{
	if(hModule==NULL) this->MessageBox("load failure!");
	FXN2 ReaderRequest=(FXN2)::GetProcAddress(hModule,"PICC_Reader_Request"); //请求卡片
	long rrn=ReaderRequest(hReader);
	if(rrn)
	{
		this->MessageBox("请求卡片失败");
		return;
	}
	FXN4 ReaderAnticoll=(FXN4)::GetProcAddress(hModule,"PICC_Reader_anticoll"); //防碰撞
	unsigned char uid[10]={0};
	int re =ReaderAnticoll(hReader,uid);
	if(re)
	{
		this->MessageBox("防碰撞失败");
		return;
	}
	FXN3 ReaderSelect=(FXN3)::GetProcAddress(hModule,"PICC_Reader_Select"); //选择卡片
	int rs=ReaderSelect(hReader,0x41);
	if(rs)
	{
		this->MessageBox("选卡失败");
		return;
	}

	CString temp;
	for(int i=0;uid[i]!=0;i++)
	{
		CString s;
		if(i==0) s.Format("UID:%02x",(int)uid[i]);
		else s.Format("%02x",(int)uid[i]);
		temp=temp+" "+s;
	}
	CString sData;
	this->GetDlgItemText(IDC_EDIT_DATA,sData);
	sData+=temp+"\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sData);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());

}

void CM1Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	FXN2 ClosePort=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close");//关闭USB
	long hReader2=ClosePort(hReader);
	FreeLibrary(hModule);	
}

void CM1Dlg::OnBtnRa() 
{

	InitialReader();
//=====================
	if((0==((CButton *)GetDlgItem(IDC_RADIO_KEYA))->GetCheck())&&(0==((CButton *)GetDlgItem(IDC_RADIO_KEYB))->GetCheck()))
	{
		this->MessageBox("未选中");
		return;
	}
	CString SecNr;
	this->GetDlgItemText(IDC_EDIT_SN,SecNr);
	int iSecNr=_ttoi(SecNr);
	int re=0;
	if(1==((CButton *)GetDlgItem(IDC_RADIO_KEYA))->GetCheck())
	{
		FXNB ReadAuth=(FXNB)::GetProcAddress(hModule,"PICC_Reader_Authentication");//密钥认证1
		re=ReadAuth(hReader,0,iSecNr);
	}else
	{
		FXNB ReadAuth=(FXNB)::GetProcAddress(hModule,"PICC_Reader_Authentication");//密钥认证1
		re=ReadAuth(hReader,4,iSecNr);
	}
	if(re)
		this->MessageBox("存储密钥认证失败");
}

void CM1Dlg::OnBtnRa2() 
{
	InitialReader();
	FXNA StrToHex=(FXNA)::GetProcAddress(hModule,"StrToHex");//数据转换
	CString SecNr;
	this->GetDlgItemText(IDC_EDIT_SN,SecNr);
	int iSecNr=_ttoi(SecNr);
	int re=0;
	if(1==((CButton *)GetDlgItem(IDC_RADIO_KEYA))->GetCheck())
	{
		unsigned char key[10]={0};
		FXNC ReadAuth=(FXNC)::GetProcAddress(hModule,"PICC_Reader_Authentication_Pass");//密钥认证2
		CString sPass;
		this->GetDlgItemText(IDC_EDIT_PASS,sPass);
		int n=StrToHex((unsigned char *)sPass.GetBuffer(sPass.GetLength()) , sPass.GetLength() , key);
		re=ReadAuth(hReader,0x60,iSecNr,key);
	}else
	{
		unsigned char key[10]={0};
		FXNC ReadAuth=(FXNC)::GetProcAddress(hModule,"PICC_Reader_Authentication_Pass");//密钥认证2
		CString sPass;
		this->GetDlgItemText(IDC_EDIT_PASS,sPass);
		int n=StrToHex((unsigned char *)sPass.GetBuffer(sPass.GetLength()) , sPass.GetLength() , key);
		re=ReadAuth(hReader,0x61,iSecNr,key);
	}
	if(re)
		this->MessageBox("存储密钥认证失败");
}

int CM1Dlg::InitialReader()
{
	FXN2 ReaderRequest=(FXN2)::GetProcAddress(hModule,"PICC_Reader_Request"); //请求卡片
	long rrn=ReaderRequest(hReader);
	if(rrn)
	{
		return -1;
	}
	FXN4 ReaderAnticoll=(FXN4)::GetProcAddress(hModule,"PICC_Reader_anticoll"); //防碰撞
	unsigned char uid[10]={0};
	int re2 =ReaderAnticoll(hReader,uid);
	if(re2)
	{
		return -1;
	}
	FXN3 ReaderSelect=(FXN3)::GetProcAddress(hModule,"PICC_Reader_Select"); //选择卡片
	int rs=ReaderSelect(hReader,0x41);
	if(rs)
	{
		return -1;
	}
	return 0;
}

void CM1Dlg::OnBtnRead() 
{
	if(InitialReader())
	{
		this->MessageBox("初始化失败");
		return;
	}
	CString sBlockNr;
	this->GetDlgItemText(IDC_EDIT_BLOCKN,sBlockNr);
	int iBlockNr=_ttoi(sBlockNr);
	int iSecNr=(iBlockNr)/4;
	int re=0;
	if(Authentication(iSecNr))
	{
		this->MessageBox("密钥认证失败");
		return;
	}
	unsigned char datahex[40]={0};
	FXND ReaderReadHex=(FXND)::GetProcAddress(hModule,"PICC_Reader_ReadHEX");
	re = ReaderReadHex(hReader,iBlockNr,datahex);//读取第n块数据
	if(re)
	{
		this->MessageBox("读取失败");
		return;
	}
	CString data;
	CString temp;
	temp.Format("block%02d:",iBlockNr);
	this->GetDlgItemText(IDC_EDIT_DATA,data);
	data+=temp;;
	data+=datahex;
	data+="\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,data);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

int CM1Dlg::Authentication(int iSecNr)
{
	int re=0;
	FXNA StrToHex=(FXNA)::GetProcAddress(hModule,"StrToHex");//数据转换
	if(1==((CButton *)GetDlgItem(IDC_RADIO_KEYA))->GetCheck())
	{
		unsigned char key[10]={0};
		FXNC ReadAuth=(FXNC)::GetProcAddress(hModule,"PICC_Reader_Authentication_Pass");//密钥认证2
		CString sPass;
		this->GetDlgItemText(IDC_EDIT_PASS,sPass);
		int n=StrToHex((unsigned char *)sPass.GetBuffer(sPass.GetLength()) , sPass.GetLength() , key);
		re=ReadAuth(hReader,0x60,iSecNr,key);
	}else
	{
		unsigned char key[10]={0};
		FXNC ReadAuth=(FXNC)::GetProcAddress(hModule,"PICC_Reader_Authentication_Pass");//密钥认证2
		CString sPass;
		this->GetDlgItemText(IDC_EDIT_PASS,sPass);
		int n=StrToHex((unsigned char *)sPass.GetBuffer(sPass.GetLength()) , sPass.GetLength() , key);
		re=ReadAuth(hReader,0x61,iSecNr,key);
	}
	return re;
}

void CM1Dlg::OnBtnWritehex() 
{
//	if(InitialReader())
//	{
//		this->MessageBox("初始化失败");
//		return;
//	}
	CString sBlockNr;
	this->GetDlgItemText(IDC_EDIT_BLOCKN,sBlockNr);
	int iBlockNr=_ttoi(sBlockNr);
	int iSecNr=(iBlockNr)/4;
	int re=0;
	if(Authentication(iSecNr))
	{
		this->MessageBox("密钥认证失败");
		return;
	}

	CString temp;
	this->GetDlgItemText(IDC_EDIT_WRITEDATA,temp);
	if(temp.GetLength()!=32)
	{
		this->MessageBox("数据格式不正确");
		return;
	}
	unsigned char datahex[40]={0};
	memcpy(datahex,temp,temp.GetLength());
	FXND ReaderWriteHex=(FXND)::GetProcAddress(hModule,"PICC_Reader_WriteHEX");
	re = ReaderWriteHex(hReader,iBlockNr,datahex);//读取第n块数据
	if(re)
	{
		this->MessageBox("写入失败");
		return;
	}
}

void CM1Dlg::OnBtnInitial() 
{
//	if(InitialReader())
//	{
//		this->MessageBox("初始化失败");
//		return;
//	}
	CString sBlockNr;
	this->GetDlgItemText(IDC_EDIT_BLOCKN,sBlockNr);
	int iBlockNr=_ttoi(sBlockNr);
	int iSecNr=(iBlockNr)/4;
	int re=0;
	if(Authentication(iSecNr))
	{
		this->MessageBox("密钥认证失败");
		return;
	}

	CString sValue;
	this->GetDlgItemText(IDC_EDIT_VALUE,sValue);
	int iValue=_ttoi(sValue);
	FXNE ReaderInitial=(FXNE)::GetProcAddress(hModule,"PICC_Reader_Initval");
	re = ReaderInitial(hReader,iBlockNr,iValue);//初始化
}

void CM1Dlg::OnBtnIncrement() 
{
	if(InitialReader())
	{
		this->MessageBox("初始化失败");
		return;
	}
	CString sBlockNr;
	this->GetDlgItemText(IDC_EDIT_BLOCKN,sBlockNr);
	int iBlockNr=_ttoi(sBlockNr);
	int iSecNr=(iBlockNr)/4;
	int re=0;
	if(Authentication(iSecNr))
	{
		this->MessageBox("密钥认证失败");
		return;
	}

	CString sValue;
	this->GetDlgItemText(IDC_EDIT_VALUE,sValue);
	int iValue=_ttoi(sValue);
	FXNE ReaderIncrement=(FXNE)::GetProcAddress(hModule,"PICC_Reader_Increment");
	re = ReaderIncrement(hReader,iBlockNr,iValue);//初始化
	if(re)
	{
		CString temp;
		temp.Format("增值错误，代码:%d",re);
		this->MessageBox(temp);
	}
}

void CM1Dlg::OnBtnDescment() 
{
	if(InitialReader())
	{
		this->MessageBox("初始化失败");
		return;
	}
	CString sBlockNr;
	this->GetDlgItemText(IDC_EDIT_BLOCKN,sBlockNr);
	int iBlockNr=_ttoi(sBlockNr);
	int iSecNr=(iBlockNr)/4;
	int re=0;
	if(Authentication(iSecNr))
	{
		this->MessageBox("密钥认证失败");
		return;
	}

	CString sValue;
	this->GetDlgItemText(IDC_EDIT_VALUE,sValue);
	int iValue=_ttoi(sValue);
	FXNE ReaderDecrement=(FXNE)::GetProcAddress(hModule,"PICC_Reader_Decrement");
	re = ReaderDecrement(hReader,iBlockNr,iValue);//初始化
	if(re)
	{
		CString temp;
		temp.Format("减值错误，代码:%d",re);
		this->MessageBox(temp);
	}
}

void CM1Dlg::OnBtnReadval() 
{
	if(InitialReader())
	{
		this->MessageBox("初始化失败");
		return;
	}
	CString sBlockNr;
	this->GetDlgItemText(IDC_EDIT_BLOCKN,sBlockNr);
	int iBlockNr=_ttoi(sBlockNr);
	int iSecNr=(iBlockNr)/4;
	int re=0;
	if(Authentication(iSecNr))
	{
		this->MessageBox("密钥认证失败");
		return;
	}

	CString sValue;
	unsigned long value;
	int iValue=_ttoi(sValue);
	FXNF ReaderReadVal=(FXNF)::GetProcAddress(hModule,"PICC_Reader_Readval");
	re = ReaderReadVal(hReader,iBlockNr,&value);//初始化
	if(re)
	{
		CString temp;
		temp.Format("减值错误，代码:%d",re);
		this->MessageBox(temp);
	}
	CString data;
	this->GetDlgItemText(IDC_EDIT_DATA,data);
	CString temp;
	temp.Format("第%d的数值为:%d\n",iBlockNr,value);
	data+="\r\n";
	data+=temp;
	this->SetDlgItemText(IDC_EDIT_DATA,data);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CM1Dlg::OnBtnClear() 
{
	this->SetDlgItemText(IDC_EDIT_DATA,"");
}

void CM1Dlg::OnBtnRastr() 
{
	if(InitialReader())
	{
		this->MessageBox("初始化失败");
		return;
	}
	CString sBlockNr;
	this->GetDlgItemText(IDC_EDIT_BLOCKN,sBlockNr);
	int iBlockNr=_ttoi(sBlockNr);
	int iSecNr=(iBlockNr)/4;
	int re=0;
	if(Authentication(iSecNr))
	{
		this->MessageBox("密钥认证失败");
		return;
	}
	unsigned char datahex[40]={0};
	FXND ReaderRead=(FXND)::GetProcAddress(hModule,"PICC_Reader_Read");
	re = ReaderRead(hReader,iBlockNr,datahex);//读取第n块数据
	if(re)
	{
		this->MessageBox("读取失败");
		return;
	}
	CString data;
	CString temp;
	temp.Format("block%02d:",iBlockNr);
	this->GetDlgItemText(IDC_EDIT_DATA,data);
	data+=temp;;
	data+=datahex;
	data+="\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,data);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CM1Dlg::OnBtnWritestr() 
{
//	if(InitialReader())
//	{
//		this->MessageBox("初始化失败");
//		return;
//	}
	CString sBlockNr;
	this->GetDlgItemText(IDC_EDIT_BLOCKN,sBlockNr);
	int iBlockNr=_ttoi(sBlockNr);
	int iSecNr=(iBlockNr)/4;
	int re=0;
	if(Authentication(iSecNr))
	{
		this->MessageBox("密钥认证失败");
		return;
	}

	CString temp;
	this->GetDlgItemText(IDC_EDIT_WRITEDATA,temp);
	if(temp.GetLength()>16)
	{
		this->MessageBox("数据格式不正确");
		return;
	}
	FXND ReaderWrite=(FXND)::GetProcAddress(hModule,"PICC_Reader_Write");
	re = ReaderWrite(hReader,iBlockNr,(unsigned char *)temp.GetBuffer(temp.GetLength()));//读取第n块数据
	if(re)
	{
		this->MessageBox("写入失败");
		return;
	}
}

void CM1Dlg::OnBtnRaall() 
{
	CString data;
	CString temp;
	for(int iBlockNr=0;iBlockNr<=63;iBlockNr++)
	{
		this->GetDlgItemText(IDC_EDIT_DATA,data);
		if(InitialReader())
		{
			temp.Format("block%02d:",iBlockNr);
			data+=temp;
			data+="初始化失败";
			data+="\r\n";
			this->SetDlgItemText(IDC_EDIT_DATA,data);
			continue;
		}
		int iSecNr=(iBlockNr)/4;
		int re=0;
		if(Authentication(iSecNr))
		{
			temp.Format("block%02d:",iBlockNr);
			data+=temp;
			data+="密钥认证失败";
			data+="\r\n";
			this->SetDlgItemText(IDC_EDIT_DATA,data);
			continue;
		}
		unsigned char datahex[40]={0};
		FXND ReaderReadHex=(FXND)::GetProcAddress(hModule,"PICC_Reader_ReadHEX");
		re = ReaderReadHex(hReader,iBlockNr,datahex);//读取第n块数据
		if(re)
		{
			temp.Format("block%02d:",iBlockNr);
			data+=temp;
			data+="读取失败";
			data+="\r\n";
			this->SetDlgItemText(IDC_EDIT_DATA,data);
			continue;
		}
		CString temp;
		temp.Format("block%02d:",iBlockNr);
		this->GetDlgItemText(IDC_EDIT_DATA,data);
		data+=temp;;
		data+=datahex;
		data+="\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,data);
	}
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CM1Dlg::OnBtnLoadkey() 
{
	CDialogLoadKey dlg;
	dlg.hReader=hReader;
	dlg.hModule=hModule;
	dlg.DoModal();
}


void CM1Dlg::OnBtnOpenport() 
{
	FXN OpenPort=(FXN)::GetProcAddress(hModule,"ICC_Reader_Open"); //打开USB
	hReader=OpenPort("USB1");	//打开 USB1 口
	if(hReader<=0)
		this->MessageBox("打开端口失败");
}

void CM1Dlg::OnBtnCloseport() 
{
	FXN2 ClosePort=(FXN2)::GetProcAddress(hModule,"ICC_Reader_Close");//关闭USB
	long hReader2=ClosePort(hReader);
	if(hReader2)
		this->MessageBox("关闭端口失败");
}
