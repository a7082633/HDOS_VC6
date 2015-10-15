// dialogInput2.cpp : implementation file
//

#include "stdafx.h"
#include "InterfaceDemo.h"
#include "dialogInput2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dialogInput2 dialog

int CheckDec(CString strIN);
int CheckHex(CString strIN);

dialogInput2::dialogInput2(CWnd* pParent /*=NULL*/)
	: CDialog(dialogInput2::IDD, pParent)
{
	//{{AFX_DATA_INIT(dialogInput2)
	m_edit1 = _T("");
	m_edit10 = _T("");
	m_edit11 = _T("");
	m_edit12 = _T("");
	m_edit13 = _T("");
	m_edit14 = _T("");
	m_edit15 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit4 = _T("");
	m_edit5 = _T("");
	m_edit6 = _T("");
	m_edit7 = _T("");
	m_edit8 = _T("");
	m_edit9 = _T("");
	//}}AFX_DATA_INIT
}


void dialogInput2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dialogInput2)
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT10, m_edit10);
	DDX_Text(pDX, IDC_EDIT11, m_edit11);
	DDX_Text(pDX, IDC_EDIT12, m_edit12);
	DDX_Text(pDX, IDC_EDIT13, m_edit13);
	DDX_Text(pDX, IDC_EDIT14, m_edit14);
	DDX_Text(pDX, IDC_EDIT15, m_edit15);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_EDIT6, m_edit6);
	DDX_Text(pDX, IDC_EDIT7, m_edit7);
	DDX_Text(pDX, IDC_EDIT8, m_edit8);
	DDX_Text(pDX, IDC_EDIT9, m_edit9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dialogInput2, CDialog)
	//{{AFX_MSG_MAP(dialogInput2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dialogInput2 message handlers

void dialogInput2::OnCancel() 
{
	m_edit1 = _T("");
	m_edit10 = _T("");
	m_edit11 = _T("");
	m_edit12 = _T("");
	m_edit13 = _T("");
	m_edit14 = _T("");
	m_edit15 = _T("");
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


bool iserase(CString t)
{
	CString tmp ;
	tmp = t;
	tmp.MakeLower();
	if (tmp.Compare("%erase%") )
		return false;
	else
		return true;
}


void dialogInput2::OnOK() 
{
	UpdateData(TRUE);

	if (!iserase(m_edit1))
	{
	if (((m_edit1.GetLength() != 2 ) && (m_edit1.GetLength() != 0 )) ||(CheckHex(m_edit1) != 0))
		{
			MessageBox("ABO数据错误","", MB_ICONERROR);
			return;
		}
	}
	if (!iserase(m_edit2))
	{
	if ((m_edit2.GetLength() > 2 ) ||(CheckDec(m_edit2) != 0))
		{
			MessageBox("RH数据错误","", MB_ICONERROR);
			return;
		}
	}
	if (!iserase(m_edit3))
	{
	if (((m_edit3.GetLength() != 2 ) && (m_edit3.GetLength() != 0 )) ||(CheckHex(m_edit3) != 0))
		{
			MessageBox("哮喘数据错误","", MB_ICONERROR);
			return;
		}
	}
	if (!iserase(m_edit4))
	{
	if (((m_edit4.GetLength() != 2 ) && (m_edit4.GetLength() != 0 )) ||(CheckHex(m_edit4) != 0))
		{
			MessageBox("心脏病数据错误","", MB_ICONERROR);
			return;
		}
	}
	if (!iserase(m_edit5))
	{
	if (((m_edit5.GetLength() != 2 ) && (m_edit5.GetLength() != 0 )) ||(CheckHex(m_edit5) != 0))
		{
			MessageBox("心血管数据错误","", MB_ICONERROR);
			return;
		}
	}
	if (!iserase(m_edit6))
	{
	if (((m_edit6.GetLength() != 2 ) && (m_edit6.GetLength() != 0 )) ||(CheckHex(m_edit6) != 0))
		{
			MessageBox("癫痫病数据错误","", MB_ICONERROR);
			return;
		}
	}
	if (!iserase(m_edit7))
	{
	if (((m_edit7.GetLength() != 2 ) && (m_edit7.GetLength() != 0 )) ||(CheckHex(m_edit7) != 0))
		{
			MessageBox("凝血紊乱数据错误","", MB_ICONERROR);
			return;
		}
	}
	if (!iserase(m_edit8))
	{
	if (((m_edit8.GetLength() != 2 ) && (m_edit8.GetLength() != 0 )) ||(CheckHex(m_edit8) != 0))
		{
			MessageBox("糖尿病数据错误","", MB_ICONERROR);
			return;
		}
	}
	if (!iserase(m_edit9))
	{
	if (((m_edit9.GetLength() != 2 ) && (m_edit9.GetLength() != 0 )) ||(CheckHex(m_edit9) != 0))
		{
			MessageBox("青光眼数据错误","", MB_ICONERROR);
			return;
		}
	}

	if (!iserase(m_edit10))
	{
	if (((m_edit10.GetLength() != 2 ) && (m_edit10.GetLength() != 0 )) ||(CheckHex(m_edit10) != 0))
		{
			MessageBox("透析数据错误","", MB_ICONERROR);
			return;
	}}
	if (!iserase(m_edit11))
	{
	if (((m_edit11.GetLength() != 2 ) && (m_edit11.GetLength() != 0 )) ||(CheckHex(m_edit11) != 0))
		{
			MessageBox("器官移植数据错误","", MB_ICONERROR);
			return;
	}}
	if (!iserase(m_edit12))
	{
	if (((m_edit12.GetLength() != 2 ) && (m_edit12.GetLength() != 0 )) ||(CheckHex(m_edit12) != 0))
		{
			MessageBox("器官缺失数据错误","", MB_ICONERROR);
			return;
	}}
	if (!iserase(m_edit13))
	{
	if (((m_edit13.GetLength() != 2 ) && (m_edit13.GetLength() != 0 )) ||(CheckHex(m_edit13) != 0))
		{
			MessageBox("可装卸义肢数据错误","", MB_ICONERROR);
			return;
	}}
	if (!iserase(m_edit14))
	{
	if (((m_edit14.GetLength() != 2 ) && (m_edit14.GetLength() != 0 )) ||(CheckHex(m_edit14) != 0))
		{
			MessageBox("心脏起搏器数据错误","", MB_ICONERROR);
			return;
	}}
	
	if (!iserase(m_edit15))
	{
	if (strlen(m_edit15) > 40 ) 
		{
			MessageBox("其他医学警示数据错误","", MB_ICONERROR);
			return;
	}}
	_CancelPressed = false;
	CDialog::OnOK();
}
