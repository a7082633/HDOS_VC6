// DialogWriteRelativeInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWriteRelativeInfo.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteRelativeInfo dialog


CDialogWriteRelativeInfo::CDialogWriteRelativeInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWriteRelativeInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWriteRelativeInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWriteRelativeInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWriteRelativeInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWriteRelativeInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWriteRelativeInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteRelativeInfo message handlers

void CDialogWriteRelativeInfo::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogWriteRelativeInfo::OnBtnWrite() 
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
	CString LXRXM1;                                                                                            
	CString  LXRGX1;                                                                                            
	CString  LXRDH1;                                                                                         
	CString  LXRXM2;      
	CString  LXRGX2;	
	CString  LXRDH2;                                                                             
	CString  LXRXM3;        
	CString  LXRGX3;                                                                                               
	CString  LXRDH3;    
	this->GetDlgItemText(IDC_EDIT_LXRXM1,LXRXM1);
	this->GetDlgItemText(IDC_EDIT_LXRGX1,LXRGX1);
	this->GetDlgItemText(IDC_EDIT_LXRDH1,LXRDH1);
	this->GetDlgItemText(IDC_EDIT_LXRXM2,LXRXM2);
	this->GetDlgItemText(IDC_EDIT_LXRGX2,LXRGX2);
	this->GetDlgItemText(IDC_EDIT_LXRDH2,LXRDH2);
	this->GetDlgItemText(IDC_EDIT_LXRXM3,LXRXM3);
	this->GetDlgItemText(IDC_EDIT_LXRGX3,LXRGX3);
	this->GetDlgItemText(IDC_EDIT_LXRDH3,LXRDH3);
	re=iW_DF01EF06Info(hDev,LXRXM1.GetBuffer(0),LXRGX1.GetBuffer(0),LXRDH1.GetBuffer(0),LXRXM2.GetBuffer(0),LXRGX2.GetBuffer(0),LXRDH2.GetBuffer(0),LXRXM3.GetBuffer(0),LXRGX3.GetBuffer(0),LXRDH3.GetBuffer(0));
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
