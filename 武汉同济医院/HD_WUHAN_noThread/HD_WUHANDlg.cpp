// HD_WUHANDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HD_WUHAN.h"
#include "HD_WUHANDlg.h"

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
// CHD_WUHANDlg dialog

CHD_WUHANDlg::CHD_WUHANDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHD_WUHANDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHD_WUHANDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHD_WUHANDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHD_WUHANDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHD_WUHANDlg, CDialog)
	//{{AFX_MSG_MAP(CHD_WUHANDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_OPENTHREAD, OnBtnOpenthread)
	ON_BN_CLICKED(IDC_BTN_CLOSETHREAD, OnBtnClosethread)
	ON_BN_CLICKED(IDC_BTN_READINFO, OnBtnReadinfo)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHD_WUHANDlg message handlers

BOOL CHD_WUHANDlg::OnInitDialog()
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
	m_hThread=NULL;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHD_WUHANDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHD_WUHANDlg::OnPaint() 
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
HCURSOR CHD_WUHANDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHD_WUHANDlg::OnBtnOpen() 
{
//	ReaderHandle=ICC_Reader_Open("USB1"); 
//	if(ReaderHandle<=0)
//	{
//		this->SetDlgItemText(IDC_EDIT_DATA,"打开端口失败");
//	}else
//	{
//		this->SetDlgItemText(IDC_EDIT_DATA,"打开端口成功");
//	}
}

void CHD_WUHANDlg::OnBtnClose() 
{
//	int i=ICC_Reader_Close(ReaderHandle);
//	if(i!=0)
//	{
//		this->SetDlgItemText(IDC_EDIT_DATA,"关闭端口失败");
//	}else
//	{
//		this->SetDlgItemText(IDC_EDIT_DATA,"关闭端口成功");
//	}
}

