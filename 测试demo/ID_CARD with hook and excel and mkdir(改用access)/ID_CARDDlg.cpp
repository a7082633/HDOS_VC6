// ID_CARDDlg.cpp : implementation file
//
#include "stdafx.h"
#include "ID_CARD.h"
#include "ID_CARDDlg.h"
#include <direct.h>
#include <odbcinst.h>
#include <afxdb.h>
#include <io.h>
#include <winuser.h>
#include "DialogQueryData.h"
//#include "excel.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
HHOOK Hook;
int ik=0;
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
// CID_CARDDlg dialog

CID_CARDDlg::CID_CARDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CID_CARDDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CID_CARDDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//s="";
}

void CID_CARDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CID_CARDDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CID_CARDDlg, CDialog)
	//{{AFX_MSG_MAP(CID_CARDDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENDEV, OnBtnOpendev)
	ON_BN_CLICKED(IDC_BTN_CLOSEDEV, OnBtnClosedev)
	ON_BN_CLICKED(IDC_BTN_CLA_CONTENT, OnBtnClaContent)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_BN_CLICKED(IDC_BTN_CLOSEHOOK, OnBtnClosehook)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_OPENQUERY, OnBtnOpenquery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CID_CARDDlg message handlers

BOOL CID_CARDDlg::OnInitDialog()
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
	m_hThread=NULL;
	m_hHookThread=NULL;
	AfxOleInit();
	//CoInitialize(NULL);
	HRESULT hr; 
	////////////连接数据库//////////////
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
		if(SUCCEEDED(hr))
		{
			m_pConnection->ConnectionTimeout = 5;
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=HD_IDDB.mdb","","",adModeUnknown);///连接数据库
			//上面一句中连接字串中的Provider是针对ACCESS2000环境的，对于ACCESS97,需要改为:Provider=Microsoft.Jet.OLEDB.3.51;  }
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
		return FALSE;
	} 
	//打开纪录集Log
	//m_pRecordset=m_pConnection->Execute("INSERT INTO DBID(姓名,性别,民族,出生日期,家庭住址,身份证号码,签发机关,有效期起,有效期止) VALUES ('2','2','2','2','2','2','2','2','2')",&RecordsAffected,adCmdText);
	//	r.CreateInstance(_uuidof(Recordset));
	m_pRecordset.CreateInstance("ADODB.Recordset");
	CString s="select * from DBID";
	_bstr_t bs=s.AllocSysString();
	m_pRecordset->Open(bs,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
//	m_pRecordset->Close();
//	m_pRecordset->Open(bs,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	// TODO: Add extra initialization here
	//初始化数据查询窗口
	CDialogQueryData *pDlgQuery=new CDialogQueryData();
	m_pDlgQuery=pDlgQuery;
	pDlgQuery->m_pRecordset=m_pRecordset;
	pDlgQuery->m_pConnection=m_pConnection;
	pDlgQuery->Create(IDD_DIALOG_QUERYDATA);
//	m_pRecordset->Close();
	//pDlgQuery->ShowWindow(SW_SHOWNORMAL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CID_CARDDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CID_CARDDlg::OnPaint() 
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
HCURSOR CID_CARDDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CID_CARDDlg::OnBtnOpendev() 
{
	if(m_hThread==NULL)
		m_hThread=::CreateThread(NULL, 0, ReaderThread,this, 0, NULL);
	GetDlgItem(IDC_BTN_OPENDEV)->ShowWindow(SW_HIDE); 
	GetDlgItem(IDC_BTN_CLOSEDEV)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_STATIC_STATE_CARD,"");
}

void CID_CARDDlg::OnBtnClosedev() 
{
	if(this->m_hThread!=NULL)
	{
		::TerminateThread(m_hThread,NULL);
		m_hThread=NULL;
	}
	GetDlgItem(IDC_BTN_OPENDEV)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BTN_CLOSEDEV)->ShowWindow(SW_HIDE); 
	SetDlgItemText(IDC_STATIC_STATE_CARD,"");
	int re = -1;
	for(iPort=1001; iPort<=1016; iPort++)
	{
		//调用HD_InitComm()函数
		re = HD_CloseComm(iPort);
	}
	if(re == 0)
	{
		SetDlgItemText(IDC_STATIC_STATE,"关闭设备成功！");
		//AfxMessageBox("关闭设备成功！");
	}
	
	//搜索串口
	for(iPort=1; iPort<=16; iPort++)
	{
		re = HD_CloseComm(iPort);
	}
}


