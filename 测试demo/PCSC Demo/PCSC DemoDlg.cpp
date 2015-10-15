// PCSC DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCSC Demo.h"
#include "PCSC DemoDlg.h"

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
// CPCSCDemoDlg dialog

CPCSCDemoDlg::CPCSCDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPCSCDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPCSCDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPCSCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPCSCDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPCSCDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CPCSCDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_BN_CLICKED(IDC_BTN_OPENDEV, OnBtnOpendev)
	ON_BN_CLICKED(IDC_BTN_CLOSEDEV, OnBtnClosedev)
	ON_BN_CLICKED(IDC_BTN_EXCAPDU, OnBtnExcapdu)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCSCDemoDlg message handlers

BOOL CPCSCDemoDlg::OnInitDialog()
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
	hCardHandle[0]=NULL;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPCSCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPCSCDemoDlg::OnPaint() 
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
HCURSOR CPCSCDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPCSCDemoDlg::OnBtnTest() 
{
	CString temp;
	SCARDCONTEXT        hSC; 
	LONG                lReturn; 
	lReturn = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hSC); 
	if ( lReturn!=SCARD_S_SUCCESS )
	{
		temp+="Failed SCardEstablishContext";
		this->SetDlgItemText(IDC_STATIC_DEV,temp);
	}
	///列出设备表
	char mszReaders[1024];
	LPTSTR pReader, pReaderName[2];  
	DWORD     dwLen=sizeof(mszReaders); 
	int        nReaders=0; 
	lReturn = SCardListReaders(hSC, NULL, (LPTSTR)mszReaders, &dwLen); 
	if ( lReturn==SCARD_S_SUCCESS ) 
	{ 
		pReader = (LPTSTR)mszReaders; 
		while (*pReader !='\0'  ) 
		{ 
			if ( nReaders<2 ) //使用系统中前2个读卡器 
                pReaderName[nReaders++]=pReader; 
			temp+=pReader;
			temp+="|";
			this->SetDlgItemText(IDC_STATIC_DEV,temp);
			pReader = pReader + strlen(pReader) + 1;
		}   
	}
	//与读卡器连接
	SCARDHANDLE     hCardHandle[2]; 
	DWORD           dwAP;   //读卡器实际使用协议
	lReturn = SCardConnect(hSC, pReaderName[0],SCARD_SHARE_SHARED,  SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCardHandle[0], &dwAP); 
	if (lReturn!=SCARD_S_SUCCESS ) 
	{ 
		temp+="Failed SCardConnect!";
		this->SetDlgItemText(IDC_STATIC_DEV,temp);
		return ;
	}
	//发送指令
	BYTE        recvBuffer[260]; 
	unsigned long   sendSize, recvSize; 
	BYTE        sw1, sw2; 
	BYTE    select_mf[]={0x00, 0x84, 0x00, 0x00, 0x08}; 
	sendSize=5; 
	recvSize=sizeof(recvBuffer); 
	lReturn = SCardTransmit(hCardHandle[0], SCARD_PCI_T0, select_mf, sendSize,  NULL, recvBuffer, &recvSize); 
	if ( lReturn != SCARD_S_SUCCESS ) 
	{ 
		temp+="Failed SCardTransmit!";
		this->SetDlgItemText(IDC_STATIC_DEV,temp);
		return ;
	} 
	//返回的数据，recvSize=2 sw1=recvBuffer[recvSize-2]; sw2=recvBuffer[recvSize-1];
	//断开链接
	lReturn = SCardDisconnect(hCardHandle[0], SCARD_LEAVE_CARD); 
	if ( lReturn != SCARD_S_SUCCESS ) 
	{ 
		temp+="Failed SCardDisconnect!";
		this->SetDlgItemText(IDC_STATIC_DEV,temp);
		return ;
	}
	//释放资源
	lReturn = SCardReleaseContext(hSC); 
	if ( lReturn!=SCARD_S_SUCCESS ) 
	{
		temp+="Failed SCardReleaseContext!";
		this->SetDlgItemText(IDC_STATIC_DEV,temp);
		return ;
	}
}

void CPCSCDemoDlg::OnBtnClear() 
{
	this->SetDlgItemText(IDC_EDIT_DATA,"");
}

void CPCSCDemoDlg::OnBtnOpendev() 
{
	CString sOld;
	if(hCardHandle[0]!=NULL)
	{
		this->GetDlgItemText(IDC_EDIT_DATA,sOld);
		sOld+="设备已打开!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sOld);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return;
	}
	lReturn = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hSC); 
	if ( lReturn!=SCARD_S_SUCCESS )
	{
		this->GetDlgItemText(IDC_EDIT_DATA,sOld);
		sOld+="获取设备上下文失败!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sOld);
	}
	///列出设备表
	dwLen=sizeof(mszReaders); 
	nReaders=0; 
	lReturn = SCardListReaders(hSC, NULL, (LPTSTR)mszReaders, &dwLen); 
	if ( lReturn==SCARD_S_SUCCESS ) 
	{ 
		pReader = (LPTSTR)mszReaders; 
		while (*pReader !='\0'  ) 
		{ 
			if ( nReaders<2 ) //使用系统中前2个读卡器 
                pReaderName[nReaders++]=pReader; 
			//temp+=pReader;
			//temp+="|";
			//this->SetDlgItemText(IDC_STATIC_DEV,temp);
			pReader = pReader + strlen(pReader) + 1;
		}   
	}else
	{
		this->GetDlgItemText(IDC_EDIT_DATA,sOld);
		sOld+="列出设备表失败!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sOld);
		SCardReleaseContext(hSC);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return;
	}
	//与读卡器连接
	lReturn = SCardConnect(hSC, pReaderName[0],SCARD_SHARE_SHARED,  SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCardHandle[0], &dwAP); 
	if (lReturn!=SCARD_S_SUCCESS ) 
	{ 
		this->GetDlgItemText(IDC_EDIT_DATA,sOld);
		sOld+="打开设备失败,可能未插卡!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sOld);
		SCardReleaseContext(hSC);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return;
	}else
	{
		this->GetDlgItemText(IDC_EDIT_DATA,sOld);
		sOld+="打开设备成功!";
		sOld+="\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sOld);
	}
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CPCSCDemoDlg::OnBtnClosedev() 
{
	CString sOld;
	lReturn = SCardDisconnect(hCardHandle[0], SCARD_LEAVE_CARD); 
	if ( lReturn != SCARD_S_SUCCESS ) 
	{ 
		this->GetDlgItemText(IDC_EDIT_DATA,sOld);
		sOld+="关闭设备失败!";
		sOld+="\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sOld);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return ;
	}else
	{
		hCardHandle[0]=NULL;
		this->GetDlgItemText(IDC_EDIT_DATA,sOld);
		sOld+="关闭设备成功!";
		sOld+="\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sOld);
	}
	SCardReleaseContext(hSC);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}
