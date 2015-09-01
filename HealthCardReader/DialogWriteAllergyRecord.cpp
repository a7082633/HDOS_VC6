// DialogWriteAllergyRecord.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWriteAllergyRecord.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteAllergyRecord dialog


CDialogWriteAllergyRecord::CDialogWriteAllergyRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWriteAllergyRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWriteAllergyRecord)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWriteAllergyRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWriteAllergyRecord)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWriteAllergyRecord, CDialog)
	//{{AFX_MSG_MAP(CDialogWriteAllergyRecord)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteAllergyRecord message handlers

void CDialogWriteAllergyRecord::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogWriteAllergyRecord::OnBtnWrite() 
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
	CString GMWZMC;         
	CString GMFY;                                                                                        
	this->GetDlgItemText(IDC_EDIT_GMWZMC,GMWZMC);
	this->GetDlgItemText(IDC_EDIT_GMFY,GMFY);
	re=iW_DF02EF07Info(hDev,GMWZMC.GetBuffer(0),GMFY.GetBuffer(0));
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
