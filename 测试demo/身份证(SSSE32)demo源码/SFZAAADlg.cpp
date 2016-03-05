// SFZAAADlg.cpp : implementation file
//

#include "stdafx.h"
#include "SFZAAA.h"
#include "SFZAAADlg.h"

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
// CSFZAAADlg dialog

CSFZAAADlg::CSFZAAADlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSFZAAADlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSFZAAADlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSFZAAADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSFZAAADlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSFZAAADlg, CDialog)
	//{{AFX_MSG_MAP(CSFZAAADlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNOPEN, OnBtnopen)
	ON_BN_CLICKED(IDC_BTNCLEN, OnBtnclen)
	ON_BN_CLICKED(IDC_BTNREAD, OnBtnread)
	ON_BN_CLICKED(IDC_CLOSETHREAD, OnClosethread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSFZAAADlg message handlers

BOOL CSFZAAADlg::OnInitDialog()
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
	this->SetWindowText("华大身份证阅读程序");
	this->m_hThread=NULL;
	this->hReader=NULL;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSFZAAADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSFZAAADlg::OnPaint() 
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
HCURSOR CSFZAAADlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void CSFZAAADlg::OnBtnopen() 
{
	// TODO: Add your control notification handler code here
	if(hReader==NULL)
		hReader = ICC_Reader_Open("USB1");
	if(hReader >0)
	{
		MessageBox("设备连接成功");
	}
	else
		MessageBox("设备连接失败");
}

void CSFZAAADlg::OnBtnclen() 
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_SNAME,"");
	SetDlgItemText(IDC_SSEX,"");
	SetDlgItemText(IDC_SMINZU,"");
	SetDlgItemText(IDC_SBIR,"");
	SetDlgItemText(IDC_SADDER,"");
	SetDlgItemText(IDC_SJIGUAN,"");
	SetDlgItemText(IDC_SNUM,"");
	SetDlgItemText(IDC_SDATA,"");
//	SetDlgItemText(IDC_SPHTO,"");
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_SPHTO);
	CRect lRect;
	pStatic->GetClientRect(&lRect);
	pStatic->GetDC()->FillSolidRect(lRect.left ,lRect.top ,lRect.Width(),lRect.Height(), RGB(240, 240, 240));
	//这个是GDI清空图片控件的，if this program have problem ,it must be not mine program.
	//TODO:Add 
}


//读取信息
void CSFZAAADlg::OnBtnread() 
{
	// TODO: Add your control notification handler code here
	if(m_hThread==NULL)
		m_hThread=::CreateThread(NULL, 0, ReaderThread,this, 0, NULL);
}
DWORD WINAPI CSFZAAADlg::ReaderThread(LPVOID lpParameter)
{
	CString s;
	CSFZAAADlg *pDlg=(CSFZAAADlg *)lpParameter;
	while(1)
	{
		unsigned char UID[10];
		//	char bmp[77725];
		
		char name[256]={0};
		char sex[256]={0};
		char minzu[256]={0};
		char bir[256]={0};
		char addres[256]={0};
		char num[256]={0};
		char jiguan[256]={0};
		char EffectData[256]={0};
		char date[256]={0};
		char errmsg[256]={0};
		
		CString str;
		CString newstr;
		int a=0;
		a = PICC_Reader_ID_Request(pDlg->hReader);//身份证寻卡
		a = PICC_Reader_ID_Select(pDlg->hReader);//身份证选卡
		int re = PICC_Reader_ReadIDMsg(pDlg->hReader, "D:\\zp.bmp", 
										name, sex,
										minzu, bir,
										addres,num,
										jiguan,EffectData, 
										date,errmsg);
			/*参数： 
			ReaderHandle ：IN 设备句柄
			pBmpFileData：IN 如果pBmpFileData==NULL，则不生成照片，如需生成照片，这里输出照片数据信息，需分配77725字节空间
			pName：OUT 姓名
			pSex：OUT 性别
			pNation：OUT 民族
			pBirth：OUT 出生日期
			pAddress：OUT 家庭住址
			pCertNo：OUT 身份证号
			pDepartment：OUT 发证机关
			pEffectData：OUT 发证日期
			pExpire：OUT 有效日期*/
		if(0 == re)
		{
			str.Format("%s",name); //姓名
			pDlg->SetDlgItemText(IDC_SNAME,str);
			str.Empty();

			str.Format("%s",sex);//性别
			pDlg->SetDlgItemText(IDC_SSEX,str);
			str.Empty();

			str.Format("%s",minzu);// 民族
			pDlg->SetDlgItemText(IDC_SMINZU,str);
			str.Empty();

			str.Format("%s",bir);//出生
			pDlg->SetDlgItemText(IDC_SBIR,str);
			str.Empty();

			str.Format("%s",addres);//住址
			pDlg->SetDlgItemText(IDC_SADDER,str);
			str.Empty();

			str.Format("%s",num);//身份证号
			pDlg->SetDlgItemText(IDC_SNUM,str);
			str.Empty();

			str.Format("%s",jiguan);//发证机关
			pDlg->SetDlgItemText(IDC_SJIGUAN,str);
			str.Empty();

			str.Format("%s",EffectData);//有效日期
			newstr.Format("%s",date);
			str = str+"-"+newstr;
			pDlg->SetDlgItemText(IDC_SDATA,str);
			str.Empty();

			/*str.Format("%s",bmp);//照片
			SetDlgItemText(IDC_SPHTO,str);
			str.Empty();*/

			CStatic* pWnd = (CStatic*)pDlg->GetDlgItem(IDC_SPHTO); 
			
			pWnd->ModifyStyle(0xf,SS_BITMAP|SS_CENTERIMAGE);//设置静态控件窗口风格为位图居中显示
			//显示图片
			pWnd->SetBitmap((HBITMAP)::LoadImage(NULL,
				"D:\\zp.bmp",		//资源号或本地文件名
				IMAGE_BITMAP,				//装载位图 IMAGE_CURSOR光标 IMAGE_ICON图标
				0,							//宽度 0为默认大小
				0,							//高度 像素为单位
				LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
		}
	}
	return 0;
}

void CSFZAAADlg::OnClosethread() 
{
	if(this->m_hThread!=NULL)
	{
		::TerminateThread(m_hThread,NULL);
		::CloseHandle(m_hThread);
		m_hThread=NULL;
	}
}
