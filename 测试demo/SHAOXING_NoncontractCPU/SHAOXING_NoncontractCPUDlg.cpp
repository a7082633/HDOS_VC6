// SHAOXING_NoncontractCPUDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SHAOXING_NoncontractCPU.h"
#include "SHAOXING_NoncontractCPUDlg.h"

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
// CSHAOXING_NoncontractCPUDlg dialog

CSHAOXING_NoncontractCPUDlg::CSHAOXING_NoncontractCPUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSHAOXING_NoncontractCPUDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSHAOXING_NoncontractCPUDlg)
	m_data = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSHAOXING_NoncontractCPUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSHAOXING_NoncontractCPUDlg)
	DDX_Control(pDX, IDC_COMBO_NTYPE, m_comboNType);
	DDX_Control(pDX, IDC_COMBO_NRWORKKEY, m_comboNRWorkKey);
	DDX_Control(pDX, IDC_COMBO_NRMAINKEY, m_comboNrMainKey);
	DDX_Control(pDX, IDC_COMBO_KEYLEN, m_comboKeyLen);
	DDX_Text(pDX, IDC_EDIT_DATA, m_data);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSHAOXING_NoncontractCPUDlg, CDialog)
	//{{AFX_MSG_MAP(CSHAOXING_NoncontractCPUDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN_PORT, OnBtnOpenPort)
	ON_BN_CLICKED(IDC_BTN_CLOSE_PORT, OnBtnClosePort)
	ON_BN_CLICKED(IDC_BTN_FIND_CARD, OnBtnFindCard)
	ON_BN_CLICKED(IDC_BTN_CARD_RESET, OnBtnCardReset)
	ON_BN_CLICKED(IDC_BTN_EXC_APDU, OnBtnExcApdu)
	ON_BN_CLICKED(IDC_BTN_OPENKEYBOARD, OnBtnOpenkeyboard)
	ON_BN_CLICKED(IDC_BTN_CLOSEBOARD, OnBtnCloseboard)
	ON_BN_CLICKED(IDC_BTN_DL_MAINKEY, OnBtnDlMainkey)
	ON_BN_CLICKED(IDC_BTN_DL_WORKKEY, OnBtnDlWorkkey)
	ON_BN_CLICKED(IDC_BTN_ACTIVEKEY, OnBtnActivekey)
	ON_BN_CLICKED(IDC_BTN_SET_KEYLEN, OnBtnSetKeylen)
	ON_BN_CLICKED(IDC_BTN_GETPIN, OnBtnGetpin)
	ON_BN_CLICKED(IDC_BTN_GETNPIN, OnBtnGetnpin)
	ON_BN_CLICKED(IDC_BTN_NKEY, OnBtnNkey)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSHAOXING_NoncontractCPUDlg message handlers

