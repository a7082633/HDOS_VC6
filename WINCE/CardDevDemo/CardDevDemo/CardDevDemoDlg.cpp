// CardDevDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CardDevDemo.h"
#include "CardDevDemoDlg.h"
#include "CardDev.h"
#include <string>
using namespace std;

#pragma comment(lib, "CardDev.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int UnicodeToAnsi(unsigned short *Src, char *Des, int start, int len)
{
	wchar_t wsztemp[70]={0};
	//	char szStr[100];
	for(int i=0;i<len/2;i++)
	{
		wsztemp[i]=Src[2*i]+(Src[2*i+1]<<8);		
	}
	sprintf(Des, "%S", wsztemp);
	return 0;
}

//字符串转换为十六进制数据
int StrToHex(unsigned char *strIn, int inLen, unsigned char *strOut)
{
	int j = 0;
	
	int len = strlen((char*)strIn);
	
	if(inLen > len)
	{
		return -2;  //字符长度超过有效范围
	}
	
	unsigned char *pstrTemp  = new unsigned char[len+1];
	
	for(int i=0; i<inLen-1; i+=2, j++)
	{
		if(strIn[i]>='0' && strIn[i]<='9')
		{
			pstrTemp[i] = strIn[i] - '0';
		}
		else if(strIn[i]>='A' && strIn[i]<='F')
		{
			pstrTemp[i] = strIn[i] - 'A' + 10;
		}
		else if(strIn[i]>='a' && strIn[i]<='f')
		{
			pstrTemp[i] = strIn[i] - 'a' + 10;
		}
		else
		{
			return -1;     //非十六进制字符
		}
		
		if(strIn[i+1]>='0' && strIn[i+1]<='9')
		{
			pstrTemp[i+1] = strIn[i+1] - '0';
		}
		else if(strIn[i+1]>='A' && strIn[i+1]<='F')
		{
			pstrTemp[i+1] = strIn[i+1] - 'A' + 10;
		}
		else if(strIn[i+1]>='a' && strIn[i+1]<='f')
		{
			pstrTemp[i+1] = strIn[i+1] - 'a' + 10;
		}
		else
		{
			return -1;     //非十六进制字符
		}
		
		strOut[j] = (pstrTemp[i] << 4) & 0xF0;
		strOut[j] += pstrTemp[i+1] & 0x0F;
	}
	
	delete []pstrTemp;
	
	return 0;   //成功返回
}

void HexToStr(unsigned char *Src,unsigned char *Des,int len)
{
	char a[3]={0};
	for(int i=0;i<len;i++)
	{
		sprintf(a,"%X",Src[i]);
		if (i==0)
			strcpy((char*)Des,a);
		else
			strcat((char*)Des,a);
	}
}

int UnicodeToANSI( const wstring& str, char* Des)   
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_ACP, 0,str.c_str(),-1,NULL,0,NULL,NULL );
	pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte( CP_ACP,0, str.c_str(),-1,pElementText, iTextLen,NULL,NULL );
	strcpy(Des, pElementText);
	delete[] pElementText;
	return 0;
}

int AnsiToUnicode(const char *Src, wchar_t *Des)
{
	int    iLen;
	// Ansi char to Unicode
	iLen = MultiByteToWideChar( CP_ACP, 0, Src, -1, NULL, 0 );
	::MultiByteToWideChar( CP_ACP, 0, Src, -1, Des, iLen );
	return 0;
}

// CCardDevDemoDlg 对话框

CCardDevDemoDlg::CCardDevDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardDevDemoDlg::IDD, pParent)
	, m_key(0x60)
	, m_strbuf(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardDevDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCardDevDemoDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPEN, &CCardDevDemoDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CCardDevDemoDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_ACTIVE, &CCardDevDemoDlg::OnBnClickedBtnActive)
	ON_BN_CLICKED(IDC_BTN_AUTH, &CCardDevDemoDlg::OnBnClickedBtnAuth)
	ON_BN_CLICKED(IDC_RADIO1, &CCardDevDemoDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CCardDevDemoDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BTN_READ, &CCardDevDemoDlg::OnBnClickedBtnRead)
	ON_BN_CLICKED(IDC_BTN_WRITE, &CCardDevDemoDlg::OnBnClickedBtnWrite)
	ON_BN_CLICKED(IDC_BTN_CERT, &CCardDevDemoDlg::OnBnClickedBtnCert)
