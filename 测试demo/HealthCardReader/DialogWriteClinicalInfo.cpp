// DialogWriteClinicalInfo.cpp : implementation file
//

#include "stdafx.h"
#include "HealthCardReader.h"
#include "DialogWriteClinicalInfo.h"
#include "HealthCardReaderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteClinicalInfo dialog


CDialogWriteClinicalInfo::CDialogWriteClinicalInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogWriteClinicalInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogWriteClinicalInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogWriteClinicalInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogWriteClinicalInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogWriteClinicalInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogWriteClinicalInfo)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogWriteClinicalInfo message handlers

void CDialogWriteClinicalInfo::OnOK() 
{	
	CDialog::OnOK();
}

void CDialogWriteClinicalInfo::OnBtnWrite() 
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
	CString ABOXX;           //ABO血型代码
	CString RHXX;            //RH血型代码
	CString XCBZ;            //哮喘标志
	CString XZBBZ;           //心脏病标志
	CString XNXGBBZ;         //心脑血管病标志
	CString DXBBZ;          //癫痫病标志
	CString NXWLBZ;          //凝血紊乱标志
	CString TNBBZ;          //糖尿病标志
	CString QGYBZ;           //青光眼标志
	CString TXBZ;            //透析标志
	CString QGYZBZ;          //器官移植标志
	CString QGQSBZ;          //器官缺失标志
	CString KZXYZBZ;         //可装卸义肢标志
	CString XZQBQBZ;         //心脏起搏器标志
	CString QTYXJSMC;         //其他医学警示名称                                                                                  
	this->GetDlgItemText(IDC_EDIT_ABOXX,ABOXX);
	this->GetDlgItemText(IDC_EDIT_RHXX,RHXX);
	this->GetDlgItemText(IDC_EDIT_XCBZ,XCBZ);
	this->GetDlgItemText(IDC_EDIT_XZBBZ,XZBBZ);
	this->GetDlgItemText(IDC_EDIT_XNXGBBZ,XNXGBBZ);
	this->GetDlgItemText(IDC_EDIT_DXBBZ,DXBBZ);
	this->GetDlgItemText(IDC_EDIT_NXWLBZ,NXWLBZ);
	this->GetDlgItemText(IDC_EDIT_TNBBZ,TNBBZ);
	this->GetDlgItemText(IDC_EDIT_QGYBZ,QGYBZ);
	this->GetDlgItemText(IDC_EDIT_TXBZ,TXBZ);
	this->GetDlgItemText(IDC_EDIT_QGYZBZ,QGYZBZ);
	this->GetDlgItemText(IDC_EDIT_QGQSBZ,QGQSBZ);
	this->GetDlgItemText(IDC_EDIT_KZXYZBZ,KZXYZBZ);
	this->GetDlgItemText(IDC_EDIT_XZQBQBZ,XZQBQBZ);
	this->GetDlgItemText(IDC_EDIT_QTYXJSMC,QTYXJSMC);
	re=iW_DF02EF05Info(hDev,ABOXX.GetBuffer(0),RHXX.GetBuffer(0),XCBZ.GetBuffer(0)
		,XZBBZ.GetBuffer(0),XNXGBBZ.GetBuffer(0),DXBBZ.GetBuffer(0)
		,NXWLBZ.GetBuffer(0),TNBBZ.GetBuffer(0),QGYBZ.GetBuffer(0)
		,TXBZ.GetBuffer(0),QGYZBZ.GetBuffer(0),QGQSBZ.GetBuffer(0)
		,KZXYZBZ.GetBuffer(0),XZQBQBZ.GetBuffer(0),QTYXJSMC.GetBuffer(0));
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
