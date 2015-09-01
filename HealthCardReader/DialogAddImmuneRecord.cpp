// DialogAddImmuneRecord.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogAddImmuneRecord.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogAddImmuneRecord dialog


CDialogAddImmuneRecord::CDialogAddImmuneRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAddImmuneRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAddImmuneRecord)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogAddImmuneRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAddImmuneRecord)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAddImmuneRecord, CDialog)
	//{{AFX_MSG_MAP(CDialogAddImmuneRecord)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAddImmuneRecord message handlers

void CDialogAddImmuneRecord::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogAddImmuneRecord::OnBtnWrite() 
{
	//上电
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("健康卡上电失败!");
		return;
	}
	CHealthCardReaderDlg *dlg=(CHealthCardReaderDlg*)pDlg;
	CString MYJZMC;                                                                                       
	CString  MYJZSJ;                                                                                        
	this->GetDlgItemText(IDC_EDIT_MYJZMC,MYJZMC);
	this->GetDlgItemText(IDC_EDIT_MYJZSJ,MYJZSJ);
	re=iW_DF02EF08Info(hDev,MYJZMC.GetBuffer(0),MYJZSJ.GetBuffer(0));
	if(re!=0)
	{
		CString temp;
		temp.Format("添加记录失败,错误代码:%d\r\n",re);
		dlg->UpdateData();
		dlg->m_sData=temp;
		dlg->UpdateData(FALSE);
		CDialog::OnOK();
		return;
	}
	dlg->UpdateData();
	dlg->m_sData="添加记录成功\r\n";
	dlg->UpdateData(FALSE);
	CDialog::OnOK();
}
