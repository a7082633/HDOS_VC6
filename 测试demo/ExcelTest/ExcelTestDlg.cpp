// ExcelTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExcelTest.h"
#include "ExcelTestDlg.h"

//首先别忘了包含头文件“excel.h”，若用到_variant_t()时，需要包含头文件“comdef.h”和“comutil.h”，否则会出现错误：
//“error C2065: '_variant_t' : undeclared identifier”
#include "excel.h"
#include "comdef.h"//里边定义了各种接口及类，是实现COM组件的基础类型
#include "comutil.h"
#include <direct.h>

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
// CExcelTestDlg dialog

CExcelTestDlg::CExcelTestDlg(CWnd* pParent /*=NULL*/)
: CDialog(CExcelTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExcelTestDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExcelTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExcelTestDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExcelTestDlg, CDialog)
//{{AFX_MSG_MAP(CExcelTestDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_EXCELTEST, OnExceltest)
ON_BN_CLICKED(IDC_OPEN_ADD, OnOpenAdd)
ON_BN_CLICKED(IDC_OPEN_READ, OnOpenRead)
ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelTestDlg message handlers

BOOL CExcelTestDlg::OnInitDialog()
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

void CExcelTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExcelTestDlg::OnPaint() 
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
HCURSOR CExcelTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//功能：打开Excel文件,使用Excel程序显示，不读数据，也不写入数据,手工使用鼠标关闭Excel文件。
//hlt2012.4.1
void CExcelTestDlg::OnExceltest() 
{
//_Application		CApplicaton		Application.h	Excel应用法度。
/*
	Workbooks	CWorkbooks	Workbooks.h	工作簿的容器，里面包含了Excel应用法度打开的所有工作簿。

	_Workbook	CWorkbook	Workbook.h		单个工作簿。

	Worksheets	CWorksheets	Worksheets.h	单个工作簿中的Sheet表格的容器，
											包含该工作簿中的所有Sheet。

	_Worksheet	CWorksheet	Worksheet.h	   单个Sheet表格。
		
	Range	CRange	Range.h	必然命量的单位格，可对单位格进行单个或多个单位格进行操纵。
*/
	// TODO: Add your control notification handler code here
	CString path;
	
	CString  str_t;
	CTime t = CTime::GetCurrentTime();//函数前要加CTime::，不然不会转换成现代日期
	int m_year = t.GetYear();
	int m_month = t.GetMonth();
	int m_day = t.GetDay();
	
	str_t.Format("\SSC_%d.%d.%d.",m_year,m_month,m_day);
	
	//sInfoPath = "F:\\Card信息";
	//sInfoPath = "\Card信息";
	sInfoPath = str_t;
	//	sInfoPath = sInfoPath + str_t;
	//DeleteFile(picPathstr);
	//创建EXCEL目录
//	path = sInfoPath;
//	_mkdir(path);//要#include <direct.h>
	
	//声明操作excel文件类的对象
    _Application objApp;// _application代表了EXCEL服务器   
    Workbooks objBooks; //workbooks表示整个Excel服务器(表现为一个.xls文件)里所有的表,
					//(可以通过"新建"得到多个表,即MDI程序里的一个视窗一样,所有的视窗就是workbooks), 
   	COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
    
	//检测电脑上是否安装了Excel程序。
    if(!objApp.CreateDispatch("Excel.Application"))     
	{ AfxMessageBox("无法启动Excel程序，请正确安装!");     
	return;     
	}     
	
    objApp.m_bAutoRelease   =   TRUE; //??什么意思？
	objApp.SetVisible(TRUE);  //打开Excel程序，没有显示任何数据。 
	
	objApp.SetUserControl(TRUE);//允许其它用户控制Excel,否则Excel将一闪即逝
	
	//下面两句的功能和 objBooks = objApp.GetWorkbooks();  一样。
    LPDISPATCH   pWkBooks   =   objApp.GetWorkbooks();  //GetWorkbooks什么功能？
	objBooks.AttachDispatch(pWkBooks,TRUE);   //将一个IDispatch连接附着于COleDispatchDriver对象
    
	//获得当前程序所在的路径,excel文件在此路径下。
    char CurrentProgramPath[MAX_PATH];     
    GetCurrentDirectory(MAX_PATH,CurrentProgramPath);   
    CString ExcelFilePathName =  CurrentProgramPath;//ExcelFilePathName表示excel文件的路径和文件名 
    //ExcelFilePathName   +=   "\\CardInfo.xls"; 
	ExcelFilePathName   +=   "\\sInfoPath";
	ExcelFilePathName   +=   ".xls";
	
    //打开Excel文件，如果前面设置了objApp.SetVisible(TRUE)，所以下句命令执行后，
														//显示这个excel文件的数据。
	//如果前面没有设置objAppApp.SetVisible(TRUE)，下句命令执行后，不会显示这个Excel文件的数据。
    //采用只读方式打开excel文件，_variant_t(true), true必须为小写，大写编译出错。
	objBooks.Open(ExcelFilePathName,VOptional, _variant_t(false), VOptional, VOptional, VOptional, VOptional, VOptional,     
		VOptional,  VOptional,  VOptional,   VOptional, VOptional,VOptional,VOptional);   
	
	
}

