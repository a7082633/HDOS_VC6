// RWHealthSpeedTestDlg.h : header file
//

#if !defined(AFX_RWHEALTHSPEEDTESTDLG_H__374E86CB_7BE7_48C9_818B_A68C53B1BC91__INCLUDED_)
#define AFX_RWHEALTHSPEEDTESTDLG_H__374E86CB_7BE7_48C9_818B_A68C53B1BC91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRWHealthSpeedTestDlg dialog

class CRWHealthSpeedTestDlg : public CDialog
{
// Construction
public:
	bool SetExcelData(int row,int column,char *szData);
	CRWHealthSpeedTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRWHealthSpeedTestDlg)
	enum { IDD = IDD_RWHEALTHSPEEDTEST_DIALOG };
	CString	m_data;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRWHealthSpeedTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRWHealthSpeedTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRonefkjg();
	afx_msg void OnBtnInitialpro();
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnBtnRhundredfkjg();
	afx_msg void OnBtnRoneckr();
	afx_msg void OnBtnRhundredckr();
	afx_msg void OnBtnRonezp();
	afx_msg void OnBtnRhundredzp();
	afx_msg void OnBtnRoneyxq();
	afx_msg void OnBtnRhundredyxq();
	afx_msg void OnBtnRonedz();
	afx_msg void OnBtnRhundreddz();
	afx_msg void OnBtnRonelxr();
	afx_msg void OnBtnRhundredlxr();
	afx_msg void OnBtnRonezyhy();
	afx_msg void OnBtnRhundredzyhy();
	afx_msg void OnBtnRonezjxx();
	afx_msg void OnBtnRhundredzjxx();
	afx_msg void OnBtnRonelcjbxx();
	afx_msg void OnBtnWonelcjbxx();
	afx_msg void OnBtnRwhundredlcjbxx();
	afx_msg void OnBtnRonetsxx();
	afx_msg void OnBtnWonetsxx();
	afx_msg void OnBtnRwhundredtsxx();
	afx_msg void OnBtnRonegmxx();
	afx_msg void OnBtnWonegmxx();
	afx_msg void OnBtnRwhundredgmxx();
	afx_msg void OnBtnRonemyxx();
	afx_msg void OnBtnWonemyxx();
	afx_msg void OnBtnRwhundredmyxx();
	afx_msg void OnBtnRonemzxx();
	afx_msg void OnBtnWonemzxx();
	afx_msg void OnBtnRwhundredmzxx();
	afx_msg void OnBtnRonezyxx();
	afx_msg void OnBtnWonezyxx();
	afx_msg void OnBtnRwhundredzyxx();
	afx_msg void OnBtnReadallonece();
	afx_msg void OnBtnReadallhundred();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RWHEALTHSPEEDTESTDLG_H__374E86CB_7BE7_48C9_818B_A68C53B1BC91__INCLUDED_)
