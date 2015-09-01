// DialogLoadKey.cpp : implementation file
//

#include "stdafx.h"
#include "M1.h"
#include "DialogLoadKey.h"
#include "DlialogPass.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogLoadKey dialog


CDialogLoadKey::CDialogLoadKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogLoadKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogLoadKey)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogLoadKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogLoadKey)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogLoadKey, CDialog)
	//{{AFX_MSG_MAP(CDialogLoadKey)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_RADIO_S50, OnRadioS50)
	ON_BN_CLICKED(IDC_RADIO_S70, OnRadioS70)
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, OnBtnDownload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogLoadKey message handlers

BOOL CDialogLoadKey::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, "ÉÈÇø", LVCFMT_CENTER, 40);
	m_list.InsertColumn(1, "ÃÜÂë", LVCFMT_LEFT, 90);
	m_list.InsertColumn(2, "×´Ì¬", LVCFMT_LEFT, 40);
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_KEYA);
	radio->SetCheck(1);
	radio=(CButton*)GetDlgItem(IDC_RADIO_S50);
	radio->SetCheck(1);
	for(int i=0;i<=15;i++)
	{
		int n=m_list.GetItemCount();
		CString temp;
		temp.Format("%d",i);
		m_list.InsertItem(n,temp);
		m_list.SetItemText(n,1,"FFFFFFFFFFFF");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogLoadKey::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{

	//POSITION pos=m_list.GetFirstSelectedItemPosition();

	NMLISTVIEW * pNMListView = (NMLISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;
	if (nItem == -1) return;
	CString sSecNr=m_list.GetItemText(nItem,0);
	CString sPass=m_list.GetItemText(nItem,1);

	//m_list.SetItemText(nItem,1,"haha");

	CDlialogPass *dlg=new CDlialogPass;
	dlg->m_pass=sPass;
	dlg->m_ListHwnd=m_list.m_hWnd;
	dlg->m_nItem=nItem;
	dlg->DoModal();

	*pResult = 0;
}


void CDialogLoadKey::OnRadioS50() 
{
	m_list.DeleteAllItems();
	for(int i=0;i<=15;i++)
	{
		int n=m_list.GetItemCount();
		CString temp;
		temp.Format("%d",i);
		m_list.InsertItem(n,temp);
		m_list.SetItemText(n,1,"FFFFFFFFFFFF");
	}
}

void CDialogLoadKey::OnRadioS70() 
{
	m_list.DeleteAllItems();
	for(int i=0;i<=39;i++)
	{
		int n=m_list.GetItemCount();
		CString temp;
		temp.Format("%d",i);
		m_list.InsertItem(n,temp);
		m_list.SetItemText(n,1,"FFFFFFFFFFFF");
	}
}
typedef int(__stdcall *FXN)(char*);
typedef int(__stdcall *FXN2)(long);
typedef int(__stdcall *FXN3)(long,unsigned char);
typedef int(__stdcall *FXN4)(long,unsigned char*);
typedef int(__stdcall *FXN5)(long);
typedef int(__stdcall *FXN6)(long,int,int,unsigned char *);
typedef int(__stdcall *FXN7)(long,int,int,unsigned char *);
typedef int(__stdcall *FXN8)(long,unsigned char *);
typedef int(__stdcall *FXN9)(long);
typedef int(__stdcall *FXNA)(unsigned char *,int,unsigned char *);
typedef int(__stdcall *FXNB)(long , unsigned char , unsigned char);
typedef int(__stdcall *FXNC)(long , unsigned char , unsigned char,unsigned char *);
typedef int(__stdcall *FXND)(long , unsigned char , unsigned char *);
typedef int(__stdcall *FXNE)(long , unsigned char , unsigned long);
typedef int(__stdcall *FXNF)(long , unsigned char ,unsigned long *);
void CDialogLoadKey::OnBtnDownload() 
{
	if((0==((CButton *)GetDlgItem(IDC_RADIO_S50))->GetCheck())&&(0==((CButton *)GetDlgItem(IDC_RADIO_S70))->GetCheck()))
	{
		this->MessageBox("Î´Ñ¡ÖÐ");
		return;
	}
	FXNC LoadKeyHEX=(FXNC)::GetProcAddress(hModule,"PICC_Reader_LoadKeyHEX");
	if(m_list.GetItemCount()==0)
	{
		this->MessageBox("ÎÞÃÜÂë");
		return;
	}
	int iCarType=0;
	if(1==((CButton *)GetDlgItem(IDC_RADIO_KEYB))->GetCheck())
		iCarType=4;
	for(int i=0;i<m_list.GetItemCount();i++)
	{
		CString temp=m_list.GetItemText(i,1);
		int re=LoadKeyHEX(hReader,iCarType,i,(unsigned char *)temp.GetBuffer(0));
		if(re)
			m_list.SetItemText(i,2,"No");
		else
			m_list.SetItemText(i,2,"YES");
	}
}
