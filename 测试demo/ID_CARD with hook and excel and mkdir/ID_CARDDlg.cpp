// ID_CARDDlg.cpp : implementation file
//
#include "stdafx.h"
#include "ID_CARD.h"
#include "ID_CARDDlg.h"
#include <direct.h>
#include "SpreadSheet.h"
#include <odbcinst.h>
#include <afxdb.h>
#include <io.h>
#include <winuser.h>
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
	ON_BN_CLICKED(IDC_BTN_SELCTPHODIR, OnBtnSelctphodir)
	ON_BN_CLICKED(IDC_BTN_IDCARD_EXCEL, OnBtnIdcardExcel)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_BN_CLICKED(IDC_BTN_OPENHOOK, OnBtnOpenhook)
	ON_BN_CLICKED(IDC_BTN_CLOSEHOOK, OnBtnClosehook)
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
	this->GetLastPath("PhotoDir.txt",sPhotoPath);
	this->GetLastPath("InfoDir.txt",sInfoPath);
	this->SetDlgItemText(IDC_EDIT_PHOTODIR,sPhotoPath);
	this->SetDlgItemText(IDC_EDIT_INFODIR,sInfoPath);
	// TODO: Add extra initialization here
	
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
			char picData[80000]={0};
			char fingerData[80000]={0};

			//创建目录
			CString path;
			path=pDlg->sPhotoPath+"\\身份证照片";
			int i=_mkdir(path);
			//照片路径
			CString picPathstr;
			picPathstr=path+"\\zp.bmp";

			CString sTemp;
			int re = HD_Authenticate();
			if(re==0)
			{
				//re = HD_Read_BaseMsg(picPathstr, name, sex, nation, born, address, cardNo, issuedat, effectedDate, expiredDate);
				re = HD_Read_BaseMsg("zp.bmp", name, sex, nation, born, address, cardNo, issuedat, effectedDate, expiredDate);
				//移动文件
				//MoveFile("zp.bmp","C:\\File3.txt");
				//修改文件名字
				//rename(picPathstr,path+"\\"+cardNo+".bmp");
				char sShowPath[100]={0};
				sprintf(sShowPath,"%s\\%s.bmp",path,cardNo);
				MoveFile("zp.bmp",sShowPath);
				//DeleteFile(picPathstr);
				//创建EXCEL目录
				path=pDlg->sInfoPath+"\\身份证信息";
				_mkdir(path);
				path+="\\CardInfo.xls";
				//写EXCEL
				CSpreadSheet SS(path, "TestSheet",true);			
				CStringArray sampleArray;				
				SS.BeginTransaction();			
				// 加入标题
				//姓名、性别、身份证号码、有效期、签发机关、住址。
				sampleArray.RemoveAll();
				sampleArray.Add("姓名");
				sampleArray.Add("性别");
				sampleArray.Add("民族");
				sampleArray.Add("出生日期");
				sampleArray.Add("身份证号码");
				sampleArray.Add("有效期");
				sampleArray.Add("签发机关");
				sampleArray.Add("住址");
				SS.AddHeaders(sampleArray);	
				//加入数据
				sampleArray.RemoveAll();
				sampleArray.Add(name);
				sampleArray.Add(sex);
				sampleArray.Add(nation);
				sTemp.Format("%.4s-%.2s-%.2s",born,born+4,born+6);
				sampleArray.Add(sTemp);
				sampleArray.Add(cardNo);
				sTemp.Format("%.4s.%.2s.%.2s-%.4s.%.2s.%.2s",effectedDate,effectedDate+4,effectedDate+6,expiredDate,expiredDate+4,expiredDate+6);
				sampleArray.Add(sTemp);
				sampleArray.Add(issuedat);
				sampleArray.Add(address);
				SS.AddRow(sampleArray);
				SS.Commit();	
				//re = HD_Read_BaseInfo(picData, name, sex, nation, born, address, cardNo, issuedat, effectedDate, expiredDate);
				//re = HD_Read_BaseFPInfo(fingerData,picData, name, sex, nation, born, address, cardNo, issuedat, effectedDate, expiredDate);
				if(re==0)
				{
					int n=sizeof(BITMAPFILEHEADER);
					pDlg->SetDlgItemText(IDC_STATIC_STATE_CARD,"身份证读取成功,请放下一张身份证！");
					pDlg->SetDlgItemText(IDC_EDIT_NAME,name);
					pDlg->SetDlgItemText(IDC_EDIT_SEX,sex);
					pDlg->SetDlgItemText(IDC_EDIT_NATION,nation);
					sTemp.Format("%.4s年%.2s月%.2s日",born,born+4,born+6);
					pDlg->SetDlgItemText(IDC_EDIT_BORNDATE,sTemp);
					pDlg->SetDlgItemText(IDC_EDIT_ADDR,address);
					sTemp.Format("%.4s.%.2s.%.2s-%.4s.%.2s.%.2s",effectedDate,effectedDate+4,effectedDate+6,expiredDate,expiredDate+4,expiredDate+6);
					pDlg->SetDlgItemText(IDC_EDIT_DEADLINE,sTemp);
					pDlg->SetDlgItemText(IDC_EDIT_SIGNADDR,issuedat);
					pDlg->SetDlgItemText(IDC_EDIT_CARDNO,cardNo);
					//显示照片
					HBITMAP hBitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),sShowPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
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

void CID_CARDDlg::OnButton2() 
{
	this->Invalidate();
}


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

void CID_CARDDlg::OnBtnSelctphodir() 
{
	char szPath[100];     //存放选择的目录路径 
    CString str;
    ZeroMemory(szPath, sizeof(szPath)); 
    BROWSEINFO bi;   
    bi.hwndOwner = m_hWnd;   
    bi.pidlRoot = NULL;   
    bi.pszDisplayName = szPath;   
    bi.lpszTitle = "请选择需要打包的目录：";   
    bi.ulFlags = BIF_RETURNONLYFSDIRS; 
    bi.lpfn = _BrowseCallbackProc;    
    bi.lParam = (LPARAM)sPhotoPath.GetBuffer(0);
    bi.iImage = 0;   
    //弹出选择目录对话框
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   
    if(lp && SHGetPathFromIDList(lp,szPath))   
    {
		this->SetDlgItemText(IDC_EDIT_PHOTODIR,szPath);
		sPhotoPath=szPath;
		this->SetLastPath(szPath,"PhotoDir.txt");
    }
}

void CID_CARDDlg::OnBtnIdcardExcel() 
{
	char szPath[100];     //存放选择的目录路径 
    CString str;
    ZeroMemory(szPath, sizeof(szPath)); 
    BROWSEINFO bi;   
    bi.hwndOwner = m_hWnd;   
    bi.pidlRoot = NULL;   
    bi.pszDisplayName = szPath;   
    bi.lpszTitle = "请选择需要打包的目录：";   
    bi.ulFlags = BIF_RETURNONLYFSDIRS; 
    bi.lpfn = _BrowseCallbackProc;    
    bi.lParam = (LPARAM)sInfoPath.GetBuffer(0);   
    bi.iImage = 0;  
    //弹出选择目录对话框
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   
    if(lp && SHGetPathFromIDList(lp,szPath))   
    {
		//ToFilePath=szPath;
		this->SetDlgItemText(IDC_EDIT_INFODIR,szPath);
		sInfoPath=szPath;
		this->SetLastPath(szPath,"InfoDir.txt");
    }
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
void CID_CARDDlg::OnBtnOpenhook() 
{
	if(m_hHookThread==NULL)
		m_hHookThread=::CreateThread(NULL, 0, HookThread,this, 0, NULL);
	Hook=SetWindowsHookEx(WH_KEYBOARD_LL,KeyBoardHookPro,::AfxGetInstanceHandle(),0);
	GetDlgItem(IDC_BTN_OPENHOOK)->ShowWindow(SW_HIDE); 
	GetDlgItem(IDC_BTN_CLOSEHOOK)->ShowWindow(SW_SHOW);
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
LRESULT CALLBACK CID_CARDDlg::KeyBoardHookPro(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT Param = (PKBDLLHOOKSTRUCT)lParam;
	if(nCode == HC_ACTION)
	{
		//if(wParam == WM_KEYDOWN)
		if (WM_KEYDOWN == wParam || wParam == WM_SYSKEYDOWN) 
		{
			switch(Param->vkCode)
			{
			case VK_F1:
				ik=1;
				return 1;
			case VK_F2:
				ik=2;
				return 1;
			case VK_F3:
				ik=3;
				return 1;
			case VK_F4:
				ik=4;
				return 1;
			case VK_F5:
				ik=5;
				return 1;
			case VK_F6:
				ik=6;
				return 1;
			case VK_F7:
				ik=7;
				return 1;
			case VK_F8:
				ik=8;
				return 1;
			}
		}
	}
	return CallNextHookEx(Hook, nCode, wParam, lParam); //回调; //回调
}

DWORD WINAPI CID_CARDDlg::HookThread(LPVOID lpParameter)
{
	CID_CARDDlg *pDlg=(CID_CARDDlg *)lpParameter;
	CString s;
	while(1)
	{
		switch(ik)
		{
		case 1:
			ik=0;
			pDlg->GetDlgItemText(IDC_EDIT_NAME,s);
			s.TrimRight();
			pDlg->SendKeys(s);
			break;
		case 2:
			pDlg->GetDlgItemText(IDC_EDIT_SEX,s);
			s.TrimRight();
			pDlg->SendKeys(s);
			ik=0;
			break;
		case 3:
			pDlg->GetDlgItemText(IDC_EDIT_NATION,s);
			s.TrimRight();
			pDlg->SendKeys(s);
			ik=0;
			break;
		case 4:
			pDlg->GetDlgItemText(IDC_EDIT_BORNDATE,s);
			s.TrimRight();
			pDlg->SendKeys(s);
			ik=0;
			break;
		case 5:
			pDlg->GetDlgItemText(IDC_EDIT_SIGNADDR,s);
			s.TrimRight();
			pDlg->SendKeys(s);
			ik=0;
			break;
		case 6:
			pDlg->GetDlgItemText(IDC_EDIT_DEADLINE,s);
			s.TrimRight();
			pDlg->SendKeys(s);
			ik=0;
			break;
		case 7:
			pDlg->GetDlgItemText(IDC_EDIT_ADDR,s);
			s.TrimRight();
			pDlg->SendKeys(s);
			ik=0;
			break;
		case 8:
			pDlg->GetDlgItemText(IDC_EDIT_CARDNO,s);
			s.TrimRight();
			pDlg->SendKeys(s);
			ik=0;
			break;
		}
		::Sleep(100);
	}
	return 0;
}

void CID_CARDDlg::SendAscii(wchar_t data, BOOL shift)
{
	INPUT input[2];
	memset(input, 0, 2 * sizeof(INPUT));
	
	if (shift)
	{
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VK_SHIFT;
		SendInput(1, input, sizeof(INPUT));
	}
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = data;
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = data;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(2, input, sizeof(INPUT));
	if (shift)
	{
		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VK_SHIFT;
		input[0].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, input, sizeof(INPUT));  
	}
}

void CID_CARDDlg::SendUnicode(wchar_t data)
{
	INPUT input[2];
	memset(input, 0, 2 * sizeof(INPUT));
	
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = data;
	input[0].ki.dwFlags = 0x4;//KEYEVENTF_UNICODE;
	
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = 0;
	input[1].ki.wScan = data;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP | 0x4;//KEYEVENTF_UNICODE;
	
	SendInput(2, input, sizeof(INPUT));
}

void CID_CARDDlg::SendKeys(CString msg)
{
	short vk;
	BOOL shift;
	USES_CONVERSION;
	wchar_t* data = T2W(msg.GetBuffer(0));
	int len = wcslen(data);
	for(int i=0;i<len;i++)
	{
		if (data[i]>=0 && data[i]<256) //ascii字符
		{
			vk = VkKeyScanW(data[i]);
			if (vk == -1)
			{
				SendUnicode(data[i]);
			}
			else
			{
				if (vk < 0)
				{
					vk = ~vk + 0x1;
				}
				
				shift = vk >> 8 & 0x1;
				
				if (GetKeyState(VK_CAPITAL) & 0x1)
				{
					if (data[i]>='a' && data[i]<='z' || data[i]>='A' && data[i]<='Z')
					{
						shift = !shift;
					}
				}
				SendAscii(vk & 0xFF, shift);
			}
		}
		else //unicode字符
		{
			SendUnicode(data[i]);
		}
	}
}


void CID_CARDDlg::SetLastPath(CString LastPath, CString ReadMePath)
{
    CStdioFile    m_ReadMe;
    CString        LineGetString    =    _T("");
    CString        ReadMeInf[1000];
    bool        PathFlag        = false;
    int i = 0;
    int j = 0;
        //ReadMePath自己定义一个文件路径
    if( m_ReadMe.Open( ReadMePath, CFile::modeWrite|CFile:: modeCreate) ==0)
    {
        return;
    }
    else
    {
        m_ReadMe.WriteString(CString("LASTPATH:") + LastPath + CString("\\"));
        m_ReadMe.Close();
    }
}

CString CID_CARDDlg::GetLastPath(CString ReadMePath,CString &LastPath)
{
    CStdioFile    m_ReadMe;
    CString        LineGetString    =    _T("");
    if( m_ReadMe.Open( ReadMePath, CFile::modeRead|CFile::typeBinary) ==0)
    {
        return CString("");
    }
    else
    {
        m_ReadMe.ReadString(LineGetString);
        if(LineGetString.Find(CString("LASTPATH:"))!=-1)
            {                
                LastPath = LineGetString.Mid(9,LineGetString.GetLength()-10);
            }
        m_ReadMe.Close();

        if(PathFileExists(LastPath))//判断该路径是否存在
        {
            return LastPath;
        }
        else
        {
            return CString("");
        }
    }
    return CString("");
}
