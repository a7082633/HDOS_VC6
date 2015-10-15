// SHAOXING_NoncontractCPUDlg.h : header file
//

#if !defined(AFX_SHAOXING_NONCONTRACTCPUDLG_H__CF870B9C_F481_4896_A536_DDB6B3DEBC9B__INCLUDED_)
#define AFX_SHAOXING_NONCONTRACTCPUDLG_H__CF870B9C_F481_4896_A536_DDB6B3DEBC9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSHAOXING_NoncontractCPUDlg dialog

class CSHAOXING_NoncontractCPUDlg : public CDialog
{
// Construction
public:
	int iKeyDev;
	HMODULE hModule;
	int hDev;
	CSHAOXING_NoncontractCPUDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSHAOXING_NoncontractCPUDlg)
	enum { IDD = IDD_SHAOXING_NONCONTRACTCPU_DIALOG };
	CComboBox	m_comboNType;
	CComboBox	m_comboNRWorkKey;
	CComboBox	m_comboNrMainKey;
	CComboBox	m_comboKeyLen;
	CString	m_data;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSHAOXING_NoncontractCPUDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSHAOXING_NoncontractCPUDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpenPort();
	afx_msg void OnBtnClosePort();
	afx_msg void OnBtnFindCard();
	afx_msg void OnBtnCardReset();
	afx_msg void OnBtnExcApdu();
	virtual void OnOK();
	afx_msg void OnBtnOpenkeyboard();
	afx_msg void OnBtnCloseboard();
	afx_msg void OnBtnDlMainkey();
	afx_msg void OnBtnDlWorkkey();
	afx_msg void OnBtnActivekey();
	afx_msg void OnBtnSetKeylen();
	afx_msg void OnBtnGetpin();
	afx_msg void OnBtnGetnpin();
	afx_msg void OnBtnNkey();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHAOXING_NONCONTRACTCPUDLG_H__CF870B9C_F481_4896_A536_DDB6B3DEBC9B__INCLUDED_)
