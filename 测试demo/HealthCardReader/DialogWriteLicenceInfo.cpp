// DialogWriteLicenceInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWriteLicenceInfo.h"
#include "HealthCardReaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteLicenceInfo dialog


CDialogWriteLicenceInfo::CDialogWriteLicenceInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWriteLicenceInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWriteLicenceInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWriteLicenceInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWriteLicenceInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWriteLicenceInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWriteLicenceInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteLicenceInfo message handlers

void CDialogWriteLicenceInfo::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogWriteLicenceInfo::OnBtnWrite() 
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
	CString ZJLB;                                                                                       
	CString  ZJHM;                                                                                        
	CString  JKDAH;                                                                                     
	CString  XNHZH;  
	this->GetDlgItemText(IDC_EDIT_ZJLB,ZJLB);
	this->GetDlgItemText(IDC_EDIT_ZJHM,ZJHM);
	this->GetDlgItemText(IDC_EDIT_JKDAH,JKDAH);
	this->GetDlgItemText(IDC_EDIT_XNHZH,XNHZH);
	re=iW_DF01EF08Info(hDev,ZJLB.GetBuffer(0),ZJHM.GetBuffer(0),JKDAH.GetBuffer(0),XNHZH.GetBuffer(0));
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
