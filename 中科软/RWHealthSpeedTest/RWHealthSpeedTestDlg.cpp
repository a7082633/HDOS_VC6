// RWHealthSpeedTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RWHealthSpeedTest.h"
#include "RWHealthSpeedTestDlg.h"
#include "excel.h"
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
// CRWHealthSpeedTestDlg dialog

CRWHealthSpeedTestDlg::CRWHealthSpeedTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRWHealthSpeedTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRWHealthSpeedTestDlg)
	m_data = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRWHealthSpeedTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRWHealthSpeedTestDlg)
	DDX_Text(pDX, IDC_EDIT_DATA, m_data);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRWHealthSpeedTestDlg, CDialog)
	//{{AFX_MSG_MAP(CRWHealthSpeedTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RONEFKJG, OnBtnRonefkjg)
	ON_BN_CLICKED(IDC_BTN_INITIALPRO, OnBtnInitialpro)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_RHUNDREDFKJG, OnBtnRhundredfkjg)
	ON_BN_CLICKED(IDC_BTN_RONECKR, OnBtnRoneckr)
	ON_BN_CLICKED(IDC_BTN_RHUNDREDCKR, OnBtnRhundredckr)
	ON_BN_CLICKED(IDC_BTN_RONEZP, OnBtnRonezp)
	ON_BN_CLICKED(IDC_BTN_RHUNDREDZP, OnBtnRhundredzp)
	ON_BN_CLICKED(IDC_BTN_RONEYXQ, OnBtnRoneyxq)
	ON_BN_CLICKED(IDC_BTN_RHUNDREDYXQ, OnBtnRhundredyxq)
	ON_BN_CLICKED(IDC_BTN_RONEDZ, OnBtnRonedz)
	ON_BN_CLICKED(IDC_BTN_RHUNDREDDZ, OnBtnRhundreddz)
	ON_BN_CLICKED(IDC_BTN_RONELXR, OnBtnRonelxr)
	ON_BN_CLICKED(IDC_BTN_RHUNDREDLXR, OnBtnRhundredlxr)
	ON_BN_CLICKED(IDC_BTN_RONEZYHY, OnBtnRonezyhy)
	ON_BN_CLICKED(IDC_BTN_RHUNDREDZYHY, OnBtnRhundredzyhy)
	ON_BN_CLICKED(IDC_BTN_RONEZJXX, OnBtnRonezjxx)
	ON_BN_CLICKED(IDC_BTN_RHUNDREDZJXX, OnBtnRhundredzjxx)
	ON_BN_CLICKED(IDC_BTN_RONELCJBXX, OnBtnRonelcjbxx)
	ON_BN_CLICKED(IDC_BTN_WONELCJBXX, OnBtnWonelcjbxx)
	ON_BN_CLICKED(IDC_BTN_RWHUNDREDLCJBXX, OnBtnRwhundredlcjbxx)
	ON_BN_CLICKED(IDC_BTN_RONETSXX, OnBtnRonetsxx)
	ON_BN_CLICKED(IDC_BTN_WONETSXX, OnBtnWonetsxx)
	ON_BN_CLICKED(IDC_BTN_RWHUNDREDTSXX, OnBtnRwhundredtsxx)
	ON_BN_CLICKED(IDC_BTN_RONEGMXX, OnBtnRonegmxx)
	ON_BN_CLICKED(IDC_BTN_WONEGMXX, OnBtnWonegmxx)
	ON_BN_CLICKED(IDC_BTN_RWHUNDREDGMXX, OnBtnRwhundredgmxx)
	ON_BN_CLICKED(IDC_BTN_RONEMYXX, OnBtnRonemyxx)
	ON_BN_CLICKED(IDC_BTN_WONEMYXX, OnBtnWonemyxx)
	ON_BN_CLICKED(IDC_BTN_RWHUNDREDMYXX, OnBtnRwhundredmyxx)
	ON_BN_CLICKED(IDC_BTN_RONEMZXX, OnBtnRonemzxx)
	ON_BN_CLICKED(IDC_BTN_WONEMZXX, OnBtnWonemzxx)
	ON_BN_CLICKED(IDC_BTN_RWHUNDREDMZXX, OnBtnRwhundredmzxx)
	ON_BN_CLICKED(IDC_BTN_RONEZYXX, OnBtnRonezyxx)
	ON_BN_CLICKED(IDC_BTN_WONEZYXX, OnBtnWonezyxx)
	ON_BN_CLICKED(IDC_BTN_RWHUNDREDZYXX, OnBtnRwhundredzyxx)
	ON_BN_CLICKED(IDC_BTN_READALLONECE, OnBtnReadallonece)
	ON_BN_CLICKED(IDC_BTN_READALLHUNDRED, OnBtnReadallhundred)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRWHealthSpeedTestDlg message handlers

