// DialogWriteSpecialInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWriteSpecialInfo.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteSpecialInfo dialog


CDialogWriteSpecialInfo::CDialogWriteSpecialInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWriteSpecialInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWriteSpecialInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWriteSpecialInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWriteSpecialInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWriteSpecialInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWriteSpecialInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteSpecialInfo message handlers

void CDialogWriteSpecialInfo::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogWriteSpecialInfo::OnBtnWrite() 
{
	//�ϵ�
	char ATR[100]={0};
	int re=PowerOn(hDev,0x01,ATR);
	if(re!=0)
	{
		this->MessageBox("�������ϵ�ʧ��!");
		return;
	}
	CHealthCardReaderDlg *dlg=(CHealthCardReaderDlg*)pDlg;
	CString JSBBZ;                                                                                            
	this->GetDlgItemText(IDC_EDIT_JSBBZ,JSBBZ);
	re=iW_DF02EF06Info(hDev,JSBBZ.GetBuffer(0));
	if(re!=0)
	{
		CString temp;
		temp.Format("д��ʧ��,�������:%d\r\n",re);
		dlg->UpdateData();
		dlg->m_sData=temp;
		dlg->UpdateData(FALSE);
		CDialog::OnOK();
		return;
	}
	dlg->UpdateData();
	dlg->m_sData="д��ɹ�\r\n";
	dlg->UpdateData(FALSE);
	CDialog::OnOK();
}