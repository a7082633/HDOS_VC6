// SendCmd_HealthDlg.h : header file
//

#if !defined(AFX_SENDCMD_HEALTHDLG_H__0CE31247_2CF8_4E23_822F_320114D0917C__INCLUDED_)
#define AFX_SENDCMD_HEALTHDLG_H__0CE31247_2CF8_4E23_822F_320114D0917C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSendCmd_HealthDlg dialog

class CSendCmd_HealthDlg : public CDialog
{
// Construction
public:
	int radio;
	CSendCmd_HealthDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSendCmd_HealthDlg)
	enum { IDD = IDD_SENDCMD_HEALTH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendCmd_HealthDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSendCmd_HealthDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnClose();
	afx_msg void OnBtnUserpoweron();
	afx_msg void OnBtnSendapdu();
	afx_msg void OnBtnSampoweron();
	afx_msg void OnRadioUser();
	afx_msg void OnRadioSam();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDCMD_HEALTHDLG_H__0CE31247_2CF8_4E23_822F_320114D0917C__INCLUDED_)