END_MESSAGE_MAP()


// CCardDevDemoDlg 消息处理程序

BOOL CCardDevDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

#ifdef WIN32_PLATFORM_WFSP
	if (!m_dlgCommandBar.Create(this) ||
	    !m_dlgCommandBar.InsertMenuBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建 CommandBar\n");
		return FALSE;      // 未能创建
	}
#endif // WIN32_PLATFORM_WFSP
	// TODO: 在此添加额外的初始化代码

	//初始化数据
	SetDlgItemText(IDC_EDIT_KEY, L"FFFFFFFFFFFF");
	//串口号
	CString strItem = L"";
	int i = 0;
	CComboBox *pCmbComNo = (CComboBox*)GetDlgItem(IDC_CMB_COM_NO);
	pCmbComNo->ResetContent();
	for (i=0; i < 10; i++)
	{
		strItem.Format(L"com%d",i+1);
		pCmbComNo->AddString(strItem);
	}
	pCmbComNo->SetCurSel(0);// com1:

	CComboBox *pCmbNum = (CComboBox*)GetDlgItem(IDC_CMB_COM_NUM);
	pCmbNum->ResetContent();
	for (i=0; i < 64; i++)
	{
		strItem.Format(L"%d",i);
		pCmbNum->AddString(strItem);
	}
	pCmbNum->SetCurSel(0);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CCardDevDemoDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_CARDDEVDEMO_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_CARDDEVDEMO_DIALOG));
	}
}
#endif


void CCardDevDemoDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox *pCmbComNo = (CComboBox*)GetDlgItem(IDC_CMB_COM_NO);
	int port = pCmbComNo->GetCurSel() + 1;

	long ren = hd_Open(port);
	if(ren)
	{
		AfxMessageBox(_T("打开端口失败"));
		return;
	}
	MessageBox(_T("打开端口成功"));
}

void CCardDevDemoDlg::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码
	long ren = hd_Close();
	if(ren)
	{
		AfxMessageBox(_T("关闭端口失败"));
		return;
	}
	MessageBox(_T("关闭端口成功"));
}

void CCardDevDemoDlg::OnBnClickedBtnActive()
{
	// TODO: 在此添加控件通知处理程序代码 
	TCHAR uid[41] = {0};
	CString temp;
	m_strbuf.Empty();
	long ren = hd_Active(uid);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("寻卡失败, 错误码：");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}

	m_strbuf += _T("寻卡成功");
	SetDlgItemText(IDC_EDIT_RED, uid);
	SetDlgItemText(IDC_STATIC_RE, m_strbuf);
}

void CCardDevDemoDlg::OnBnClickedBtnAuth()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str, temp;
	char databuf[20] = {0};
	unsigned char data[20] = {0};
	TCHAR data1[20] = {0};
	int stat = 0;
	m_strbuf.Empty();
	CComboBox *pCmbNum = (CComboBox*)GetDlgItem(IDC_CMB_COM_NUM);
	int SecNr = pCmbNum->GetCurSel() / 4;
	GetDlgItemText(IDC_EDIT_KEY, str);

	memcpy(data1, str, str.GetLength()*2);
	UnicodeToANSI(data1, databuf);

	StrToHex((unsigned char*)databuf, 12, data);

	long ren = hd_AuthPass(m_key, SecNr, data);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("认证失败, 错误码：");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}
	
	m_strbuf += _T("认证成功");
	SetDlgItemText(IDC_STATIC_RE, m_strbuf);
	
}

void CCardDevDemoDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = 0x60;
}

void CCardDevDemoDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_key = 0x61;
}