void CHD_WUHANDlg::OnBtnRead()
{
//	ReaderHandle=ICC_Reader_Open("USB1"); 
//	//处理磁条卡
//	unsigned char rlen=0;
//	char DataBuffer[400]={0};
//	int i=Rcard(ReaderHandle,2,2,&rlen,DataBuffer);
//	CString temp;
//	if(DataBuffer[0]!=NULL)
//	{
//		temp.Format("磁条卡:%s",DataBuffer);
//		this->SetDlgItemText(IDC_EDIT_DATA,temp);
//		ICC_Reader_Close(ReaderHandle);
//		return ;
//	}
//	/////////////////////////////////////////////
//	i=ICC_Reader_DisCardType(ReaderHandle);
//	if(i>0)
//	{
//		//this->SetDlgItemText(IDC_EDIT_DATA,"接触CPU卡");
//		unsigned char cmd[100]={0};
//		unsigned char Response[100]={0};
//		///////////////////////////////////
//		char KH[100]={0};
//		unsigned char FKRQ[10]={0};
//		unsigned char KYXQ[10]={0};
//		unsigned char SHBZHM[50]={0};
//		///////////////////////////////////
//		i=ICC_Reader_PowerOn(ReaderHandle,0x01,Response);
//		if(i <= 0)
//		{
//			temp.Format("社保卡上电失败,错误代码:%d",i);
//			this->SetDlgItemText(IDC_EDIT_DATA,temp);
//			ICC_Reader_Close(ReaderHandle);
//			return ;
//		}
//		//选SSSE
//		memcpy(cmd, "\x00\xA4\x04\x00\x0F\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF", 20);
//		i= ICC_Reader_Application(ReaderHandle,0x01, 20, cmd, Response);
//		if(Response[i-2]!=0x61 && Response[i-2]!=0x90)
//		{
//			temp.Format("社保卡选SSSE失败,错误代码:%d",i);
//			this->SetDlgItemText(IDC_EDIT_DATA,temp);
//			ICC_Reader_PowerOff(ReaderHandle,0x01);
//			ICC_Reader_Close(ReaderHandle);
//			return ;
//		}
//		//选SSSE/EF05
//		memset(cmd, 0, 20);
//		memcpy(cmd, "\x00\xA4\x02\x00\x02\xEF\x05", 7);
//		i = ICC_Reader_Application(ReaderHandle, 0x01, 7, cmd, Response);
//		if(i<0 || Response[i-2]!=0x90)
//		{
//			temp.Format("社保卡选SSSE-EF05失败,错误代码:%d",i);
//			this->SetDlgItemText(IDC_EDIT_DATA,temp);
//			ICC_Reader_PowerOff(ReaderHandle,0x01);
//			ICC_Reader_Close(ReaderHandle);
//			return ;
//		}
//		//卡号
//		memset(cmd, 0, 7);
//		memset(Response, 0, 100);
//		memcpy(cmd, "\x00\xB2\x07\x04\x0B", 5);
//		i = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
//		if(i<0 && Response[i-2]!=0x90)
//		{
//			temp.Format("社保卡读取卡号失败,错误代码:%d",i);
//			this->SetDlgItemText(IDC_EDIT_DATA,temp);
//			ICC_Reader_PowerOff(ReaderHandle,0x01);
//			ICC_Reader_Close(ReaderHandle);
//			return ;
//		}
//		memcpy(KH, Response+2,i-4);
//		//发卡日期
//		memset(cmd, 0, 7);
//		memset(Response, 0, 100);
//		memcpy(cmd, "\x00\xB2\x05\x04\x06", 5);
//		i = ICC_Reader_Application(ReaderHandle,0x01, 5, cmd, Response);
//		if(i<0 && Response[i-2]!=0x90)
//		{
//			temp.Format("社保卡读取发卡日期失败,错误代码:%d",i);
//			this->SetDlgItemText(IDC_EDIT_DATA,temp);
//			ICC_Reader_PowerOff(ReaderHandle,0x01);
//			ICC_Reader_Close(ReaderHandle);
//			return ;
//		}
//		HexToStr(Response+2,4,FKRQ);
//		//卡有效期
//		memset(cmd, 0, 7);
//		memset(Response, 0, 100);
//		memcpy(cmd, "\x00\xB2\x06\x04\x06", 5);
//		i = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
//		if(i<0 && Response[i-2]!=0x90)
//		{
//			temp.Format("社保卡读取有效期失败,错误代码:%d",i);
//			this->SetDlgItemText(IDC_EDIT_DATA,temp);
//			ICC_Reader_PowerOff(ReaderHandle, 0x01);
//			ICC_Reader_Close(ReaderHandle);
//			return ;
//		}
//		HexToStr(Response+2,4,KYXQ);
//		//选SSSE/EF06
//		memset(cmd, 0, 20);
//		memset(Response, 0, 100);
//		memcpy(cmd, "\x00\xA4\x02\x00\x02\xEF\x06", 7);
//		i = ICC_Reader_Application(ReaderHandle, 0x01, 7, cmd, Response);
//		if(i<0 || Response[i-2]!=0x90)
//		{
//			temp.Format("选SSSE/EF06失败,错误代码:%d",i);
//			this->SetDlgItemText(IDC_EDIT_DATA,temp);
//			ICC_Reader_PowerOff(ReaderHandle, 0x01);
//			ICC_Reader_Close(ReaderHandle);
//			return ;
//		}
//		//社会保障号码
//		memset(cmd, 0, 7);
//		memset(Response, 0, 100);
//		memcpy(cmd, "\x00\xB2\x08\x00\x14", 5);
//		i = ICC_Reader_Application(ReaderHandle, 0x01, 5, cmd, Response);
//		if(i<0 && Response[i-2]!=0x90)
//		{
//			temp.Format("社保卡读取身份证(社保号)失败,错误代码:%d",i);
//			this->SetDlgItemText(IDC_EDIT_DATA,temp);
//			ICC_Reader_PowerOff(ReaderHandle, 0x01);
//			ICC_Reader_Close(ReaderHandle);
//			return ;
//		}
//		memcpy(SHBZHM, Response+2,i-4);
//		temp.Format("社保卡:%s|%s|%s|%s",KH,FKRQ,KYXQ,SHBZHM);
//		ICC_Reader_PowerOff(ReaderHandle, 0x01);
//		this->SetDlgItemText(IDC_EDIT_DATA,temp);
//		ICC_Reader_Close(ReaderHandle);
//		return ;
//	}
//	else
//	{
//		//非接触卡
//		//身份证
//		i=PICC_Reader_ID_Request(ReaderHandle);//身份证寻卡
//		if(i==0)
//		{
//			i=PICC_Reader_ID_Select(ReaderHandle);//身份证选卡
//			if(i)
//			{
//				temp.Format("身份证选卡失败");
//				this->SetDlgItemText(IDC_EDIT_DATA,temp);
//				ICC_Reader_Close(ReaderHandle);
//				return ;
//			}
//			char pName[50]={0};
//			char pSex[10]={0};
//			char pNation[10]={0};
//			char pBirth[50]={0};
//			char pAddress[100]={0};
//			char pCertNo[50]={0};
//			char pDepartment[100]={0};
//			char pEffectData[50]={0};
//			char pExpire[20]={0};
//			char pErrMsg[50]={0};
//			i=PICC_Reader_ReadIDMsg(ReaderHandle,NULL,pName,pSex,pNation,pBirth,pAddress,pCertNo, 
//				pDepartment ,pEffectData,pExpire,pErrMsg);
//			temp.Format("身份证信息:%s|%s|%s|%s|%s|%s|%s|%s|%s|%s",pName,pSex,pNation,pBirth,pAddress,pCertNo, 
//				pDepartment ,pEffectData,pExpire,pErrMsg);
//			this->SetDlgItemText(IDC_EDIT_DATA,temp);
//			ICC_Reader_Close(ReaderHandle);
//			return ;
//		}else
//		{
//			////////////////////////////////////////
//			unsigned char uid[20]={0};
//			unsigned char Response[100]={0};
//			i=PICC_Reader_SetTypeA(ReaderHandle);
//			i=PICC_Reader_Request(ReaderHandle);
//			i=PICC_Reader_anticoll(ReaderHandle,uid);
//			i=PICC_Reader_Select(ReaderHandle,0x41);
//			i=PICC_Reader_PowerOnTypeA(ReaderHandle,Response);
//			if(i>=0)
//			{
//				//非接触/CPU卡(健康卡)
//				i=iDOpenPort();
//				if(i) 
//				{
//					iDClosePort();
//					return;
//				}
//				HANDLE hDev;
//				char ATR[50]={0};
//				i=PowerOn(hDev,0x01,ATR);
//				if(i) 
//				{
//					iDClosePort();
//					return;
//				}
//				char KLB[100]={0};
//				char GFBB[100]={0};
//				char FKJGMC[100]={0};
//				char FKJGDM[100]={0};
//				char FKJGZS[500]={0};
//				char FKSJ[100]={0};
//				char KH[100]={0};
//				char AQM[100]={0}; 
//				char XPXLH[100]={0}; 
//				char YYCSDM[100]={0};
//				i=iR_DDF1EF05Info(hDev,KLB,GFBB, FKJGMC, FKJGDM, FKJGZS, FKSJ, KH, AQM, XPXLH,YYCSDM);
//				temp.Format("健康卡:%s|%s",KH,FKSJ);
//				this->SetDlgItemText(IDC_EDIT_DATA,temp);
//				iDClosePort();
//				ICC_Reader_Close(ReaderHandle);
//				return ;
//			}else
//			{
//				//非接触/M1卡
//				memset(uid,0x00,20);
//				int i=PICC_Reader_Request(ReaderHandle);
//				if(i) 
//				{
//					ICC_Reader_Close(ReaderHandle);
//					return ;
//				}
//				i=PICC_Reader_anticoll(ReaderHandle,uid);
//				if(i) 
//				{
//					ICC_Reader_Close(ReaderHandle);
//					return ;
//				}
//				temp.Format("M1卡:%s",uid);
//				this->SetDlgItemText(IDC_EDIT_DATA,temp);
//				ICC_Reader_Close(ReaderHandle);
//				return ;
//			}
//		}
//	}
}