BOOL CRWHealthSpeedTestDlg::OnInitDialog()
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
	this->SetDlgItemText(IDC_EDIT_PIN,"1234");
	HRESULT hr; 
	hr = CoInitialize(NULL); 
	//::PostQuitMessage(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRWHealthSpeedTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRWHealthSpeedTestDlg::OnPaint() 
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
HCURSOR CRWHealthSpeedTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRWHealthSpeedTestDlg::OnBtnRonefkjg() 
{
	HANDLE hDev=NULL;
	char KLB[100]={0};
	char GFBB[100]={0};
	char FKJGMC[100]={0};
	char FKJGDM[100]={0};
	char FKJGZS[500]={0};
	char FKSJ[100]={0};
	char KH[100]={0};
	char AQM[100]={0}; 
	char XPXLH[100]={0}; 
	char YYCSDM[100]={0};
	clock_t start,end;
	start=clock();
	int rt=iR_DDF1EF05Info(hDev,KLB, GFBB,FKJGMC,FKJGDM,FKJGZS,FKSJ,KH,AQM,XPXLH,YYCSDM);//
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读发卡机构数据测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("1次读发卡机构数据测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);
	temp.Format("%d",end-start);
	if(!SetExcelData(2,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnInitialpro() 
{
	HANDLE hDev=NULL;
	char ATR[50]={0};
	CString sPIN;
	int rt=iDOpenPort();
	if(rt)
	{
		UpdateData(true); 
		m_data+="打开设备失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=PowerOn(hDev,1,ATR) ; //slot 1  User; slot 0x11 SAM1
	if(rt)
	{
		UpdateData(true); 
		m_data+="用户卡上电失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=PowerOn(hDev,17,ATR) ; //slot 1  User; slot 0x11 SAM1
	if(rt)
	{
		UpdateData(true); 
		m_data+="PSAM卡上电失败!\r\n";
		UpdateData(false);
		return;
	}
	this->GetDlgItemText(IDC_EDIT_PIN,sPIN);
	rt=iVerifyPIN(hDev,sPIN.GetBuffer(0)) ;
	sPIN.ReleaseBuffer();
	if(rt)
	{
		UpdateData(true); 
		m_data+="PSAM校验失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	m_data+="初始化成功!\r\n";
	UpdateData(false);
}

void CRWHealthSpeedTestDlg::OnClose() 
{
	//this->MessageBox("close");
	iDClosePort();
	CDialog::OnClose();
}

void CRWHealthSpeedTestDlg::OnOK() 
{	
//	CDialog::OnOK();
}

void CRWHealthSpeedTestDlg::OnBtnRhundredfkjg() 
{
	HANDLE hDev=NULL;
	char KLB[100]={0};
	char GFBB[100]={0};
	char FKJGMC[100]={0};
	char FKJGDM[100]={0};
	char FKJGZS[500]={0};
	char FKSJ[100]={0};
	char KH[100]={0};
	char AQM[100]={0}; 
	char XPXLH[100]={0}; 
	char YYCSDM[100]={0};
	int iSuccess=0,iFailure=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iR_DDF1EF05Info(hDev,KLB,GFBB,FKJGMC,FKJGDM,FKJGZS,FKSJ,KH,AQM,XPXLH,YYCSDM);
		if(rt==0)
			iSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dTemp2=iSuccess/100.0*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读发卡机构数据测试的平均时间:%f毫秒\r\n100次读发卡机构数据测试的成功率:%f％\r\n",dTemp,dTemp2);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(2,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dTemp2);
	if(!SetExcelData(2,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRoneckr() 
{
	HANDLE hDev=NULL;
	char XM[50]={0};             //姓名
	char XB[50]={0};               //性别代码
	char MZ[50]={0};               //民族代码
	char CSRQ[50]={0};             //出生日期，YYYYMMDD格式
	char SFZH[50]={0};            //居民身份证号
	clock_t start,end;
	start=clock();
	int rt=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读持卡人信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读持卡人信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(3,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRhundredckr() 
{
	HANDLE hDev=NULL;
	char XM[50]={0};             //姓名
	char XB[50]={0};               //性别代码
	char MZ[50]={0};               //民族代码
	char CSRQ[50]={0};             //出生日期，YYYYMMDD格式
	char SFZH[50]={0};            //居民身份证号
	int iSuccess=0,iFailure=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
		if(rt==0)
			iSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dTemp2=(iSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读持卡人数据测试的平均时间:%f毫秒\r\n100次读持卡人数据测试的成功率:%f％\r\n",dTemp,dTemp2);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(3,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dTemp2);
	if(!SetExcelData(3,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonezp() 
{
	HANDLE hDev=NULL;
	unsigned char picData[3075]={0};
	clock_t start,end;
	start=clock();
	int rt=iR_DDF1EF07Info(hDev,picData);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读照片信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读照片信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(4,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRhundredzp() 
{
	HANDLE hDev=NULL;
	unsigned char picData[3075]={0};
	int iSuccess=0,iFailure=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iR_DDF1EF07Info(hDev,picData);
		if(rt==0)
			iSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dTemp2=(iSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读照片测试的平均时间:%f毫秒\r\n100次读照片测试的成功率:%f％\r\n",dTemp,dTemp2);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(4,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dTemp2);
	if(!SetExcelData(4,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRoneyxq() 
{
	HANDLE hDev=NULL;
	char KYXQ[21]={0};			//卡有效期
	char BRDH1[21]={0};         //本人电话1
	char BRDH2[21]={0};           //本人电话2
	char YLFYZFFS1[21]={0};		  //医疗费用支付方式1
	char YLFYZFFS2[21]={0};		  //医疗费用支付方式2
	char YLFYZFFS3[21]={0};	
	clock_t start,end;
	start=clock();
	int rt=iR_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读有效期测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读有效期测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(5,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRhundredyxq() 
{
	HANDLE hDev=NULL;
	char KYXQ[21]={0};			//卡有效期
	char BRDH1[21]={0};         //本人电话1
	char BRDH2[21]={0};           //本人电话2
	char YLFYZFFS1[21]={0};		  //医疗费用支付方式1
	char YLFYZFFS2[21]={0};		  //医疗费用支付方式2
	char YLFYZFFS3[21]={0};	
	int iSuccess=0,iFailure=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iR_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
		if(rt==0)
			iSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dTemp2=(iSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读有效期测试的平均时间:%f毫秒\r\n100次读有效期测试的成功率:%f％\r\n",dTemp,dTemp2);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(5,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dTemp2);
	if(!SetExcelData(5,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonedz() 
{
	HANDLE hDev=NULL;
	char DZLB1[21]={0};		
	char DZ1[120]={0};       
	char DZLB2[21]={0};     
	char DZ2[120]={0};		  
	clock_t start,end;
	start=clock();
	int rt=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读地址测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读地址测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(6,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRhundreddz() 
{
	HANDLE hDev=NULL;
	char DZLB1[21]={0};		
	char DZ1[120]={0};       
	char DZLB2[21]={0};     
	char DZ2[120]={0};	
	int iSuccess=0,iFailure=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
		if(rt==0)
			iSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dTemp2=(iSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读地址测试的平均时间:%f毫秒\r\n100次读地址测试的成功率:%f％\r\n",dTemp,dTemp2);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(6,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dTemp2);
	if(!SetExcelData(6,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonelxr() 
{
	HANDLE hDev=NULL;
	char LXRXM1[40]={0};		
	char LXRGX1[2]={0};       
	char LXRDH1[30]={0};
	char LXRXM2[40]={0};		
	char LXRGX2[2]={0};       
	char LXRDH2[30]={0}; 
	char LXRXM3[40]={0};		
	char LXRGX3[2]={0};       
	char LXRDH3[30]={0}; 	  
	clock_t start,end;
	start=clock();
	int rt=iR_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读联系人测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读联系人测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(7,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRhundredlxr() 
{
	HANDLE hDev=NULL;
	char LXRXM1[40]={0};		
	char LXRGX1[2]={0};       
	char LXRDH1[30]={0};
	char LXRXM2[40]={0};		
	char LXRGX2[2]={0};       
	char LXRDH2[30]={0}; 
	char LXRXM3[40]={0};		
	char LXRGX3[2]={0};       
	char LXRDH3[30]={0}; 	
	int iSuccess=0,iFailure=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iR_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
		if(rt==0)
			iSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dTemp2=(iSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读联系人测试的平均时间:%f毫秒\r\n100次读联系人测试的成功率:%f％\r\n",dTemp,dTemp2);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(7,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dTemp2);
	if(!SetExcelData(7,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonezyhy() 
{
	HANDLE hDev=NULL;
	char WHCD[10]={0};		
	char HYZK[10]={0};       
	char ZY[10]={0}; 
	clock_t start,end;
	start=clock();
	int rt=iR_DF01EF07Info(hDev,WHCD,HYZK,ZY);	 
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读职业婚姻测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读职业婚姻测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(8,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRhundredzyhy() 
{
	HANDLE hDev=NULL;
	char WHCD[10]={0};		
	char HYZK[10]={0};       
	char ZY[10]={0}; 	
	int iSuccess=0,iFailure=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iR_DF01EF07Info(hDev,WHCD,HYZK,ZY);	 
		if(rt==0)
			iSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dTemp2=(iSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读职业婚姻测试的平均时间:%f毫秒\r\n100次读职业婚姻测试的成功率:%f％\r\n",dTemp,dTemp2);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(8,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dTemp2);
	if(!SetExcelData(8,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonezjxx() 
{
	HANDLE hDev=NULL;
	char ZJLB[20]={0};		
	char ZJHM[20]={0};       
	char JKDAH[20]={0};
	char XNHZH[20]={0};
	clock_t start,end;
	start=clock();
	int rt=iR_DF01EF08Info(hDev,ZJLB,ZJHM,JKDAH,XNHZH);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读证件信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读证件信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(9,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRhundredzjxx() 
{
	HANDLE hDev=NULL;
	char ZJLB[20]={0};		
	char ZJHM[20]={0};       
	char JKDAH[20]={0};
	char XNHZH[20]={0};	
	int iSuccess=0,iFailure=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iR_DF01EF08Info(hDev,ZJLB,ZJHM,JKDAH,XNHZH); 
		if(rt==0)
			iSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dTemp2=(iSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读证件信息测试的平均时间:%f毫秒\r\n100次读证件信息测试的成功率:%f％\r\n",dTemp,dTemp2);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(9,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dTemp2);
	if(!SetExcelData(9,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonelcjbxx() 
{
	HANDLE hDev=NULL;
	char ABOXX[10]={0};		
	char RHXX[10]={0};       
	char XCBZ[10]={0};
	char XZBBZ[10]={0};
	char XNXGBBZ[10]={0};         //心脑血管病标志
	char DXBBZ[10]={0};           //癫痫病标志
	char NXWLBZ[10]={0};          //凝血紊乱标志
	char TNBBZ[10]={0};           //糖尿病标志
	char QGYBZ[10]={0};           //青光眼标志
	char TXBZ[10]={0};          //透析标志
	char QGYZBZ[10]={0};          //器官移植标志
	char QGQSBZ[10]={0};        //器官缺失标志
	char KZXYZBZ[10]={0};         //可装卸义肢标志
	char XZQBQBZ[10]={0};        //心脏起搏器标志
	char QTYXJSMC[50]={0};
	clock_t start,end;
	start=clock();
	int rt=iR_DF02EF05Info(hDev,ABOXX,RHXX,XCBZ,XZBBZ,XNXGBBZ,DXBBZ,NXWLBZ,TNBBZ,QGYBZ,TXBZ,QGYZBZ,QGQSBZ,KZXYZBZ,XZQBQBZ,QTYXJSMC);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读临床基本信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读临床基本信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(10,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnWonelcjbxx() 
{
	HANDLE hDev=NULL;
	char ABOXX[10]="01";		
	char RHXX[10]="02";       
	char XCBZ[10]="03";
	char XZBBZ[10]="04";
	char XNXGBBZ[10]="05";         //心脑血管病标志
	char DXBBZ[10]="06";           //癫痫病标志
	char NXWLBZ[10]="07";          //凝血紊乱标志
	char TNBBZ[10]="08";           //糖尿病标志
	char QGYBZ[10]="09";           //青光眼标志
	char TXBZ[10]="10";          //透析标志
	char QGYZBZ[10]="11";          //器官移植标志
	char QGQSBZ[10]="12";        //器官缺失标志
	char KZXYZBZ[10]="13";         //可装卸义肢标志
	char XZQBQBZ[10]="14";        //心脏起搏器标志
	char QTYXJSMC[50]="15";
	clock_t start,end;
	start=clock();
	int rt=iW_DF02EF05Info(hDev,ABOXX,RHXX,XCBZ,XZBBZ,XNXGBBZ,DXBBZ,NXWLBZ,TNBBZ,QGYBZ,TXBZ,QGYZBZ,QGQSBZ,KZXYZBZ,XZQBQBZ,QTYXJSMC);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次写临床基本信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次写临床基本信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(10,3,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRwhundredlcjbxx() 
{
	HANDLE hDev=NULL;
	char ABOXX[10]="01";		
	char RHXX[10]="02";       
	char XCBZ[10]="03";
	char XZBBZ[10]="04";
	char XNXGBBZ[10]="05";         //心脑血管病标志
	char DXBBZ[10]="06";           //癫痫病标志
	char NXWLBZ[10]="07";          //凝血紊乱标志
	char TNBBZ[10]="08";           //糖尿病标志
	char QGYBZ[10]="09";           //青光眼标志
	char TXBZ[10]="10";          //透析标志
	char QGYZBZ[10]="11";          //器官移植标志
	char QGQSBZ[10]="12";        //器官缺失标志
	char KZXYZBZ[10]="13";         //可装卸义肢标志
	char XZQBQBZ[10]="14";        //心脏起搏器标志
	char QTYXJSMC[50]="15";
	//////////////////////读
	char RABOXX[10]="01";		
	char RRHXX[10]="02";       
	char RXCBZ[10]="03";
	char RXZBBZ[10]="04";
	char RXNXGBBZ[10]="05";         //心脑血管病标志
	char RDXBBZ[10]="06";           //癫痫病标志
	char RNXWLBZ[10]="07";          //凝血紊乱标志
	char RTNBBZ[10]="08";           //糖尿病标志
	char RQGYBZ[10]="09";           //青光眼标志
	char RTXBZ[10]="10";          //透析标志
	char RQGYZBZ[10]="11";          //器官移植标志
	char RQGQSBZ[10]="12";        //器官缺失标志
	char RKZXYZBZ[10]="13";         //可装卸义肢标志
	char RXZQBQBZ[10]="14";        //心脏起搏器标志
	char RQTYXJSMC[50]="15";
	int iWSuccess=0,iRSuccess=0,iWRSuccess=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iW_DF02EF05Info(hDev,ABOXX,RHXX,XCBZ,XZBBZ,XNXGBBZ,DXBBZ,NXWLBZ,TNBBZ,QGYBZ,TXBZ,QGYZBZ,QGQSBZ,KZXYZBZ,XZQBQBZ,QTYXJSMC);
		if(rt==0)
			iWSuccess++;
		rt=iR_DF02EF05Info(hDev,RABOXX,RRHXX,RXCBZ,RXZBBZ,RXNXGBBZ,RDXBBZ,RNXWLBZ,RTNBBZ,RQGYBZ,RTXBZ,RQGYZBZ,RQGQSBZ,RKZXYZBZ,RXZQBQBZ,RQTYXJSMC);
		if(rt==0)
			iRSuccess++;
		if(!strcmp(ABOXX,RABOXX)&&!strcmp(RHXX,RRHXX)&&!strcmp(XCBZ,RXCBZ)&&!strcmp(XZBBZ,RXZBBZ)&&!strcmp(XNXGBBZ,RXNXGBBZ)&&
			!strcmp(DXBBZ,RDXBBZ)&&!strcmp(NXWLBZ,RNXWLBZ)&&!strcmp(TNBBZ,RTNBBZ)&&!strcmp(QGYBZ,RQGYBZ)&&!strcmp(TXBZ,RTXBZ)&&
			!strcmp(QGYZBZ,RQGYZBZ)&&!strcmp(QGQSBZ,RQGQSBZ)&&!strcmp(KZXYZBZ,RKZXYZBZ)&&!strcmp(XZQBQBZ,RXZQBQBZ)&&!strcmp(QTYXJSMC,QTYXJSMC))
			iWRSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dWTemp=(iWSuccess/100.0)*100;
	double dRTemp=(iRSuccess/100.0)*100;
	double dWRTemp=(iWRSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读写临床信息测试的平均时间:%f毫秒\r\n100次读临床信息测试的成功率:%f％\r\n100次写临床信息测试的成功率:%f％\r\n100次写读临床信息测试的成功率:%f％\r\n",dTemp,dRTemp,dWTemp,dWRTemp);
	m_data+=temp;
	UpdateData(false);


	temp.Format("%f",dTemp);
	if(!SetExcelData(10,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dRTemp);
	if(!SetExcelData(10,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dWTemp);
	if(!SetExcelData(10,6,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonetsxx() 
{
	HANDLE hDev=NULL;
	char JSBBZ[10]={0};		
	clock_t start,end;
	start=clock();
	int rt=iR_DF02EF06Info(hDev,JSBBZ);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读特殊信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读特殊信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(11,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnWonetsxx() 
{
	HANDLE hDev=NULL;
	char JSBBZ[10]="01";		
	clock_t start,end;
	start=clock();
	int rt=iW_DF02EF06Info(hDev,JSBBZ);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次写特殊信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次写特殊信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(11,3,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRwhundredtsxx() 
{
	HANDLE hDev=NULL;
	char JSBBZ[10]="01";
	//////////////////////读
	char RJSBBZ[10]={0};
	int iWSuccess=0,iRSuccess=0,iWRSuccess=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iW_DF02EF06Info(hDev,JSBBZ);
		if(rt==0)
			iWSuccess++;
		rt=iR_DF02EF06Info(hDev,RJSBBZ);
		if(rt==0)
			iRSuccess++;
		if(!strcmp(JSBBZ,RJSBBZ))
			iWRSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dWTemp=(iWSuccess/100.0)*100;
	double dRTemp=(iRSuccess/100.0)*100;
	double dWRTemp=(iWRSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读写特殊信息测试的平均时间:%f毫秒\r\n100次读特殊信息测试的成功率:%f％\r\n100次写特殊信息测试的成功率:%f％\r\n100次写读特殊信息测试的成功率:%f％\r\n",dTemp,dRTemp,dWTemp,dWRTemp);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(11,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dRTemp);
	if(!SetExcelData(11,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dWTemp);
	if(!SetExcelData(11,6,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonegmxx() 
{
	HANDLE hDev=NULL;
	char GMWZMC[30]={0};	
	char GMFY[120]={0};	
	clock_t start,end;
	start=clock();
	int rt=iR_DF02EF07Info(hDev,1,GMWZMC,GMFY);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读过敏信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读过敏信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(12,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnWonegmxx() 
{
	HANDLE hDev=NULL;
	char GMWZMC[30]="01";	
	char GMFY[120]="02";			
	clock_t start,end;
	start=clock();
	int rt=iW_DF02EF07Info(hDev,GMWZMC,GMFY);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次写过敏信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次写过敏信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(12,3,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRwhundredgmxx() 
{
	HANDLE hDev=NULL;
	char GMWZMC[30]="01";	
	char GMFY[120]="02";
	//////////////////////读
	char RGMWZMC[30]={0};	
	char RGMFY[120]={0};
	int iWSuccess=0,iRSuccess=0,iWRSuccess=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iW_DF02EF07Info(hDev,GMWZMC,GMFY);
		if(rt==0)
			iWSuccess++;
		rt=iR_DF02EF07Info(hDev,1,RGMWZMC,RGMFY);
		if(rt==0)
			iRSuccess++;
		if(!strcmp(GMWZMC,RGMWZMC)&&!strcmp(GMFY,RGMFY))
			iWRSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dWTemp=(iWSuccess/100.0)*100;
	double dRTemp=(iRSuccess/100.0)*100;
	double dWRTemp=(iWRSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读写过敏信息测试的平均时间:%f毫秒\r\n100次读过敏信息测试的成功率:%f％\r\n100次写过敏信息测试的成功率:%f％\r\n100次写读过敏信息测试的成功率:%f％\r\n",dTemp,dRTemp,dWTemp,dWRTemp);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(12,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dRTemp);
	if(!SetExcelData(12,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dWTemp);
	if(!SetExcelData(12,6,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonemyxx() 
{
	HANDLE hDev=NULL;
	char MYJZMC[30]={0};	
	char MYJZSJ[10]={0};
	clock_t start,end;
	start=clock();
	int rt=iR_DF02EF08Info(hDev,1,MYJZMC,MYJZSJ);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读免疫信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读免疫信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(13,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnWonemyxx() 
{
	HANDLE hDev=NULL;
	char MYJZMC[30]="01";	
	char MYJZSJ[10]="02";			
	clock_t start,end;
	start=clock();
	int rt=iW_DF02EF08Info(hDev,MYJZMC,MYJZSJ);
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次写免疫信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次写免疫信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(13,3,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRwhundredmyxx() 
{
	HANDLE hDev=NULL;
	char MYJZMC[30]="01";	
	char MYJZSJ[10]="02000000";
	//////////////////////读
	char RMYJZMC[30]={0};	
	char RMYJZSJ[10]={0};
	int iWSuccess=0,iRSuccess=0,iWRSuccess=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iW_DF02EF08Info(hDev,MYJZMC,MYJZSJ);
		if(rt==0)
			iWSuccess++;
		rt=iR_DF02EF08Info(hDev,1,RMYJZMC,RMYJZSJ);
		if(rt==0)
			iRSuccess++;
		if(!strcmp(MYJZMC,RMYJZMC)&&!strcmp(MYJZSJ,RMYJZSJ))
			iWRSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dWTemp=(iWSuccess/100.0)*100;
	double dRTemp=(iRSuccess/100.0)*100;
	double dWRTemp=(iWRSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读写免疫信息测试的平均时间:%f毫秒\r\n100次读免疫信息测试的成功率:%f％\r\n100次写免疫信息测试的成功率:%f％\r\n100次写读免疫信息测试的成功率:%f％\r\n",dTemp,dRTemp,dWTemp,dWRTemp);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(13,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dRTemp);
	if(!SetExcelData(13,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dWTemp);
	if(!SetExcelData(13,6,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonemzxx() 
{
	HANDLE hDev=NULL;
	char szData[5000]={0};
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=1;i<=5;i++)
	{

		rt=iR_DF03EDInfo (hDev,i,szData,0,3013,1);
	}
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读5条门诊信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读5条门诊信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(14,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnWonemzxx() 
{
	HANDLE hDev=NULL;
	char szData[5000]={0};
	memset(szData,0x31,4000);
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=1;i<=5;i++)
	{

		rt=iW_DF03EDInfo (hDev,i,szData,0,3013,1);
	}
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次写5条门诊信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次写5条门诊信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(14,3,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRwhundredmzxx() 
{
	HANDLE hDev=NULL;
	char szData[5000]={0};
	memset(szData,0x31,3013);
	//////////////////////读
	char szRData[5000]={0};
	int iWSuccess=0,iRSuccess=0,iWRSuccess=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iW_DF03EDInfo (hDev,1,szData,0,3013,1);
		if(rt==0)
			iWSuccess++;
		rt=iR_DF03EDInfo (hDev,1,szRData,0,3013,1);
		if(rt==0)
			iRSuccess++;
		if(!strcmp(szData,szRData))
			iWRSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dWTemp=(iWSuccess/100.0)*100;
	double dRTemp=(iRSuccess/100.0)*100;
	double dWRTemp=(iWRSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读写门诊信息测试的平均时间:%f毫秒\r\n100次读门诊信息测试的成功率:%f％\r\n100次写门诊信息测试的成功率:%f％\r\n100次写读门诊信息测试的成功率:%f％\r\n",dTemp,dRTemp,dWTemp,dWRTemp);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(14,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dRTemp);
	if(!SetExcelData(14,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dWTemp);
	if(!SetExcelData(14,6,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRonezyxx() 
{
	HANDLE hDev=NULL;
	char szData[5000]={0};
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=1;i<=3;i++)
	{

		rt=iR_DF03EEInfo (hDev,i,szData,0,1639,1);
	}
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次读3条住院信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次读3条住院信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(15,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnWonezyxx() 
{
	HANDLE hDev=NULL;
	char szData[5000]={0};
	memset(szData,0x31,1639);
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=1;i<=3;i++)
	{

		rt=iW_DF03EDInfo (hDev,i,szData,0,1639,1);
	}
	end=clock();
	if(rt)
	{
		UpdateData(true); 
		m_data+="1次写3条住院信息测试失败!\r\n";
		UpdateData(false);
		return;
	}
	UpdateData(true); 
	CString temp;
	temp.Format("一次写3条住院信息测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(15,3,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnRwhundredzyxx() 
{
	HANDLE hDev=NULL;
	char szData[5000]={0};
	memset(szData,0x31,1639);
	//////////////////////读
	char szRData[5000]={0};
	int iWSuccess=0,iRSuccess=0,iWRSuccess=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iW_DF03EEInfo (hDev,1,szData,0,1639,1);
		if(rt==0)
			iWSuccess++;
		rt=iR_DF03EDInfo (hDev,1,szRData,0,1639,1);
		if(rt==0)
			iRSuccess++;
		if(!strcmp(szData,szRData))
			iWRSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dWTemp=(iWSuccess/100.0)*100;
	double dRTemp=(iRSuccess/100.0)*100;
	double dWRTemp=(iWRSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次读写住院信息测试的平均时间:%f毫秒\r\n100次读住院信息测试的成功率:%f％\r\n100次写住院信息测试的成功率:%f％\r\n100次写读住院信息测试的成功率:%f％\r\n",dTemp,dRTemp,dWTemp,dWRTemp);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(15,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dRTemp);
	if(!SetExcelData(15,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dWTemp);
	if(!SetExcelData(15,6,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnReadallonece() 
{
	HANDLE hDev=NULL;
	char KLB[100]={0};
	char GFBB[100]={0};
	char FKJGMC[100]={0};
	char FKJGDM[100]={0};
	char FKJGZS[500]={0};
	char FKSJ[100]={0};
	char KH[100]={0};
	char AQM[100]={0}; 
	char XPXLH[100]={0}; 
	char YYCSDM[100]={0};
	////////////////////
	char XM[50]={0};             //姓名
	char XB[50]={0};               //性别代码
	char MZ[50]={0};               //民族代码
	char CSRQ[50]={0};             //出生日期，YYYYMMDD格式
	char SFZH[50]={0};            //居民身份证号
	////////////////////
	char KYXQ[21]={0};			//卡有效期
	char BRDH1[21]={0};         //本人电话1
	char BRDH2[21]={0};           //本人电话2
	char YLFYZFFS1[21]={0};		  //医疗费用支付方式1
	char YLFYZFFS2[21]={0};		  //医疗费用支付方式2
	char YLFYZFFS3[21]={0};	
	/////////////////////////
	unsigned char picData[3075]={0};
	/////////////////////////
	char DZLB1[21]={0};		
	char DZ1[120]={0};       
	char DZLB2[21]={0};     
	char DZ2[120]={0};	
	//////////////////////////
	char LXRXM1[40]={0};		
	char LXRGX1[2]={0};       
	char LXRDH1[30]={0};
	char LXRXM2[40]={0};		
	char LXRGX2[2]={0};       
	char LXRDH2[30]={0}; 
	char LXRXM3[40]={0};		
	char LXRGX3[2]={0};       
	char LXRDH3[30]={0}; 
	//////////////////
	char WHCD[10]={0};		
	char HYZK[10]={0};       
	char ZY[10]={0}; 
	//////////////////
	char ZJLB[20]={0};		
	char ZJHM[20]={0};       
	char JKDAH[20]={0};
	char XNHZH[20]={0};
	//////////////////////
	char ABOXX[10]={0};		
	char RHXX[10]={0};       
	char XCBZ[10]={0};
	char XZBBZ[10]={0};
	char XNXGBBZ[10]={0};         //心脑血管病标志
	char DXBBZ[10]={0};           //癫痫病标志
	char NXWLBZ[10]={0};          //凝血紊乱标志
	char TNBBZ[10]={0};           //糖尿病标志
	char QGYBZ[10]={0};           //青光眼标志
	char TXBZ[10]={0};          //透析标志
	char QGYZBZ[10]={0};          //器官移植标志
	char QGQSBZ[10]={0};        //器官缺失标志
	char KZXYZBZ[10]={0};         //可装卸义肢标志
	char XZQBQBZ[10]={0};        //心脏起搏器标志
	char QTYXJSMC[50]={0};
	//////////////////////////
	char JSBBZ[10]={0};	
	///////////////////
	char GMWZMC[30]={0};	
	char GMFY[120]={0};	
	///////////////////////
	char MYJZMC[30]={0};	
	char MYJZSJ[10]={0};
	///////////////////
	char szData[5000]={0};
	clock_t start,end;
	start=clock();
	int rt=iR_DDF1EF05Info(hDev,KLB, GFBB,FKJGMC,FKJGDM,FKJGZS,FKSJ,KH,AQM,XPXLH,YYCSDM);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读发卡机构数据失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读持卡人数据失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=iR_DDF1EF07Info(hDev,picData);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读照片数据失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=iR_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读有效期失败!\r\n";
		UpdateData(false);
		return;
	}	  
	rt=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读地址失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=iR_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读联系人失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=iR_DF01EF07Info(hDev,WHCD,HYZK,ZY);	 
	if(rt)
	{
		UpdateData(true); 
		m_data+="读职业婚姻失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=iR_DF01EF08Info(hDev,ZJLB,ZJHM,JKDAH,XNHZH);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读证件信息失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=iR_DF02EF05Info(hDev,ABOXX,RHXX,XCBZ,XZBBZ,XNXGBBZ,DXBBZ,NXWLBZ,TNBBZ,QGYBZ,TXBZ,QGYZBZ,QGQSBZ,KZXYZBZ,XZQBQBZ,QTYXJSMC);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读临床信息失败!\r\n";
		UpdateData(false);
		return;
	}	
	rt=iR_DF02EF06Info(hDev,JSBBZ);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读特殊信息失败!\r\n";
		UpdateData(false);
		return;
	}	
	rt=iR_DF02EF07Info(hDev,1,GMWZMC,GMFY);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读过敏信息失败!\r\n";
		UpdateData(false);
		return;
	}	
	rt=iR_DF02EF08Info(hDev,1,MYJZMC,MYJZSJ);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读免疫信息失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=iR_DF03EDInfo (hDev,1,szData,0,3013,1);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读门诊信息1失败!\r\n";
		UpdateData(false);
		return;
	}
	rt=iR_DF03EEInfo (hDev,1,szData,0,1639,1);
	if(rt)
	{
		UpdateData(true); 
		m_data+="读住院信息1失败!\r\n";
		UpdateData(false);
		return;
	}
	end=clock();
	UpdateData(true); 
	CString temp;
	temp.Format("全读数据测试的时间:%d毫秒\r\n",end-start);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%d",end-start);
	if(!SetExcelData(16,2,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}

void CRWHealthSpeedTestDlg::OnBtnReadallhundred() 
{	
	HANDLE hDev=NULL;
	char KLB[100]={0};
	char GFBB[100]={0};
	char FKJGMC[100]={0};
	char FKJGDM[100]={0};
	char FKJGZS[500]={0};
	char FKSJ[100]={0};
	char KH[100]={0};
	char AQM[100]={0}; 
	char XPXLH[100]={0}; 
	char YYCSDM[100]={0};
	////////////////////
	char XM[50]={0};             //姓名
	char XB[50]={0};               //性别代码
	char MZ[50]={0};               //民族代码
	char CSRQ[50]={0};             //出生日期，YYYYMMDD格式
	char SFZH[50]={0};            //居民身份证号
	////////////////////
	char KYXQ[21]={0};			//卡有效期
	char BRDH1[21]={0};         //本人电话1
	char BRDH2[21]={0};           //本人电话2
	char YLFYZFFS1[21]={0};		  //医疗费用支付方式1
	char YLFYZFFS2[21]={0};		  //医疗费用支付方式2
	char YLFYZFFS3[21]={0};	
	/////////////////////////
	unsigned char picData[3075]={0};
	/////////////////////////
	char DZLB1[21]={0};		
	char DZ1[120]={0};       
	char DZLB2[21]={0};     
	char DZ2[120]={0};	
	//////////////////////////
	char LXRXM1[40]={0};		
	char LXRGX1[2]={0};       
	char LXRDH1[30]={0};
	char LXRXM2[40]={0};		
	char LXRGX2[2]={0};       
	char LXRDH2[30]={0}; 
	char LXRXM3[40]={0};		
	char LXRGX3[2]={0};       
	char LXRDH3[30]={0}; 
	//////////////////
	char WHCD[10]={0};		
	char HYZK[10]={0};       
	char ZY[10]={0}; 
	//////////////////
	char ZJLB[20]={0};		
	char ZJHM[20]={0};       
	char JKDAH[20]={0};
	char XNHZH[20]={0};
	//////////////////////
	char ABOXX[10]={0};		
	char RHXX[10]={0};       
	char XCBZ[10]={0};
	char XZBBZ[10]={0};
	char XNXGBBZ[10]={0};         //心脑血管病标志
	char DXBBZ[10]={0};           //癫痫病标志
	char NXWLBZ[10]={0};          //凝血紊乱标志
	char TNBBZ[10]={0};           //糖尿病标志
	char QGYBZ[10]={0};           //青光眼标志
	char TXBZ[10]={0};          //透析标志
	char QGYZBZ[10]={0};          //器官移植标志
	char QGQSBZ[10]={0};        //器官缺失标志
	char KZXYZBZ[10]={0};         //可装卸义肢标志
	char XZQBQBZ[10]={0};        //心脏起搏器标志
	char QTYXJSMC[50]={0};
	//////////////////////////
	char JSBBZ[10]={0};	
	///////////////////
	char GMWZMC[30]={0};	
	char GMFY[120]={0};	
	///////////////////////
	char MYJZMC[30]={0};	
	char MYJZSJ[10]={0};
	///////////////////
	char szData[5000]={0};
	int iRSuccess=0,iWRSuccess=0;
	clock_t start,end;
	int rt=0;
	start=clock();
	for(int i=0;i<100;i++)
	{
		rt=iR_DDF1EF05Info(hDev,KLB, GFBB,FKJGMC,FKJGDM,FKJGZS,FKSJ,KH,AQM,XPXLH,YYCSDM);
		if(rt)
			continue;
		rt=iR_DDF1EF06Info(hDev,XM,XB,MZ,CSRQ,SFZH);
		if(rt)
			continue;
		rt=iR_DDF1EF07Info(hDev,picData);
		if(rt)
			continue;
		rt=iR_DDF1EF08Info(hDev,KYXQ,BRDH1,BRDH2,YLFYZFFS1,YLFYZFFS2,YLFYZFFS3);
		if(rt)
			continue;
		rt=iR_DF01EF05Info(hDev,DZLB1,DZ1,DZLB2,DZ2);
		if(rt)
			continue;
		rt=iR_DF01EF06Info(hDev,LXRXM1,LXRGX1,LXRDH1,LXRXM2,LXRGX2,LXRDH2,LXRXM3,LXRGX3,LXRDH3);
		if(rt)
			continue;
		rt=iR_DF01EF07Info(hDev,WHCD,HYZK,ZY);	 
		if(rt)
			continue;
		rt=iR_DF01EF08Info(hDev,ZJLB,ZJHM,JKDAH,XNHZH);
		if(rt)
			continue;
		rt=iR_DF02EF05Info(hDev,ABOXX,RHXX,XCBZ,XZBBZ,XNXGBBZ,DXBBZ,NXWLBZ,TNBBZ,QGYBZ,TXBZ,QGYZBZ,QGQSBZ,KZXYZBZ,XZQBQBZ,QTYXJSMC);
		if(rt)
			continue;
		rt=iR_DF02EF06Info(hDev,JSBBZ);
		if(rt)
			continue;
		rt=iR_DF02EF07Info(hDev,1,GMWZMC,GMFY);
		if(rt)
			continue;
		rt=iR_DF02EF08Info(hDev,1,MYJZMC,MYJZSJ);
		if(rt)
			continue;
		rt=iR_DF03EDInfo (hDev,1,szData,0,3013,1);
		if(rt)
			continue;
		rt=iR_DF03EEInfo (hDev,1,szData,0,1639,1);
		if(rt)
			continue;
		iRSuccess++;
	}
	end=clock();
	double dTemp=(end-start)/100.0;
	double dRTemp=(iRSuccess/100.0)*100;
	UpdateData(true); 
	CString temp;
	temp.Format("100次全读测试的平均时间:%f毫秒\r\n100次全读测试的成功率:%f％\r\n",dTemp,dRTemp);
	m_data+=temp;
	UpdateData(false);

	temp.Format("%f",dTemp);
	if(!SetExcelData(16,4,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();

	temp.Format("%f％",dRTemp);
	if(!SetExcelData(16,5,temp.GetBuffer(0)))
	{
		UpdateData(true); 
		CString temp;
		temp.Format("写入表格失败!\r\n");
		m_data+=temp;
		UpdateData(false);
	}
	temp.ReleaseBuffer();
}



bool CRWHealthSpeedTestDlg::SetExcelData(int row, int column, char *szData)
{
	COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CString path;
	char path2[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,path2);
	path=path2;
	path+="\\ReaderSpeedTest.xls";
	_Application objApp;
	_Workbook objBook;
	Workbooks objBooks;
	Worksheets objSheets;
	_Worksheet objSheet;
	Range objRange, usedRange;
	objApp.SetAlertBeforeOverwriting(FALSE);
	objApp.SetDisplayAlerts(FALSE);
	if (!objApp.CreateDispatch("Excel.Application"))
	{
		::AfxMessageBox("确认是否安装了Excel");
		return false;
	}
	objBooks = objApp.GetWorkbooks();
	objBook = objBooks.Open(path, VOptional, VOptional, VOptional, VOptional, VOptional, 
	VOptional, VOptional, VOptional, VOptional, VOptional, VOptional, VOptional, VOptional, VOptional);
	objSheets = objBook.GetWorksheets();
	objSheet = objSheets.GetItem(COleVariant((short)1));
	objRange.AttachDispatch(objSheet.GetCells(), true);
	/////////////////////////////////
	char temp[100]={0};
	strcpy(temp,(const char *)szData);
	objRange.SetItem(COleVariant(long(row)),COleVariant(long(column)),COleVariant(temp));
	objRange.AttachDispatch(objSheet.GetColumns(),true);
				//				// 保存文件
	objBook.Save();
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	objBook.SetSaved(TRUE);
	//				objBook.SaveAs(COleVariant(path.GetBuffer(0)),covOptional,covOptional,covOptional,
	//					covOptional,covOptional,(long)0,covOptional,covOptional,covOptional,covOptional,covOptional);
	path.ReleaseBuffer();
	objRange.ReleaseDispatch();
	//				// 关闭文件
	objRange.Clear();
	objBook.Close(COleVariant((short)FALSE),VOptional,VOptional);
	objBooks.Close();
	objApp.Quit();	
	return true;
}