DWORD WINAPI CID_CARDDlg::ReaderThread(LPVOID lpParameter)
{
	//AfxOleInit();
//	HRESULT hr; 
//	hr = CoInitialize(NULL); 
	CString s;
	CID_CARDDlg *pDlg=(CID_CARDDlg *)lpParameter;
	int i=0;
	while(1)
	{
		if(0==(i=pDlg->InitComm()))
		{
			pDlg->SetDlgItemText(IDC_STATIC_STATE,"设备已经连接上");
			char name[200]={0};
			char sex[200]={0};
			char nation[200]={0};
			char born[200]={0};
			char address[400]={0};
			char cardNo[400]={0};
			char issuedat[200]={0};
			char effectedDate[200]={0};
			char expiredDate[200]={0};
			char picData[77725]={0};
			char temp2[300]={0};
			char g_pBmpFile[255] = {0};
			strcpy(g_pBmpFile, "D:\\zp.bmp");
			CString sTemp="";
			int re = HD_Authenticate();
			if(re==0)
			{
				re = HD_Read_BaseInfo(g_pBmpFile,picData,name, sex, nation, born, address, cardNo, issuedat, effectedDate, expiredDate);
				if(re==0)
				{
					//access
					try
					{
//						pDlg->m_pRecordset->Open("SELECT * FROM DBID",pDlg->m_pConnection.GetInterfacePtr(),adOpenStatic,adLockOptimistic,adCmdText); 
						pDlg->m_pRecordset->AddNew();///添加新记录 
						pDlg->m_pRecordset->PutCollect("姓名",_variant_t(name)); 
						pDlg->m_pRecordset->PutCollect("性别",_variant_t(sex));
						pDlg->m_pRecordset->PutCollect("民族",_variant_t(nation));
						sprintf(temp2,"%.4s-%.2s-%.2s",born,born+4,born+6);
						pDlg->m_pRecordset->PutCollect("出生日期",_variant_t(temp2));
						pDlg->m_pRecordset->PutCollect("家庭住址",_variant_t(address));
						pDlg->m_pRecordset->PutCollect("身份证号码",_variant_t(cardNo));
						pDlg->m_pRecordset->PutCollect("签发机关",_variant_t(issuedat));
						sprintf(temp2,"%.4s-%.2s-%.2s",effectedDate,effectedDate+4,effectedDate+6);
						pDlg->m_pRecordset->PutCollect("有效期起",_variant_t(temp2));
						sprintf(temp2,"%.4s-%.2s-%.2s",expiredDate,expiredDate+4,expiredDate+6);
						pDlg->m_pRecordset->PutCollect("有效期止",_variant_t(temp2));
						pDlg->m_pRecordset->Update();
					}catch(CException e)
					{
						e.ReportError();
						::AfxMessageBox("请再次检查数据");
					}
					pDlg->SetDlgItemText(IDC_STATIC_STATE_CARD,"身份证读取成功,请放下一张身份证！");
					pDlg->SetDlgItemText(IDC_EDIT_NAME,name);
					pDlg->SetDlgItemText(IDC_EDIT_SEX,sex);
					pDlg->SetDlgItemText(IDC_EDIT_NATION,nation);
					//picData,name, sex, nation, born, address, cardNo, issuedat, effectedDate, expiredDate
					sTemp.Format("%.4s年%.2s月%.2s日",born,born+4,born+6);
					pDlg->SetDlgItemText(IDC_EDIT_BORNDATE,sTemp);
					pDlg->SetDlgItemText(IDC_EDIT_ADDR,address);
					sTemp.Format("%.4s.%.2s.%.2s-%.4s.%.2s.%.2s",effectedDate,effectedDate+4,effectedDate+6,expiredDate,expiredDate+4,expiredDate+6);
					pDlg->SetDlgItemText(IDC_EDIT_DEADLINE,sTemp);
					pDlg->SetDlgItemText(IDC_EDIT_SIGNADDR,issuedat);
					pDlg->SetDlgItemText(IDC_EDIT_CARDNO,cardNo);
					//显示照片
					HBITMAP hBitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),g_pBmpFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
					BITMAP bm;
					::GetObject(hBitmap, sizeof( bm ), &bm );
					int bmWidth = bm.bmWidth;
					int bmHeight = bm.bmHeight;
					CDC *pDC=pDlg->GetDC();
					CDC MemDC;
					MemDC.CreateCompatibleDC(pDC); 
					MemDC.SelectObject(hBitmap);
					pDC->BitBlt(352,20,bmWidth,bmHeight,&MemDC,0,0,SRCCOPY);
					MemDC.DeleteDC();
				}
				else
					pDlg->SetDlgItemText(IDC_STATIC_STATE_CARD,"身份证读取失败，请重试！");
			}
		}else
		{
			pDlg->SetDlgItemText(IDC_STATIC_STATE,"设备未连接");
		}
		::Sleep(500);
	}
	return 0;
}




