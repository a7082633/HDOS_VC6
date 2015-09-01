// ContactCPUDlg.h : header file
//

#if !defined(AFX_CONTACTCPUDLG_H__5B59B88E_78A2_406C_B7E2_A5D93EB22D62__INCLUDED_)
#define AFX_CONTACTCPUDLG_H__5B59B88E_78A2_406C_B7E2_A5D93EB22D62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CContactCPUDlg dialog

class CContactCPUDlg : public CDialog
{
// Construction
public:
	int nSlot;
	int nCpuPara;
	long hReader;
	CContactCPUDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CContactCPUDlg)
	enum { IDD = IDD_CONTACTCPU_DIALOG };
	CComboBox	m_cb;
	CComboBox	m_slot;
	CComboBox	m_combobox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContactCPUDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CContactCPUDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnPoweron();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnBtnSetcpupara();
	afx_msg void OnBtnExc();
	afx_msg void OnBtnPoweroff();
	afx_msg void OnBtnClear();
	afx_msg void OnBtnOpenport();
	afx_msg void OnBtnCloseport();
	afx_msg void OnBtnCpoweron();
	afx_msg void OnBtnHpoweron();
	afx_msg void OnBtnCla();
	afx_msg void OnSelchangeComboApdu();
	afx_msg void OnSelendokComboApdu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTACTCPUDLG_H__5B59B88E_78A2_406C_B7E2_A5D93EB22D62__INCLUDED_)
