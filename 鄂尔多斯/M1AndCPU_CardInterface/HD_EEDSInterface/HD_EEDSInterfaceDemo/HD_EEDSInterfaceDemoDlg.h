// HD_EEDSInterfaceDemoDlg.h : header file
//

#if !defined(AFX_HD_EEDSINTERFACEDEMODLG_H__A40A493F_7FA9_48DB_8CE6_8D3F74813614__INCLUDED_)
#define AFX_HD_EEDSINTERFACEDEMODLG_H__A40A493F_7FA9_48DB_8CE6_8D3F74813614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHD_EEDSInterfaceDemoDlg dialog

class CHD_EEDSInterfaceDemoDlg : public CDialog
{
// Construction
public:
	CHD_EEDSInterfaceDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHD_EEDSInterfaceDemoDlg)
	enum { IDD = IDD_HD_EEDSINTERFACEDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHD_EEDSInterfaceDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHD_EEDSInterfaceDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HD_EEDSINTERFACEDEMODLG_H__A40A493F_7FA9_48DB_8CE6_8D3F74813614__INCLUDED_)