int CID_CARDDlg::InitComm()
{
	int re=0;
	for(iPort=1001; iPort<=1016; iPort++)
	{
		re = HD_InitComm(iPort);
		if(0==re)
		{
			//this->MessageBox("ok");
			return 0;
		}
		if (iPort==1015)
		{
			for(iPort=1001; iPort<=1016; iPort++)
			{
				//调用HD_InitComm()函数
				re = HD_CloseComm(iPort);
			}
		}
	}
	return 1;
}

void CID_CARDDlg::OnBtnClaContent() 
{
	SetDlgItemText(IDC_STATIC_STATE_CARD,"");
	SetDlgItemText(IDC_EDIT_NAME,"");
	SetDlgItemText(IDC_EDIT_SEX,"");
	SetDlgItemText(IDC_EDIT_NATION,"");
	SetDlgItemText(IDC_EDIT_BORNDATE,"");
	SetDlgItemText(IDC_EDIT_ADDR,"");
	SetDlgItemText(IDC_EDIT_DEADLINE,"");
	SetDlgItemText(IDC_EDIT_SIGNADDR,"");
	SetDlgItemText(IDC_EDIT_CARDNO,"");
	this->Invalidate();
}

//DEL void CID_CARDDlg::OnButton1() 
//DEL {
//DEL 	HBITMAP hBitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"D:\\zp.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
//DEL 	BITMAP bm;
//DEL 	::GetObject(hBitmap, sizeof( bm ), &bm );
//DEL 	int bmWidth = bm.bmWidth;
//DEL 	int bmHeight = bm.bmHeight;
//DEL 	CDC *pDC=this->GetDC();
//DEL 	CDC MemDC;
//DEL 	MemDC.CreateCompatibleDC(pDC); 
//DEL 	MemDC.SelectObject(hBitmap);
//DEL 	pDC->BitBlt(352,20,bmWidth,bmHeight,&MemDC,0,0,SRCCOPY);
//DEL 	MemDC.DeleteDC();
//DEL }



int CALLBACK _BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM pData)  
{   
    TCHAR szDir[MAX_PATH];   
    switch(uMsg)   
    {   
    case BFFM_INITIALIZED:   
        // WParam is TRUE since you are passing a path.   
        // It would be FALSE if you were passing a pidl.   
        SendMessage(hwnd,BFFM_SETSELECTION, TRUE, (LPARAM)pData);  
        break; 
	case BFFM_SELCHANGED:  
        // Set the status window to the currently selected path.   
        if (SHGetPathFromIDList((LPITEMIDLIST)lParam ,szDir))   
        {  
            SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)szDir);   
        }   
        break;  
    }   
    return 0;   
}  



void CID_CARDDlg::OnButtonTest() 
{
//	//创建目录
//	CString path;
//	path=sPhotoPath+"\\身份证照片";
//	int i=_mkdir(path);
//	//照片路径
//	char cardNo[100]="450922";
//	CString picPathstr;
//	picPathstr=path+"\\"+cardNo+".bmp";
//-----------------------
//	CString path;
//	path=sPhotoPath+"\\身份证照片";
//	int i=_mkdir(path);
	keybd_event('a',0x01,0,0); // 揿 Alt 
	keybd_event('a',0x01,KEYEVENTF_KEYUP,0); // 键弹上 
}
void CID_CARDDlg::OnBtnClosehook() 
{
    if(Hook)  
    {  
        BOOL result = UnhookWindowsHookEx((HHOOK)Hook); // 卸载钩子  
        if (result) Hook = NULL;  
    }
	if(this->m_hThread!=NULL)
	{
		::TerminateThread(m_hHookThread,NULL);
		m_hHookThread=NULL;
	}
	GetDlgItem(IDC_BTN_OPENHOOK)->ShowWindow(SW_SHOW); 
	GetDlgItem(IDC_BTN_CLOSEHOOK)->ShowWindow(SW_HIDE);
}




void CID_CARDDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
//	m_pRecordset->Close();
//	m_pRecordset=NULL;
	if (m_pRecordset->GetState() == adStateOpen)
	{
		m_pRecordset->Close();
	}
	if(m_pConnection->State) 
		m_pConnection->Close(); ///如果已经打开了连接则关闭它
	if (m_pConnection)
	{
		m_pConnection.Release();
		m_pConnection = NULL;
	}
	CDialogQueryData *pDlg=(CDialogQueryData *)m_pDlgQuery;
	delete pDlg;
	//CoUninitialize();
	CDialog::OnClose();
}

void CID_CARDDlg::OnBtnOpenquery() 
{
	CDialogQueryData *pDlg=(CDialogQueryData *)m_pDlgQuery;
	pDlg->ShowWindow(SW_SHOWNORMAL);
}
