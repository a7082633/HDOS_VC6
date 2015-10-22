// InputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InterfaceDemo.h"
#include "InputDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InputDialog dialog
static int _formType;

InputDialog::InputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(InputDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(InputDialog)
	m_static1 = _T("");
	m_static2 = _T("");
	m_static3 = _T("");
	m_static4 = _T("");
	m_static5 = _T("");
	m_static6 = _T("");
	m_static7 = _T("");
	m_static8 = _T("");
	m_static9 = _T("");
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit4 = _T("");
	m_edit5 = _T("");
	m_edit6 = _T("");
	m_edit7 = _T("");
	m_edit8 = _T("");
	m_edit9 = _T("");
	m_static10 = _T("");
	m_edit10 = _T("");
	//}}AFX_DATA_INIT

//	switch (type)
//	{
//	case 0 :
//		m_static1 = "测试1";
//		UpdateData(TRUE);
//		break;
//
//	case 1:
//		m_static1 = "测试1";
//		UpdateData(TRUE);
//		break;
//	}
}


void InputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InputDialog)
	DDX_Control(pDX, IDC_EDIT1, m_cedit1);
	DDX_Text(pDX, IDC_STATIC1, m_static1);
	DDX_Text(pDX, IDC_STATIC2, m_static2);
	DDX_Text(pDX, IDC_STATIC3, m_static3);
	DDX_Text(pDX, IDC_STATIC4, m_static4);
	DDX_Text(pDX, IDC_STATIC5, m_static5);
	DDX_Text(pDX, IDC_STATIC6, m_static6);
	DDX_Text(pDX, IDC_STATIC7, m_static7);
	DDX_Text(pDX, IDC_STATIC8, m_static8);
	DDX_Text(pDX, IDC_STATIC9, m_static9);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_EDIT6, m_edit6);
	DDX_Text(pDX, IDC_EDIT7, m_edit7);
	DDX_Text(pDX, IDC_EDIT8, m_edit8);
	DDX_Text(pDX, IDC_EDIT9, m_edit9);
	DDX_Text(pDX, IDC_STATIC10, m_static10);
	DDX_Text(pDX, IDC_EDIT10, m_edit10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InputDialog, CDialog)
	//{{AFX_MSG_MAP(InputDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InputDialog message handlers

void InputDialog::OnCancel() 
{
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit4 = _T("");
	m_edit5 = _T("");
	m_edit6 = _T("");
	m_edit7 = _T("");
	m_edit8 = _T("");
	m_edit9 = _T("");
	_CancelPressed = true;
	CDialog::OnCancel();
}


int CheckDec(CString strIN)
{
	char StrIN[256];
	strcpy(StrIN , strIN);
	int Lng,i;
	char C[2];
	Lng=strlen(StrIN);
	for(i=1;i<=Lng;i++)
	{
		memcpy(C,StrIN+i-1,1);
		if (!((C[0]>=0x30 )&&(C[0]<=0x39)))
		return -1;
	}
	return 0;
}


int CheckHex(CString strIN)
{
	char StrIN[256];
	strcpy(StrIN , strIN);
	int Lng,i;
	char C[2];
	Lng=strlen(StrIN);
	for(i=1;i<=Lng;i++)
	{
		memcpy(C,StrIN+i-1,1);
		if (  !((C[0]>=0x30 && C[0]<=0x39)||(C[0]>=0x41 && C[0]<=0x46)||(C[0]>=0x61 && C[0]<=0x66))  )
		return -1;
	}
	return 0;
}


bool isErase(CString t)
{
	CString tmp ;
	tmp = t;
	tmp.MakeLower();
	if (tmp.Compare("%erase%") )
		return false;
	else
		return true;
}

