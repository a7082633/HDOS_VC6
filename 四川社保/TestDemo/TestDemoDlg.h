// TestDemoDlg.h : header file
//

#if !defined(AFX_TESTDEMODLG_H__714E2CEF_68EE_4036_BF3E_46C2F5FCA1A7__INCLUDED_)
#define AFX_TESTDEMODLG_H__714E2CEF_68EE_4036_BF3E_46C2F5FCA1A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDemoDlg dialog

class CTestDemoDlg : public CDialog
{
// Construction
public:
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
	afx_msg void OnBtnCall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDEMODLG_H__714E2CEF_68EE_4036_BF3E_46C2F5FCA1A7__INCLUDED_)