void CHD_WUHANDlg::OnBtnOpenthread() 
{
	if(m_hThread==NULL)
		m_hThread=::CreateThread(NULL, 0, ReaderThread,this, 0, NULL);
}

DWORD WINAPI CHD_WUHANDlg::ReaderThread(LPVOID lpParameter)
{
//	CHD_WUHANDlg *pDlg=(CHD_WUHANDlg *)lpParameter;
//	while(1)
//	{
//		CString temp;
//		//temp.Empty();
//		pDlg->SetDlgItemText(IDC_STATIC_STATE,"状态:读卡器空闲中!");
//		char dataOut[500]={0};
//		char ERR[500]={0};
//		int i=IC_GetData(dataOut,ERR);
//		if(i) continue;
//		temp.Format("%s------%s",dataOut,ERR);
//		pDlg->SetDlgItemText(IDC_EDIT_DATA,temp);
//		while(1)
//		{
//			i=IC_GetData(dataOut,ERR);
//			if(i!=0)
//				break;
//			pDlg->SetDlgItemText(IDC_STATIC_STATE,"状态:请把卡拿开，放下一张卡!");
//			::Sleep(100);
//		}
//	}
	return 0;
}

void CHD_WUHANDlg::OnBtnClosethread() 
{
	if(m_hThread!=NULL)
	{
		::TerminateThread(m_hThread,NULL);
		m_hThread=NULL;
	}
}

void CHD_WUHANDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CHD_WUHANDlg::OnBtnReadinfo() 
{	
	char dataOut[500]={0};
	char pErr[50]={0};
	CString time;
	this->GetDlgItemText(IDC_EDIT_TIMEOUT,time);
	int i=IC_GetData(dataOut,pErr);
	if(i==0)
	{
		this->SetDlgItemText(IDC_EDIT_DATA,dataOut);
	}else
	{
		this->SetDlgItemText(IDC_STATIC_STATE,pErr);
	}

}
//void WINAPI TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
//{
//
//}
void CHD_WUHANDlg::OnButton1() 
{
//	typedef void(*FXN)();
//	FXN a=OnBtnReadinfo2();
	::SetTimer(this->m_hWnd,1000,2000,TimerProc);
}


void WINAPI CHD_WUHANDlg::TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	CHD_WUHANDlg *pDlg= (CHD_WUHANDlg *)FromHandle(hWnd);
	pDlg->OnBtnReadinfo();
}