BOOL CSHAOXING_NoncontractCPUDlg::OnInitDialog()
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
	//hModule=::LoadLibrary("SSSE32.dll");
	m_comboNRWorkKey.SetCurSel(0);
	m_comboNrMainKey.SetCurSel(0);
	m_comboKeyLen.SetCurSel(0);
	m_comboNType.SetCurSel(0);
	m_comboNType.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSHAOXING_NoncontractCPUDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSHAOXING_NoncontractCPUDlg::OnPaint() 
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
HCURSOR CSHAOXING_NoncontractCPUDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSHAOXING_NoncontractCPUDlg::OnBtnOpenPort() 
{
	hDev=st_init(100,9600);
	if(hDev>0)
	{
		this->UpdateData();
		m_data+="端口打开成功";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
	}else
	{
		this->UpdateData();
		m_data+="端口打开失败";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnClosePort() 
{
	int re=st_exit(hDev); 
	if(re==0)
	{
		this->UpdateData();
		m_data+="端口关闭成功";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
	}else
	{
		this->UpdateData();
		m_data+="端口关闭失败";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnFindCard() 
{
	unsigned long TagType[20]={0};//36
	char Num[50]={0};//36
	int re=st_card(hDev,0,TagType);
	if(re!=0)
	{
		this->UpdateData();
		m_data+="寻卡失败";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
		return;
	}
	memcpy(Num,TagType,36);
	CString temp;
	temp.Format("%s",Num);
	for(int i=2;i<temp.GetLength();)
	{
		temp.Insert(i," ");
		i=i+3;
	}
	this->UpdateData();
	m_data+="卡序列号:";
	m_data+=temp;
	m_data+="\r\n";
	this->UpdateData(FALSE);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
	this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
}

void CSHAOXING_NoncontractCPUDlg::OnBtnCardReset() 
{
	unsigned char rlen[20]={0};
	unsigned char rbuff[50]={0};
	int re=st_pro_reset(hDev,rlen,rbuff); 
	if(re!=0)
	{
		this->UpdateData();
		m_data+="复位失败";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return;
	}
	this->UpdateData();
	m_data+="ATR:";
	m_data+=rbuff;
	m_data+="\r\n";
	this->UpdateData(FALSE);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}
//typedef long(__stdcall *FXN)(unsigned char *,int,unsigned char *);
void CSHAOXING_NoncontractCPUDlg::OnBtnExcApdu() 
{
	CString sAPDU;
	this->GetDlgItemText(IDC_EDIT_APDU,sAPDU);
	int n=0;
	while(-1!=(n=sAPDU.FindOneOf(" ")))
	{
		sAPDU.Delete(n);
	}
	unsigned char APDU[200]={0};
	//FXN StrToHex=(FXN)::GetProcAddress(hModule,"StrToHex"); 
	StrToHex((unsigned char *)sAPDU.GetBuffer(0),sAPDU.GetLength(),APDU);
	unsigned char rlen=50;
	unsigned char rbuff[500]={0};
	unsigned char slen=sAPDU.GetLength();
	int re=st_pro_command (hDev,slen,(unsigned char *)sAPDU.GetBuffer(0),&rlen,rbuff);
	if(re!=0)
	{
		this->UpdateData();
		m_data+="指令执行失败";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();
		return;
	}

	this->UpdateData();
	m_data+="发送指令:";
	m_data+=sAPDU;
	m_data+="\r\n";
	this->UpdateData(FALSE);


	//FXN HexToStr=(FXN)::GetProcAddress(hModule,"HexToStr");
	unsigned char rbuff2[500]={0};
	HexToStr(rbuff,rlen,rbuff2);

	CString temp;
	temp.Format("%s",rbuff2);
	for(int i=2;i<temp.GetLength();)
	{
		temp.Insert(i," ");
		i=i+3;
	}

	this->UpdateData();
	m_data+="返回数据:";
	m_data+=temp;
	m_data+="\r\n";
	this->UpdateData(FALSE);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
	this->GetDlgItem(IDC_EDIT_APDU)->SetFocus();

}

void CSHAOXING_NoncontractCPUDlg::OnOK() 
{	
	CDialog::OnOK();
}

void CSHAOXING_NoncontractCPUDlg::OnBtnOpenkeyboard() 
{
	iKeyDev=st_kb_open(100,9600);
	if(iKeyDev>0)
	{
		this->UpdateData();
		m_data+="键盘端口打开成功";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}else
	{
		this->UpdateData();
		m_data+="键盘端口打开失败";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnCloseboard() 
{
	int re=st_kb_close(iKeyDev);
	if(re==0)
	{
		this->UpdateData();
		m_data+="键盘端口关闭成功";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}else
	{
		this->UpdateData();
		m_data+="键盘端口关闭失败";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnDlMainkey() 
{
	CString sKey;
	GetDlgItemText(IDC_EDIT_KEY_DATA,sKey);
	int destype=0;
	if(sKey.GetLength()==16)  destype=0;
	else if(sKey.GetLength()==32) destype=1;
	else 
	{
		this->UpdateData();
		m_data+="密钥长度有误!";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return;
	}
	int mainkeyno=m_comboNrMainKey.GetCurSel();
	unsigned char keybuff[100]={0};
	StrToHex((unsigned char *)sKey.GetBuffer(0),sKey.GetLength(),keybuff);
	int re=st_kb_downloadmainkey(iKeyDev,destype,mainkeyno,(unsigned char *)sKey.GetBuffer(0));
	re=st_kb_downloadmainkey(iKeyDev,destype,mainkeyno,keybuff);
	if(re==0)
	{
		this->UpdateData();
		m_data+="主密钥下载成功!";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}else
	{
		CString temp;
		temp.Format("错误代码:%d",re);
		this->UpdateData();
		m_data+="主密钥下载失败,"+temp;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnDlWorkkey() 
{
	CString sKey;
	GetDlgItemText(IDC_EDIT_KEY_DATA,sKey);
	int destype=0;
	if(sKey.GetLength()==16)  destype=0;
	else if(sKey.GetLength()==32) destype=1;
	else 
	{
		this->UpdateData();
		m_data+="密钥长度有误!";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return;
	}
	int mainkeyno=m_comboNRWorkKey.GetCurSel();
	int re=st_kb_downloadmainkey(iKeyDev,destype,mainkeyno,(unsigned char *)sKey.GetBuffer(0));
	if(re==0)
	{
		this->UpdateData();
		m_data+="工作密钥下载成功!";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}else
	{
		CString temp;
		temp.Format("错误代码:%d",re);
		this->UpdateData();
		m_data+="工作钥下载失败,"+temp;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnActivekey() 
{
	int mainkeyno=m_comboNrMainKey.GetCurSel();
	int userkeyno=m_comboNRWorkKey.GetCurSel();
	int re=st_kb_activekey(iKeyDev,mainkeyno,userkeyno); 
	if(re==0)
	{
		this->UpdateData();
		m_data+="激活密钥成功!";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}else
	{
		CString temp;
		temp.Format("错误代码:%d",re);
		this->UpdateData();
		m_data+="激活密钥失败,"+temp;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnSetKeylen() 
{
	int passlen=m_comboNRWorkKey.GetCurSel();
	int re=st_kb_setpasslen(iKeyDev,passlen+1); 
	if(re==0)
	{
		this->UpdateData();
		m_data+="设置输入密码长度成功!";
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}else
	{
		CString temp;
		temp.Format("错误代码:%d",re);
		this->UpdateData();
		m_data+="设置输入密码长度失败,"+temp;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnGetpin() 
{
	unsigned char planpin[200]={0};
	int re=st_kb_getpin(iKeyDev,1,planpin);
	if(re==0)
	{
		this->UpdateData();
		m_data+="明文密码:";
		m_data+=planpin;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}else
	{
		CString temp;
		temp.Format("错误代码:%d",re);
		this->UpdateData();
		m_data+="获取明文密码失败,"+temp;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnGetnpin() 
{
	unsigned char planpin[200]={0};
	CString sCardno;
	this->GetDlgItemText(IDC_EDIT_CARDNO,sCardno);
	int re=st_kb_getenpin(iKeyDev,1,(unsigned char *)sCardno.GetBuffer(0),planpin); 
	if(re==0)
	{
		this->UpdateData();
		m_data+="密文密码:";
		m_data+=planpin;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}else
	{
		CString temp;
		temp.Format("错误代码:%d",re);
		this->UpdateData();
		m_data+="获取密文密码失败,"+temp;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}
}

void CSHAOXING_NoncontractCPUDlg::OnBtnNkey() 
{
	int type=m_comboNType.GetCurSel();
	int mainkeyno=m_comboNrMainKey.GetCurSel();
	int userkeyno=m_comboNRWorkKey.GetCurSel();
	CString src;
	this->GetDlgItemText(IDC_EDIT_WAITN,src);
	char dst[100]={0};
	int re=st_getDes(iKeyDev,type,mainkeyno,userkeyno, src.GetBuffer(0), dst);
	if(re==0)
	{
		this->UpdateData();
		m_data+="加密后:";
		m_data+=dst;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}else
	{
		CString temp;
		temp.Format("错误代码:%d",re);
		this->UpdateData();
		m_data+="加密失败,"+temp;
		m_data+="\r\n";
		this->UpdateData(FALSE);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
	}
}

void CSHAOXING_NoncontractCPUDlg::OnButton1() 
{
	char VSoftware[20]={0};
	char VHardware[20]={0};
	char VBoot[20]={0};
	char VDate[20]={0};
	int i=ICC_Reader_GetDeviceVersion(hDev,VSoftware,VHardware,VBoot,VDate);
}
