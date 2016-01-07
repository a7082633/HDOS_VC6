// HD_BHGXDLL_DEMODlg.h : header file
//

#if !defined(AFX_HD_BHGXDLL_DEMODLG_H__52AC4C8C_EABA_43F7_A0C5_7A42A0E9B8D4__INCLUDED_)
#define AFX_HD_BHGXDLL_DEMODLG_H__52AC4C8C_EABA_43F7_A0C5_7A42A0E9B8D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHD_BHGXDLL_DEMODlg dialog

class CHD_BHGXDLL_DEMODlg : public CDialog
{
// Construction
public:
	CHD_BHGXDLL_DEMODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHD_BHGXDLL_DEMODlg)
	enum { IDD = IDD_HD_BHGXDLL_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_BHGXDLL_DEMODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHD_BHGXDLL_DEMODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpendevice();
	afx_msg void OnBtnClosedevice();
	afx_msg void OnBtnReadbin();
	afx_msg void OnBtnIselect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_BHGXDLL_DEMODLG_H__52AC4C8C_EABA_43F7_A0C5_7A42A0E9B8D4__INCLUDED_)