int chartoint(char c)
{
	switch (c)
	{
	case '0':
		return 0;break;
	case '1':
		return 1;break;
	case '2':
		return 2;break;
	case '3':
		return 3;break;
	case '4':
		return 4;break;
	case '5':
		return 5;break;
	case '6':
		return 6;break;
	case '7':
		return 7;break;
	case '8':
		return 8;break;
	case '9':
		return 9;break;
	case 'A':
	case 'a':
		return 10;break;
	case 'B':
	case 'b':
		return 11;break;
	case 'C':
	case 'c':
		return 12;break;
	case 'D':
	case 'd':
		return 13;break;
	case 'E':
	case 'e':
		return 14;break;
	case 'F':
	case 'f':
		return 15;break;
	default:
		break;

	}
	return 0;
}
int HexstrToBin(unsigned char *bin, unsigned char *asc,int len)
{
	for(int i=0;i<len/2;i++)
	{
		bin[i]=chartoint(asc[2*i])*16+chartoint(asc[2*i+1]);
	}
	return len/2;
}
int BinToHexstr(unsigned char *HexStr,unsigned char *Bin,int  BinLen)
{
	char Temp1[3];
	char *result;
	int ret;
	int lens;
	lens=BinLen;
	if (lens<=0) return 0;
	result=(char *)malloc((lens*2+2)*sizeof( char));
	if (!result) return 0;
	memset(result,0,sizeof(result));
	for (int i=0;i<lens;i++)
	{
		memset(Temp1,0,sizeof(Temp1));
		ret=sprintf(Temp1,"%X",Bin[i]);
		if (strlen(Temp1)==1) {
			Temp1[1]=Temp1[0];
			Temp1[0]='0';
		}
		strcat(result,Temp1);

	}
	strcpy((char *)HexStr,result);
	
	free(result);
	return 2*i;
}
void CPCSCDemoDlg::OnBtnExcapdu() 
{
	CString sOld;
	CString sAPDU;
	this->GetDlgItemText(IDC_EDIT_APDU,sAPDU);
	this->GetDlgItemText(IDC_EDIT_DATA,sOld);
	sOld+="发送指令:"+sAPDU+"\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sOld);
	int n=0;
	while(-1!=(n=sAPDU.FindOneOf(" ")))
	{
		sAPDU.Delete(n);
	}
	if(sAPDU.GetLength()%2!=0)
	{
		this->GetDlgItemText(IDC_EDIT_DATA,sOld);
		sOld+="发送指令长度有误!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sOld);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return;
	}
	unsigned char bincmd[255]={0};
	HexstrToBin(bincmd,(unsigned char*)sAPDU.GetBuffer(0),sAPDU.GetLength());
	sAPDU.ReleaseBuffer();
	//发送指令
	BYTE        recvBuffer[260]; 
	unsigned long   sendSize, recvSize; 
	BYTE        sw1, sw2; 
	sendSize=sAPDU.GetLength()/2; 
	recvSize=sizeof(recvBuffer); 
	lReturn = SCardTransmit(hCardHandle[0], SCARD_PCI_T0, bincmd, sendSize,  NULL, recvBuffer, &recvSize); 
	if ( lReturn != SCARD_S_SUCCESS ) 
	{ 
		this->GetDlgItemText(IDC_EDIT_DATA,sOld);
		sOld+="发送指令失败!\r\n";
		this->SetDlgItemText(IDC_EDIT_DATA,sOld);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
		pedit->LineScroll(pedit->GetLineCount());
		return;
	} 
	unsigned char HexStr[255]={0};
	BinToHexstr(HexStr,recvBuffer,recvSize);
	this->GetDlgItemText(IDC_EDIT_DATA,sOld);
	sOld+="返回信息:";
	CString temp;
	for(int i=0;i<recvSize;i++)
	{
		int index=i*2;
		temp.Format("%c%c ",HexStr[index],HexStr[index+1]);
		sOld+=temp;
	}
	//sOld+=HexStr;
	sOld+="\r\n";
	this->SetDlgItemText(IDC_EDIT_DATA,sOld);
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_DATA);
	pedit->LineScroll(pedit->GetLineCount());
}

void CPCSCDemoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(hCardHandle[0]!=NULL)
	{
		SCardDisconnect(hCardHandle[0], SCARD_LEAVE_CARD); 
		SCardReleaseContext(hSC);
	}
	CDialog::OnClose();
}
