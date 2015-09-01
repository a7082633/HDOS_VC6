// PSAMDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InterfaceDemo.h"
#include "PSAMDialog.h"
//#include "UH_BHZ_HC_V001.h"

#include <fstream>
#include "WINBASE.H"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UHSLOT_PSAM1	1
/////////////////////////////////////////////////////////////////////////////
// PSAMDialog dialog

static int iReaderHandle;

PSAMDialog::PSAMDialog(CWnd* pParent /*=NULL*/)
	: CDialog(PSAMDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(PSAMDialog)
	m_PIN = _T("");
	m_OldPIN = _T("");
	m_NEWPIN = _T("");
	//}}AFX_DATA_INIT
}


void PSAMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PSAMDialog)
	DDX_Control(pDX, IDC_LIST, m_cListBox);
	DDX_Text(pDX, IDC_EDIT_PIN, m_PIN);
	DDX_Text(pDX, IDC_EDIT_OldPIN, m_OldPIN);
	DDX_Text(pDX, IDC_EDIT_NewPIN, m_NEWPIN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PSAMDialog, CDialog)
	//{{AFX_MSG_MAP(PSAMDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PSAMDialog message handlers


//VerifyPIN
void PSAMDialog::OnButton1() 
{
/*	char PIN[30+1] = {0};		
	UpdateData(TRUE);
	strcpy(PIN ,m_PIN);

	int nRet = UH_Verify_Pin(iReaderHandle , UHSLOT_PSAM1 , PIN);
	if (nRet == 0)
	{
		CString s = "";
		s.Format("PIN验证成功");
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
*/
	return;
}	

void PSAMDialog::SetHandle(int ihandle)
{
	iReaderHandle = ihandle;	
}

//UpdatePIN
void PSAMDialog::OnButton2() 
{
	char oPIN[30+1] = {0};		
	char nPIN[30+1] = {0};	
	UpdateData(TRUE);

	strcpy(oPIN ,m_OldPIN);
	strcpy(nPIN ,m_NEWPIN);
/*
	int nRet = UH_Change_Pin(iReaderHandle , UHSLOT_PSAM1 , oPIN , nPIN);
	if (nRet == 0)
	{
		CString s = "";
		s.Format("PIN修改成功");
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
*/
	return;
	
}

//获取公共信息
void PSAMDialog::OnButton3() 
{
/*	char info[150];
	int nRet = UH_Reader_SAM_Public(iReaderHandle,UHSLOT_PSAM1,info);

	if (nRet == 0)
	{
		CString s = "";
		s.Format("执行成功");
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
		m_cListBox.AddString(info);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
*/
	return;
}




//获取应用信息
void PSAMDialog::OnButton5() 
{
/*	char info[150];
	int nRet = UH_Reader_SAM_PublicApp(iReaderHandle,UHSLOT_PSAM1,info);

	if (nRet == 0)
	{
		CString s = "";
		s.Format("执行成功");
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
		m_cListBox.AddString(info);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
*/
	return;
	
}

//获取终端信息
void PSAMDialog::OnButton4() 
{
/*	char info[150];
	int nRet = UH_Reader_SAM_Terminal(iReaderHandle,UHSLOT_PSAM1,info);

	if (nRet == 0)
	{
		CString s = "";
		s.Format("执行成功");
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
		m_cListBox.AddString(info);
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
*/
	return;
}

//获取证书信息
void PSAMDialog::OnButton7() 
{
/*		char info[200];
	int nRet = UH_Reader_SAM_Certificate(iReaderHandle,UHSLOT_PSAM1,info);

	if (nRet == 0)
	{
		CString s = "";
		s.Format("执行成功");
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);

		int nDataLen = 190;

		ofstream outfile("PSAM证书.dat", ios::binary);
		if (!outfile)
		{
			m_cListBox.AddString("建立outfile对象失败");
			nRet = 1;
			throw nRet;
		}
		
		for(int i = 0; i < nDataLen; i++)
		{
			outfile.write((char*)&info[i], sizeof(info[i]));
		}
		outfile.close();
		m_cListBox.AddString("PSAM证书.dat保存在当前路径下");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
*/
	return;
	
}

//函数名（定义）	获取SAM卡的发卡机构证书信息：
//int  UH_Reader_SAM_OrgCertificate (int ReaderHandle,int ICC_Slot_No,char* info)
void PSAMDialog::OnButton6() 
{
/*	char info[200];
	int nRet = UH_Reader_SAM_OrgCertificate(iReaderHandle,UHSLOT_PSAM1,info);

	if (nRet == 0)
	{
		CString s = "";
		s.Format("执行成功");
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);

		int nDataLen = 180;

		ofstream outfile("发卡机构证书.dat", ios::binary);
		if (!outfile)
		{
			m_cListBox.AddString("建立outfile对象失败");
			nRet = 1;
			throw nRet;
		}
		
		for(int i = 0; i < nDataLen; i++)
		{
			outfile.write((char*)&info[i], sizeof(info[i]));
		}
		outfile.close();
		m_cListBox.AddString("发卡机构证书.dat保存在当前路径下");
	}
	else
	{
		CString s = "";
		s.Format("ErrorCode: %d", nRet);
		m_cListBox.ResetContent();
		m_cListBox.AddString(s);
	}
*/
	return;
	
}
