// HD_ZTHDemoDlg.h : header file
//

#if !defined(AFX_HD_ZTHDEMODLG_H__52CC50B3_7894_4EB8_9651_BC31B0A2EC5B__INCLUDED_)
#define AFX_HD_ZTHDEMODLG_H__52CC50B3_7894_4EB8_9651_BC31B0A2EC5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHD_ZTHDemoDlg dialog

class CHD_ZTHDemoDlg : public CDialog
{
// Construction
public:
	CHD_ZTHDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHD_ZTHDemoDlg)
	enum { IDD = IDD_HD_ZTHDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_ZTHDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHD_ZTHDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpendevice();
	afx_msg void OnBtnClosedevice();
	afx_msg void OnBtnReadcard();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_ZTHDEMODLG_H__52CC50B3_7894_4EB8_9651_BC31B0A2EC5B__INCLUDED_)
