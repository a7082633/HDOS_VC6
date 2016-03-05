// SSSE32IDCard_ReadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SSSE32IDCard_Read.h"
#include "SSSE32IDCard_ReadDlg.h"

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
// CSSSE32IDCard_ReadDlg dialog

CSSSE32IDCard_ReadDlg::CSSSE32IDCard_ReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSSSE32IDCard_ReadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSSSE32IDCard_ReadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSSSE32IDCard_ReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSSSE32IDCard_ReadDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSSSE32IDCard_ReadDlg, CDialog)
	//{{AFX_MSG_MAP(CSSSE32IDCard_ReadDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_BN_CLICKED(IDC_BTN_FINDCARD, OnBtnFindcard)
	ON_BN_CLICKED(IDC_BTN_SELECTC, OnBtnSelectc)
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSSE32IDCard_ReadDlg message handlers

BOOL CSSSE32IDCard_ReadDlg::OnInitDialog()
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

void CSSSE32IDCard_ReadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSSSE32IDCard_ReadDlg::OnPaint() 
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
HCURSOR CSSSE32IDCard_ReadDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSSSE32IDCard_ReadDlg::OnBtnOpen() 
{
	handler=ICC_Reader_Open("USB1");
	if(handler>0)
		this->MessageBox("´ò¿ª¶Ë¿Ú³É¹¦!");
	else
		this->MessageBox("´ò¿ª¶Ë¿ÚÊ§°Ü!");
}

void CSSSE32IDCard_ReadDlg::OnBtnClose() 
{
	ICC_Reader_Close(handler);
}

void CSSSE32IDCard_ReadDlg::OnBtnFindcard() 
{
	int rt=PICC_Reader_ID_Request(handler);
	if(rt==0)
		this->MessageBox("Ñ°¿¨³É¹¦!");
	else
	{
		CString str;
		str.Format("Ñ°¿¨Ê§°Ü!´íÎó´úÂë:%d",rt);
		this->MessageBox(str);
	}
}

void CSSSE32IDCard_ReadDlg::OnBtnSelectc() 
{
	int rt=PICC_Reader_ID_Select(handler);
	if(rt==0)
		this->MessageBox("Ñ¡¿¨³É¹¦!");
	else
	{
		CString str;
		str.Format("Ñ¡¿¨Ê§°Ü!´íÎó´úÂë:%d",rt);
		this->MessageBox(str);
	}
}

void CSSSE32IDCard_ReadDlg::OnBtnRead() 
{
	char pName[50]={0};
	char pSex[50]={0};
	char pNation[50]={0};
	char pBirth[50]={0};
	char pAddress[50]={0};
	char pCertNo[50]={0};
	char pDepartment[50]={0};
	char pEffectData[50]={0};
	char pExpire[50]={0};
	char pErrMsg[50]={0};
	int rt=PICC_Reader_ReadIDMsg(handler,"D://zp.bmp",pName,pSex,pNation,pBirth,pAddress,pCertNo,pDepartment,pEffectData,pExpire,pErrMsg);
	if(rt==0)
		this->MessageBox("¶Á¿¨³É¹¦!");
	else
	{
		CString str;
		str.Format("¶Á¿¨Ê§°Ü!(%s),´íÎó´úÂë:%d",pErrMsg,rt);
		this->MessageBox(str);
	}

}
