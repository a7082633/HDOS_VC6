// NonContactCPUDlg.h : header file
//

#if !defined(AFX_NONCONTACTCPUDLG_H__8D6DD2BB_AF67_4EEF_AE8F_7FCB9619ECBF__INCLUDED_)
#define AFX_NONCONTACTCPUDLG_H__8D6DD2BB_AF67_4EEF_AE8F_7FCB9619ECBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNonContactCPUDlg dialog

class CNonContactCPUDlg : public CDialog
{
// Construction
public:
	void InitialB();
	void InitialA();
	long hReader;
	CNonContactCPUDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNonContactCPUDlg)
	enum { IDD = IDD_NONCONTACTCPU_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNonContactCPUDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNonContactCPUDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPowerOn();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnBtnExc();
	afx_msg void OnBtnOpenport();
	afx_msg void OnBtnCloseport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NONCONTACTCPUDLG_H__8D6DD2BB_AF67_4EEF_AE8F_7FCB9619ECBF__INCLUDED_)
