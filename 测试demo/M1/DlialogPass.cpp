// DlialogPass.cpp : implementation file
//

#include "stdafx.h"
#include "M1.h"
#include "DlialogPass.h"
#include "DialogLoadKey.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlialogPass dialog


CDlialogPass::CDlialogPass(CWnd* pParent /*=NULL*/)
	: CDialog(CDlialogPass::IDD, pParent)
{
	m_pass="";
	//{{AFX_DATA_INIT(CDlialogPass)
	//}}AFX_DATA_INIT
}


void CDlialogPass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlialogPass)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlialogPass, CDialog)
	//{{AFX_MSG_MAP(CDlialogPass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlialogPass message handlers

void CDlialogPass::OnOK() 
{
	m_list.m_hWnd=m_ListHwnd;
	CString sPass;
	this->GetDlgItemText(IDC_EDIT_PASS,sPass);
	if(sPass.GetLength()==12)
	{
		m_list.SetItemText(m_nItem,1,sPass);
		CDialog::OnOK();
	}else
		this->MessageBox("输入数据格式有误!");
}

BOOL CDlialogPass::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->SetDlgItemText(IDC_EDIT_PASS,	m_pass);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


