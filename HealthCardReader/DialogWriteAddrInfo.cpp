// DialogWriteAddrInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWriteAddrInfo.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteAddrInfo dialog


CDialogWriteAddrInfo::CDialogWriteAddrInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWriteAddrInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWriteAddrInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWriteAddrInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWriteAddrInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWriteAddrInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWriteAddrInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteAddrInfo message handlers

void CDialogWriteAddrInfo::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogWriteAddrInfo::OnBtnWrite() //MHC_CARDINTERFACE_API DWORD __stdcall wsc_GetCardInfo(HANDLE hCard,void *pvSelect,int nItem);
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
	CString DZLB1;                                                                                       
	CString  DZ1;                                                                                        
	CString  DZLB2;                                                                                     
	CString  DZ2;  
	this->GetDlgItemText(IDC_EDIT_DZLB1,DZLB1);
	this->GetDlgItemText(IDC_EDIT_DZ1,DZ1);
	this->GetDlgItemText(IDC_EDIT_DZLB2,DZLB2);
	this->GetDlgItemText(IDC_EDIT_DZ2,DZ2);
	re=iW_DF01EF05Info(hDev,DZLB1.GetBuffer(0),DZ1.GetBuffer(0),DZLB2.GetBuffer(0),DZ2.GetBuffer(0));
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
