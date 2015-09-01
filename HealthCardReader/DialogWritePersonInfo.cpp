// DialogWritePersonInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWritePersonInfo.h"
#include "HealthCardReaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWritePersonInfo dialog


CDialogWritePersonInfo::CDialogWritePersonInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWritePersonInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWritePersonInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWritePersonInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWritePersonInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWritePersonInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWritePersonInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWritePersonInfo message handlers

void CDialogWritePersonInfo::OnBtnWrite() 
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
	CString XM;                                                                                       
	CString  XB;                                                                                        
	CString  MZ;                                                                                     
	CString  CSRQ;  
	CString  SFZH;	
	this->GetDlgItemText(IDC_EDIT_XM,XM);
	this->GetDlgItemText(IDC_EDIT_XB,XB);
	this->GetDlgItemText(IDC_EDIT_MZ,MZ);
	this->GetDlgItemText(IDC_EDIT_CSRQ,CSRQ);
	this->GetDlgItemText(IDC_EDIT_SFZH,SFZH);
	re=iW_DDF1EF06Info(hDev,XM.GetBuffer(0),XB.GetBuffer(0),MZ.GetBuffer(0),CSRQ.GetBuffer(0),SFZH.GetBuffer(0));
	if(re!=0)
	{
		CString temp;
		temp.Format("写入失败,错误代码:%d\r\n",re);
		dlg->UpdateData();
		dlg->m_sData=temp;
		dlg->UpdateData(FALSE);
		CDialog::OnOK();
		return;
	}
	dlg->UpdateData();
	dlg->m_sData="写入成功\r\n";
	dlg->UpdateData(FALSE);
	CDialog::OnOK();
}

void CDialogWritePersonInfo::OnOK() 
{	
	CDialog::OnOK();
}