//打开Excel文件，读出其中的数据，供后面设置Mschart控件使用。
void CExcelTestDlg::OnOpenRead() 
{
	// TODO: Add your control notification handler code here
	
	//Excel文件使用三列，第一列表示序号，第二列表示第一组份的数据，第二列表示第二组份的数据。
	//声明操作excel文件类的对象
	_Application objApp;  //_application代表了EXCEL服务器  
    Workbooks objBooks;//workbooks表示整个Excel服务器(表现为一个.xls文件)里所有的表,
	//(可以通过"新建"得到多个表,即MDI程序里的一个视窗一样,所有的视窗就是workbooks), 
    _Workbook objBook;//_workbook就是一个表,相当于MDI中的一个视窗, 
    Worksheets objSheets; // worksheets表示所有的表单,每个表都可能有很多表单,
	//(建立一个Excel文件之后,打开,可以看到有sheet1,sheet2等,所有这些sheetn就组成了worksheets)  
    _Worksheet objSheet;//_worksheet就表示一个表单,

    Range objRange,usedRange;//Range 表示元素的集合  

    COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	
    VARIANT ret;
    CString cstr="";//接收读取到的内容
	
	//检测电脑上是否安装了Excel程序。
    if(!objApp.CreateDispatch("Excel.Application"))     
	{ AfxMessageBox("无法启动Excel服务器!");     
	return;     
	}     
	
    //objApp.SetVisible(TRUE);  //打开Excel程序，没有显示任何数据。
	
	// objApp.SetUserControl(FALSE);//允许其它用户控制Excel,否则Excel将一闪即逝
    
	// objApp.m_bAutoRelease   =   TRUE; //??什么意思？
	
	objBooks = objApp.GetWorkbooks();
	
    //获得当前程序所在的路径,excel文件在此路径下。
    char CurrentProgramPath[MAX_PATH];     
    GetCurrentDirectory(MAX_PATH,CurrentProgramPath);   
    CString ExcelFilePathName =  CurrentProgramPath;//ExcelFilePathName表示excel文件的路径和文件名 
    ExcelFilePathName   +=   "\\sInfoPath";
	ExcelFilePathName   +=   ".xls";    
	
    //打开Excel文件，如果前面设置了objApp.SetVisible(TRUE)，所以下句命令执行后，显示这个excel文件的数据。
	//如果前面没有设置objAppApp.SetVisible(TRUE)，下句命令执行后，不会显示这个Excel文件的数据。
    //采用只读方式打开excel文件，_variant_t(true), true必须为小写，大写编译出错。
    objBook = objBooks.Open(ExcelFilePathName,VOptional, _variant_t(true), VOptional, VOptional,  VOptional, 
		VOptional, VOptional, VOptional,  VOptional, VOptional, VOptional, VOptional,  VOptional, VOptional);
	
    objSheets = objBook.GetWorksheets();
    //设定当前的工作表sheet是excel文件的第几个工作表
	//sheet COleVariant((short)1)表示第一个 COleVariant((short)2)表示第二个
    objSheet = objSheets.GetItem(COleVariant((short)1));
	
    //获得已经使用的行数和列数。
    usedRange.AttachDispatch(objSheet.GetUsedRange());  
	
    objRange.AttachDispatch(usedRange.GetRows());
    long   iRowNum=objRange.GetCount();//已经使用的行数

    objRange.AttachDispatch(usedRange.GetColumns());
    long iColumnNum=objRange.GetCount();//已经使用的列数
	
    //设定读取的行列范围
    //objRange = objSheet.GetRange(COleVariant("A1"), COleVariant("C1000"));
    ret = objRange.GetValue(VOptional);
    COleSafeArray sa(ret);
	
	//读出内容。
    long lNumRows; long lNumCols;
    sa.GetUBound(1, &lNumRows); sa.GetUBound(2, &lNumCols);
	
    long index[2];
    VARIANT val;
    int row, column;
	
    for(row=1;row<=iRowNum;row++)//row表示行数
	{   
		for(column=1;column<=iColumnNum;column++)//c表示列数
			
		{	
			index[0]=row;index[1]=column;
			sa.GetElement(index, &val);//val类对象中包含取的row行、column列的内容
			switch(val.vt)
			{
			case VT_R8:   //数字
				{ //TRACE("\t\t%1.2f", val.dblVal);
					CString cstr2=""; 
					cstr2.Format("%1.1f",val.dblVal); cstr+=cstr2+"\n";
					break;
				}
			case VT_BSTR:  //文字
				{//TRACE("\t\t%s",(CString)val.bstrVal);
					cstr+=(CString)val.bstrVal+"\n";
					break;
				}
			case VT_EMPTY://表示此row行、column列的内容为空。
				break;
			}
		}
	}
    AfxMessageBox(cstr);
	
    objBook.Close(COleVariant((short)FALSE),VOptional,VOptional);
    objApp.Quit();
	
	
}


