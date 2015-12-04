// HD_ReadDemo_HNDlg.h : header file
//

#if !defined(AFX_HD_READDEMO_HNDLG_H__B11E1C1A_33DA_445E_8EA3_6FE8769EA09E__INCLUDED_)
#define AFX_HD_READDEMO_HNDLG_H__B11E1C1A_33DA_445E_8EA3_6FE8769EA09E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHD_ReadDemo_HNDlg dialog

class CHD_ReadDemo_HNDlg : public CDialog
{
// Construction
public:
	long ReaderHandle;
	CHD_ReadDemo_HNDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHD_ReadDemo_HNDlg)
	enum { IDD = IDD_HD_READDEMO_HN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_ReadDemo_HNDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHD_ReadDemo_HNDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnClose();
	afx_msg void OnBtnSamon();
	afx_msg void OnBtnCardon();
	afx_msg void OnBtnRead();
	afx_msg void OnBtnSamau();
	afx_msg void OnBtnWrite();
	afx_msg void OnBtnSendcmd();
	afx_msg void OnBtnFindcard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_READDEMO_HNDLG_H__B11E1C1A_33DA_445E_8EA3_6FE8769EA09E__INCLUDED_)
