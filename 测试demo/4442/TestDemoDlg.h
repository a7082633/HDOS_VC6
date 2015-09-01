// TestDemoDlg.h : header file
//

#if !defined(AFX_TESTDEMODLG_H__F68F55D7_FB41_4D0E_B25C_FFF4617AFD3C__INCLUDED_)
#define AFX_TESTDEMODLG_H__F68F55D7_FB41_4D0E_B25C_FFF4617AFD3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDemoDlg dialog

class CTestDemoDlg : public CDialog
{
// Construction
public:
	long hReader;
	CTestDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDemoDlg)
	enum { IDD = IDD_TESTDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnElectr();
	afx_msg void OnBtnPf();
	afx_msg void OnDestroy();
	afx_msg void OnBtnRd();
	afx_msg void OnBtnWr();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnTrialt();
	afx_msg void OnBtnModify();
	afx_msg void OnBtnOpenport();
	afx_msg void OnBtnCloseport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDEMODLG_H__F68F55D7_FB41_4D0E_B25C_FFF4617AFD3C__INCLUDED_)
