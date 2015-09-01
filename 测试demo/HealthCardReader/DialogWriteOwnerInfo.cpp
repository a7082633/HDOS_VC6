// DialogWriteOwnerInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWriteOwnerInfo.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteOwnerInfo dialog


CDialogWriteOwnerInfo::CDialogWriteOwnerInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWriteOwnerInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWriteOwnerInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWriteOwnerInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWriteOwnerInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWriteOwnerInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWriteOwnerInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteOwnerInfo message handlers

void CDialogWriteOwnerInfo::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogWriteOwnerInfo::OnBtnWrite() 
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
	CString KYXQ;                                                                                       
	CString  BRDH1;                                                                                        
	CString  BRDH2;                                                                                     
	CString  YLFYZFFS1;  
	CString  YLFYZFFS2;	
	CString  YLFYZFFS3;	
	this->GetDlgItemText(IDC_EDIT_KYXQ,KYXQ);
	this->GetDlgItemText(IDC_EDIT_BRDTH1,BRDH1);
	this->GetDlgItemText(IDC_EDIT_BRDTH2,BRDH2);
	this->GetDlgItemText(IDC_EDIT_YLFYZFFS1,YLFYZFFS1);
	this->GetDlgItemText(IDC_EDIT_YLFYZFFS2,YLFYZFFS2);
	this->GetDlgItemText(IDC_EDIT_YLFYZFFS3,YLFYZFFS3);
	re=iW_DDF1EF08Info(hDev,KYXQ.GetBuffer(0),BRDH1.GetBuffer(0),BRDH2.GetBuffer(0),YLFYZFFS1.GetBuffer(0),YLFYZFFS2.GetBuffer(0),YLFYZFFS3.GetBuffer(0));
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
