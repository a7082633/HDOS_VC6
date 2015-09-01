// InterfaceDemoDlg.h : header file
//

#if !defined(AFX_INTERFACEDEMODLG_H__80334914_C64F_4ED1_BD0E_8F0D32B8AC28__INCLUDED_)
#define AFX_INTERFACEDEMODLG_H__80334914_C64F_4ED1_BD0E_8F0D32B8AC28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDemoDlg dialog

class CInterfaceDemoDlg : public CDialog
{
// Construction
public:
	CInterfaceDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInterfaceDemoDlg)
	enum { IDD = IDD_INTERFACEDEMO_DIALOG };
	CComboBox	m_cbo_myid;
	CComboBox	m_cbo_gmid;
	CComboBox	m_cbo_zyid;
	CComboBox	m_cbo_zybzid;
	CComboBox	m_cbo_mzbzid;
	CComboBox	m_cbo_mzid;
	CComboBox	m_cbo_MZ;
	CComboBox	m_cbo_ZY;
	CListBox	m_cListBox;
	CString	m_out;
	CString	m_PIN;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

//gdi用的2个变量，用于显示照片，与接口无关
public:
	int GetZhaoPianPath(CString &strPicPath);
	int SavePic(int nDataLen, byte * pbysZHAOPIAN);
	int DisPlayJPG(int nDataLen, byte * pbysZHAOPIAN);
//	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInterfaceDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonFkRead();
	afx_msg void OnButtonCbRead2();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonGmRead();
	afx_msg void OnButtonMyRead();
	afx_msg void OnButtonZzjlbsRead();
	afx_msg void OnButtonMzjlbsRead();
	afx_msg void OnButtonZyxx();
	afx_msg void OnButtonMzxxRead();
	afx_msg void OnButtonDizhiRead();
	afx_msg void OnButtonLxrRead();
	afx_msg void OnButtonZyhyRead();
	afx_msg void OnButtonZjjlxxRead();
	afx_msg void OnButtonLcjbsjRead();
	afx_msg void OnButtonTsxxRead();
	afx_msg void OnButtonCkrjbxxWrite();
	afx_msg void OnButtonFkWrite();
	afx_msg void OnButtonGmWrite();
	afx_msg void OnButtonMyjbsjWrite();
	afx_msg void OnButtonZyjlWrite();
	afx_msg void OnButtonZzjlyxErase();
	afx_msg void OnButtonMzjlbsWrite();
	afx_msg void OnButtonMzjlbsErase();
	afx_msg void OnButtonZyxxWrite();
	afx_msg void OnButtonMzxxWrite();
	afx_msg void OnButtonDzxxWrite();
	afx_msg void OnButtonLxrxxWrite();
	afx_msg void OnButton1ZyhyxxWrite();
	afx_msg void OnButtonZjjlxxWrite();
	afx_msg void OnButtonLcjbsjWrite();
	afx_msg void OnButtonTsxxsjWrite();
	afx_msg void OnDestroy();
	afx_msg void OnButtonZpRead();
	afx_msg void OnButtonWsbRead();
	afx_msg void OnButtonWsbWrite();
	afx_msg void OnButtonZpWrite();
	afx_msg void OnButtonWsbOpen();
	afx_msg void OnButtonWsbClose();
	afx_msg void OnButtonDizhiRead2();
	afx_msg void OnButtonDzxxWrite2();
	afx_msg void OnBUTTONerrmsg();
	afx_msg void OnButtonMzSign();
	afx_msg void OnButtonZySign();
	afx_msg void OnButtonPsam();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonResetpsam();
	afx_msg void OnButtonReset3();
	afx_msg void OnReadall();
	afx_msg void OnWriteall();
	afx_msg void OnReadedll();
	afx_msg void OnWriteedll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACEDEMODLG_H__80334914_C64F_4ED1_BD0E_8F0D32B8AC28__INCLUDED_)