void InputDialog::OnOK() 
{
	UpdateData(TRUE);
	int i;
	switch(_formType) 
	{
	case FILE_DDF1EF08:
		if (!isErase(m_edit1))
		{
			if ((m_edit1.GetLength() > 8) ||(CheckDec(m_edit1) != 0))
			{
				MessageBox("卡有效期数据错误","", MB_ICONERROR);
				return;
			}
		}
		i = strlen(m_edit2);
		if (i > 20) 
		{
			MessageBox("本人电话1数据错误","", MB_ICONERROR);
			return;
		}
		i = strlen(m_edit3);
		if (i > 20) 
		{
			MessageBox("本人电话2数据错误","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit4))
		{
		if ((m_edit4.GetLength() > 2) ||(CheckDec(m_edit4) != 0))
		{
			MessageBox("医疗费用支付方式1数据错误","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit5))
		{
		if ((m_edit5.GetLength() > 2) ||(CheckDec(m_edit5) != 0))
		{
			MessageBox("医疗费用支付方式2数据错误","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit6))
		{
		if ((m_edit6.GetLength() > 2) ||(CheckDec(m_edit6) != 0))
		{
			MessageBox("医疗费用支付方式6数据错误","", MB_ICONERROR);
			return;
		}}
		
		break;
	case FILE_DF01EF05:
		if (!isErase(m_edit1))
		{
		if ((m_edit1.GetLength() > 2) ||(CheckDec(m_edit1) != 0))
		{
			MessageBox("地址类别1数据错误","", MB_ICONERROR);
			return;
		}}
		i = strlen(m_edit2);
		if (i > 100) 
		{
			MessageBox("地址1数据错误","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit3))
		{
		if ((m_edit3.GetLength() > 2) ||(CheckDec(m_edit3) != 0))
		{
			MessageBox("地址类别2数据错误","", MB_ICONERROR);
			return;
		}}
		i = strlen(m_edit4);
		if (i > 100) 
		{
			MessageBox("地址2数据错误","", MB_ICONERROR);
			return;
		}
		break;
	case FILE_DF01EF06:
		i = strlen(m_edit1);
		if (i > 30) 
		{
			MessageBox("联系人姓名1数据错误","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit2))
		{
			if ((m_edit2.GetLength() > 2) ||(CheckDec(m_edit2) != 0))
			{
				MessageBox("联系人关系1数据错误","", MB_ICONERROR);
				return;
			}
		}
		if (strlen(m_edit3) > 20) 
		{
			MessageBox("联系人电话1数据错误","", MB_ICONERROR);
			return;
		}
		i = strlen(m_edit4);
		if (i > 30) 
		{
			MessageBox("联系人姓名2数据错误","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit5))
		{
			if ((m_edit5.GetLength() > 2) ||(CheckDec(m_edit5) != 0))
			{
				MessageBox("联系人关系2数据错误","", MB_ICONERROR);
				return;
			}
		}
		if (strlen(m_edit6) > 20) 
		{
			MessageBox("联系人电话2数据错误","", MB_ICONERROR);
			return;
		}
		i = strlen(m_edit7);
		if (i > 30) 
		{
			MessageBox("联系人姓名3数据错误","", MB_ICONERROR);
			return;
		}
		if (!isErase(m_edit8))
		{
		if ((m_edit8.GetLength() > 2) ||(CheckDec(m_edit8) != 0))
		{
			MessageBox("联系人关系3数据错误","", MB_ICONERROR);
			return;
		}}
		if (strlen(m_edit9) > 20) 
		{
			MessageBox("联系人电话3数据错误","", MB_ICONERROR);
			return;
		}

		break;
	case FILE_DF01EF07:
		if (!isErase(m_edit1))
		{
		if ((m_edit1.GetLength() > 2) ||(CheckDec(m_edit1) != 0))
		{
			MessageBox("文化程度代码数据错误","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit2))
		{
		if ((m_edit2.GetLength() > 2) ||(CheckDec(m_edit2) != 0))
		{
			MessageBox("婚姻状况代码数据错误","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit3))
		{
			if (strlen(m_edit3) > 3) 
			{
				MessageBox("职业代码数据错误","", MB_ICONERROR);
				return;
			}
		}
		break;
	case FILE_DF01EF08:
		if (!isErase(m_edit1))
		{
		if ((m_edit1.GetLength() > 2) ||(CheckDec(m_edit1) != 0))
		{
			MessageBox("证件类别数据错误","", MB_ICONERROR);
			return;
		}}
		if (!isErase(m_edit2))
		{
		if (strlen(m_edit2) > 18) 
		{
			MessageBox("证件号码数据错误","", MB_ICONERROR);
			return;
		}}
		if (strlen(m_edit3) > 17) 
		{
			MessageBox("健康档案编号数据错误","", MB_ICONERROR);
			return;
		}
		if (strlen(m_edit4) > 18) 
		{
			MessageBox("新农合证号数据错误","", MB_ICONERROR);
			return;
		}

		break;
	case FILE_DF02EF05:		
		break;
	case FILE_DF02EF06:
		if (!isErase(m_edit1))
		{
		if ((m_edit1.GetLength() != 2) ||(CheckHex(m_edit1) != 0))
		{
			MessageBox("精神病标志数据错误","", MB_ICONERROR);
			return;
		}}
		break;	
	case FILE_DF02EF07:
		if (strlen(m_edit1) > 20) 
		{
			MessageBox("过敏物质名称数据错误","", MB_ICONERROR);
			return;
		}
		if (strlen(m_edit2) > 100) 
		{
			MessageBox("过敏反应数据错误","", MB_ICONERROR);
			return;
		}

		break;
	case FILE_DF02EF08:
		if (strlen(m_edit1) > 20) 
		{
			MessageBox("免疫接种名称数据错误","", MB_ICONERROR);
			return;
		}
		if ((m_edit2.GetLength() > 8) ||(CheckDec(m_edit2) != 0))
		{
			MessageBox("免疫接种时间数据错误","", MB_ICONERROR);
			return;
		}
		break;
	default:
		break;
	}
	_CancelPressed = false;
	CDialog::OnOK();
}

void InputDialog::Setview(int type)
{
	_formType = type;

	switch (type)
	{
	case FILE_DDF1EF05:
		m_static1 = "卡类别  an01";
		m_static2 = "规范版本 an04";
		m_static3 = "发卡机构名称 an30";
		m_static4 = "发卡机构代码 cn11";
		m_static5 = "发卡机构证书 b180";
		m_static6 = "发卡时间 cn4";
		
		m_static7 = "卡号 an18";
		m_static8 = "安全码 an3";
		m_static9 = "发卡序列号 an10";
		m_static10 = "应用城市代码 cn3";
		break;
	case FILE_DDF1EF06:
		m_static1 = "姓名  an30";
		m_static2 = "性别 b1";
		m_static3 = "民族代码 cn1";
		m_static4 = "出生日期 cn4";
		m_static5 = "居民身份证号码 an18";
		break;
	case FILE_DDF1EF08:
		m_static1 = "卡有效期  cn4";
		m_static2 = "本人电话1 an20";
		m_static3 = "本人电话2 an20";
		m_static4 = "医疗费用支付方式1 cn1";
		m_static5 = "医疗费用支付方式2 cn1";
		m_static6 = "医疗费用支付方式3 cn1";		
		break;
	case FILE_DF01EF05:
		m_static1 = "地址类别1 cn1";
		m_static2 = "地址1	   an100";
		m_static3 = "地址类别2 cn1";
		m_static4 = "地址2	   an100";
		break;
	case FILE_DF01EF06:
		m_static1 = "联系人姓名1 an30";
		m_static2 = "联系人关系1 cn1";
		m_static3 = "联系人电话1 an20";
		m_static4 = "联系人姓名2 an30";
		m_static5 = "联系人关系2 cn1";
		m_static6 = "联系人电话2 an20";
		m_static7 = "联系人姓名3 an30";
		m_static8 = "联系人关系3 cn1";
		m_static9 = "联系人电话3 an20";
		break;
	case FILE_DF01EF07:
		m_static1 = "文化程度代码 cn1";
		m_static2 = "婚姻状况代码 cn1";
		m_static3 = "职业代码	  an3";
		break;
	case FILE_DF01EF08:
		m_static1 = "证件类别 cn1";
		m_static2 = "证件号码 an18";
		m_static3 = "健康档案编号 an17";
		m_static4 = "新农合证号   an18";
		break;
	case FILE_DF02EF05:		
		break;
	case FILE_DF02EF06:
		m_static1 = "精神病标志 b1";
		break;	
	case FILE_DF02EF07:
		m_static1 = "过敏物质名称 an20";
		m_static2 = "过敏反应	  an100";
		break;
	case FILE_DF02EF08:
		m_static1 = "免疫接种名称 an20";
		m_static2 = "免疫接种时间 cn4";

		break;
	default:
		m_static1 = "异常错误";
		break;
	}
	//UpdateData(TRUE);
}