void CCardDevDemoDlg::OnBnClickedBtnRead()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char data[20] = {0};
	char databuf[20] = {0};
	TCHAR data1[20] = {0};
	CString temp;
	m_strbuf.Empty();
	CComboBox *pCmbNum = (CComboBox*)GetDlgItem(IDC_CMB_COM_NUM);
	int Addr = pCmbNum->GetCurSel();
	long ren = hd_Read((unsigned char)Addr, data);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("读卡失败, 错误码：");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}
	HexToStr((unsigned char *)databuf, data, 8);
	AnsiToUnicode(databuf, data1);
	SetDlgItemText(IDC_EDIT_RED, data1);

	m_strbuf += _T("读卡成功");
	SetDlgItemText(IDC_STATIC_RE, m_strbuf);
}

void CCardDevDemoDlg::OnBnClickedBtnWrite()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char data[20] = {0};
	char databuf[20] = {0};
	TCHAR data1[20] = {0};
	long ren = -99;
	CString str, temp;
	m_strbuf.Empty();

	CComboBox *pCmbNum = (CComboBox*)GetDlgItem(IDC_CMB_COM_NUM);
	unsigned char Addr = (unsigned char)pCmbNum->GetCurSel();

	GetDlgItemText(IDC_EDIT_RED, str);
	memcpy(data1, str, str.GetLength()*2);
	UnicodeToANSI(data1, databuf);
	StrToHex((unsigned char*)databuf, strlen(databuf), data);
	//temp.Format(L"%d", Addr);
	//AfxMessageBox(temp);
	//AfxMessageBox(L"执行写卡操作需谨慎，操作不当会导致锁卡");

	ren = hd_Write(Addr, data);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("写卡失败, 错误码：");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}
	
	m_strbuf += _T("写卡成功");
	SetDlgItemText(IDC_STATIC_RE, m_strbuf);
}

void CCardDevDemoDlg::OnBnClickedBtnCert()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR pName[200] = {0};
	TCHAR pSex[50] = {0};
	TCHAR pNation[50] = {0};
	TCHAR pBirth[50] = {0};
	TCHAR pAddress[400] = {0};
	TCHAR pCertNo[100] = {0};
	TCHAR pDepartment[100] = {0};
	TCHAR pEffectTime[100] = {0};
	TCHAR pExpire[100] = {0};
	int i = 0;
	//TCHAR pBmpFile[256] = L"\\Temp\\zp.bmp";
	//TCHAR *pBmpData = new TCHAR[77725];
	//TCHAR pBmpData[256] = {0};
	CString str, temp;
	m_strbuf.Empty();
	TCHAR wFilePath[256] = {0};
	char FilePath[256] = {0};

	GetModuleFileName(NULL, wFilePath, 256);
	//UnicodeToANSI(wFilePath, FilePath);
	for(i=wcslen(wFilePath)-1; i>0; i--)
	{
		if(wFilePath[i] == '\\')
		{
			memset(wFilePath+i+1, 0, wcslen(wFilePath)-i);
			memset(wFilePath+i+1, 0, (wcslen(wFilePath)-i)*sizeof(wchar_t));
			memcpy(wFilePath+i+1, L"zp.bmp", 12);
			break;
		}
	}

	long ren = hd_ReadIDCard(wFilePath, pName, pSex, pNation, pBirth, pAddress, pCertNo, pDepartment, pEffectTime,  pExpire);
	if(ren)
	{
		temp.Format(_T("%d"), ren);
		m_strbuf += _T("读取身份证信息失败, 错误码：");
		m_strbuf += temp;
		SetDlgItemText(IDC_STATIC_RE, m_strbuf);
		return;
	}

	str += L"姓名：";
	str += pName;
	str += L"\r\n";
	str += L"性别：";
	str += pSex;
	str += L"\r\n";
	str += L"民族：";
	str += pNation;
	str += L"\r\n";
	str += L"出生日期：";
	str += pBirth;
	str += L"\r\n";
	str += L"住址：";
	str += pAddress;
	str += L"\r\n";
    str += L"身份证号：";
	str += pCertNo;
	str += L"\r\n";
	str += L"发证机关：";
	str += pDepartment;
	str += L"\r\n";
	str += L"发证日期：";
	str += pEffectTime;
	str += L"\r\n";
	str += L"有效期：";
	str += pExpire;
	MessageBox(str);
}
