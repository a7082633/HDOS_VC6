// DialogWriteJobMarryInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWriteJobMarryInfo.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteJobMarryInfo dialog


CDialogWriteJobMarryInfo::CDialogWriteJobMarryInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWriteJobMarryInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWriteJobMarryInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWriteJobMarryInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWriteJobMarryInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWriteJobMarryInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWriteJobMarryInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteJobMarryInfo message handlers

void CDialogWriteJobMarryInfo::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogWriteJobMarryInfo::OnBtnWrite() 
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
	CString WHCD;                                                                                       
	CString  HYZK;                                                                                        
	CString  ZY;                                                                                     
	this->GetDlgItemText(IDC_EDIT_WHCD,WHCD);
	this->GetDlgItemText(IDC_EDIT_HYZK,HYZK);
	this->GetDlgItemText(IDC_EDIT_ZY,ZY);
	re=iW_DF01EF07Info(hDev,WHCD.GetBuffer(0),HYZK.GetBuffer(0),ZY.GetBuffer(0));
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