//打开一个Excel文件，在前面的数据后面添加新的数据
void CExcelTestDlg::OnOpenAdd() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr; 
	hr = CoInitialize(NULL); 
	bool isExist=true;
	//声明操作excel文件类的对象
	_Application   objApp;   //组件服务器的各个classes   //_application代表了EXCEL服务器    
	Workbooks   objBooks;//workbooks表示整个Excel服务器(表现为一个.xls文件)里所有的表,(可以通过"新建"得到多个表,即MDI程序里的一个视窗一样,所有的视窗就是workbooks), 
	_Workbook   objBook;     //_workbook就是一个表,相当于MDI中的一个视窗, 
	Worksheets   objSheets;  // worksheets表示所有的表单,每个表都可能有很多表单(建立一个Excel文件之后,打开,可以看到有sheet1,sheet2等,所有这些sheetn就组成了worksheets)  
	_Worksheet   objSheet;  //_worksheet就表示一个表单,   
	Range   objRange,usedRange; //Range 表示元素的集合  
	COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	objApp.SetAlertBeforeOverwriting(FALSE);
	objApp.SetDisplayAlerts(FALSE);
	//检测电脑上是否安装了Excel程序。
	if(!objApp.CreateDispatch("Excel.Application"))   //启动服务器     
	{   AfxMessageBox("无法启动Excel服务器!");     
	return;     
	} 
	
	//获得当前程序所在的路径,excel文件在此路径下。
	char CurrentProgramPath[MAX_PATH];     
	GetCurrentDirectory(MAX_PATH,CurrentProgramPath);   
	CString ExcelFilePathName =  CurrentProgramPath; 
	//ExcelFilePathName表示excel文件的路径和文件名 
	ExcelFilePathName   +=   "\\sInfoPath";
	ExcelFilePathName   +=   ".xls"; 
	
	objBooks=objApp.GetWorkbooks();
	//此句的功能objBooks = objApp.GetWorkbooks();一样
	//打开Excel文件，如果前面设置了objApp.SetVisible(TRUE)，所以下句命令执行后，显示这个excel文件的数据。
	//如果前面没有设置objAppApp.SetVisible(TRUE)，下句命令执行后，不会显示这个Excel文件的数据。
	try
	{
	objBook = objBooks.Open(ExcelFilePathName,VOptional,VOptional,
		VOptional,VOptional,VOptional,
		VOptional,VOptional,VOptional,
		VOptional,VOptional,VOptional,
		VOptional,VOptional,VOptional);   
	}catch(...)
	{
		objBook=objBooks.Add(vtMissing);
		isExist=false;
		//MessageBox("aaa");
	}

	objSheets = objBook.GetWorksheets(); 
	try
	{
		objSheet = objSheets.GetItem(COleVariant((short)1));
	}catch(...)
	{
		objSheet=objSheets.Add(vtMissing, vtMissing, _variant_t((long)1), vtMissing);
		//objSheet.SetName("test");
	}

	objRange.AttachDispatch(objSheet.GetCells(),true);

	
	//获得已经使用的行数
	usedRange = objSheet.GetUsedRange();

	usedRange = usedRange.GetRows();
	long iRowNum=usedRange.GetCount();//已经使用的行数 

	objRange.SetItem(COleVariant(long(1)),COleVariant(long(1)),COleVariant("header"));     
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(2)),COleVariant("header")); 
	
	objRange.SetItem(COleVariant(long(iRowNum+1)),COleVariant(long(1)),COleVariant("12"));     
	objRange.SetItem(COleVariant(long(iRowNum+1)),COleVariant(long(2)),COleVariant("34")); 
	
	if(isExist)
		objBook.Save();//如果打开的这个excel文件被其它的进程已经打开了，此句代码执行后，会出现提示是否保存的对话框。
	////如果打开的这个excel文件被其它的进程使用只读方式已经打开了，此句代码执行后，不会出现提示是否保存的对话框
	objBook.SetSaved(TRUE);
	if(!isExist)
		objBook.SaveAs(_variant_t(ExcelFilePathName),_variant_t(long(18)), vtMissing, vtMissing, vtMissing, 
			vtMissing, 0, vtMissing, vtMissing, vtMissing, 
			vtMissing, vtMissing);
	objRange.ReleaseDispatch();
	objRange.Clear();  
	objBook.Close(COleVariant((short)FALSE),VOptional,VOptional);
	objBooks.Close();     
	objApp.Quit();   
	
	
	
	
}

//类似
void CExcelTestDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	this->OnExceltest();
	
}
